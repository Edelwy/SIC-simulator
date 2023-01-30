#cilj te datoteke je zgraditi abstract syntax tree programa
"""
ZAPISKI O SIC/XE

Comment se začne s "."
Na začetku vrstice je lahko labela, ki je lahko polj. string, razen mnemonika.
Potem je mnemonik, ki mu sledijo parametri.

code in data segmenti ne obstaja. Data je lahko na zacetku, koncu, ali vmes kot hoce bit.

Vsak neprazen line je instruction ali directive.
Vse po "." je comment.
Vsak line je sestavljen iz "[label] mnemonic *[operands]"

Instructioni v F4 so isti kot F3, le da je na zacetki +.
# pred value pomeni immediate.
brez nč je preprost
@ je posredno - še za deref.
"""

from Tokenizer import tokenizer
from Parser import parser
from Tables import *
from Node import *
from Exceptions import *


class Code:
    def __init__(self, filename):
        self.filename = filename
        self.name = self.filename.split(".")[0]
        fp = open(filename)
        self.asm = fp.readlines()
        fp.close()
        self.lines = len(self.asm)
        self.tokens = None
        self.ast = None

        self.PC = 0
        self.BASE = False

        
        self.start = 0
        self.bytecode_length = 0

    def tokenize(self):
        self.tokens = tokenizer(self)
    
    def reset_PC(self):
        self.PC = 0

    #TODO: make all these line-things one-indexed instead of zero-indexed
    def tokenize(self):
        self.tokens = {}    #dict, da ohranimo line numbers for exceptions
        for line_num,line in enumerate(self.asm):
            #Če je line prazen, pojdi na naslednjega.
            if line.isspace(): continue
            try:
                line_tokens = tokenizer(line)
            except TokenizerError as e: raise AssemblySyntaxError(line,line_num,e) from e

            self.tokens[line_num] = line_tokens
                
        print("Tokenized successfully.")

    def parse(self):
        #this is sort of a first pass / left pass.
        self.ast = {}
        self.symbol_table = {}
        self.reset_PC()
        
        self.literal_table = {}
        self.literal_accumulator = 0

        self.started = False
        self.ended = False



        for line_num in range(self.lines):
            if line_num not in self.tokens: continue

            line = self.tokens[line_num]
            try:
                #parse args
                node = parser(line)
            except ParsingError as e: raise AssemblySyntaxError(self.asm[line_num], line_num, e) from e
        
            self.ast[line_num] = node

            node.enter(self)
            try:
                #add labels to symbol table
                #add literals to literals table
                #resolve (some) directives
                node.activate(self)
            except ParsingError as e:
                raise AssemblySyntaxError(self.asm[line_num], line_num, e) from e
            node.leave(self)
        if not self.started: raise MissingDirectiveError("START")
        if not self.ended: raise MissingDirectiveError("END") #TODO:myb remove
        print("First pass parsed successfully.")
    
    def resolve(self):
        self.begin()
        for line_num in range(self.lines):
            if line_num not in self.ast: continue
            node = self.ast[line_num]
            node.enter(self)
            try:
                node.resolve(self)
            except ParsingError as e:
                raise AssemblySyntaxError(self.asm[line_num], line_num, e) from e
            node.leave(self)
        #if literal table is not empty here, is problem.
        print("Symbols resolved successfully.")


    def display_symtab(self):
        for entry in self.symbol_table:
            print(f"{entry} -> {hex(self.symbol_table[entry])}")

    def display_tokens(self):
        for line in self.tokens.values():
            print(line)

    def display_ast_detailed(self):
        for node in self.ast.values():
            print(node.debug())

    def display_debug(self):
        for node in self.ast.values():
            if type(node) != type(Comment("xD")):
                print(node.detailed())

    def pretty_print(self):
        for node in self.ast.values():
            if type(node) == type(Comment("xD")):
                print(node)
            else:
                label = (node.label if node.label else "").ljust(10)
                mnemonic = node.pretty()
                print(label, mnemonic)
    #name
    #start address
    #program - tabela komand
    #symbol table:
        #dict<str, int)
        #define_symbol
        #resolve_symbol

    ###################33
    #prepare for start of visiting
    def begin(self):
        self.reset_PC()
        self.BASE = False
        #self.symbol_table = {}

    def gen_code(self):
        self.codes = {}
        self.reset_PC()
        for node in self.ast.values():
            node.enter(code)
            icode = node.emit_code(code)
            if icode != None: self.codes[self.PC] = (icode, len(node), node.mnemonic) #to keep length of code
            self.bytecode_length = code.PC
            node.leave(code)

    def emit_code_and_instr(self):
        for pc in self.codes:
            icode, codelen, mnem = self.codes[pc]
            print(hex(pc)[2:].rjust(6, '0'), hex(icode)[2:].rjust(codelen*2, '0'), mnem, sep="\t\t")

    def emit_code(self):
        acc = 0
        for pc in self.codes:
            icode, codelen, _ = self.codes[pc]
            acc = (acc << (codelen*8)) | icode
        return acc
    
    def emit_code_bytarr(self):
        hexcode = hex(self.emit_code())[2:]
        return bytes.fromhex(hexcode)

    def fw(self, num):
        return hex(num)[2:].rjust(6, '0')

    def emit_text(self):
        #first line is H. format: H<ime> <start><dolzina>
        output = ""
        header = f"H{self.name} {hex(self.start)[2:].rjust(6, '0')}{hex(self.bytecode_length)[2:].rjust(6, '0')}\n"
        output += header
        #then is T lines. format: T<PC><blok_len><codes>
        T_acc = ""
        bloklen = 0
        curr_start = 0
        first_executable = None
        self.reset_PC()
        for node in self.ast.values():
            node.enter(code)
            prevPC = self.PC
            textcode = node.emit_text(code)
            postPC = self.PC
            if prevPC != postPC:
                #an ORG happened, need to make a new row
                pass    #deal later
            if textcode != None:
                if T_acc == "": 
                    curr_start = self.PC
                    if first_executable == None: first_executable = curr_start
                T_acc += textcode
            node.leave(code)
            bloklen = len(T_acc)//2
            if bloklen >= 28 or prevPC != postPC:
                #works until some weird ltorg breaks it
                T_line = f"T{self.fw(curr_start)}{hex(bloklen)[2:].rjust(2, '0')}{T_acc}\n"
                output += T_line
                T_acc = ""
                bloklen = 0
                curr_start = self.PC
        #check if anything left to print
        if T_acc != "":
            T_line = f"T{self.fw(curr_start)}{hex(bloklen)[2:].rjust(2, '0')}{T_acc}\n"
            output += T_line
        #now just E. format: E<addr_of_first_instr>
        end = f"E{self.fw(first_executable)}\n"
        output += end
        return output




"""
    def emit_code(self):
        self.reset_PC()
        for node in self.ast.values():
            node.enter(code)
            hexchars = 2*len(node)
            hexcode = node.emit_code(code)
            if hexcode != None:
                print(hex(code.PC)[2:].rjust(6, '0'), hex(hexcode)[2:].rjust(hexchars, '0'), node.mnemonic, sep="\t\t")
                #print(hex(hexcode)[2:].rjust(hexchars, '0'), end="")
            node.leave(code)
"""     



#Mislim da ne mečemo ven komentarjev.
"""
#Vrži ven vse komentarje, ker nimajo pomena za nadaljevanje. -to bi biu ful sick challenge za napisat oneliner z list comprehensioni!
tokens_clean = []
for line in tokens:
    clean = [tok for tok in line if tok[0] != "Comment"]
    if len(clean) > 0: tokens_clean.append(clean)

"""

#PARSER - From the list of tokens, generate AST.
#Nodi v AST so podrazredi od Node, to so Comment, Instruction....

"""
code = Code("example.asm")
code.tokenize()
print("\n\n########################\n\n")
code.display_tokens()


code.parse()
print("\n\n########################\n\n")
code.display_ast_detailed()
print("\n\n########################\n\n")
code.resolve()
code.display_symtab()
print("\n\n########################\n\n")
print("Debugprint:")
print("\n\n########################\n\n")
code.display_debug()
print("\n\n########################\n\n")
print("Pretty code:")
print("\n\n########################\n\n")
code.pretty_print()
"""

code = Code("zaslon.asm")
code.tokenize() #TODO mogoce spremeni kaku hendla values
#code.display_tokens()

code.parse()
#code.display_ast_detailed()
#code.display_symtab()
code.resolve()
#code.display_debug()

#now, need to emit code.
code.gen_code()

print("\n######################\n")
bytecode = code.emit_code_bytarr()
objcode = code.emit_text()
print(objcode, sep="\n")
print("\n######################\n")
code.display_symtab()
print("\n######################\n")
code.emit_code_and_instr()