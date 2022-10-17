prog  START  0
      LDS    x
      LDT    y
      JSUB   a
      JSUB   b
      JSUB   c
      JSUB   d
      JSUB   e
halt  J      halt
.-------------------------.

a     ADDR   T,S
      STS    sum
      SUBR   T,S
      RSUB   

b     SUBR   T,S
      STS    diff
      ADDR   T,S
      RSUB

c     MULR   T,S
      STS    prod
      DIVR   T,S
      RSUB

d     LDA    #0
      ADDR   S,A
      DIVR   T,S
      STS    quot
      MULR   T,S
      RSUB

e     SUBR   S,A
      STA    mod
      RSUB

.--------------------------.
x     WORD   13
y     WORD   4
sum   RESW   1
diff  RESW   1
prod  RESW   1
quot  RESW   1
mod   RESW   1
      END    prog