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
void clear_screen(void);
void draw_word (int rand_index);
// Utility functions
int decoder (int key_pressed);
void shuffle(int *array);
void display_score(int score);
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

    int score = 0;
    int choice[4] = {0, 1, 2, 3};
    draw_title_page ();

    while(1) {
        if (state == 0) {                   // Game paused
            score = 0;                      // Reset the score
            int pressed = *(key_ptr + 3);   // Read the edge capture register
            while (pressed == 0)
                pressed = *(key_ptr + 3);
            *(key_ptr + 3) = pressed;       // Reset the edge capture register
            clear_screen();                 // Clear the screen
            state = 1;                      // Set the state to be 1 (on)
        }
        else if (state == 1) {              // Game on
            int rand_index = rand() % 12;
            draw_word(rand_index);
            shuffle(choice);                // Shuffle the array for choices
            draw_choice(choice);

            int pressed = *(key_ptr + 3);   // Read the edge capture register
            while (pressed == 0)
                pressed = *(key_ptr + 3);
            *(key_ptr + 3) = pressed;       // Reset the edge capture register
            int index = 0;
            
            index = decoder(pressed);
            if (choice[index] == rand_index % 4)
                score++;
            display_score(score);
        }
    }
}

int decoder (int key_pressed) {
    int index = 0;
    switch (key_pressed) {
        case 1: index = 3;
                break;
        case 2: index = 2;
                break;
        case 4: index = 1;
                break;
        case 8: index = 0;
                break;
    }
}

void shuffle(int * choice) {
    int i = 0;
    for (i = 0; i < 3; ++i) {
        size_t j = i + rand() / (RAND_MAX / (4 - i) + 1);
        int t = choice[j];
        choice[j] = choice[i];
        choice[i] = t;
    }
}