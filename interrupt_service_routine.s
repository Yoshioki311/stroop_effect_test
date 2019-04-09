                .extern time_left

                .global pushbutton_ISR

pushbutton_ISR:
                LDR      R0, =0xFF200050 // base address of the key port
                LDR      R1, [R0, #0xC]  // read the edge capture register
                STR      R1, [R0, #0xC]  // clear the interrupt

                MOV      PC, LR

                .global interval_timer_ISR

interval_timer_ISR:
                LDR      R0, =0xFF202000 // base address of the interval timer
                LDR      R1, [R0]        // read the status register
                AND      R1, #0xFFFFFFFE
                STR      R1, [R0]        // write 0 to TO to reset

                LDR      R1, =time_left  // Decrement stopwatch
                LDR      R2, [R1]
                SUB      R2, #1
                STR      R2, [R1]

                CMP      R2, #0
                BNE      DISPLAY

                MOV      R1, #0b1011     // Stop the timer
                STR      R1, [R0, #4]
                MOVW     R1, #0x4240     // lower 16 bits of count value
                STR      R1, [R0, #8]    // 100MHz * 0.01s = 1,000,000 = 0xF4240
                MOVW     R1, #0xF        // higher 16 bits of count value
                STR      R1, [R0, #12]

DISPLAY:        PUSH     {R4, LR}
                MOV      R0, R2 
                LDR      R4, =PATTERN

                BL       DIVIDE
                LDRB     R2, [R4, +R0]
                MOV      R3, R2

                MOV      R0, R1
                BL       DIVIDE
                LDRB     R2, [R4, +R0]
                LSL      R2, #8
                ORR      R3, R2

                MOV      R0, R1
                BL       DIVIDE
                LDRB     R2, [R4, +R0]
                LSL      R2, #16
                ORR      R3, R2

                LDRB     R2, [R4, +R1]
                LSL      R2, #24
                ORR      R3, R2

                LDR      R0, =0xFF200020
                STR      R3, [R0]

                POP      {R4, PC}

// Subroutine DIVIDE
// Input: R0
// Output: Quotient in R1, Remainder in R0
DIVIDE:         MOV      R2, #0
CONT:           CMP      R0, #10
                BLT      DIV_END
                SUB      R0, #10
                ADD      R2, #1
                B        CONT
DIV_END:        MOV      R1, R2
                MOV      PC, LR

PATTERN:        .byte  0x3F					//'0'
                .byte  0x06					//'1'
                .byte  0x5B					//'2'
                .byte  0x4F					//'3'
                .byte  0x66					//'4'
                .byte  0x6D					//'5'
                .byte  0x7D					//'6'
                .byte  0x07					//'7'
                .byte  0x7F					//'8'
                .byte  0x67					//'9'
                .skip  2				  	//maintain word alignment

                .end

@ interval_timer_ISR:
@                 LDR      R0, =0xFF202000 // base address of the interval timer
@                 MOV      R1, #0x9
@                 STR      R1, [R0, #4]    // stop the timer

@                 MOVW     R1, #0x5E00     // lower 16 bits of count value
@                 STR      R1, [R0, #8]    // 100MHz * 30s = 3,000,000,000 = 0xB2D05E00
@                 MOVW     R1, #0xB2D0     // higher 16 bits of count value
@                 STR      R1, [R0, #12]   // reload the timer

@                 LDR      R1, [R0]        // read the status register
@                 AND      R1, #0xFFFFFFFE
@                 STR      R1, [R0]        // write 0 to TO to reset

@                 LDR      R0, =state
@                 LDR      R1, [R0]
@                 CMP      R1, #1
@                 BNE      END

@                 MOV      R1, #0
@                 STR      R1, [R0]

@ END:            MOV      PC, LR
