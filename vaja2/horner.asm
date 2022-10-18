
prog  START  0
      LDX    #1
      LDS    #0
      JSUB   poly
halt  J      halt
.-------------------------.
poly  LDT    in . nalozimo tocko ki jo racunamo
      MULR   T,S
      ADDR   X,S
      TIX    #6
      JLT    poly
      STS    in
      RSUB   
.-------------------------.
in    WORD   2

. ALGORITEM:
. S = 1 + 0*2
. S = 2 + 1*2
. S = 3 + 4*2
. S = 4 + 11*2
. S = 5 + 26*2