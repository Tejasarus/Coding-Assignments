;=================================================
; Name: Tejas Shah
; Email: tshah021@ucr.edu
; 
; Lab: lab 1
; Lab section: 023 ex 1
; TA: 
; 
;=================================================
.ORIG x3000
 LEA R0, MSG_TO_PRINT

 PUTS

 HALT

 MSG_TO_PRINT .STRINGZ "Hello World!!\n"

.END