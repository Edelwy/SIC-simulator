# SIMULATOR: SIC/XE
## REGISTERS:
- there are **9 registers** 
- `get_value`: returns the value 
- `set_value`: sets the value 
- **indexing**: the registers are labeled with indexes from 0 to 8.
	- `registrs[i]` gives you the register at index `i`
	- note: the elements of the `registrs` array are pointers to said objects,
it is important that we use references to the registers we need. 
***example**: `Register &tmp = *registrs[i]`*

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