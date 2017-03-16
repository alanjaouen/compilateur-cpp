#! /bin/python3

from dialog import Dialog
import cmd
import locale
import os
import rstr
import subprocess


class InterTestSuite(cmd.Cmd):
    """Command processor."""

    def do_quit(self, line):
        """quit.\n\tQuit the command processor."""
        return True

    def do_testsuite(self, line):
        """testsuite.\n\tLaunch the testsuite."""
        isnotfile = True
        while (isnotfile):
            tc_path = input("Enter the real path to tc binary: ")
            isnotfile = not os.path.isfile(tc_path)
            if isnotfile:
                print("Path is not correct")
        ts_options = input("Enter the options for the testsuite: ")
        tscmd = "./epitestsuite.py --my " + tc_path + " " + ts_options
        ts = subprocess.run(tscmd, shell=True, stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE)
        if ts.returncode == 0:
            print(ts.stdout.decode("utf-8"))
            return
        else:
            print("Oups, an error occured:")
            print(tscmd + " returned: " + str(ts.returncode))
            print(ts.stderr.decode("utf-8"))
            return

    def do_fuzzing(self, line):
        """fuzzing.\n\tRandom testing built on regex string generation."""
        d = Dialog(dialog="dialog")
        d.set_background_title("Tiger Compiler TestSuite")
        code, tag = d.menu("Which type of fuzzing do you wanna do?",
                           choices=[
                               ("(1)", "Random"),
                               ("(2)", "Select from a list")])
        if code == d.OK:
            if tag == "(2)":
                code, tags = d.checklist("For which categories?",
                                         choices=[
                                             ("Literals", "", False),
                                             ("Array and record", "", False),
                                             ("Variables, field, elements", "",
                                                 False),
                                             ("Object", "", False),
                                             ("Function", "", False),
                                             ("Method", "", False),
                                             ("Operations", "", False),
                                             ("Assignment", "", False),
                                             ("Type", "", False),
                                             ("Class", "", False),
                                             ("Control structures", "", False)
                                         ])
                if code != d.OK:
                    os.system('clear')
                    return
                if not tags:
                    os.system('clear')
                    print("You didn't choose anything.")
                    return
            else:
                tags = ("Literals", "Array and record",
                        "Variables, field, elements", "Object", "Function",
                        "Method", "Operations", "Assignement", "Type",
                        "Class", "Control structures")
            os.system('clear')
            print(*tags, sep='\n')
            count = input("How many random tests should be created? ")
            for i in range(int(count)):
                global categories
                for cat in tags:
                    print(rstr.xeger(categories[cat]()))
        else:
            os.system('clear')


def literals():
    return "([a-z])\w{2,10}|(nil)|([0-9]{1,4})"


def array_record():
    return "(type ([a-z])\w{2,10} = (\{[a-z]\w{2,10} : ((string)|(int))" +\
           "(, [a-z]\w{2,10} : ((string)|(int))){0,3}\}){1})|" +\
           "(type ([a-z])\w{2,10} (([a-z])\w{2,10} ){0,1}of ([a-z])\w{2,10})"


def variables_field_elements():
    return "([a-z])\w{2,10}((.([a-z])\w{2,10})|(\[([a-z])\w{2,10}\]))"


if __name__ == '__main__':
    locale.setlocale(locale.LC_ALL, '')
    global categories
    categories = {
        "Literals": literals,
        "Array and record": array_record,
        "Variables, field, elements": variables_field_elements
    }
    InterTestSuite().cmdloop()
