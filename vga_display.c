extern volatile int pixel_buffer_start;
extern short TITLEPAGE [240][320];
extern short RED_CHOICE [40][60];

void draw_title_page () {
    int i = 0;
    int j = 0;
    for (i = 0; i < 240; i++)
        for (j = 0; j < 320; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = TITLEPAGE[i][j];
}