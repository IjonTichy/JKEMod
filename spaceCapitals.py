#!/usr/bin/python3

# Desired behaviour:
#  potato = potato
#  Potato = Potato
#  potAto = pot Ato
#  poTAto = po TAto
#  poTaTo = po Ta To
#  POT700 = POT 700

import string

class NextLetter(Exception): pass
class Done(Exception): pass

UPPERCASE   = string.ascii_uppercase   # for shorter comparisons
LOWERCASE   = string.ascii_lowercase
LETTERS     = UPPERCASE + LOWERCASE
SPACES      = string.whitespace
NUMBERS     = "0123456789"


inp = ""

try:
    while inp != "quit":

        try:
            inp = input()

        except EOFError:
            raise Done

        else:
            if inp == "quit":
                raise Done

        newString = []
        newInput = inp.strip()
        newLen = len(newInput)

        for n, i in enumerate(newInput):

            try:
                if n == 0:
                    newString.append(i)
                    raise NextLetter


                if i in UPPERCASE:
                    if newInput[n - 1] in LOWERCASE:
                        newString.extend(" ")

                    if newInput[n - 1] in UPPERCASE and (n + 1 != newLen):
                        if newInput[n + 1] in LOWERCASE:
                            newString.extend(" ")


                if i in NUMBERS:
                    if newInput[n - 1] not in LETTERS:
                        newString.extend(i)
                    else:
                        newString.extend(" " + i)

                    raise NextLetter

                newString.extend(i)


            except NextLetter:
                pass




        out = "".join(newString)

        out = "\" {0} \"".format(out)

        print(out)
except Done:
    pass
