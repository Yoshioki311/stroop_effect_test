#include <stdlib.h>
#include <time.h>
#include "address_map_arm.h"

/*------------------Global variables------------------*/
// Variables for VGA display
volatile int pixel_buffer_start;
volatile char * char_buffer_ptr = (char *)FPGA_CHAR_BASE;
// Variable for recording time left for one try of the game
volatile int time_left = 3000;
// Variable for recording game state
volatile int state = 0;
// Variable for determining if key has been pressed
volatile int key_pressed = 0;
// Variable for recording which key has been pressed
volatile int key = 0;
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
void draw_choice(int * choice);
void draw_text(int x, int y, char *text_ptr);
void clean_text(void);
// Utility functions
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

    /*----------Declare pointers to ARM address-----------*/
    volatile int * pixel_ctrl_ptr = (int *)PIXEL_BUF_CTRL_BASE;
    volatile int * interval_timer_ptr = (int *)TIMER_BASE;
    volatile int * lower_hex_ptr = (int *)HEX3_HEX0_BASE;
    pixel_buffer_start = *pixel_ctrl_ptr;
    /*----------------------------------------------------*/

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
            
            while (key_pressed == 0)        // Idle when key not pressed
                ;
            key_pressed = 0;                // Reset key_pressed flag
            *lower_hex_ptr = 0x4F3F3F3F;    // HEX3-0 shows 30:00
            *(interval_timer_ptr + 1) = 7;  // STOP = 0; START = 1; CONT = 1; ITO = 1
            score = 0;                      // Reset the score
            display_score(score);
            clear_screen();                 // Clear the screen
        }
        else if (state == 1) {              // Game on
            clean_text();                   // Clear the text buffer
            game_start = 1;                 // Not returning to the titlepage anymore
            int rand_index = rand() % 12;
            draw_word(rand_index);
            shuffle(choice);                // Shuffle the array for choices
            draw_choice(choice);

            while (key_pressed == 0 && state != 0) 
                ;
            key_pressed = 0;                // Reset key_pressed flag 
            if (state == 0) continue;

            if (choice[key] == rand_index % 4)
                score++;
            display_score(score);
        }
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
