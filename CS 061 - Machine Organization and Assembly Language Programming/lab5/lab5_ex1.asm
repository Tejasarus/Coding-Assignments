;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 5, ex 1
; Lab section: 023
; TA: Shirin
; 
;=================================================
.orig x3000
LD R0, DEC_1_1
LD R1, counter
LD R3, ARRAY
	
	;;puts in "array"
	WHILE
		ADD R1, R1, #-1
		BRn END_WHILE
		STR R0, R3, #0
		ADD R0, R0, R0
		ADD R3, R3, #1
		BR WHILE
	END_WHILE
	
	LD R3, ARRAY
	LDR R2, R3, #6
	
	;outputs in binary
	LD R1, counter
	WHILE_TWO
		ADD R1, R1, #-1
		BRn END_WHILE_TWO
		
		LDR R0, R3, #0
		LD R6, PRINT_PTR ;call the print subroutine
		JSRR R6
		ADD R3, R3, #1
		BR WHILE_TWO
	END_WHILE_TWO
	
	HALT
	
; Local Data
	
DEC_1_1 .FILL #1
counter .FILL #10
ARRAY .FILL x4000
PRINT_PTR .FILl x3200
.end
	
;Data
	
.ORIG x4000
.BLKW #10
.end
;==================================================
.orig x3200
PRINT
ST R0, BACKUP_R0_3200
ST R1, BACKUP_R1_3200
ST R2, BACKUP_R2_3200
ST R3, BACKUP_R3_3200
ST R4, BACKUP_R4_3200
ST R5, BACKUP_R5_3200
ST R6, BACKUP_R6_3200
ST R7, BACKUP_R7_3200
;-------------------------------
;INSERT CODE STARTING FROM HERE
;--------------------------------
ADD R1, R0, #0
LD R2, DEC_4
LOOP
LD R3, DEC_4
LOOP_2
LD R0, HEX_30
LD R5, EIGHTK
AND R5, R5, R1
BRn OUTPUT_1

OUTPUT_0
OUT
BR END_OUTPUT

OUTPUT_1
ADD R0,R0,#1
OUT
END_OUTPUT

ADD R1, R1, R1
ADD R3, R3, #-1
BRp LOOP_2
ADD R2, R2, #-1
BRz ENDING
LD R0, SPACE_CHAR
OUT
BR LOOP
ENDING
LD R0, newline                      ; LD copies the value stored at the address newline into R0	            
OUT   

LD R0, BACKUP_R0_3200
LD R1, BACKUP_R1_3200
LD R2, BACKUP_R2_3200
LD R3, BACKUP_R3_3200
LD R4, BACKUP_R4_3200
LD R5, BACKUP_R5_3200
LD R6, BACKUP_R6_3200
LD R7, BACKUP_R7_3200
	
RET
;---------------	
;Data
;---------------
BACKUP_R0_3200 	.BLKW 	#1
BACKUP_R1_3200 	.BLKW 	#1
BACKUP_R2_3200 	.BLKW 	#1
BACKUP_R3_3200 	.BLKW 	#1
BACKUP_R4_3200	.BLKW 	#1
BACKUP_R5_3200	.BLKW 	#1
BACKUP_R6_3200	.BLKW 	#1
BACKUP_R7_3200	.BLKW 	#1 
HEX_30 .FILL x30
SPACE_CHAR .FILL x20
newline .FILL x0A
DEC_4 .FILL #4
EIGHTK .FILL x8000

.END
