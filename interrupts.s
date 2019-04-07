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

                MOVW     R1, #0x5E00     // lower 16 bits of count value
                STR      R1, [R0, #8]    // 100MHz * 30s = 3,000,000,000 = 0xB2D05E00
                MOVW     R1, #0xB2D0     // higher 16 bits of count value
                STR      R1, [R0, #12]

                LDR      R1, [R0, #4]    // fetch from control register
                ORR      R1, #0b0011     // enable interrupt and auto reload
                STR      R1, [R0, #4]

                BX       LR