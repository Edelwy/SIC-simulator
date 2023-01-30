from Tables import *

#we could pass data as self.tokens = tokens if we needed
class AssemblyError(Exception):
    pass

class TokenizerError(AssemblyError):
    def __init__(self, tokens):
        self.message = f"-> {tokens} is invalid syntax"

#TODO: clean up these secondary errors with no constructor to print better

class ParsingError(AssemblyError):
    def __init__(self):
        self.message = "-> unknown"

class DuplicateLabelError(ParsingError):
    def __init__(self, label):
        self.message = f"-> label \"{label}\" already defined"

class UndefinedSymbolError(ParsingError):
    def __init__(self, mnemonic, symbols, symbol):
        self.message = f"-> mnemonic {mnemonic} has undefined symbol \"{symbol}\""

class NumOperandsError(ParsingError):
    def __init__(self, mnemonic, format, passed):
        expected = num_args[format]
        form = str(format).split(".")[1]
        self.message = f"-> mnemonic {mnemonic} of format {str(form)} takes {expected} operands but got {passed}"
        
class DuplicateDirectiveError(ParsingError):
    def __init__(self, d):
        self.message = f"-> forbidden to use \"{d}\" twice"

class MissingDirectiveError(ParsingError):
    def __init__(self, d):
        self.message = f"-> program is missing directive \"{d}\""

class InvalidLabelError(ParsingError):
    def __init__(self, label):
        self.message = f"-> label {label} is invalid"

class OperandValueError(ParsingError):
    def __init__(self, operand):
        self.message = f"-> operand {operand} is not suitable"

class AssemblySyntaxError(AssemblyError):
    #TODO: rename to AssemblyError (not syntax)
    "Raised when code <line> on <line_number> is not syntax ok"
    def __init__(self, line, line_number, reason):
        if line.endswith("\n"): line = line[:-1]
        line = line.lstrip()
        self.message = f"\nError on line {line_number+1}: \"{line}\": "
        #FUJ JE TO
        if reason:
            self.message += reason.message
        super().__init__(self.message)