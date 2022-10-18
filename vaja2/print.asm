prog  START  0
      
      TD     out
      LDCH   #83
      WD     out
      LDCH   #73
      WD     out
      LDCH   #67
      WD     out
      LDCH   #47
      WD     out
      LDCH   #88
      WD     out
      LDCH   #69
      WD     out
      LDCH   #10
      WD     out
halt  J      halt
.-------------------------.
out   BYTE   X'AA'
err   BYTE   2