volatile int pixel_buffer_start;
extern short TITLEPAGE [240][320];

int main(void) {
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    pixel_buffer_start = *pixel_ctrl_ptr;
    int i, j;
    for (i=0; i<240; i++)
        for (j=0; j<320; j++)
        *(short int *)(pixel_buffer_start + (j << 10) + (i << 1)) = TITLEPAGE[i][j];
}