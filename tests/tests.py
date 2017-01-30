#!/usr/bin/env python3

import os
import argparse
import subprocess



class bcolors:
    HEADER =    '\033[95m'
    OKBLUE =    '\033[94m'
    GREEN =     '\033[92m'
    WARNING =   '\033[93m'
    CYAN =      '\033[38;5;33m'
    FAIL =      '\033[91m'
    ENDC =      '\033[0m'
    MAGENTA =   '\033[38;5;163m'

def print_cat(arg):
    print (
        bcolors.CYAN
        + "==================================================\n"
        + "Test " + arg + "\n"
        + "=================================================="
        + bcolors.ENDC)

def category(category):
    print_cat(category)
    if not os.path.isdir(category):
                    print (bcolors.WARNING + "No tests found for {} category \
                    \n".format(category) + bcolors.ENDC)
    else:
        for root, dirs, files in os.walk(category):
            for name in files:

                print(bcolors.WARNING + "\nTest from : "
                      + os.path.join(root, name) +  bcolors.ENDC)

                my = subprocess.run(['./../thl',
                                     os.path.join(root, name)],
                                    stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE)

                print ("return code :"
                      + ((bcolors.GREEN + str(my.returncode) + bcolors.ENDC)
                         if my.returncode == 0
                         else (bcolors.FAIL + str(my.returncode) + bcolors.ENDC)))
                if my.returncode != 0:
                    print ("stderr :" + (str(my.stderr))
                              if  my.stderr != ""
                              else (bcolors.FAIL + "empty" + bcolors.ENDC))

def exec_all(args):
    print (bcolors.MAGENTA + "Launch tests suite  on all tests \n"
           + bcolors.ENDC)
    os.chdir("tests")
    for root, dirs, files in os.walk("."):
        for name in dirs:
            category(name)
            print ("\n")

def list_dir():
    print (bcolors.WARNING + "Available tests category : \n" + bcolors.ENDC)
    for root, dirs, files in os.walk("."):
        for name in dirs:
            print (os.path.join(root, name))
    print ("\n")

if __name__ == '__main__':
    parser = argparse.ArgumentParser(conflict_handler='resolve')
    parser.add_argument("-l","--list", help="list all the available \
    categories", action="store_true")
    parser.add_argument("-c","--category", help="Execute the test suite on the \
    categories passed in argument only.")
    args = parser.parse_args()
    if (args.list):
        list_dir()
    else:
        if (args.category != None):
            category(args.category)
        else:
            exec_all(args)
