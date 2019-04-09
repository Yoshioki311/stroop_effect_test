                .extern time_left
                .extern state
                .extern key_pressed
                .extern key

                .global pushbutton_ISR

pushbutton_ISR:
                LDR      R0, =0xFF200050 // base address of the key port
                LDR      R1, [R0, #0xC]  // read the edge capture register
                STR      R1, [R0, #0xC]  // clear the interrupt

                LDR      R0, =key_pressed
                MOV      R2, #1
                STR      R2, [R0]        // set key pressed to true

                LDR      R0, =state
                LDR      R2, [R0]
                CMP      R2, #0
                BEQ      START_GAME

                LDR      R0, =key
                
                CMP      R1, #1
                MOVEQ    R3, #3

                CMP      R1, #2
                MOVEQ    R3, #2

                CMP      R1, #4
                MOVEQ    R3, #1

                CMP      R1, #8
                MOVEQ    R3, #0

                STR      R3, [R0]

                B        END_KEY_ISR

START_GAME:     MOV      R2, #1          // set state to game started
                STR      R2, [R0]
                B        END_KEY_ISR

                LDR      R0, =time_left
                MOVW     R2, #3000
                STR      R2, [R0]

END_KEY_ISR:    MOV      PC, LR

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

                CMP      R2, #0          // time_left == 0?
                BNE      DISPLAY

                MOV      R1, #0b1011     // Stop the timer
                STR      R1, [R0, #4]
                MOVW     R1, #0x4240     // lower 16 bits of count value
                STR      R1, [R0, #8]    // 100MHz * 0.01s = 1,000,000 = 0xF4240
                MOVW     R1, #0xF        // higher 16 bits of count value
                STR      R1, [R0, #12]

                LDR      R0, =state      // set state to game paused
                MOV      R1, #0
                STR      R1, [R0]

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