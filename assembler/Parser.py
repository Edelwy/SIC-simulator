from Tables import *
from Node import *
from Mnemonic import *
from Exceptions import *

#TODO: make these errors make more sense
def check_num_args(format, values):
    if (format == Macro.F3m or format == Macro.F4m) and len(values) == 2 and values[1] == "X":
        return True
    else: return num_args[format] == len(values)

def parse_label(label):
    #if label not in reserved words
    if label not in mnemonics and label not in registers and (label == None or label.isalnum()): return label
    else: raise InvalidLabelError(label)

def parse_symbol(s):
    #we want this to be nonempty
    if s: return parse_label(s)
    else: raise ValueError

def parse_integer(n):
    #can be 0x... or 0b... or 0o.... or 123... or -123...
    if n[0] == '0':
        if len(n) == 1: return int(n[0])
        elif n[1] == 'b':
            return int(n, 2) #these things raise a ValueError when can not resolve
        elif n[1] == 'o':
            return int(n, 8)
        elif n[1] == 'x':
            return int(n, 16)
        else:
            raise ValueError
    return int(n)

def parse_integer_or_symbol(n):
    try:
        return parse_integer(n)
    except ValueError:
        return parse_symbol(n)

def parse_register(r):
    #TODO: assumption - we return register number instead of oznaka
    if r in registers:
        return registers[r]
    else:
        raise OperandValueError(r)

def parse_expression(e):
    #An expression is ints, or possible symbols, separated by +-*/.
    #Parentheses not yet implemented.
    #Operator order will be implemented by two passes.
    sequence =  []
    buf = ""
    ops = "+-*/()"
    for char in e.strip():
        if char in ops:
            if buf: sequence.append(parse_integer_or_symbol(buf))
            buf = ""
            sequence.append(char)
        else:
            buf += char
    if buf: sequence.append(parse_integer_or_symbol(buf))
    return sequence

def parse_data(d):
    #can be C'...' characters, X'...' hex, or an integer.   
    if d[1] == "'" and d[-1] == "'":
        if d.startswith("C"):
            s = d[2:-1]
            nums = [ord(c) for c in s]
            #whitespace is lost to the tokenizer, assuming
            if not nums: nums = [0x20]
            sum = 0
            for ch in nums:
                sum *= 0x100
                sum += ch
            return sum
        elif d.startswith("X"):
            return int(d[2:-1], 16)
        else: raise OperandValueError(d)
    else:
        return parse_integer(d)

def parse_memory(m):
    mode = m[0]
    if mode in ("#", "@", "="): m = m[1:]
    else: mode = None
    X = False
    if m.endswith(",X"): 
        X = True
        m = m[:-2]
    if mode == "=":
        m = parse_data(m)
    else:
        m = parse_expression(m)
    return mode, m, X

def parse_mnemonic(mnemonic, values):
    f4 = False
    if mnemonic.startswith("+"): 
        mnemonic = mnemonic[1:]
        f4 = True
    format = mnemonics[mnemonic]
    if format == Macro.F3m and f4: format = Macro.F4m
    if not check_num_args(format, values): raise NumOperandsError(mnemonic, format, len(values))

    if format == Macro.D:
        M = MnemonicD(mnemonic)
    elif format == Macro.Dn:
        n = parse_expression(values[0])
        M = MnemonicDn(mnemonic, n)
    elif format == Macro.Sd:
        d = parse_data(values[0])
        M = MnemonicSd(mnemonic, d)
    elif format == Macro.Sn:
        n = parse_integer(values[0])
        M = MnemonicSn(mnemonic, n)
    elif format == Macro.F1:
        M = MnemonicF1(mnemonic)
    elif format == Macro.F2n:
        n = parse_integer(values[0])
        M = MnemonicF2n(mnemonic, n)
    elif format == Macro.F2r:
        r = parse_register(values[0])
        M = MnemonicF2r(mnemonic, r)
    elif format == Macro.F2rn:
        r = parse_register(values[0])
        n = parse_integer(values[1])
        M = MnemonicF2rn(mnemonic, r, n)
    elif format == Macro.F2rr:
        r1 = parse_register(values[0])
        r2 = parse_register(values[1])
        M = MnemonicF2rr(mnemonic, r1, r2)
    elif format == Macro.F3:
        M = MnemonicF3(mnemonic)
    elif format == Macro.F3m:
        if len(values) == 2:
            values[0] = values[0] + ",X" #we can trust check_num_args
        mode, expr, X = parse_memory(values[0])
        M = MnemonicF3m(mnemonic, mode, expr, X)
    elif format == Macro.F4m:
        if len(values) == 2:
            values[0] = values[0] + ",X"
        mode, expr, X = parse_memory(values[0])
        M = MnemonicF4m(mnemonic, mode, expr, X)

    return M, format

#IN: list of tokens, OUT: node with mnemonic
def parser(tokens):
    label = None
    mnemonic = None
    comment = None
    values = []

    #Tu assumamo d je basic syntax uredu, syntax_check v Tokenizerju je poskrbel, torej če srečamo Label vemo da je na začetku vrstice in samo eden...
    for token in tokens:
        if token[0] == "Label":
            label = token[1]
        if token[0] == "Comment":
            comment = token[1]
        if token[0] == "Mnemonic":
            mnemonic = token[1]
        if token[0] == "Value":
            values.append(token[1])

    if values: values = "".join(values).split(",")
    #values so seznam ki lahko izgleda kot ["A,B,C"] ali ["A,", "B,", "C"]
    #formatting them properly, so separate arguments will be separate
    #now values is list of 1 or 2 things.

    if mnemonic == None: return Comment(comment)
        
    #TODO: ze tukaj bi lahko marsikaj preveril, preden gres v konstruktorje reci
    label_p = parse_label(label)
    mnemonic_p, format = parse_mnemonic(mnemonic, values)

    if format in (Macro.D, Macro.Dn):
        node = Directive(mnemonic_p, label_p, comment)
    elif format in (Macro.Sd, Macro.Sn):
        node = Storage(mnemonic_p, label_p, comment)
    elif format == Macro.F1:
        node = InstructionF1(mnemonic_p, label_p, comment)
    elif format in (Macro.F2n, Macro.F2r, Macro.F2rn, Macro.F2rr):
        node = InstructionF2(mnemonic_p, label_p, comment)
    elif format in (Macro.F3, Macro.F3m):
        node = InstructionF3(mnemonic_p, label_p, comment)
    elif format == Macro.F4m:
        node = InstructionF4(mnemonic_p, label_p, comment)
    return node