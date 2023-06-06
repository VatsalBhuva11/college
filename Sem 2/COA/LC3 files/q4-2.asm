.ORIG x3000


AND R2, R2, #0;

ADD R2, R2, #6;

LD R1, ASCII_ZERO    ; Load the ASCII value of '0' into R1



loop

AND R0, R0, #0;
ADD R0, R2, R1 ; Calculate the ASCII value of the current number
OUT         ; Print the current number

LD R0, SPACE

OUT



ADD R2, R2, #-1    ; Decrement n

BRp loop 


AND R2, R2, #0;

ADD R2, R0, R1; Calculate the ASCII value of the current number

OUT
HALT

ASCII_ZERO  .FILL x0030 ; ASCII value of '0'

SPACE .FILL #32

.END