;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 8, ex 1
; Lab section: 023
; TA: Shirin
; 
;=================================================
.orig x3000

;GET STRING, THEN PRINT IT
LEA R1, ARRAY
LD R6, SUB_GET_STRING_PTR
JSRR R6

LEA R0, ARRAY
PUTS

HALT

SUB_GET_STRING_PTR .FILL x3200
ARRAY .BLKW #100

.END
;----------------------------------------------------------------------------------------------------------------
; Subroutine: SUB_GET_STRING
; Parameter (R1): The starting address of the character array
; Postcondition: The subroutine has prompted the user to input a string,
; terminated by the [ENTER] key (the "sentinel"), and has stored
; the received characters in an array of characters starting at (R1).
; the array is NULL-terminated; the sentinel character is NOT stored.
; Return Value (R5): The number of non-sentinel characters read from the user.
; R1 contains the starting address of the array unchanged.
;-----------------------------------------------------------------------------------------------------------------

.orig x3200

ST R0, BACKUP_R0_3200
ST R1, BACKUP_R1_3200
ST R2, BACKUP_R2_3200
ST R3, BACKUP_R3_3200
ST R4, BACKUP_R4_3200
ST R6, BACKUP_R6_3200
ST R7, BACKUP_R7_3200

LD R2, NEWLINE
NOT R2, R2
ADD R2, R2, #1
AND R5, R5, x0

LOOP_1_3200
    GETC
    OUT
    
    STR R0, R1, #0
    
    ADD R0,R0,R2
    BRz END_LOOP_1_3200
    
    ADD R1, R1, #1

    
    BR LOOP_1_3200

END_LOOP_1_3200

AND R0,R0, x0
STR R0, R1, #0

LD R0, BACKUP_R0_3200
LD R1, BACKUP_R1_3200
LD R2, BACKUP_R2_3200
LD R3, BACKUP_R3_3200
LD R4, BACKUP_R4_3200
LD R6, BACKUP_R6_3200
LD R7, BACKUP_R7_3200
RET

BACKUP_R0_3200 .BLKW #1
BACKUP_R1_3200 .BLKW #1
BACKUP_R2_3200 .BLKW #1
BACKUP_R3_3200 .BLKW #1
BACKUP_R4_3200 .BLKW #1
BACKUP_R5_3200 .BLKW #1
BACKUP_R6_3200 .BLKW #1
BACKUP_R7_3200 .BLKW #1
NEWLINE .FILL x0A

.END