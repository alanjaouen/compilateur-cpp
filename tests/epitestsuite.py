#! /bin/python3

from termcolor import colored
import argparse
import click
import os
import subprocess
import sys
import tempfile
import yaml


def options(args):
    """Option parsing."""
    parser = argparse.ArgumentParser(description="Tiger Compiler TestSuite")
    parser.add_argument("-l", "--list", action="store_true", default=False,
                        help="display the list of test categories")
    parser.add_argument("-c", "--category", metavar="CATEGORY", default=[],
                        nargs='+',
                        help="execute the testsuite on the categories " +
                        "passed in argument only")
    parser.add_argument("-s", "--sanity", action="store_true", default=False,
                        help="execute the testsuite with sanity checks " +
                        "enabled (valgrind)")
    parser.add_argument("-o", "--output", metavar="FILE", default=sys.stdout,
                        help="write output of tests in FILE")
    parser.add_argument("-H", "--havm", default="",
                        help="execute output of the tests in havm, H must be" +
                        " given to -p")
    requiredNamed = parser.add_argument_group('required arguments')

    requiredNamed.add_argument("--my", metavar="FILE",
                               help="path to the binary to be tested",
                               required=True)
    requiredNamed.add_argument("-p", "--options", metavar="OPT",
                               help="add the options for all the tests",
                               required=True)
    options = parser.parse_args(args)
    if options.list:
        for category in list_category('config.yaml'):
            print("- " + category)
        return
    if options.category != []:
        parse_config('config.yaml', options.category, options.sanity,
                     options.output, options.my, options.options, options.havm)
    else:
        parse_config('config.yaml', list_category('config.yaml'),
                     options.sanity, options.output, options.my,
                     options.options, options.havm)


def list_category(yaml_file):
    """Category listing."""
    with open(yaml_file, 'r') as f:
        config = yaml.load(f)
    categories = []
    for section in config:
        if section == "categories":
            with click.progressbar(label="Generating list of category",
                                   length=len(config[section]),
                                         show_eta=True, width=0) as pbar:
                for category in config[section]:
                    categories.append(category)
                    pbar.update(1)
    print(colored("Succeed", 'green'))
    return categories


def get_status(my, ref):
    """Getting status."""
    if my == ref:
        return (0, "\tmy returned: " + str(my) +
                   "\n\tref returned: " + str(ref))
    else:
        return (1, "\tmy returned: " + str(my) +
                   "\n\tref returned: " + str(ref))


def errormsg(percent, category, mycmd, msg):
    """Generating error message."""
    global output
    global fail
    output += colored(percent + mycmd + ": FAIL:\n" + msg, 'red')
    fail += colored(category + ": " + mycmd, 'red') + "\n"
    return 1


def parse_config(yaml_file, categories_list, sanity, foutput, my_path,
                 options, havm):
    """Parsing configfile."""
    with open(yaml_file, 'r') as f:
        config = yaml.load(f)
    global fail
    fail = ""
    failed = 0
    incr = 0
    fo = open(foutput, 'w') if foutput != sys.stdout else sys.stdout
    with click.progressbar(label="\nCategories passed:", show_eta=True,
                           width=0, length=len(categories_list), file=fo) \
            as pcat:
        for category in categories_list:
            title = "Testing " + category
            ctitle = colored(title, 'white', 'on_blue')
            with open(category + config["categories"][category], 'r') as sf:
                subconfig = yaml.load(sf)
            with click.progressbar(label=ctitle + ":",
                                   length=len(subconfig), file=fo,
                                   show_eta=True, width=0) \
                    as ptest:
                global output
                output = ""
                count = failed
                commands = []
                for test in subconfig:
                    mycmd = ""
                    if sanity:
                        mycmd += "valgrind --leak-check=full " +\
                                 "--error-exitcode=201 "
                    mycmd += my_path + " -" + options
                    if test.startswith("--", 0, 2):
                        line = test.split()
                        mycmd += " " + line[0]
                        mycmd += " " + category + "/" + line[1]
                    else:
                        mycmd += " " + category + "/" + test
                    mycmd = ' '.join(mycmd.strip().split())
                    percent = "[Test " + str(list(subconfig).index(test) +
                                             1) + "] "
                    commands.append([mycmd, subconfig[test], percent, mycmd])
                processes = []
                for cmd in commands:
                    processes.append([subprocess.Popen(cmd[0], shell=True,
                                                       stdout=subprocess.PIPE,
                                                       stderr=subprocess.PIPE),
                                      cmd[1], cmd[2], cmd[3]])
                while processes:
                    for p in processes:
                        if p[0].poll is None:
                            continue
                        pstdout, pstderr = p[0].communicate()
                        if sanity:
                            status = get_status(p[0].returncode, 0)
                        elif havm:
                            status = get_status(p[0].returncode, 0)
                        else:
                            status = get_status(p[0].returncode, p[1])
                        if status[0] != 0:
                            failed += errormsg(p[2], category, p[3], status[1])
                        else:
                            output += colored(p[2] + p[3] + ": PASS:\n" +
                                              status[1], 'green')
                            if havm:
                                tmp = tempfile.NamedTemporaryFile()
                                tmp.write(pstdout)
                                cmd = "havm --" + havm + " " + tmp.name
                                havm_proc = subprocess.run(
                                                    cmd, shell=True,
                                                    stdout=subprocess.PIPE,
                                                    stderr=subprocess.PIPE)
                                output += "\nstdout:\n"
                                output += havm_proc.stdout.decode("utf-8")
                                output += "\nstderr:\n"
                                output += havm_proc.stderr.decode("utf-8")
                                tmp.close()
                            ptest.update(1)
                        output += "\n"
                        processes.remove(p)
                fo.write(output)
            if count == failed:
                incr += 1
        if (incr != 0):
            pcat.update(incr)
        if fo is not sys.stdout:
            fo.close()
    if failed > 0:
        title = "the " + str(failed) + " following tests failed:"
        print("-" * len(title) + "\n" + colored(title, 'red'))
        print(fail[:-1])
    else:
        title = "Everything succeed"
        print("-" * len(title) + "\n" + colored(title, 'green'))


if __name__ == '__main__':
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    f = open('tigrou.ascii', 'r')
    file_content = f.read()
    print('\033[93m' + file_content + '\033[0m')
    f.close()
    options(sys.argv[1:])
