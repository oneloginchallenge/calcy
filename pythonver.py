import sys
import re

def gcf(a, b):
    if a==0:
        return b
    if b==0:
        return a
    return gcf(a%b, b) if a > b else gcf(b%a, a)

def show(numerator=0, denominator=1, *junk):
    fracs = numerator%(denominator or 1)
    whole = (numerator-fracs)/(denominator or 1)
    out = ""
    if whole > 0:
        out += "{}{}".format(whole, "_" if fracs > 0 else "")
    if fracs > 0:
        out += "{}/{}".format(fracs, denominator)
    return "= {}".format(out)

def simplify(numerator, denominator):
    if denominator == 1:
        return numerator, denominator
    factor = gcf(abs(numerator), abs(denominator)) or 1
    return (numerator/factor, denominator/factor)


def unify(fn):
    def _unif(num1, den1, num2, den2):
        if den1 != den2:
            return fn(num1*den2, den1*den2, num2*den1, den2*den1)
        return fn(num1, den1, num2, den2)
    return _unif

@unify
def add(num1, den1, num2, den2):
    return simplify(num1+num2, den1)

@unify
def subtract(num1, den1, num2, den2):
    return simplify(num1-num2, den1)

def multiply(num1, den1, num2, den2):
    return simplify(num1*num2, den1*den2)

def divide(num1, den1, num2, den2):
    return simplify(num1*den2, num2*den1)

def parse_token(token):
    num = 0
    den = 1
    for entirety in re.findall(r"^-*[0-9]+$", token):
        return (int(entirety), 1)
    for wholenum in re.findall(r"-*[0-9]+_", token):
        num += int(wholenum.strip("_"))
    for fraction in re.findall(r"-*[0-9]+/[1-9]+", token):
        numerator, denominator = map(int, fraction.split("/"))
        num, den = add(num, den, numerator, denominator)
    return (num, den)

def arithmetic(cur, token):
    def _arith(op, numerator, denominator, *junk):
        opons = {"+": add, "-":subtract, "*":multiply, "/":divide}
        if token in opons.keys():
            return (token, numerator, denominator)
        num, den = parse_token(token)
        return (op,)+opons.get(op, add)(numerator, denominator, num, den)
    return _arith(*cur)

def procline(line, ops=["*","+"]):
    def fixup(txt, op):
        return txt.replace(op, " {0} ".format(op))
    tokens = re.split(r'\s+', reduce(fixup, ops, line).strip())
    return reduce(arithmetic, tokens, ('+', 0, 1))[1:]

def main():
    for out in [show(*procline(x)) for x in sys.stdin.readlines()]:
        print out

if __name__ == "__main__":
    main()
