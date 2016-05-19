#include "MainFile.h"

void buildScroller(char *str); //Loads the scrolling variables as necesary to load a string input maximum 20 characters of "A-Z", " ", and "0-9"

int scroll(int colorize, int color); //Scrolls 1 step, colorize = 1 colors based on color, otherwise = 1. Color is color 0-6(no clear) if outside of this range then it will randomly choose a color
																		 //each step. returns 1 not done, returns 0 when done.
		
