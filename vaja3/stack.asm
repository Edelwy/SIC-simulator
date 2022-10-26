.---------------------------------------------.
.----------- TESTIRANJE PROGRAMA -------------.

MAIN       	START       	0
		JSUB		STACKINIT

		LDA		#79
		STA		@STACKPTR
		JSUB		STACKPUSH

		LDA		#76
		STA		@STACKPTR
		JSUB		STACKPUSH

		LDA		#69
		STA		@STACKPTR
		JSUB		STACKPUSH

		LDA		#72
		STA		@STACKPTR
		JSUB		STACKPUSH

		JSUB		STACKPOP
		LDA		@STACKPTR
		JSUB		PRINT

		JSUB		STACKPOP
		LDA		@STACKPTR
		JSUB		PRINT

		JSUB		STACKPOP
		LDA		@STACKPTR
		JSUB		PRINT
		JSUB		PRINT

		JSUB		STACKPOP
		LDA		@STACKPTR
		JSUB		PRINT

		LDA		#10
		JSUB		PRINT

		LDA		#5
		LDT		#1
		JSUB		FACT
		JSUB		PRINT
		

HALT 		J		HALT

.---------------------------------------------.
.----------- OPERACIJE NA STACKU -------------.

STACKINIT   	STA         	REG_A . spravimo vsebino registra A
            	LDA         	#STACK . naložimo naslov kjer se zacne stack 
            	STA         	STACKPTR . shranimo stackpointer
            	LDA         	REG_A . nazaj naložimo vsebino A
            	RSUB

STACKPUSH   	STA        	REG_A . OPOMBA: na sklad pisemo rocno, tu samo povecujamo stackpointer
            	LDA         	STACKPTR 
            	ADD         	#3 . stackpointer povečamo za eno besedo
            	STA         	STACKPTR
            	LDA         	REG_A
           	RSUB

STACKPOP    	STA         	REG_A
            	LDA         	STACKPTR
            	SUB         	#3
            	STA         	STACKPTR
            	LDA         	REG_A
            	RSUB

.---------------------------------------------.
.-------------- IZPIS NA EKRAN ---------------.

PRINT		TD		OUT
		WD		OUT
		RSUB

.---------------------------------------------.
.----------------- FAKULTETA -----------------.

ROB		COMP		#1
		JGT		FACT
		
		JSUB		STACKPOP
		LDA		@STACKPTR
		JSUB		RETURN
		
FACT		STL		@STACKPTR
		JSUB		STACKPUSH

		MULR		A,T
		SUB		#1
		STT		@STACKPTR
		JSUB		STACKPUSH
		JSUB		ROB

RETURN		JSUB		STACKPOP
		LDS		@STACKPTR

		JSUB		STACKPOP
		LDT		@STACKPTR
		LDL		#0
		ADDR		S,L
		RSUB

.---------------------------------------------.
.------ PROSTOR REZERVIRAN ZA SKLAD ----------. 

STACKPTR	RESW		1
STACK		RESW		1024
REG_A        	RESW        	1

IN		BYTE		X'00'
OUT		BYTE		X'01'
ERR		BYTE		X'02'