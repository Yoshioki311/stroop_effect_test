#include <stdlib.h>
#include <time.h>
#include "address_map_arm.h"

/*------------------Global variables------------------*/
// // Variables to be written by interrupt service routines
// volatile int key_dir = 0;
// Variables for VGA display
volatile int pixel_buffer_start;
// Variable for reccording game state, changed by ISR
volatile int state = 0;
/*----------------------------------------------------*/

/*----------------Function declaration----------------*/
// Set up interrupts
void set_A9_IRQ_stack(void);
void config_GIC(void);
void config_interval_timer(void);
void config_KEYs(void);
void enable_A9_interrupts(void);
// VGA related functions
void draw_title_page (void);
/*----------------------------------------------------*/

int main(void) {

    /*-------------------Seeding random-------------------*/
    srand(time(NULL));
    /*----------------------------------------------------*/

    /*--------------Interrupt configuration---------------*/
    // initialize the stack pointer for IRQ mode
    set_A9_IRQ_stack();
    // configure the general interrupt controller
    config_GIC();
    // configure Altera interval timer to generate interrupts
    config_interval_timer(); 
    // configure pushbutton KEYs to generate interrupts
    config_KEYs(); 
    // enable interrupts
    enable_A9_interrupts(); 
    /*----------------------------------------------------*/

    volatile int * pixel_ctrl_ptr = (int *)PIXEL_BUF_CTRL_BASE;
    volatile int * key_ptr = (int *)KEY_BASE;
    pixel_buffer_start = *pixel_ctrl_ptr;
    draw_title_page ();
    

    // while(1) {
    //     if (state == 0) { // Game paused
    //         int pressed = *(key_ptr + 3); // Read the edge capture register
    //         while (pressed == 0)
    //             pressed = *(key_ptr + 3);
    //         *(key_ptr + 3) = pressed; // Reset the edge capture register
    //         state = 1; // Set the state to be 1 (on)
    //     }
    //     else if (state == 1) { // Game on
    //         int random_index = rand() % 12;
    //     }
    // }
}