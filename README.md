# Calculator Coding Challenge

Write a command line program in the language of your choice that will
take operations on fractions as an input and produce a fractional
result.

Legal operators shall be *, /, +, - (multiply, divide, add, subtract)
Operands and operators shall be separated by one or more spaces Mixed
numbers will be represented by
whole_numerator/denominator. e.g. "3_1/4"

Improper fractions and whole numbers are also allowed as operands


? 1/2 * 3_3/4
= 1_7/8
? 2_3/8 + 9/8
3_1/2

# Notes

Tested on OpenBSD, Linux, and MacOS.  Would test on Windows if I had
one available.  If you have valgrind installed, you can check for
memory leaks by running `make checkmem`.

Running `make` will build and do a few spot checks on the system.