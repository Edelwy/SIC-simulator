from enum import Enum
#0 means Directive, 1 means Storage
directives = {
    "START":0,
    "END":0,
    "ORG":0,
    "EQU":0,
    "USE":0,
    "LTORG":0,
    "BASE":0,
    "NOBASE":0,
    "EXTDEF":0,
    "EXTREF":0,
    "BYTE":1,
    "WORD":1,
    "RESB":1,
    "RESW":1
}

#-1: unknown, 1: F1, 2: F2, 3:F3, vsak iz F3 je F4 če damo plus odspredi. če je S, nemam pojma
# EXCEPT RSUB ne tejka argumentov in je useless mu dat + odspred
instructions = {
    "LDA":3,
    "LDX":3,
    "LDL":3,
    "STA":3,
    "STX":3,
    "STL":3,

    "ADD":3,
    "SUB":3,
    "MUL":3,
    "DIV":3,
    "COMP":3,
    "TIX":3,

    "JEQ":3,
    "JGT":3, 
    "JLT":3, 
    "J":3, 

    "AND":3, 
    "OR":3,

    "JSUB":3,
    "RSUB":3,

    "LDCH":3,
    "STCH":3,

    "ADDF":3,
    "SUBF":3,
    "MULF":3,
    "DIVF":3,
    "COMPF":3, 

    "LDB":3,
    "LDS":3,
    "LDF":3,
    "LDT":3,
    "STB":3,
    "STS":3,
    "STF":3,
    "STT":3,

    "LPS":3, 
    "STI":3, 
    "STSW":3,

    "RD":3, 
    "WD":3, 
    "TD":3, 

    "SSK":3,

    "FLOAT":1, 
    "FIX":1,
    "NORM":1,
    "SIO":1,
    "HIO":1, 
    "TIO":1,

    "ADDR":2,
    "SUBR":2,
    "MULR":2,
    "DIVR":2,
    "COMPR":2,
    "SHIFTL":2,
    "SHIFTR":2,
    "RMO":2,
    "SVC":2,
    "CLEAR":2,
    "TIXR":2
}

opcodes = {
    "ADD": 0x18,
    "ADDF": 0x58,
    "ADDR": 0x90,
    "AND": 0x40,
    "CLEAR": 0xB4,
    "COMP": 0x28,
    "COMPF": 0x88,
    "COMPR": 0xA0,
    "DIV": 0x24,
    "DIVF": 0x64,
    "DIVR": 0x9C,
    "FIX": 0xC4,
    "FLOAT": 0xC0,
    "HIO": 0xF4,
    "J": 0x3C,
    "JEQ": 0x30,
    "JGT": 0x34,
    "JLT": 0x38,
    "JSUB": 0x48,
    "LDA": 0x00,
    "LDB": 0x68,
    "LDCH": 0x50,
    "LDF": 0x70,
    "LDL": 0x08,
    "LDS": 0x6C,
    "LDT": 0x74,
    "LDX": 0x04,
    "LPS": 0xD0,
    "MUL": 0x20,
    "MULF": 0x60,
    "MULR": 0x98,
    "NORM": 0xC8,
    "OR": 0x44,
    "RD": 0xD8,
    "RMO": 0xAC,
    "RSUB": 0x4C,
    "SHIFTL": 0xA4,
    "SHIFTR": 0xA8,
    "SIO": 0xF0,
    "SSK": 0xEC,
    "STA": 0x0C,
    "STB": 0x78,
    "STCH": 0x54,
    "STF": 0x80,
    "STI": 0xD4,
    "STL": 0x14,
    "STS": 0x7C,
    "STSW": 0xE8,
    "STT": 0x84,
    "STX": 0x10,
    "SUB": 0x1C,
    "SUBF": 0x5C,
    "SUBR": 0x94,
    "SVC": 0xB0,
    "TD": 0xE0,
    "TIO": 0xF8,
    "TIX": 0x2C,
    "TIXR": 0xB8,
    "WD": 0xDC
}

class Macro(Enum):
    D = 0
    Dn = 1
    Sd = 2
    Sn = 3
    F1 = 4
    F2n = 5
    F2r = 6
    F2rn = 7
    F2rr = 8
    F3 = 9
    F3m = 10
    F4m = 11

num_args = {
    Macro.D: 0,
    Macro.Dn: 1,
    Macro.Sd: 1,
    Macro.Sn: 1,
    Macro.F1: 0,
    Macro.F2n: 1,
    Macro.F2r: 1,
    Macro.F2rn: 2,
    Macro.F2rr: 2,
    Macro.F3: 0,
    Macro.F3m: 1,
    Macro.F4m: 1
}

registers = {
    "A": 0,
    "X": 1,
    "L": 2,
    "B": 3,
    "S": 4,
    "T": 5,
    "F": 6
}
registers_inv = {
    0: "A",
    1: "X",
    2: "L",
    3: "B",
    4: "S",
    5: "T",
    6: "F"
}
mnemonics = {
    "NOBASE": Macro.D,
    "LTORG": Macro.D,

    "START": Macro.Dn,
    "END": Macro.Dn,
    "BASE": Macro.Dn,
    "EQU": Macro.Dn,
    "ORG": Macro.Dn,

    "BYTE": Macro.Sd,
    "WORD": Macro.Sd,

    "RESB": Macro.Sn,
    "RESW": Macro.Sn,

    "LDA": Macro.F3m,
    "LDX": Macro.F3m,
    "LDL": Macro.F3m,
    "STA": Macro.F3m,
    "STX": Macro.F3m,
    "STL": Macro.F3m,

    "ADD": Macro.F3m,
    "SUB": Macro.F3m,
    "MUL": Macro.F3m,
    "DIV": Macro.F3m,
    "COMP": Macro.F3m,
    "TIX": Macro.F3m,

    "JEQ": Macro.F3m,
    "JGT": Macro.F3m, 
    "JLT": Macro.F3m, 
    "J": Macro.F3m, 

    "AND": Macro.F3m, 
    "OR": Macro.F3m,

    "JSUB": Macro.F3m,

    "RSUB": Macro.F3,

    "LDCH": Macro.F3m,
    "STCH": Macro.F3m,

    "ADDF": Macro.F3m,
    "SUBF": Macro.F3m,
    "MULF": Macro.F3m,
    "DIVF": Macro.F3m,
    "COMPF": Macro.F3m, 

    "LDB": Macro.F3m,
    "LDS": Macro.F3m,
    "LDF": Macro.F3m,
    "LDT": Macro.F3m,
    "STB": Macro.F3m,
    "STS": Macro.F3m,
    "STF": Macro.F3m,
    "STT": Macro.F3m,

    "LPS": Macro.F3m, 
    "STI": Macro.F3m, 
    "STSW": Macro.F3m,

    "RD": Macro.F3m, 
    "WD": Macro.F3m, 
    "TD": Macro.F3m, 

    "SSK": Macro.F3m,

    "FLOAT": Macro.F1, 
    "FIX": Macro.F1,
    "NORM": Macro.F1,
    "SIO": Macro.F1,
    "HIO": Macro.F1, 
    "TIO": Macro.F1,

    "ADDR": Macro.F2rr,
    "SUBR": Macro.F2rr,
    "MULR": Macro.F2rr,
    "DIVR": Macro.F2rr,
    "COMPR": Macro.F2rr,
    "SHIFTL": Macro.F2rn,
    "SHIFTR": Macro.F2rn,
    "RMO": Macro.F2rr,
    "SVC": Macro.F2n,
    "CLEAR": Macro.F2r,
    "TIXR": Macro.F2r
}

pomnilniske = ["LDA","LDX","LDL","STA","STX","STL","LDB","LDS","LDF","LDT","STB","STS","STF","STT", "LDCH", "STCH"]
#TO BE DETERMINED: ali so tukaj notri tudi rsub, jsub, j, jlt, jgt, jeq?
#to be determined s poskusanjem
#exclude "LDCH","STCH", zarad literalov?!??!?!?!?