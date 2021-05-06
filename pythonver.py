import sys
import re

def simplify(numerator, denominator):
    return "= {}/{}".format(numerator, denominator)

def unify(fn):
    def _unif(num1, den1, num2, den2):
        if den1 != den2:
            return fn(num1*den2, den1*den2, num2*den1, den2*den1)
        return fn(num1, den1, num2, den2)
    return _unif

@unify
def add(num1, den1, num2, den2):
    return (num1+num2, den1)

@unify
def subtract(num1, den1, num2, den2):
    return (num1-num2, den1)

def multiply(num1, den1, num2, den2):
    return (num1*num2, den1*den2)

def divide(num1, den1, num2, den2):
    return (num1*den2, num2*den1)

def parse_token(token):
    num = 0
    den = 1
    # 3_1/2 3 
    return (num, den)

def arithmetic(cur, token):
    def _arith(op, numerator, denominator, *junk):
        opons = {"+": add, "-":subtract, "*":multiply, "/":divide}
        if token in opons.keys():
            return (token, numerator, denominator)
        num, den = parse_token(token)
        return opons.get(op, add)(numerator, denominator, num, den)

    return _arith(*cur)

def procline(line, ops=["*","+"]):
    def fixup(txt, op):
        return txt.replace(op, " {0} ".format(op))
    tokens = re.split(r'\s+', reduce(fixup, ops, line).strip())
    return reduce(arithmetic, tokens, ('+', 0, 1))

print [procline(x) for x in sys.stdin.readlines()]
