;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu 
; 
; Lab: lab 9, ex 2
; Lab section: 023
; TA: Shirin
; 
;=================================================

; test harness
.orig x3000
LEA R0, prompt
PUTS
GETC
OUT

LD R6, COUNT_ONES_PTR
JSRR R6

ADD R2, R0, #0
LD R0, newline
OUT

LEA R0, NUMBERS_MESSAGE
PUTS

ADD R0, R2, #0
OUT

LEA R0, IS_MESSAGE
PUTS

ADD R0, R1, #0
ADD R0, R0, #12
ADD R0, R0, #12
ADD R0, R0, #12
ADD R0, R0, #12
OUT
				 
halt
;-----------------------------------------------------------------------------------------------
; test harness local data:

prompt .STRINGZ "Please input a SINGLE character:\n"
newline .fill x0A
NUMBERS_MESSAGE .STRINGZ "The number of 1's in '"
IS_MESSAGE .STRINGZ "' is: "
COUNT_ONES_PTR .FILL x3200


;===============================================================================================
.end

; subroutines:

;------------------------------------------------------------------------------------------
; Subroutine: SUB_COUNT_ONES (Be sure to fill details in below)
;
; Parameter (R):  
; Return Value: 
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

LD R2, DEC_8
AND R1, R1, x0
AND R3, R3, x0
ADD R3, R3, #1

LOOP

	LD R0, BACKUP_R0_3200
	AND R0, R0, R3
	BRnz MOVE 
	ADD R1, R1, #1
	
	MOVE
	ADD R3, R3, R3
	ADD R2, R2, #-1
	BRp LOOP
	
END_LOOP

LD R0, BACKUP_R0_3200
LD R2, BACKUP_R2_3200
LD R3, BACKUP_R3_3200
LD R4, BACKUP_R4_3200
LD R5, BACKUP_R5_3200
LD R6, BACKUP_R6_3200
LD R7, BACKUP_R7_3200				 

ret
;-----------------------------------------------------------------------------------------------
; SUB_COUNT_ONES local data
BACKUP_R0_3200 .BLKW #1
BACKUP_R1_3200 .BLKW #1
BACKUP_R2_3200 .BLKW #1
BACKUP_R3_3200 .BLKW #1
BACKUP_R4_3200 .BLKW #1
BACKUP_R5_3200 .BLKW #1
BACKUP_R6_3200 .BLKW #1
BACKUP_R7_3200 .BLKW #1

DEC_8 .FILL #8
.end

