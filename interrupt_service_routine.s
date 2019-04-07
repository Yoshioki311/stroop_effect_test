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

                MOV      PC, LR
