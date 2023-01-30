prog  START  0
      LDS    x
      LDT    y

a     ADDR   T,S
      STS    #sum
      SUBR   T,S  

b     SUBR   T,S
      STS    #diff
      ADDR   T,S

c     MULR   T,S
      STS    #prod
      DIVR   T,S

d     LDA    #0
      ADDR   S,A
      DIVR   T,S
      STS    #quot
      MULR   T,S

e     SUBR   S,A
      STA    #mod
halt  J      #halt

x     WORD   13
y     WORD   4
sum   RESW   1
diff  RESW   1
prod  RESW   1
quot  RESW   1
mod   RESW   1
      END    prog