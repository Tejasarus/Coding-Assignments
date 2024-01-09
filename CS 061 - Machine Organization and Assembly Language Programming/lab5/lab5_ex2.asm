;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 5, ex 2
; Lab section: 023
; TA: Shirin
; 
;=================================================
.orig x3000

LD R5, READER_PTR
JSRR R5
	
HALT

READER_PTR		.FILL	x3400	
.end

;subroutine

.orig x3400

ST R7, BACKUP_R7_3400
ST R6, BACKUP_R6_3400
ST R5, BACKUP_R5_3400
ST R4, BACKUP_R4_3400
ST R3, BACKUP_R3_3400
ST R1, BACKUP_R1_3400
ST R0, BACKUP_R0_3400


WHILE
	LD R6, DEC_15
	LD R5, HEX
	NOT R5, R5
	ADD R5, R5, #1
	GETC
	OUT
LOOP   
    GETC
    OUT
    
IF
	ADD R1, R5, R0 ;;if its a zero, go to num_zero, else go to num_one
	BRz NUM_ZERO
    BRp NUM_ONE
    
NUM_ZERO  
	ADD R2, R2, R2
	ADD R2, R2, #0
	BRzp CONT ;move on
	
NUM_ONE
    ADD R2, R2, R2	;add the powers of two
    ADD R2, R2, R1 

CONT	
    ADD R6, R6, #-1
    BRzp LOOP
    END_LOOP
    
END_WHILE  

LD R7, BACKUP_R7_3400
LD R6, BACKUP_R6_3400
LD R5, BACKUP_R5_3400
LD R4, BACKUP_R4_3400
LD R3, BACKUP_R3_3400
LD R1, BACKUP_R1_3400
LD R0, BACKUP_R0_3400

RET
	

BACKUP_R7_3400      	.BLKW		#1
BACKUP_R6_3400      	.BLKW		#1
BACKUP_R5_3400      	.BLKW		#1
BACKUP_R4_3400      	.BLKW		#1
BACKUP_R3_3400      	.BLKW		#1
BACKUP_R1_3400      	.BLKW		#1
BACKUP_R0_3400      	.BLKW		#1

DEC_15 .FILL #15	
HEX	.FILL x30
.END
