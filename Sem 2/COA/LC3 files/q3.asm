.ORIG x3000

AND R5, R5, #0
AND R6, R6, #0
AND R7, R7, #0
ADD R5, R5, #1
ADD R7, R7, #-1

;loading from memory
LD R0, A
LD R1, B

BGE R0, R1, 



;fill memory locations A and B with 12 and 13
A .fill 12
B .fill 13

HALT
.END