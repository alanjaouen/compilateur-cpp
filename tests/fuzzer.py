#!/usr/bin/python3

from dialog import Dialog
import cmd
import locale
import os
import rstr


class InterTestSuite(cmd.Cmd):
    """Command processor"""
    def do_quit(self, line):
        """quit\n\tQuit the command processor"""
        return True


    def do_token_gen(self, regex):
        print(rstr.xeger(regex))


    def do_fuzzing(self, line):
        d = Dialog(dialog="dialog")
        d.set_background_title("Tiger Compiler TestSuite")
        code, tag = d.menu("Which type of fuzzing do you wanna do?",
                choices=[("(1)", "Random"),
                         ("(2)", "Select from a list")])
        if code == d.OK:
            if tag == "(1)":
                os.system('clear')
                count = input("How many random tests should be created? ")
                print(count)
            else:
                code, tags = d.checklist("For which categories?",
                        choices=[("Literals", "", False),
                                 ("Array and record", "", False),
                                 ("Variables, field, elements", "", False),
                                 ("Object", "", False),
                                 ("Function", "", False),
                                 ("Method", "", False),
                                 ("Operations", "", False),
                                 ("Assignment", "", False),
                                 ("Type", "", False),
                                 ("Class", "", False),
                                 ("Control structures", "", False)])
                if code == d.OK:
                    os.system('clear')
                    print(*tags, sep='\n')


if __name__ == '__main__':
    locale.setlocale(locale.LC_ALL, '')
    InterTestSuite().cmdloop()
