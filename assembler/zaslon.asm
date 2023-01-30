. Rutine za zaslon
ScrSub      START 0
first       CLEAR A
loop1       LDCH =C'*'
            JSUB scrfill
            JSUB scrclear
            J loop1
            LDA #5
            LDS #4
            JSUB scrgoto
loop        LDCH =C'A'
            JSUB scrch
            J loop
halt        J halt
            LTORG
. ********** Screen
scrcols     EQU 80
scrrows     EQU 25
scrlen      EQU 2000
scrpos      WORD X'000000'
                    . screen goto A=row S=col
scrgoto     MUL #scrcols
            ADDR S,A
            STA scrpos
            RSUB
                    . print A=ch
scrch       LDX scrpos
            +STCH screen,X
            TIXR A
            STX scrpos
            RSUB
                    . clear/fill screen
scrclear    LDCH =C' '
scrfill     CLEAR X
            LDS #scrlen
scrclearl   +STCH screen,X
            TIXR S
            JLT scrclearl
            RSUB
            LTORG
            ORG 47104
screen      RESB 80
            LDA 1
end            END first

