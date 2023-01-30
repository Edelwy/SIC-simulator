from Mnemonic import *
from Tables import *
from Exceptions import *


class Node:
    #en node je en line asm.

    #label
    #mnemonic
    #comment
    #Node vsebuje mnemonic. Lahko ima label ki ga označuje. Lahko ima komentar po njemu.
    #TODO: Should not have values. values should be in mnemonic which is of class Mnemonic.
    def __init__(self, mnemonic, label=None, comment=None):
        self.mnemonic = mnemonic
        self.label = label
        self.comment = comment
    
    def __repr__(self):
        #toString()
        lab = self.label + ": " if self.label else ""
        mnem = str(self.mnemonic) + " " if self.mnemonic else ""
        comm = self.comment if self.comment else ""
        return lab + mnem + comm

    def __len__(self):
        return 0

    def debug(self):
        return f"(Type: {str(type(self)).split('.')[1][:-2]}, Label: {self.label}, Mnemonic: {self.mnemonic}, Comment: {self.comment})"

    def detailed(self):
        lab = f"<{self.label}>:" if self.label else ""
        op = self.mnemonic
        return f"{str(type(self)).split('.')[1][:-2].ljust(20)}{lab.ljust(12)}{op}"

    def enter(self, code):
        pass

    def leave(self, code):
        code.PC += len(self)
        #TODO: fix with ltorg

    def activate(self, code):
        if not self.label: return
        if self.label in code.symbol_table: raise DuplicateLabelError(self.label)
        code.symbol_table[self.label] = code.PC

    def resolve(self, code):
        pass

    def pretty(self):
        return self.mnemonic.pretty()

    def emit_code(self, code):
        return None
    
    def emit_text(self, code):
        bcode = self.emit_code(code)
        if bcode != None:
            return hex(bcode)[2:].rjust(2*len(self),"0")

        
        




class Comment(Node):
    def __init__(self, comment):
        super().__init__(None, comment=comment)

class InstructionF1(Node):

    def __len__(self):
        return 1

    #TODO: turn this into byte arrays
    #AND MOVE TO MNEMONIC PLEASE: call .assemble
    def emit_code(self, code):
        opcode = self.mnemonic.opcode
        self.hexcode = opcode
        return self.hexcode



class InstructionF2(Node):

    def __len__(self):
        return 2

    def emit_code(self, code):
        opcode = self.mnemonic.opcode
        r1, r2 = self.mnemonic.assemble()
        self.hexcode = opcode << 8 | r1 << 4 | r2
        return self.hexcode

class Resolvable(Node):
    def resolve(self, code):
        symbols = self.mnemonic.get_symbols()
        if symbols == None: return None
        
        for sym in symbols:
            if sym not in code.symbol_table:
                raise UndefinedSymbolError(self.mnemonic, symbols, sym)
        #all symbols are defined. now to calculate actual address
        e = self.mnemonic.expr.copy()
        #first pass: turn symbols to values
        for i in range(len(e)):
            if e[i] in code.symbol_table:
                e[i] = code.symbol_table[e[i]]
            #turn division to integer division for eval
            if e[i] == "/": e[i] = "//"
        #TODO: SEPARATE SYMBOL RESOLUTION AND ARITHMETIC.
        #second pass: arithmetic
        #TODO: think if it makes sense to even store ints as ints
        #eval wants strings
        evaluated = eval("".join([str(x) for x in e]))
        
        #TODO: modes, X, (DO I DO THAT HERE? NO PROLLY)
        self.mnemonic.resolved_address(evaluated)
        return evaluated


class Memory(Resolvable):
    def __init__(self, mnemonic, label=None, comment=None):
        super().__init__(mnemonic, label, comment)
        self.nixbpe = {
            "n": 0,
            "i": 0,
            "x": 0,
            "b": 0,
            "p": 0,
            "e": 0
        }

    def set_PC_relative(self):
        self.nixbpe["b"] = 0
        self.nixbpe["p"] = 1

    def set_base_relative(self):
        self.nixbpe["b"] = 1
        self.nixbpe["p"] = 0

    def set_direct(self):
        self.nixbpe["b"] = 0
        self.nixbpe["p"] = 0

    def set_indirect(self):
        self.nixbpe["n"] = 1
        self.nixbpe["i"] = 0

    def set_immediate(self):
        self.nixbpe["n"] = 0
        self.nixbpe["i"] = 1

    def set_simple(self):
        self.nixbpe["n"] = 1
        self.nixbpe["i"] = 1

    def set_SIC(self):
        self.nixbpe["n"] = 0
        self.nixbpe["i"] = 0

    def set_indexed(self):
        self.nixbpe["x"] = 1

    def get_mode_ni(self):
        n = self.nixbpe["n"]
        i = self.nixbpe["i"]
        if n == 0:
            if i == 0: return "SIC"
            elif i == 1: return "IMM"
        elif n == 1:
            if i == 0: return "IND"
            elif i == 1: return "SIM"
    
    def get_mode_bp(self):
        b = self.nixbpe["b"]
        p = self.nixbpe["p"]
        if b == 0:
            if p == 0: return "DIR"
            elif p == 1: return "PCR"
        elif b == 1:
            if p == 0: return "BAS"
            elif p == 1: return "INV"

    def get_nixbpe(self):
        bits = 0
        for bit in self.nixbpe.values():
            bits = (bits << 1) + bit
        return bits
    

class InstructionF3(Memory):
        #1. write to literal table:
        # table[address] : this, .<literalvalue>

        #2. when LTORG is called:
        #for each entry in literal table:
        #place its <literalvalue> in memory with a label, put teh entry in symtab, and properly increment the PCs
        #go to its mnemonic, and give it label
    def activate(self, code):
        super().activate(code)
        if self.mnemonic.mode == "=":
            code.literal_table[code.PC] = self

    def resolve(self, code):
        addr = super().resolve(code) 
        if addr == None: 
            self.set_simple()
            return #izjema za F3 ki ni F3m
        #take care of nixbpe - e is taken care of by constructor


        #n,i
        if addr >= 2**15 or addr < -2048: raise OperandValueError(addr)
        elif addr >= 2**12:
            self.set_SIC()
            #ne sme imeti @ ali #.
            if self.mnemonic.mode != None: raise OperandValueError(self.mnemonic.mode)
        else:
            if self.mnemonic.mode == "#":
                self.set_immediate()
            elif self.mnemonic.mode == "@":
                self.set_indirect()
            else:
                self.set_simple()

        #b,p
        #pod dolocenimi pogoji je treba tukaj reci, naj se direktno resolva.
        if self.mnemonic.get_symbols() != None and len(self.mnemonic.get_symbols()) == 0 and self.mnemonic.name in pomnilniske and self.mnemonic.mode != "=":
            self.set_direct()
        #possible solution: ce je F3m (morda celo le load/store)
        # in ima za operand integer, naj bo direkt.

        elif code.BASE == False:
            self.set_PC_relative()
            self.PC = code.PC + len(self) #is this foolproof?
        elif addr in range(-2048, 4096):
            self.set_base_relative()
            self.base = code.BASE
        else:
            #should never happen
            self.set_direct()
            #problem: nekatere stvari je vseeno treba setat direkt. npr, loade vedno direkt al ne?!??!?!???

        #hack - NAROBE; mislim da ce je pomnilniska? ionget
        if self.mnemonic.mode == "#": #and type of operand is numeric and not symbol?!?
            #self.set_direct() #then pc + # and base + # is not possible...
            pass
        #x
        if self.mnemonic.X:
            self.set_indexed()

            
    def __len__(self):
        return 3

    def emit_code(self, code):
        opcode = self.mnemonic.opcode
        nixbpe = self.get_nixbpe()
        if self.mnemonic.name == "RSUB": #TODO: IS RSUB opcode 4F or 4C?!?!?!?!?
            #this weird format 3
            return opcode << 16 | nixbpe << 12
        mode_ni = self.get_mode_ni()
    
                    
        
        if mode_ni == "SIC":
            address = self.mnemonic.addr
            return opcode << 18 | ((nixbpe << 12) & 0b111000) | address
        else:
            operand = self.mnemonic.addr
            mode_bp = self.get_mode_bp()

            if mode_bp == "PCR":
                #NEEDS INFO OF PC AT THAT MOMENT?
                ta = operand - self.PC #next
                pass
            elif mode_bp == "BAS":
                #NODE NEEDS INFO OF BASE AT THAT MOMENT?
                ta = operand - self.base
            elif mode_bp == "DIR":
                ta = operand
            #ALSO X INDEXING
            #TODO: X indexing
            #?? LIKE THIS?!?!?
            if self.mnemonic.X:
                ta = ta #pristej vsebino registra X. ali naj to jaz naredim?
            
            if mode_ni == "IMM":
                offset = ta
            elif mode_ni == "IND":
                #@
                offset = ta #offset = pomnilnik[ta]
            elif mode_ni == "SIM":
                offset = ta

            xX = ("INDX" if self.mnemonic.X else "")
            #print(f"op = {hex(opcode)}, nixbpe = {bin(nixbpe)}, mode = {mode_bp}, mode_ni = {mode_ni}, {xX}")
            return opcode << 16 | nixbpe << 12 | offset & 0xfff #sanitycheck?!

class InstructionF4(Memory):
    def __init__(self, mnemonic, label=None, comment=None):
        super().__init__(mnemonic, label, comment)
        self.nixbpe["e"] = 1
        
    def resolve(self, code):
        addr = super().resolve(code)
        #nixbpe: e is 1 by constructor
        #b,p
        self.set_direct()
        #x
        if self.mnemonic.X:
            self.set_indexed()
        #n,i
        if addr >= 2**20: raise OperandValueError(addr)
        
        if self.mnemonic.mode == "#":
            self.set_immediate()
        elif self.mnemonic.mode == "@":
            self.set_indirect()
        else:
            self.set_simple()

    def __len__(self):
        return 4

    #TODO: check consistency between f3 and 4

    def emit_code(self, code):
        opcode = self.mnemonic.opcode
        nixbpe = self.get_nixbpe()
        address = self.mnemonic.addr
        return opcode << 24 | nixbpe << 20 | address

class Directive(Resolvable):
    #START; END; USE; EQU; ORG; LTORG; BASE; NOBASE;
    #only USE left which is to be done later, when we have blocks
    def __init__(self, mnemonic, label=None, comment=None):
        super().__init__(mnemonic, label, comment)
    def resolve(self, code):
        #resolve symbols if it has them
        directive = self.mnemonic.name
        arg = super().resolve(code) #None if there is no
        if directive == "BASE":
            code.BASE = arg 
            #TODO: think if this should be address of symbol?
            #IS THIS TOO late to do this=
            #i suppose da ja... BASE na nek sym, in potem X za indexing?
        if directive == "NOBASE":
            code.BASE = False
        #SHOULD I BE RESOLVING DIRECTIVES OR DOES IT DO IT LATER??

    def activate(self, code):
        super().activate(code)
        if self.mnemonic.name == "LTORG" or self.mnemonic.name == "END":
            self.children = {}
            codepc = code.PC
            for lit_address in code.literal_table:
                lit_node = code.literal_table[lit_address]
                lit_value = lit_node.mnemonic.expr
                lit_symbol = "$" + str(code.literal_accumulator)
                code.symbol_table[lit_symbol] = codepc
                lit_node.mnemonic.expr = codepc
                if lit_value < 2**8:
                    self.children[codepc] = (lit_value, 1)
                    codepc += 1
                elif lit_value < 2**24:
                    self.children[codepc] = (lit_value, 3)
                    codepc += 3
                else: raise OperandValueError(lit_value)
                code.literal_accumulator += 1
                lit_node.set_simple()
                lit_node.set_PC_relative()
            code.literal_table = {}

        if self.mnemonic.name == "ORG":
            code.PC = self.mnemonic.expr[0] #is this good enough? int?
            #TODO: FIX THIS there makes no sense that this should be like this

        if self.mnemonic.name == "EQU":
            #TODO: poljbni izrazi

            if self.label == None: raise InvalidLabelError("for EQU")
            code.symbol_table[self.label] = self.mnemonic.expr[0] #is this good enough also?
            #NOT GOOD ENOUGH: NOT WORKING WITH DATA. PUT THESE ERRORS OUT AND LET IT PARSE BETTER.

        if self.mnemonic.name == "START":
            if code.started: raise DuplicateDirectiveError("START")
            code.PC = self.mnemonic.expr[0] #nism sure ali je to res
            code.started = True
            code.start = self.mnemonic.expr[0]
        
        if self.mnemonic.name == "END":
            if code.ended: raise DuplicateDirectiveError("END")
            code.ended = True

    def pretty(self):
        if self.mnemonic.name == "LTORG" or self.mnemonic.name == "END":
            return f"{self.mnemonic.name}\n" + "\n".join([f"\t\t\tBYORD {hex(self.children[c][0])}" for c in self.children])
        else: return self.mnemonic.pretty()

    def emit_code(self, code):
        if self.mnemonic.name == "LTORG":
            data_acc = 0
            for data, size in self.children.values():                
                mask = 0xff if size==1 else 0xffffff
                data_acc = (data_acc << size*8) | (data & mask)
            return data_acc
        
        if self.mnemonic.name == "ORG":
            code.PC = self.mnemonic.expr[0] #is this good enough? int?
            

    def __len__(self):
        if self.mnemonic.name == "LTORG":# or "END":
            l = 0
            for child in self.children.values():
                l += child[1]
            return l
        else: return 0


class Storage(Node):
    #BYTE; WORD; RESB; RESW
    def __len__(self):
        mnem = self.mnemonic.name
        if mnem == "BYTE": return 1
        elif mnem == "WORD": return 3
        elif mnem == "RESB": return 1*self.mnemonic.n
        elif mnem == "RESW": return 3*self.mnemonic.n
    
    def emit_code(self, code):
        if self.mnemonic.name == "BYTE":
            return self.mnemonic.d & 0xff
        elif self.mnemonic.name == "WORD":
            return self.mnemonic.d & 0xffffff
        else:
            return 0 #the calling method should make sure of the length reserv.

    def emit_text(self, code):
        if self.mnemonic.name == "BYTE" or self.mnemonic.name == "WORD":
            return super().emit_text(code)
        else: return None