volatile int pixel_buffer_start;
extern short TITLEPAGE [240][320];
extern short RED_CHOICE [40][60];

void draw_title_page ();

int main(void) {
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    pixel_buffer_start = *pixel_ctrl_ptr;
    draw_title_page ();
}

void draw_title_page () {
    for (int i = 0; i < 240; i++)
        for (int j = 0; j < 320; j++)
            *(short int *)(pixel_buffer_start + (i << 10) + (j << 1)) = TITLEPAGE[i][j];
}