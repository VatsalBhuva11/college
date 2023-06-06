.ORIG x3000

AND R1,R1,#0 ; R1=0

ADD R1,R1,#5 ; R1=7 n=7
AND R2,R2,#0 ; R2=0
ADD R2,R2,#1 ; R2=1 f=1

FACT ; loop
AND R4,R4,#0 ; R4=0 r=0
AND R3,R3,#0 ; R3=0 
ADD R3,R3,R1 ; R3=R1 i=n

MULT ; loop
ADD R4,R4,R2 ; R4+=R2 r+=f
ADD R3,R3,#-1 ; R3-- i--

BRp MULT ; R3>0? i>0
AND R2,R2, #0 ; R2=0
ADD R2,R2,R4 ; R2=R4 f=r
ADD R1,R1,#-1 ; R1-- n--
BRp FACT ; R1>0? n>0
HALT ; CATCH FIRE

.END