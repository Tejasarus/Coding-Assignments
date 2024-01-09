;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 1, ex 2
; Lab section: 023
; TA: Shirin
; 
;=================================================
.ORIG x3000
    
    AND R2, R2, x0
   ; LD R2, DEC_0
    LD R3, DEC_12
    LD R4, DEC_6
    
    DO_WHILE_LOOP
        ADD R2, R2, R3
        ADD R4, R4, #-1
        BRp DO_WHILE_LOOP
    END_DO_WHILE_LOOP
    HALT
;LOCAL DATA
    DEC_0  .FILL #0
    DEC_12 .FILL #12
    DEC_6  .FILL #6

.end