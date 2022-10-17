prog  START  0
      JSUB   a
      JSUB   b
      JSUB   c
      JSUB   d
      JSUB   e
halt  J      halt
.-------------------------.

a     LDA    x
      ADD    y
      STA    sum
      RSUB

b     LDA    x
      SUB    y
      STA    diff
      RSUB

c     LDA    x
      MUL    y
      STA    prod
      RSUB

d     LDA    x
      DIV    y
      STA    quot
      RSUB

e     LDA    quot
      MUL    y
      STA    tmp
      LDA    x
      SUB    tmp
      STA    mod
      RSUB

.-------------------------.
x     WORD   13
y     WORD   4
tmp   WORD   1
sum   RESW   1
diff  RESW   1
prod  RESW   1
quot  RESW   1
mod   RESW   1
      END    prog



