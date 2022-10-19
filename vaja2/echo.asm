prog    START   0
        LDA	str
        JSUB	string
test1   JSUB	nl

        LDA	#87
        JSUB	char
test2   JSUB	nl

        LDA	st
        JSUB	num
test3   JSUB	nl
        
halt    J       halt
.-------------------------.

char    TD      out
        WD      out
        RSUB
.-------------------------.

nl      TD      out
        LDA	#10
        WD      out
        RSUB
.-------------------------.
. velikost registra A: 3 bajti
. velikost enega znaka 1 bajt
. v registru A je lahko string z 3 crkami
. dodati moramo /0

string  STA     temp
        TD	out
        LDCH	temp
        WD	out

        LDX	#1
        LDCH	temp,X
        WD	out

        LDX	#2
        LDCH	temp,X
        WD	out

        WD	#0
        LDA	temp

        RSUB
.-------------------------. 
. registri: S,A,X

num     STA     temp
        STA	div10
        TD	out
        LDX     #0
        LDS	#0
        LDT	#0

. for loop: shrani stevilo!
for     DIV	#10
        LDS	div10
        STA	div10
        MUL	#10
        SUBR	A,S
        LDA	#48
        ADDR	A,S
        STS	stevilo,X
        LDA	#3
        ADDR	A,X
        LDA	#1
        ADDR	A,T
        LDA	div10
        COMP	#0
        JGT     for

        LDX	#0
        LDA	#1
        SUBR	A,T
        STT	stevke

izpis   LDX	#3
        MULR	T,X
        LDA	stevilo,X
        JSUB	string
        LDX	#0
        COMPR	X,T
        JEQ	end
        LDA	#1
        SUBR	A,T
        J	izpis
        
end     LDL	#test3
        RSUB	
.-------------------------.
str     WORD    X'4D4E4F'
st	WORD    12345 . HEX: 10B

temp    RESW    1
div10   RESW    1
stevke  RESW    1
stevilo RESW    15

in      BYTE    X'00'
out     BYTE    X'01'
err     BYTE    X'02'



