                .extern state

                .global pushbutton_ISR

pushbutton_ISR:
                LDR      R0, =0xFF200050 // base address of the key port
                LDR      R1, [R0, #0xC]  // read the edge capture register
                STR      R1, [R0, #0xC]  // clear the interrupt

                MOV      PC, LR

                .global interval_timer_ISR

interval_timer_ISR:
                LDR      R0, =0xFF202000 // base address of the interval timer
                MOV      R1, #0x9
                STR      R1, [R0, #4]    // stop the timer

                MOVW     R1, #0x5E00     // lower 16 bits of count value
                STR      R1, [R0, #8]    // 100MHz * 30s = 3,000,000,000 = 0xB2D05E00
                MOVW     R1, #0xB2D0     // higher 16 bits of count value
                STR      R1, [R0, #12]   // reload the timer

                LDR      R1, [R0]        // read the status register
                AND      R1, #0xFFFFFFFE
                STR      R1, [R0]        // write 0 to TO to reset

                LDR      R0, =state
                LDR      R1, [R0]
                CMP      R1, #1
                BNE      END

                MOV      R1, #0
                STR      R1, [R0]

END:            MOV      PC, LR
