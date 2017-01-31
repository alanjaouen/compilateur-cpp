#!/usr/bin/python3

from termcolor import colored
import argparse
import click
import difflib
import os
import subprocess
import sys
import yaml


def options(args):
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
    parser.add_argument("-t", "--timeout", metavar="TIME", default=-1,
                        help="set TIME as a timeout for the tests " +
                        "(in seconds)")
    options = parser.parse_args(args)
    global time
    time = int(options.timeout)
    if options.list:
        for category in list_category('config.yaml'):
            print("- " + category)
        return
    if options.category != []:
        parse_config('config.yaml', options.category, options.sanity,
                     options.output)
    else:
        parse_config('config.yaml', list_category('config.yaml'),
                     options.sanity, options.output)


def list_category(yaml_file):
    with open(yaml_file, 'r') as f:
        config = yaml.load(f)
    categories = []
    for section in config:
        if section == "categories":
            with click.progressbar(label="Generating list of category",
                    length=len(config[section]), show_eta=True, width=0) as pbar:
                for category in config[section]:
                    categories.append(category)
                    pbar.update(1)
    print(colored("Succeed", 'green'))
    return categories


def get_status(my, ref):
    returncode = my + ref
    if returncode == 0 or returncode == 4 or returncode == 6:
        return (0, "\tmy returned: " + str(my) +\
                   "\n\tref returned: " + str(ref))
    elif returncode == 2:
        return (2, "\tmy returned: " + str(my) +\
                   "\n\tref returned: " + str(ref))
    elif returncode == 3:
        return (3, "\tmy returned: " + str(my) +\
                   "\n\tref returned: " + str(ref))
    elif returncode == 5:
        return (5, "\tmy returned: " + str(my) +\
                   "\n\tref returned: " + str(ref))
    else:
        return (1, "\tOups! An error occured. my returned: " + str(my) +\
                   " and ref returned: " + str(ref))


def errormsg(percent, category, mycmd, comment, msg):
    global output
    global fail
    output += colored(percent + mycmd + ": FAIL:\n" + msg, 'red')
    fail += colored(category + ": " + mycmd, 'red') + "\n"
    return 1


def parse_config(yaml_file, categories_list, sanity, foutput):
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
                for test in subconfig:
                    mycmd = ""
                    if sanity:
                        mycmd += "valgrind "
                    mycmd += config["my"]
                    mycmd += " " + category + "/"+ test
                    mycmd = ' '.join(mycmd.strip().split())
                    percent = "[" + str(int(((list(subconfig).index(test) + 1)
                                        / len(subconfig) * 100))) + "%] "
                    if time != -1:
                        try:
                            my = subprocess.run(mycmd, shell=True, timeout=time,
                                                stdout=subprocess.PIPE,
                                                stderr=subprocess.PIPE)
                        except subprocess.TimeoutExpired:
                            failed += errormsg(percent, category, mycmd,
                                               subconfig[test], "timeout\n")
                            continue
                    else:
                        my = subprocess.run(mycmd, shell=True,
                                            stdout=subprocess.PIPE,
                                            stderr=subprocess.PIPE)
                    status = get_status(my.returncode, subconfig[test])
                    if status[0] != 0:
                        failed += errormsg(percent, category, mycmd,
                                           subconfig[test], status[1])
                    else:
                        output += colored(percent + mycmd + ": PASS:" +\
                                          status[1], 'green')
                        ptest.update(1)
                    output += "\n"
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
    if sys.stdout.isatty():
        options(sys.argv[1:])
    else:
        parse_config('config.yaml', list_category('config.yaml'), False,
                     sys.stdout)
