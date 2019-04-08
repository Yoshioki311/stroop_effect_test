#include <stdlib.h>
#include <time.h>
#include "address_map_arm.h"

/*------------------Global variables------------------*/
// // Variables to be written by interrupt service routines
// volatile int key_dir = 0;
// Variables for VGA display
volatile int pixel_buffer_start;
volatile char * char_buffer_ptr = (char *)FPGA_CHAR_BASE;
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
void draw_text(int x, int y, char *text_ptr);
void clean_text(void);
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
    // config_KEYs();
    // enable interrupts
    enable_A9_interrupts();
    /*----------------------------------------------------*/

    volatile int * pixel_ctrl_ptr = (int *)PIXEL_BUF_CTRL_BASE;
    volatile int * interval_timer_ptr = (int *)TIMER_BASE;
    volatile int * key_ptr = (int *)KEY_BASE;
    pixel_buffer_start = *pixel_ctrl_ptr;

    int game_start = 0;
    int score = 0;
    int choice[4] = {0, 1, 2, 3};
    draw_title_page();
    display_score(0);

    while(1) {
        if (state == 0) {                   // Game paused
            clean_text();                   // Clear the text buffer
            if (game_start == 1) {
                clear_screen();             // Clear the screen
                char score_0 = score % 10;
                char score_1 = score / 10;
                char score_str[10] = {'s', 'c', 'o', 'r', 'e', ':', ' ', ' ', ' ', '\0'};
                score_str[7] = '0' + score_1;
                score_str[8] = '0' + score_0;
                clean_text();
                draw_text(34, 20, score_str);
                char sentence[] = {'P', 'r', 'e', 's', 's', ' ', 'a', 'n', 'y', ' ', 'K', 'E',
                                   'Y', ' ', 't', 'o', ' ', 'r', 'e', 's', 't', 'a', 'r', 't', '\0'};
                draw_text(27, 30, sentence);
            }

            int pressed = *(key_ptr + 3);   // Read the edge capture register
            while (pressed == 0)            // Wait until key being pressed
                pressed = *(key_ptr + 3);
            *(key_ptr + 3) = pressed;       // Reset the edge capture register
            *(interval_timer_ptr + 1) = 5;  // Start the timer
            score = 0;                      // Reset the score
            display_score(score);
            state = 1;                      // Set the state to be 1 (on)
            clear_screen();                 // Clear the screen
        }
        else if (state == 1) {              // Game on
            clean_text();                   // Clear the text buffer
            game_start = 1;                 // Not returning to the titlepage anymore
            int rand_index = rand() % 12;
            draw_word(rand_index);
            shuffle(choice);                // Shuffle the array for choices
            draw_choice(choice);

            if (state == 0) continue;       // Check if interrupt happened

            int pressed = *(key_ptr + 3);   // Read the edge capture register
            while (pressed == 0) {          // Wait until key being pressed
                pressed = *(key_ptr + 3);
                if (state == 0) break;      // Check if interrupt happened
            }
            if (state == 0) continue;       // Check if interrupt happened
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
