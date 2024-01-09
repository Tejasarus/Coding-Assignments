;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 4, ex 1
; Lab section: 023
; TA: Shirin
; 
;=================================================
.orig x3000
LD R1, ARRAY
LD R3, DEC_0
STR R3, R1, #0

LD R4, DEC_9

DO_WHILE
ADD R3, R3, #1
ADD R1, R1, #1
STR R3, R1, #0

ADD R4, R4, #-1
BRp DO_WHILE
END_DO_WHILE

HALT

;DATA
DEC_0 .FILL #0
ARRAY .FILL x4000
DEC_9 .FILL #9

.END


.orig x4000
.BLKW #10
.END