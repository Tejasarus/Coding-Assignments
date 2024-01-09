;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 8, ex 3
; Lab section: 023
; TA: Shirin
; 
;=================================================
.orig x3000

;ex 1 test
;GET STRING, THEN PRINT IT
lea r0, prompt
puts

LEA R1, ARRAY
LD R6, SUB_GET_STRING_PTR
JSRR R6

;LEA R0, ARRAY
;PUTS

;ex 2 test

;LEA R0, NEWLINE
;PUTS

LEA R0, THE_STRING ;START THE MESSAGE
PUTS

LEA R0, ARRAY
PUTS

LD R6, SUB_IS_PALINDROME_PTR ;CALL PALINDROME SUBROUTINE
JSRR R6

ADD R4, R4, #0
BRp TRUE ;IF IT IS, GO HERE

FALSE ;ELSE, GO HERE
    LEA R0, IS_FALSE
    PUTS
    BR GO_TO_END ;FINISH

TRUE
    LEA R0, IS_TRUE
    PUTS
    
GO_TO_END

HALT

SUB_GET_STRING_PTR .FILL x3200
ARRAY .BLKW #100

NEWLINE .FILL x0A
prompt .stringz "enter a string"
THE_STRING .STRINGZ "The string "
IS_TRUE .STRINGZ " IS a palindrome"
IS_FALSE .STRINGZ " IS NOT a palindrome"
SUB_IS_PALINDROME_PTR .FILL x3400

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

LD R2, NEWLINE_3200
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
    ADD R5, R5, #1
    
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
NEWLINE_3200 .FILL x0A

.END

;------------------------------------------------------------------------------------------------------------------
; Subroutine: SUB_IS_PALINDROME
; Parameter (R1): The starting address of a null-terminated string
; Parameter (R5): The number of characters in the array.
; Postcondition: The subroutine has determined whether the string at (R1) is
; a palindrome or not, and returned a flag to that effect.
; Return Value: R4 {1 if the string is a palindrome, 0 otherwise}
;------------------------------------------------------------------------------------------------------------------
.orig x3400

ST R0, BACKUP_R0_3400
ST R1, BACKUP_R1_3400
ST R2, BACKUP_R2_3400
ST R3, BACKUP_R3_3400
ST R4, BACKUP_R4_3400
ST R5, BACKUP_R5_3400
ST R6, BACKUP_R6_3400
ST R7, BACKUP_R7_3400

LD R6, SUB_TO_UPPER_PTR
JSRR R6

ADD R2, R1, R5
ADD R2, R2, #-1

WHILE_1

    ;Check to see if we hit the middle, if we did, then the string is a palindrome
    ADD R4, R2, #0
    NOT R4, R4
    ADD R4, R4, #1
    ADD R4, R1, R4
    BRzp TRUE_3400
        
    LDR R0, R1, #0
    LDR R3, R2, #0
    NOT R3, R3
    ADD R3, R3, #1
    ADD R0, R0, R3
    BRnp FALSE_3400
    
    ADD R1, R1, #1
    ADD R2, R2, #-1
    BR WHILE_1
END_WHILE_1

TRUE_3400
    AND R4, R4, x0
    ADD R4, R4, #1 ;SET R4 TO TRUE AND CALL IT A DAY
    BR GO_TO_END_3400

FALSE_3400
    AND R4, R4, x0
    
GO_TO_END_3400

LD R0, BACKUP_R0_3400
LD R1, BACKUP_R1_3400
LD R2, BACKUP_R2_3400
LD R3, BACKUP_R3_3400
LD R5, BACKUP_R5_3400
LD R6, BACKUP_R6_3400
LD R7, BACKUP_R7_3400
RET

SUB_TO_UPPER_PTR .FILL x3600

BACKUP_R0_3400 .BLKW #1
BACKUP_R1_3400 .BLKW #1
BACKUP_R2_3400 .BLKW #1
BACKUP_R3_3400 .BLKW #1
BACKUP_R4_3400 .BLKW #1
BACKUP_R5_3400 .BLKW #1
BACKUP_R6_3400 .BLKW #1
BACKUP_R7_3400 .BLKW #1 

.END

;------------------------------------------------------------------------------------------------------------------
; Subroutine: SUB_TO_UPPER
; Parameter (R1): Starting address of a null-terminated string
; Postcondition: The subroutine has converted the string to upper-case in-place
; i.e. the upper-case string has replaced the original string
; No return value, no output (but R1 still contains the array address, unchanged).
;------------------------------------------------------------------------------------------------------------------
.orig x3600

ST R0, BACKUP_R0_3600
ST R1, BACKUP_R1_3600
ST R2, BACKUP_R2_3600
ST R3, BACKUP_R3_3600
ST R4, BACKUP_R4_3600
ST R5, BACKUP_R5_3600
ST R6, BACKUP_R6_3600
ST R7, BACKUP_R7_3600

LD R2, BIT

LOOP_1_3600

    LDR R0, R1, #0
    ADD R0, R0, #0
    BRz END_LOOP_1_3600
    
    AND R0, R0, R2
    STR R0, R1, #0
    
    ADD R1, R1, #1
    
    BR LOOP_1_3600
    
END_LOOP_1_3600

LD R0, BACKUP_R0_3600
LD R1, BACKUP_R1_3600
LD R2, BACKUP_R2_3600
LD R3, BACKUP_R3_3600
LD R4, BACKUP_R4_3600
LD R5, BACKUP_R5_3600
LD R6, BACKUP_R6_3600
LD R7, BACKUP_R7_3600

RET

BIT .FILL x005F

BACKUP_R0_3600 .BLKW #1
BACKUP_R1_3600 .BLKW #1
BACKUP_R2_3600 .BLKW #1
BACKUP_R3_3600 .BLKW #1
BACKUP_R4_3600 .BLKW #1
BACKUP_R5_3600 .BLKW #1
BACKUP_R6_3600 .BLKW #1
BACKUP_R7_3600 .BLKW #1

.END
