MAIN       	START       	0
		JSUB		SCRFILL
		JSUB		SCRCLEAR

		LDCH		#0xDA
		STCH		COLOUR
		JSUB		SCRFILL

		LDCH		#0xAB
		STCH		COLOUR
		JSUB		SCRFILL
		JSUB		SCRCLEAR
HALT		J		HALT

.---------------------------------------------.
.---------------- FUNKCIJE -------------------.

SCRFILL		LDX		#0
FOR		LDA		SCREEN		
		ADDR		X,A
		+STA		SCRTEMP
		LDCH		COLOUR
		+STCH		@SCRTEMP

		TIX		SCRLEN
		JLT		FOR
		JEQ		FOR	
		RSUB

SCRCLEAR	LDA		#0
		STA		COLOUR
		J		SCRFILL		

.---------------------------------------------.
.------------------ EKRAN --------------------.

SCREEN		WORD        	X'00A000'
SCRCOLS		WORD		64
SCRROWS		WORD		64
SCRLEN		WORD		4096

COLOUR		BYTE		X'FF'
SCRTEMP		RESB		1