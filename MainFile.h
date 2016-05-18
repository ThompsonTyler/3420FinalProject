#include "MK64F12.h"
#include "stdlib.h"

#define WHITE  0 //Color Definitions
#define MAGENTA 1
#define YELLOW 2
#define RED 3
#define CYAN 4
#define BLUE 5
#define GREEN 6
#define CLEAR 7

extern int buttons[6]; //Buttons based on rising edge trigger
extern int buttonsLast[6]; //Buttons based on actual state

extern uint8_t backdrop[8][8]; //8x8 matrix for backdrop image

void delay(int count); //Delay a for loop of count

int mod(int a, int b);	//Modulo working for negative numbers

void clearBack(void); //Clears backdrop

void swapScreens(void);	//Pushes data from backdrop into screen

void checkButtons(void);	//Initializes a button check (Shouldn't need to be run outside of main loop unless absolutely necesary)

//Functions declared by outsides, but called by main

extern int play1pMario(void);	//Plays a 1p mario "turn" returns 0 if terminating. 1 if not.

extern void updateSheet(int state, uint8_t color);	//Loads slide animation in state state and background color color

extern void rainbowTest(void);	//Loads a rainbow into backdrop
