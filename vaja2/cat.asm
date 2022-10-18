prog  START  0
      JSUB   beri
halt  J      halt

.-------------------------.
beri  TD     in
      RD     in
      STA    char
      COMP   #4
      JEQ    end
      J      pisi 

end   TD     out
      WD     #10
      RSUB

.-------------------------.
pisi  TD     out
      LDA    char
      WD     out
      J      beri

.-------------------------.
in    BYTE   X'00'
out   BYTE   X'01'
err   BYTE   X'02'

char  RESB   1  . spravimo znak :)