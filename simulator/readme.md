# SIMULATOR: SIC/XE

## COMPILE:
-	makefile with commands: **make**, **make clean**

## REGISTERS:
- there are **9 registers** 
- `get_value`: returns the value 
- `set_value`: sets the value 
- **indexing**: the registers are labeled with indexes from 0 to 6 and then 8 and 9.
	- `get_reg` gives you the register at index `i`
	- note: it is important that we use references to the registers we need. 
***example**: `Register &tmp = get_reg(i)`*

## RAM:
- an array of **bytes** 
- **max address** is at index 32768
- `MP`: points to the first available slot
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
- method `not_implemented` and method `invalid_code` returns:
	- 0: command for processor
	- 1: command for assembler 
	- -1: command does not exist