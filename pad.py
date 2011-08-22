#!/usr/bin/env python3

"""
A module, containing padding-related functions. Avoids things like
ljust, rjust, and center so as to not be redundant.
"""

__all__ = ["pad", "unpad"]

class UnpadError(Exception): pass

def testDocs():
    import doctest;
    doctest.testmod()

def pad(valStr, lpad = -1, rpad = -1, padChar=" ", set=False):
    """
Pads a string. By default, the padder is a space, the amount to pad on
both sides is one, and stripping the current padding is false. For
examples:

>>> pad('spam')
' spam '

You can define how much padding goes on either side, too.

>>> pad('spam', 2)
'  spam  '
>>> pad('spam', 2, 4)
'  spam    '

Also, you can choose the padding character.

>>> pad('spam', 2, 4, padChar="=")
'==spam===='

If there's already padding, you can also choose to strip it away.
However, the character to be stripped will be equal to the pad
character, so you might still have to do manual pad stripping.

>>> pad('   spam ', 2, 4, padChar="=", set=False)
'==   spam ===='
>>> pad('   spam ', 2, 4, padChar="=", set=True)
'==   spam ===='
>>> pad('   spam '.strip(), 2, 4, padChar="=", set=True)
'==spam===='
>>> pad('===spam=', 2, 4, padChar="=", set=True)
'==spam===='

It's trivial to add a pad pad, like this:

>>> pad(pad('spam'), 10, padChar="=")
'========== spam =========='
"""

    if set:
        valStr = valStr.strip(padChar)

    if lpad < 0:
        lpad = 1

    if rpad < 0:
        rpad = lpad

    return "{0}{1}{2}".format(padChar*lpad, valStr, padChar*rpad)


def unpad(valStr, lunpad=-1, runpad=-1, unpadChar=""):
    """
Will attempt to unpad a string. By default, it'll assume that the
padding character is the first character in the string, and will unpad
by one character, on both sides, like so:

>>> unpad('===spam===')
'==spam=='

Like the pad function, you can specify the amount to unpad:

>>> unpad('===spam===', 2)
'=spam='
>>> unpad('===spam===', 2, 3)
'=spam'

You can also explicity define the unpadding character (although it
really won't be necessary, more likely than not):

>>> unpad('===spam===', 2, 3, unpadChar="=")
'=spam'

However, if unpad doesn't find purely the pad character you defined (or
it assumed), it'll raise an UnpadError akin to the following:

>>> unpad('===spam===', unpadChar=" ")
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "pad.py", line 67, in unpad
    raise UnpadError("cannot unpad without cutting into main string")
UnpadError: cannot unpad without cutting into main string
"""
    if lunpad < 0:
        lunpad = 1

    if runpad < 0:
        runpad = lunpad

    if not unpadChar:
        unpadChar = valStr[0]

    lunpadStr = unpadChar*lunpad
    runpadStr = unpadChar*runpad

    if valStr.startswith(lunpadStr) and valStr.endswith(runpadStr):
        return valStr[lunpad:-runpad]
    else:
        raise UnpadError("cannot unpad without cutting into main string")


if __name__ == "__main__":
    testDocs()
