prog  START  0
      LDX    #1
      LDS    #5
      JSUB   poly
halt  J      halt
.-------------------------.
poly   LDA    #5
      SUBR   X,A .A je koeficient
      STA    k

      LDT    in . nalozimo tocko ki jo racunamo
      STX    i  . shranimo indeks
      LDX    #0 . nastavimo indeks na 0
      JSUB   exp
      LDX    i  . spet nastavimo nazaj
      LDA    k

      MULR   A,T
      STT    temp
      ADDR   T,S
      STS    st

      TIX    #5
      JLT    poly
      LDL    #halt
      RSUB   
.-------------------------.
exp   TIX    i
      JEQ    end
      LDA    in
      MULR   A,T
      JLT    exp
end   RSUB
.-------------------------.
in    WORD   2 
i     RESW   1
st    RESW   1
temp  RESW   1
k     RESW   1

. ideja:
. recimo, da vzamem X za indeks
. vzamem A koeficient
. vzamem T za tocko
. vzamem S za sestevek
. TIX = poveca X za ena in ga primerja z nečim
