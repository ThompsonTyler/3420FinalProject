#include "MK64F12.h"
#include "stdlib.h"
#include "time.h" 
#include "string.h"
#include "stdio.h"

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

extern int play2pMario(void); //Plays a 2p mario "turn" returns 0 if terminating, 1 if not, 2 if p1 wins, 3 if p2 wins

extern void mario2pReset(void);

extern void snakeReset(void);

extern void updateSheet(int state, uint8_t color);	//Loads slide animation in state state and background color color

extern void rainbowTest(void);	//Loads a rainbow into backdrop

extern int playSnake(void);

extern void buildScroller(char *str);

extern int scroll(int colorize, int color);

extern void setLevel(int x);
