;=================================================
; Name: Tejas Shah
; Email: tshah021
; 
; Lab: lab 4, ex 3
; Lab section: 023
; TA: shirin
; 
;=================================================
.orig x3000
LD R1, ARRAY
LD R3, DEC_1
STR R3, R1, #0
LD R4, DEC_9

WHILE
ADD R4, R4, #0
	
ADD R3, R3, R3
ADD R1, R1, #1
STR R3, R1, #0
	
ADD R4, R4, #-1
	
BRp WHILE
END_WHILE

HALT

DEC_1	.FILL	#1
ARRAY	.FILL	x4000	
DEC_9	.FILL	#9
.end

.orig x4000
.BLKW #10
.end