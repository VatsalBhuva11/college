.ORIG x3000    ; Start of the program

    ; Load the value from memory into R1
    LD R1, VALUE

    ; Check if the value is even or odd
    AND R2, R1, #1  ; Bitwise AND with 1 to check the least significant bit
    BRz EVEN        ; If the result is zero (even), branch to EVEN

ODD:
    ; Value is odd
    LEA R0, ODD_MSG  ; Load the address of the ODD_MSG string
    PUTS            ; Display the ODD_MSG string
    BR DONE         ; Branch to DONE

EVEN:
    ; Value is even
    LEA R0, EVEN_MSG ; Load the address of the EVEN_MSG string
    PUTS            ; Display the EVEN_MSG string
    BR DONE         ; Branch to DONE

DONE:
    HALT

; Data section
VALUE: .FILL #13       ; Value to be checked (change as needed)
EVEN_MSG: .STRINGZ "EVEN"  ; Message to display for even numbers
ODD_MSG: .STRINGZ "ODD"    ; Message to display for odd numbers

.END             ; End of the program