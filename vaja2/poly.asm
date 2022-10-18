prog  START  0
      LDX    #0
      LDB    #0
      LDA    #in

for   STX    i1
      LDS    #5
      STA    temp
      LDX    #1
      JSUB   poly
cmp   STS    @temp
      LDA    temp
      ADD    #3
      LDX    i1
      TIX    #3
      JLT    for            

halt  J      halt
.-------------------------.
poly  LDA    #5
      SUBR   X,A .A je koeficient
      STA    k

      LDT    @temp . nalozimo tocko ki jo racunamo
      STX    i  . shranimo indeks
      LDX    #0 . nastavimo indeks na 0
      JSUB   exp
      LDX    i  . spet nastavimo nazaj
      LDA    k

      MULR   A,T
      ADDR   T,S
      STS    st

      TIX    #5
      JLT    poly
      LDL    #cmp
      RSUB   
.-------------------------.
exp   TIX    i
      JEQ    end
      LDA    @temp
      MULR   A,T
      JLT    exp
end   RSUB
.-------------------------.
i     RESW   1
i1    RESW   1
st    RESW   1
temp  RESW   1
k     RESW   1

in    WORD   0
in2   WORD   2
in3   WORD   42

. ideja:
. recimo, da vzamem X za indeks
. vzamem A koeficient
. vzamem T za tocko
. vzamem S za sestevek
. TIX = poveca X za ena in ga primerja z nečim
