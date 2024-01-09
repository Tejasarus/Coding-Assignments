;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 6, ex 1 & 2
; Lab section: 023
; TA: Shirin
; 
;=================================================

; test harness
.orig x3000
;●	Set R4 = BASE to xA000
;●	Set R5 = MAX to xA005
;●	Set R6 = TOS to BASE = xA000 (i.e. stack starts out empty)
LD R4, BASE_PTR
LD R5, MAX_PTR
LD R6, TOS_PTR

;PUSH LOOP (to push values into an array)

AND R0, R0, x0
ADD R0, R0, #6 ;RUN LOOP 5 TIMES (STACK SHOULD BE 5 - 1), CHANGE THIS TO ABOVE FIVE TO SHOW OVERFLOW
LD R3, PUSH_PTR

LOOP

    JSRR R3
    
    ADD R0, R0, #-1
    BRp LOOP
END_LOOP

;POP LOOP (GET RID OF EVERYTHING)

AND R1, R1, x0
ADD R1, R1, #6
LD R3, POP_PTR

LOOP_TWO
    JSRR R3
    
    ADD R1, R1, #-1
    BRp LOOP_TWO
END_LOOP_TWO


LD R0, #0
LD R3, PUSH_PTR
JSRR R3

halt
;-----------------------------------------------------------------------------------------------
; test harness local data:

PUSH_PTR .FILL x3200
POP_PTR  .FILL x3400
BASE_PTR .FILL xA000 ;BASE OF STACK
MAX_PTR  .FILL xA005 ;FIVE PIECES IN THE STACK
TOS_PTR  .FILL xA000 ;TOS STANDS FOR TOP OF STACK

;===============================================================================================
.end

.orig xA000
STACK .BLKW #5

.end
; subroutines:

;------------------------------------------------------------------------------------------
; Subroutine: SUB_STACK_PUSH
; Parameter (R0): The value to push onto the stack
; Parameter (R4): BASE: A pointer to the base (one less than the lowest available
;                       address) of the stack
; Parameter (R5): MAX: The "highest" available address in the stack
; Parameter (R6): TOS (Top of Stack): A pointer to the current top of the stack
; Postcondition: The subroutine has pushed (R0) onto the stack (i.e to address TOS+1). 
;		    If the stack was already full (TOS = MAX), the subroutine has printed an
;		    overflow error message and terminated.
; Return Value: R6 ← updated TOS
;------------------------------------------------------------------------------------------
.orig x3200
				 
ST R0, BACKUP_R0_3200
;ST R1, BACKUP_R1_3200
;ST R2, BACKUP_R2_3200
;ST R3, BACKUP_R3_3200
ST R4, BACKUP_R4_3200
ST R5, BACKUP_R5_3200
ST R6, BACKUP_R6_3200
ST R7, BACKUP_R7_3200				 
				 
;========================

ADD R1, R6, #0 
NOT R1, R1
ADD R1, R1, #1
ADD R1, R1, R5 ;verify that we didnt hit the tos and if we did, error msg
BRnz ERROR

ADD R6, R6, #1 ;add one to tos
STR R0, R6, #0
BR END_ERROR

ERROR ;output overflow error
LEA R0, OVERFLOW_ERROR
PUTS
END_ERROR

;==========
LD R0, BACKUP_R0_3200
;LD R1, BACKUP_R1_3200
;LD R2, BACKUP_R2_3200
;LD R3, BACKUP_R3_3200
LD R4, BACKUP_R4_3200
LD R5, BACKUP_R5_3200
LD R7, BACKUP_R7_3200
ret
;-----------------------------------------------------------------------------------------------
; SUB_STACK_PUSH local data
BACKUP_R0_3200 .BLKW #1
BACKUP_R1_3200 .BLKW #1
BACKUP_R2_3200 .BLKW #1
BACKUP_R3_3200 .BLKW #1
BACKUP_R4_3200 .BLKW #1
BACKUP_R5_3200 .BLKW #1
BACKUP_R6_3200 .BLKW #1
BACKUP_R7_3200 .BLKW #1

OVERFLOW_ERROR .STRINGZ "OVERLOW!\n"



;===============================================================================================
.end

;------------------------------------------------------------------------------------------
; Subroutine: SUB_STACK_POP
; Parameter (R4): BASE: A pointer to the base (one less than the lowest available                      
;                       address) of the stack
; Parameter (R5): MAX: The "highest" available address in the stack
; Parameter (R6): TOS (Top of Stack): A pointer to the current top of the stack
; Postcondition: The subroutine has popped MEM[TOS] off of the stack.
;		    If the stack was already empty (TOS = BASE), the subroutine has printed
;                an underflow error message and terminated.
; Return Value: R0 ← value popped off the stack
;		   R6 ← updated TOS
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

NOT R2, R4
ADD R2, R2, #1

ADD R2, R6, R2 ;VERIFY
BRnz ERROR_MSG

LDR R0, R6, #0
ADD R6, R6, #-1 ;SUBTRACT 1 FROM TOP OF STACK

LD R2, BACKUP_R2_3400
LD R7, BACKUP_R7_3400

RET

ERROR_MSG
LEA R0, UNDERFLOW_ERROR
PUTS

LD R1, BACKUP_R1_3400
LD R2, BACKUP_R2_3400
LD R3, BACKUP_R3_3400
LD R4, BACKUP_R4_3400
LD R5, BACKUP_R5_3400
LD R7, BACKUP_R7_3400
  
  RET

;Subroutine Data
UNDERFLOW_ERROR .STRINGZ "Underflow!\n"

BACKUP_R0_3400 .BLKW #1
BACKUP_R1_3400 .BLKW #1
BACKUP_R2_3400 .BLKW #1
BACKUP_R3_3400 .BLKW #1
BACKUP_R4_3400 .BLKW #1
BACKUP_R5_3400 .BLKW #1
BACKUP_R6_3400 .BLKW #1
BACKUP_R7_3400 .BLKW #1

;===============================================================================================
.end
