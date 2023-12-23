//------------------------------------------
// Program: Fire
// Purpose: Creates the illusion of fire on one's screen...

#include <stdlib.h>
#include <conio.h>
#include <iostream.h>
#include "mygraph.hpp"

#define 	MAX_FIRES  200

void main()
{
	int count,x,y,avg,cnt = 0, x_fires[MAX_FIRES], ran_size = 70, speed = 3;
	int i,j,x_size = 2, y_size = 2, sig_ep = 0;
	unsigned char done, key, clean_screen;

	SetVidMode();
	LoadPalette("fire.pal");

	ClearScreen( 0 );

	for(count = 0; count < MAX_FIRES; count++) x_fires[count] = getrandom(1, 319);

	while(key != 'x') {
		key = 0;
		if(kbhit()) key = getch();

		if( key != 0 ) {

			if( key == 'r' ) LoadPalette("redfire.pal");
			if( key == 'b' ) LoadPalette("blufire.pal");
			if( key == 'p' ) LoadPalette("purfire.pal");

			if( (key == '+') && (ran_size <= MAX_FIRES) ) ran_size++;
			if( (key == '-') && (ran_size >= 1        ) ) ran_size--;


			if( (key == '1') && (x_size > 1) && (y_size > 1) ) {
				x_size--;
				y_size--;
			}
			if( (key == '2') && (x_size <= 10) && (y_size <= 10) ) {
				x_size++;
				y_size++;
			}

			if( (key == '4') && (cnt <= 10 ) ) speed++;
			if( (key == '3') && (cnt >  1  ) ) speed--;

			if( (key == 'c') ) clean_screen = 1;

			if( key == 'd' ) sig_ep = 1;
			if( key == 's' ) sig_ep = 0;

			if( key == 'd' ) {
				for( i = 0; i < x_size + 5; i++ ) {
					LineTo( 40, 150 + i,  60, 150 + i, 255 );
					LineTo( 40, 150 + i,  60, 170 + i, 255 );
					LineTo( 60, 170 + i,  40, 190 + i, 255 );
					LineTo( 40, 190 + i,  60, 190 + i, 255 );
				}
			}
		}

		if( cnt > speed ) {
			for(count = 0; count < ran_size; count++) SetPixel(x_fires[count], 199, 32);
			for(count = 0; count < ran_size; count++) {
				x_fires[count] += getrandom(-1,1);

				if(x_fires[count] > 319) x_fires[count] = getrandom(20, 140);
				if(x_fires[count] < 1  ) x_fires[count] = getrandom(180, 300);
				SetPixel( x_fires[count], 199, getrandom(250, 255) );
			}
			cnt = 0;
			if( getrandom(0, 100) > 99 ) clean_screen = 1;
		}

		cnt++;

		for(y = 199 - y_size; y >= 0; y -= y_size) {
			done = 1;
			for( x = x_size; x < 319 - x_size; x += x_size) {
				avg = 0;
				avg += GetPixel( x + x_size, y + y_size );
				avg += GetPixel( x + x_size, y          );
				avg += GetPixel( x         , y + y_size );
				avg += GetPixel( x - x_size, y + y_size );
				avg += GetPixel( x - x_size, y          );

				avg = (avg / 5);

				if( avg <= 32 ) avg = 0;
				if( avg >= 250) avg = 249;

				if( avg > 32 ) done = 0;

				for(i = 0; i < x_size; i++) {
					for(j = 0; j < y_size; j++) {
						SetPixel(x + j, y + i, avg); // Try avg+getran(-1,1)
					}
				}
			}
			if( (done == 1) && (clean_screen == 0) ) break;
		}
		clean_screen = 0;
	}
}








