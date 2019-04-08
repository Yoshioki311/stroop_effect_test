extern volatile int pixel_buffer_start; 
extern short title[76800];

extern short blue_choice[2400];
extern short green_choice[2400];
extern short red_choice[2400];
extern short yellow_choice[2400];

extern short blue_in_green[14400];
extern short blue_in_red[14400];
extern short blue_in_yellow[14400];
extern short green_in_blue[14400];
extern short green_in_red[14400];
extern short green_in_yellow[14400];
extern short red_in_blue[14400];
extern short red_in_green[14400];
extern short red_in_yellow[14400];
extern short yellow_in_blue[14400];
extern short yellow_in_red[14400];
extern short yellow_in_green[14400];

/*----------------Function declaration----------------*/ 
void plot_pixel(int x, int y, short int line_colour);
void clear_screen ();
void draw_title_page ();

void draw_blue_choice(int x);
void draw_green_choice(int x);
void draw_red_choice(int x);
void draw_yellow_choice(int x);
void draw_blue_in_green ();
void draw_blue_in_red ();
void draw_blue_in_yellow ();
void draw_green_in_blue ();
void draw_green_in_red ();
void draw_green_in_yellow ();
void draw_yellow_in_blue ();
void draw_yellow_in_red ();
void draw_yellow_in_green ();
/*----------------------------------------------------*/

void plot_pixel(int x, int y, short int line_colour) {
	*(short int *) (pixel_buffer_start + (y<<10)+(x<<1)) = line_colour;
}

void clear_screen() { 
	int x, y;
    for(x = 0; x < 320; ++x) { 
        for(y = 0; y < 240; ++y) { 
            *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = 0; 
        } 
    } 
} 

void draw_title_page() {
	int i, j;
	for (j = 0; j < 240; ++j) {
		for (i = 0; i < 320; ++i) {
			plot_pixel(i, j, title[j*320+i]);
		}
	}
}

/*----------------------------- Choices --------------------------------*/
void draw_blue_choice(int x) {
	int i, j;
	for (j = 110; j < 150; ++j) {
		for (i = x; i < x + 60; ++i) {
			plot_pixel(i, j, blue_choice[(j-110)*60+(i-x)]);
		}
	}
}

void draw_green_choice(int x) {
	int i, j;
	for (j = 110; j < 150; ++j) {
		for (i = x; i < x + 60; ++i) {
			plot_pixel(i, j, green_choice[(j-110)*60+(i-x)]);
		}
	}
}

void draw_red_choice(int x) {
	int i, j;
	for (j = 110; j < 150; ++j) {
		for (i = x; i < x + 60; ++i) {
			plot_pixel(i, j, red_choice[(j-110)*60+(i-x)]);
		}
	}
}

void draw_yellow_choice(int x) {
	int i, j;
	for (j = 110; j < 150; ++j) {
		for (i = x; i < x + 60; ++i) {
			plot_pixel(i, j, yellow_choice[(j-110)*60+(i-x)]);
		}
	}
}

/*----------------------------------------------------------------------*/ 
 
 
/*---------------------------- Display word ----------------------------*/ 
void draw_blue_in_green() {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, blue_in_green[(j-10)*160+(i-80)]);
		}
	}
}

void draw_blue_in_red () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, blue_in_red[(j-10)*160+(i-80)]);
		}
	}
}

void draw_blue_in_yellow () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, blue_in_yellow[(j-10)*160+(i-80)]);
		}
	}
}

void draw_green_in_blue () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, green_in_blue[(j-10)*160+(i-80)]);
		}
	}
}

void draw_green_in_red () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, green_in_red[(j-10)*160+(i-80)]);
		}
	}
}

void draw_green_in_yellow () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, green_in_yellow[(j-10)*160+(i-80)]);
		}
	}
}

void draw_red_in_blue () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, red_in_blue[(j-10)*160+(i-80)]);
		}
	}
}

void draw_red_in_green () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, red_in_green[(j-10)*160+(i-80)]);
		}
	}
}

void draw_red_in_yellow () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, red_in_yellow[(j-10)*160+(i-80)]);
		}
	}
}

void draw_yellow_in_blue () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, yellow_in_blue[(j-10)*160+(i-80)]);
		}
	}
}

void draw_yellow_in_red () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, yellow_in_red[(j-10)*160+(i-80)]);
		}
	}
}

void draw_yellow_in_green () {
	int i, j;
	for (j = 10; j < 100; ++j) {
		for (i = 80; i < 240; ++i) {
			plot_pixel(i, j, yellow_in_green[(j-10)*160+(i-80)]);
		}
	}
}

/*----------------------------------------------------------------------*/