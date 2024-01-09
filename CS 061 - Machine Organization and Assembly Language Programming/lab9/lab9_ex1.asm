;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 9, ex 1
; Lab section: 023
; TA: Shirin
; 
;=================================================

; test harness
.orig x3000

LD R6, LOAD_VALUE_PTR
JSRR R6

ADD R1, R1, #1 ;ADDING ONE TO RETURN VALUE

LD R6, PRINT_DECIMAL_PTR
JSRR R6

halt
;-----------------------------------------------------------------------------------------------
; test harness local data:

LOAD_VALUE_PTR .FILL x3200
PRINT_DECIMAL_PTR .FILL x3400

;===============================================================================================
.end

; subroutines:

;------------------------------------------------------------------------------------------
; Subroutine: SUB_LOAD_VALUE (Be sure to fill details in below)
;
; Parameter (R): None
; Return Value: R1, the hard coded (.FILL) value
;------------------------------------------------------------------------------------------
.orig x3200

ST R0, BACKUP_R0_3200
ST R1, BACKUP_R1_3200
ST R2, BACKUP_R2_3200
ST R3, BACKUP_R3_3200
ST R4, BACKUP_R4_3200
ST R5, BACKUP_R5_3200
ST R6, BACKUP_R6_3200
ST R7, BACKUP_R7_3200
		
LD R1, NUM ;literally this is all it does =)

LD R0, BACKUP_R0_3200
LD R2, BACKUP_R2_3200
LD R3, BACKUP_R3_3200
LD R4, BACKUP_R4_3200
LD R5, BACKUP_R5_3200
LD R6, BACKUP_R6_3200
LD R7, BACKUP_R7_3200
			 
ret
;-----------------------------------------------------------------------------------------------
; SUB_LOAD_VALUE local data

BACKUP_R0_3200 .BLKW #1
BACKUP_R1_3200 .BLKW #1
BACKUP_R2_3200 .BLKW #1
BACKUP_R3_3200 .BLKW #1
BACKUP_R4_3200 .BLKW #1
BACKUP_R5_3200 .BLKW #1
BACKUP_R6_3200 .BLKW #1
BACKUP_R7_3200 .BLKW #1 
	
NUM .FILL #00103
.end

;===============================================================================================


;------------------------------------------------------------------------------------------
; Subroutine: SUB_PRINT_DECIMAL (Be sure to fill details in below)
;
; Parameter (R):R1
; Return Value: none
;------------------------------------------------------------------------------------------
.orig x3400
				 
ST R0, BACKUP_R0_3400
ST R1, BACKUP_R1_3400
ST R2, BACKUP_R2_3400
ST R3, BACKUP_R3_3400
ST R4, BACKUP_R4_3400
ST R5, BACKUP_R5_3400
ST R6, BACKUP_R6_3400
ST R7, BACKUP_R7_3400
		
;Check if the inputted num (parameter) is negative
LD R0, IS_NEG
LD R2, BACKUP_R1_3400
AND R1, R1, R0 ;check to see if negative (0 is pos, 1 is neg)
BRz NO_TWOS_COMP ;if it is negative, print a "-", change the neg num to pos (2s comp) and move on
		
LD R0, NEG_SIGN ;print neg sign
OUT
NOT R2, R2 ;twos comp
ADD R2, R2, #1
		
NO_TWOS_COMP 
ADD R1, R2, #0
AND R3, R3, x0 
		
;Aight from here on out here's the plan: (this is me writing out my algorithm)
;Start @ 10000, and go down by powers of 10 to 1
;Load R4 with the negative of whatever power of 10 we're on
;ADD R4 with R1
;check if the result is negative. If it is negative, that means that we have counted the amount "powers of that specific 10" there are.
;if the result is not negative, add one to R2 and R3, which just adds one to the whatever power of 10 we are on and loop again
;ok now that your out of the loop, put whatever value was in R1 before the addition that made it negative back into R1
;check to see if r2 (the counter) is zero, because if it is, that means that there are no digits in that power (if that makes any sense) and just go to the next power of 10
;if R2 is greater than 0, plop it into r0, convert it, and output it
;go to the next 10s place and rinse and repeat =)

;10,0000 PLACE
LD R4, DEC_NEG_10000
AND R2, R2, x0
TENK_LOOP
	ADD R1, R1, R4
	BRn END_TENK_LOOP
	ADD R2, R2, #1
	ADD R3, R3, #1
	BR TENK_LOOP
END_TENK_LOOP

NOT R4, R4
ADD R4, R4, #1
ADD R1, R1, R4
		
ADD R2, R2, #0
BRz GO_TO_THOUSANDS_PLACE
		
ADD R0, R2, #0
ADD R0, R0, #12
ADD R0, R0, #12
ADD R0, R0, #12
ADD R0, R0, #12
OUT

;1,000 PLACE
GO_TO_THOUSANDS_PLACE
LD R4, DEC_NEG_1000
AND R2, R2, x0
ONEK_LOOP
	ADD R1, R1, R4
	BRn END_ONEK_LOOP
	ADD R2, R2, #1
	ADD R3, R3, #1
	BR ONEK_LOOP
END_ONEK_LOOP

NOT R4, R4
ADD R4, R4, #1
ADD R1, R1, R4
		
ADD R2, R2, #0
BRp PRINT_ONEK

ADD R3, R3, #0
BRp PRINT_ONEK
BR END_PRINT_ONEK
		
PRINT_ONEK
	ADD R0, R2, #0
	ADD R0, R0, #12
	ADD R0, R0, #12
	ADD R0, R0, #12
	ADD R0, R0, #12
	OUT
END_PRINT_ONEK
		
;100 PLACE
LD R4, DEC_NEG_100
AND R2, R2, x0
HUNDRED_LOOP
	ADD R1, R1, R4
	BRn END_HUNDRED_LOOP
	ADD R2, R2, #1
	ADD R3, R3, #1
	BR HUNDRED_LOOP
END_HUNDRED_LOOP

NOT R4, R4
ADD R4, R4, #1
ADD R1, R1, R4
		
ADD R2, R2, #0
BRp PRINT_HUNDRED

ADD R3, R3, #0
BRp PRINT_HUNDRED
BR END_PRINT_HUNDRED
		
PRINT_HUNDRED
    ADD R0, R2, #0
    ADD R0, R0, #12
    ADD R0, R0, #12
    ADD R0, R0, #12
    ADD R0, R0, #12
    OUT
END_PRINT_HUNDRED
		
;TENS PLACE
LD R4, DEC_NEG_10
AND R2, R2, x0 ;
TEN_LOOP
	ADD R1, R1, R4
	BRn END_TEN_LOOP
	ADD R2, R2, #1
	ADD R3, R3, #1
	BR TEN_LOOP
END_TEN_LOOP

NOT R4, R4
ADD R4, R4, #1
ADD R1, R1, R4
		
ADD R2, R2, #0
BRp PRINT_TEN

ADD R3, R3, #0
BRp PRINT_TEN
BR END_PRINT_TEN
		
PRINT_TEN
	ADD R0, R2, #0
	ADD R0, R0, #12
	ADD R0, R0, #12
	ADD R0, R0, #12
	ADD R0, R0, #12
	OUT
END_PRINT_TEN


;now all we have in R1 is the ones place, and we dont need to do any looping to print this, so we can just add it to r0 and out it
ADD R0, R1, #0
ADD R0, R0, #12
ADD R0, R0, #12
ADD R0, R0, #12
ADD R0, R0, #12
OUT

LD R0, BACKUP_R0_3400
LD R1, BACKUP_R1_3400
LD R2, BACKUP_R2_3400
LD R3, BACKUP_R3_3400
LD R4, BACKUP_R4_3400
LD R5, BACKUP_R5_3400
LD R6, BACKUP_R6_3400
LD R7, BACKUP_R7_3400
			 
ret
;-----------------------------------------------------------------------------------------------
; SUB_PRINT_DECIMAL local data

BACKUP_R0_3400 .BLKW #1
BACKUP_R1_3400 .BLKW #1
BACKUP_R2_3400 .BLKW #1
BACKUP_R3_3400 .BLKW #1
BACKUP_R4_3400 .BLKW #1
BACKUP_R5_3400 .BLKW #1
BACKUP_R6_3400 .BLKW #1
BACKUP_R7_3400 .BLKW #1

NEG_SIGN .FILL x2D
REMOVE_NEG_3400 .FILL x7FFF
IS_NEG .FILL x8000

DEC_NEG_10000 .FILL #-10000
DEC_NEG_1000 .FILL #-1000
DEC_NEG_100 .FILL #-100
DEC_NEG_10 .FILL #-10
.end

