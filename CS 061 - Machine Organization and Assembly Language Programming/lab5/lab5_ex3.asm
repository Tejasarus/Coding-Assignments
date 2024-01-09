;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 5, ex 3
; Lab section: 023
; TA: Shirin
; 
;=================================================
.ORIG x3000
	
LD R1, DEC_16   ;go 16 times
AND R2, R2, x0
LEA R4, USER_INPUT ;this is the 17 (b + 16) characters the user inputs (aka the "array")
	
LD R3, INVERSE_OF_B
	
IS_B ;loop that will make sure that b is inputted before moving on
	GETC
	OUT
	STR R0, R4, #0
	ADD R0, R0, R3 ;if true, move on, else output error message and reloop
	BRz MOVE_ON ;move on if it is "b"
	; The character was not B, output the error
	LD R0, newline
	OUT
	LEA R0, error_message
	PUTS
BR IS_B ;loop again
	
MOVE_ON
ADD R4, R4, #1
	
CHECKER ;check to make sure that the characters being inputted are 0s, 1s, or spaces
	ADD R2, R2, R2
		
BR ERROR  ;if its invalid, do this and call the error
		
ERROR
	LD R0, newline
	OUT
	LEA R0, error_ones_and_zeros
	PUTS
	LD R5, NEG_DEC_16
	ADD R5, R5, R1
			
	LEA R3, USER_INPUT
	KEEP ;this is to keep the 1s and 0s that have already been inputted, so the user doesnt have to type them in again
	LDR R0, R3, #0
	OUT
	ADD R3, R3, #1
	ADD R5, R5, #1
	BRnz KEEP
END_ERROR
		
GETC
OUT
		
		
LD R6, VALIDATE_PTR ;make sure the input is legit
JSRR R6
ADD R3, R3, #0
BRn ERROR   ;if it isn't call the error loop
BRz END_ERROR 


STR R0, R4, #0
ADD R4, R4, #1
ADD R0, R0, #-12
ADD R0, R0, #-12
ADD R0, R0, #-12
ADD R0, R0, #-12
ADD R2, R2, R0
ADD R1, R1, #-1
BRp CHECKER
		
END_CHECKER

LD R0, newline
OUT
HALT
	
;data
newline .FILL x0A
error_message   .STRINGZ "You have to type a b before you can begin\n"
error_ones_and_zeros .STRINGZ "You can only type 1s, 0s, and spaces\n"
USER_INPUT .BLKW #17
INVERSE_OF_B .FILL #-98
DEC_16 .FILL #16
NEG_DEC_16 .FILL #-16
VALIDATE_PTR .FILL x3400 ;make sure the input follows the rules

.end	

;======================
;VALIDATION SUBROUTINE
;======================

.ORIG x3400


VALIDATE_3400

ST R0, BACKUP_R0_3400
ST R1, BACKUP_R1_3400
ST R2, BACKUP_R2_3400
ST R3, BACKUP_R3_3400
ST R4, BACKUP_R4_3400
ST R5, BACKUP_R5_3400
ST R6, BACKUP_R6_3400
ST R7, BACKUP_R7_3400
		

IF_0_3400  ;see if char is 0     
	LD R2, NEG_0
	ADD R0, R0, R2
	BRz ITS_A_ONE_OR_ZERO
		
IF_1_3400   ;see if it is 1
	LD R0, BACKUP_R0_3400
	LD R2, NEG_1
	ADD R0, R0, R2
	BRz ITS_A_ONE_OR_ZERO
		

CHECK_SPACE_3400    ;see if it is a space, if it isnt then dont add one to the loop and keep going
	LD R0, BACKUP_R0_3400
	LD R2, NEG_SPACE
	ADD R0, R0, R2
	BRz ITS_A_SPACE
	BR NOT_A_ZERO ;jump to here
		
ITS_A_ONE_OR_ZERO
	AND R3, R3, x0
	ADD R3, R3, #1
	BR END_VALIDATING
		
ITS_A_SPACE ;make it a zero
	AND R3, R3, x0
	BR END_VALIDATING
		
NOT_A_ZERO
	AND R3, R3, x0
	ADD R3, R3, #-1 ;"reset" the loop by subtracting one
		
END_VALIDATING ;its the end (finally)

LD R0, BACKUP_R0_3400
LD R1, BACKUP_R1_3400
LD R2, BACKUP_R2_3400
LD R3, BACKUP_R3_3400
LD R4, BACKUP_R4_3400
LD R5, BACKUP_R5_3400
LD R6, BACKUP_R6_3400
LD R7, BACKUP_R7_3400
RET


BACKUP_R0_3400 	.BLKW #1
BACKUP_R1_3400 	.BLKW #1
BACKUP_R2_3400 	.BLKW #1
BACKUP_R3_3400 	.BLKW #1
BACKUP_R4_3400	.BLKW #1
BACKUP_R5_3400	.BLKW #1
BACKUP_R6_3400	.BLKW #1
BACKUP_R7_3400	.BLKW #1 

NEG_SPACE	.FILL #-32
NEG_0	    .FILL #-48
NEG_1	    .FILL #-49

.END