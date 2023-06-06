.ORIG x3000    ; Start of the program

    ; Set the initial values of R1 and R2
    LD R1, VALUE1
    LD R2, VALUE2

    ; Compare R1 and R2
    ADD R3, R1, #-1  ; Subtract 1 from R1 to get a negative value if R1 < R2
    BRn ELSE        ; If the result is negative (R1 > R2), branch to ELSE

    ; R1 > R2
    ADD R4, R1, R0  ; Move the value of R1 to R4 (or store it in memory)
    BR DONE         ; Branch to DONE

ELSE:
    ; R1 <= R2
    ADD R4, R2, R0  ; Move the value of R2 to R4 (or store it in memory)

DONE:
    ; Print the result
    LD R0, RESULT   ; Load the value of R4 into R0

    HALT

; Data section
VALUE1: .FILL 10     ; First value (change as needed)
VALUE2: .FILL -2     ; Second value (change as needed)
RESULT: .STRINGZ "" ; Storage for the result (displayed using PUTS)

.END             ; End of the program