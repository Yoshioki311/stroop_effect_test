                .global display_score

display_score:  
                PUSH {LR}
                B    DIVIDE

                LDR  R2, =PATTERN
                LDRB R2, [R2, +R0]
                MOV  R3, R2

                LDR  R2, =PATTERN
                LDRB R2, [R2, +R1]
                LSL  R2, #8
                ORR  R3, R2

                LDR  R1, =#0xFF200030
                STR  R3, [R1]

                POP  {PC}

// Subroutine DIVIDE
// Input: R0
// Output: Quotient in R1, Remainder in R0
DIVIDE:         MOV  R2, #0
CONT:           CMP  R0, #10
                BLT  DIV_END
                SUB  R0, #10
                ADD  R2, #1
                B    CONT
DIV_END:        MOV  R1, R2
                MOV  PC, LR

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