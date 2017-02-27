"""module for fuzzing."""
# !/usr/bin/python3

from dialog import Dialog
import cmd
import locale
import os
import rstr


class InterTestSuite(cmd.Cmd):
    """Command processor."""

    def do_quit(self, line):
        """
        quit.

        Quit the command processor.
        """
        return True

    def do_fuzzing(self, line):
        """
        fuzzing.

        Random testing built on regex string generation.
        """
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
    """Literals."""
    return "([a-z])\w{2,10}|(nil)|([0-9]{1,4})"


def array_record():
    """Array and record."""
    return """type ([a-z])\w{2,10} = (\{[a-z]\w{2,10} : """ +\
           """string(, [a-z]\w{2,10} : int){0,3}\}){1}"""


if __name__ == '__main__':
    locale.setlocale(locale.LC_ALL, '')
    global categories
    categories = {
        """Literals""": literals,
        """Array and record""": array_record
    }
    InterTestSuite().cmdloop()
