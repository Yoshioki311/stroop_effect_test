                .global config_KEYs

config_KEYs:    
                LDR      R0, =0xFF200058 // interrupt mask register for keys
                LDR      R1, [R0]        // fetch current bits
                ORR      R1, #0x0000000F // enable interrupts
                STR      R1, [R0]        // store bits back
                BX       LR

                .global config_interval_timer

config_interval_timer:
                LDR      R0, =0xFF202000 // base address of interval timer

                MOVW     R1, #0x4240     // lower 16 bits of count value
                STR      R1, [R0, #8]    // 100MHz * 0.01s = 1,000,000 = 0xF4240
                MOVW     R1, #0xF        // higher 16 bits of count value
                STR      R1, [R0, #12]

                LDR      R1, [R0, #4]    // fetch from control register
                ORR      R1, #0b0011     // STOP = 0; START = 0; CONT = 1; ITO = 1
                STR      R1, [R0, #4]

                BX       LR