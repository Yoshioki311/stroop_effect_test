extern volatile int pixel_buffer_start;
extern short TITLEPAGE [240][320];

extern short BLUE_CHOICE [40][60];
extern short GREEN_CHOICE [40][60];
extern short RED_CHOICE [40][60];
extern short YELLOW_CHOICE [40][60];

extern short BLUE_IN_GREEN [90][160];
extern short BLUE_IN_RED [90][160];
extern short BLUE_IN_YELLOW [90][160];

extern short GREEN_IN_BLUE [90][160];
extern short GREEN_IN_RED [90][160];
extern short GREEN_IN_YELLOW [90][160];

extern short RED_IN_BLUE [90][160];
extern short RED_IN_GREEN [90][160];
extern short RED_IN_YELLOW [90][160];

extern short YELLOW_IN_BLUE [90][160];
extern short YELLOW_IN_GREEN [90][160];
extern short YELLOW_IN_RED [90][160];

void clear_screen() {
    for(int x = 0; x < 320; ++x) {
        for(int y = 0; y < 240; ++y) {
            *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = 0;
        }
    }
}

void draw_title_page () {
    int i = 0;
    int j = 0;
    for (i = 0; i < 240; i++)
        for (j = 0; j < 320; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = TITLEPAGE[i][j];
}

void draw_word (int rand_index) {
    switch (rand_index) {
        case 0: draw_blue_in_green ();
                break;
        case 1: draw_green_in_blue ();
                break;
        case 2: draw_red_in_blue ();
                break;
        case 3: draw_yellow_in_blue ();
                break;
        case 4: draw_blue_in_red ();
                break;
        case 5: draw_green_in_red ();
                break;
        case 6: draw_red_in_green ();
                break;
        case 7: draw_yellow_in_green ();
                break;
        case 8: draw_blue_in_yellow ();
                break;
        case 9: draw_green_in_yellow ();
                break;
        case 10: draw_red_in_yellow ();
                 break;
        case 11: draw_yellow_in_red ();
                 break;
    }
}

void draw_choice (int * choice) {
    switch(choice[0]) {
        case 0: draw_blue_choice(34);
                break;
        case 1: draw_green_choice(34);
                break;
        case 2: draw_red_choice(34);
                break;
        case 3: draw_yellow_choice(34);
                break;
    }
    switch(choice[1]) {
        case 0: draw_blue_choice(108);
                break;
        case 1: draw_green_choice(108);
                break;
        case 2: draw_red_choice(108);
                break;
        case 3: draw_yellow_choice(108);
                break;
    }
    switch(choice[2]) {
        case 0: draw_blue_choice(172);
                break;
        case 1: draw_green_choice(172);
                break;
        case 2: draw_red_choice(172);
                break;
        case 3: draw_yellow_choice(172);
                break;
    }
    switch(choice[3]) {
        case 0: draw_blue_choice(236);
                break;
        case 1: draw_green_choice(236);
                break;
        case 2: draw_red_choice(236);
                break;
        case 3: draw_yellow_choice(236);
                break;
    }
}

/*----------------------------- Choices --------------------------------*/
void draw_blue_choice (int x) {
    int i = 0;
    int j = 0;
    for (i = 110; i < 150; i++)
        for (j = x; j < x + 60; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = BLUE_CHOICE[i][j];
}

void draw_green_choice (int x) {
    int i = 0;
    int j = 0;
    for (i = 110; i < 150; i++)
        for (j = x; j < x + 60; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = GREEN_CHOICE[i][j];
}

void draw_red_choice (int x) {
    int i = 0;
    int j = 0;
    for (i = 110; i < 150; i++)
        for (j = x; j < x + 60; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = RED_CHOICE[i][j];
}

void draw_yellow_choice (int x) {
    int i = 0;
    int j = 0;
    for (i = 110; i < 150; i++)
        for (j = x; j < x + 60; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = YELLOW_CHOICE[i][j];
}
/*----------------------------------------------------------------------*/

/*---------------------------- Display word ----------------------------*/
void draw_blue_in_green () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = BLUE_IN_GREEN[i][j];
}

void draw_blue_in_red () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = BLUE_IN_RED[i][j];
}

void draw_blue_in_yellow () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = BLUE_IN_YELLOW[i][j];
}

void draw_green_in_blue () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = GREEN_IN_BLUE[i][j];
}

void draw_green_in_red () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = GREEN_IN_RED[i][j];
}

void draw_green_in_yellow () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = GREEN_IN_YELLOW[i][j];
}

void draw_red_in_blue () {
    int i = 0;
    int j = 0;
   for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = RED_IN_BLUE[i][j];
}

void draw_red_in_green () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = RED_IN_GREEN[i][j];
}

void draw_red_in_yellow () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = RED_IN_YELLOW[i][j];
}

void draw_yellow_in_blue () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = YELLOW_IN_BLUE[i][j];
}

void draw_yellow_in_green () {
    int i = 0;
    int j = 0;
    for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = YELLOW_IN_GREEN[i][j];
}

void draw_yellow_in_red () {
    int i = 0;
    int j = 0;
   for (i = 10; i < 100; i++)
        for (j = 80; j < 240; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = YELLOW_IN_RED[i][j];
}
/*----------------------------------------------------------------------*/