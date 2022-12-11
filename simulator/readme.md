# SIMULATOR: SIC/XE

## COMPILE:
-	makefile with commands: **make**, **make clean**

## REGISTERS:
- there are **9 registers** 
- `get_value`: returns the value 
- `set_value`: sets the value 
- **indexing**: the registers are labeled with indexes from 0 to 6 and then 8 and 9.
	- `reg` gives you the register at index `i`
	- note: it is important that we use references to the registers we need if creating one:
 ***example**: `Register &tmp = reg(i)`*

## RAM:
- an array of **bytes** 
- **max address** is at index 32768
- `get_address`: returns the index of the first avalable slot
- `get_byte` and `get_word`:  returns **byte** or **word** on said address
-  `set_byte` and `set_word`:  stores **byte** or **word** on said address

## DEVICES:
- **max number** of devices is: 255
- index **0**: `STDIN`
- index **1**: `STDOUT`
- index **2**: `STDERR`
- other numers are text files marked as: `dev_number`
- **read only** device: `InputDev`
- **write only** device `OutputDev`
-  inicialization with a number of the device we want
 ***example**: `InputDev  std_in(n);`*

## OPCODE:
- opcode of all commands is defined in this simulator
- not all of the commands are implemented **!**
- the ones that are not are marked with `// X`
- function `not_implemented`:
	- 0: command for processor
	- 1: command for assembler 
	- -1: command does not exist
- function `valid_code` throws an error
- functions `opcode_name` and `directive_name` are given an int and return the name of the instruction


## FETCH AND EXECUTE:
- 3 classes: **Executer**, **Execute** and **Command**
- **Command**: has the implementation of instructions
- **Executor** calculates the following info: 
	- fetch and execute
	- parsing the given instruction 
	- flags: `n i x b p e` bits
	- offset for `FSIC`, `F3`, `F4` or registers for `F2`
	- PC relative, Base relative or absolute adressing
	- type of instruction
	- returns 0 - 4 for the instruction type
- **Executor**:
	- simple, immediate and indirect adressing
	- which instruction is it

## RUNNING THE PROGRAM AND CPU:
- **CPU** has functions `get_speed` and `set_speed`
- default is 10 milliseconds per instruction
- `run` function runs a certain task: not necessarily one clock tick
- starting the program with `start`: the parameter is the number of steps, 0 means no stops, 1 is a step by step execution ect.

## LOADER:
- **Reader** class for parsing the file
- loading the program into the memory 
- we have to provide the **name**:  
***example**: `PROGRAM NAME: ./test/cat.obj`*
