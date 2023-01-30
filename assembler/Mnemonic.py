from Tables import *
from Exceptions import OperandValueError

class Mnemonic():
    def __init__(self, name):
        self.name = name
        self.expr = None

    def __repr__(self):
        return f"{self.name}"
    
    def pretty(self):
        return self.__repr__()
    
    def get_symbols(self):
        return None
    


class Instruction(Mnemonic):
    def __init__(self, name):
        super().__init__(name)
        lookup = name[1:] if name.startswith("+") else name
        self.opcode = opcodes[lookup]


class MnemonicD(Mnemonic):
    pass    #for now just placeholder
class MnemonicDn(Mnemonic):
    def __init__(self, name, n):
        super().__init__(name)
        self.expr = n
    def __repr__(self):
        return f"{self.name} {self.expr}"
    def get_symbols(self):
        #DIRTY
        if type(self.expr) != type([]): self.expr = [self.expr]
        return [x for x in self.expr if type(x) == type("xD") and x not in "+-/*()"]
    def resolved_address(self, addr):
        self.addr = addr
class MnemonicSd(Mnemonic):
    def __init__(self, name, d):
        super().__init__(name)
        self.d = d
    def __repr__(self):
        return f"{self.name} {hex(self.d)}"
class MnemonicSn(Mnemonic):
    def __init__(self, name, n):
        super().__init__(name)
        self.n = n
    def __repr__(self):
        return f"{self.name} {self.n}"
class MnemonicF1(Instruction):
    def __init__(self, name):
        super().__init__(name)
class MnemonicF2n(Instruction):
    #SVC
    def __init__(self, name, n):
        super().__init__(name)
        self.n = n
    def assemble(self): #i suppose?
        return (self.n, 0)
    def __repr__(self):
        return f"{self.name} {self.n}"
class MnemonicF2r(Instruction):
    def __init__(self, name, r):
        super().__init__(name)
        self.r = r
    def assemble(self): #i suppose?
        return (self.r, 0)
    def __repr__(self):
        return f"{self.name} {registers_inv[self.r]}"
class MnemonicF2rn(Instruction):
    def __init__(self, name, r, n):
        super().__init__(name)
        self.r = r
        self.n = n
    def assemble(self):
        #in assembled instr, r2 = n-1
        return (self.r, self.n-1)
    def __repr__(self):
        return f"{self.name} {registers_inv[self.r]},{self.n}"
class MnemonicF2rr(Instruction):
    def __init__(self, name, r1, r2):
        super().__init__(name)
        self.r1 = r1
        self.r2 = r2
    def assemble(self):
        return (self.r1, self.r2)
    def __repr__(self):
        return f"{self.name} {registers_inv[self.r1]},{registers_inv[self.r2]}"
class MnemonicF3(Instruction):
    def __init__(self, name):
        super().__init__(name)
        self.mode = None
class MnemonicF3m(Instruction):
    def __init__(self, name, mode, expr, X):
        super().__init__(name)
        self.mode = mode
        self.expr = expr
        self.X = X
        self.addr = None
    def __repr__(self):
        mod = f"[{self.mode}]" if self.mode else ""
        Xx = "[X]" if self.X else ""
        ad = f" -> {hex(self.addr)}" if self.addr else ""
        return f"{self.name} {mod} {self.expr}{ad} {Xx}"

    def pretty(self):
        mod = self.mode if self.mode else ""
        Xx = ",X" if self.X else ""
        exp = "".join([str(x) for x in self.expr])
        return f"{self.name} {mod}{exp}{Xx}" 
    def get_symbols(self):
        #DIRTY
        if type(self.expr) != type([]): self.expr = [self.expr]
        #TO BE IMPROVED
        return [x for x in self.expr if type(x) == type("xD") and x not in "+-/*()"]
    def resolved_address(self, addr):
        self.addr = addr

class MnemonicF4m(Instruction):
    def __init__(self, name, mode, expr, X):
        super().__init__(name)
        self.mode = mode
        self.expr = expr
        self.X = X
    def __repr__(self):
        mod = f"[{self.mode}]" if self.mode else ""
        Xx = "[X]" if self.X else ""
        return f"{self.name} {mod} {self.expr} {Xx}"
        
    def pretty(self):
        mod = self.mode if self.mode else ""
        Xx = ",X" if self.X else ""
        exp = "".join([str(x) for x in self.expr])
        return f"+{self.name} {mod}{exp}{Xx}" 
    def get_symbols(self):
        #DIRTY
        if type(self.expr) != type([]): self.expr = [self.expr]
        return [x for x in self.expr if type(x) == type("xD") and x not in "+-/*()"]
    def resolved_address(self, addr):
        self.addr = addr