from Tables import *
from Exceptions import TokenizerError


def syntax_check(line):
    #namenjeno prvemu passu slabe sintakse, npr. line "BYTE BYTE BYTE".
    #Tu ni treba še ločevati po vrstah instructionov (f1, f2...) in čekirat pravilno št. operandov.
    #basically mora čekirat samo [label] mnemonic *[value] [comment] | comment
    #0 - start. must read comment, label, or mnemonic.
    #1 - last read the one label. must read mnemonic.
    #[2] - last read the one mnemonic, or a value. can read value(s) or comment.
    #[3] - read the one comment. cannot read any more.
    state = 0
    end_states = [2, 3]
    for token in line:
        type = token[0]
        if type == "Label":
            if state==0: state = 1
            else: return False
        elif type == "Mnemonic":
            if state==0 or state==1: state = 2
            else: return False
        elif type == "Value":
            if state==2: state = 2
            else: return False
        elif type == "Comment":
            if state==0 or state==2: state = 3
            else: return False
        else: 
            #To stanje tu naj ne bi bilo mogoče. type je gotovo eden od Label, Mnemonic, Value, Comment.
            pass
            #raise ValueError("Unknown token type:", type, "\nList of tokens was somehow corrupted.")
    
    #Ko smo prebrali cel line, moramo biti v enemu od končnih stanj 2 ali 3.
    if state not in end_states:
        return False
    return True

#TOKENIZER. INPUT: nonempty line, OUTPUT: list of tokens in the line
def tokenizer(line):

    line_list = line.split()
    line_tokenized = []
    
    for i, word in enumerate(line_list):
        #Če se token začne s piko, je vse, kar sledi, comment.
        if word.startswith("."):
            value = line[line.find(word):-1] #-1, da spusti newline.
            line_tokenized.append(("Comment", value))
            #Pojdi na nasledn line, ker je comment zadnja stvar ki se zgodi.
            break

        #Če token pripada reserved ukaz keywordom, ali pa directive keywordom, je mnemonic.
        elif word in instructions or word in directives:
            line_tokenized.append(("Mnemonic", word))

        #Za LDA obstaja tudi +LDA. To velja za vse instructions tipa F3m.
        elif word.startswith("+") and word[1:] in mnemonics and mnemonics[word[1:]] == Macro.F3m:
            line_tokenized.append(("Mnemonic", word))

        else:
            #ločevanje, če si bomo kasneje morda želeli ločevati med string / numeric data
            if i == 0 and word.isalnum():
                line_tokenized.append(("Label", word))
            else:
                line_tokenized.append(("Value", word))
        #TODO later:
        # list of reserved words
        # dovoliti le lowercase ascii labele(?)
        # kategorija za invalid input(?)
        # ker trenutno je npr. +RSUB valid labela

        #currently, only do syntax check
    if syntax_check(line_tokenized):
        return line_tokenized
    else:
        raise TokenizerError(line_tokenized)
            