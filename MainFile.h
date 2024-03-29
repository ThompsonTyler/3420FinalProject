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

extern void mario2pReset(void); //Resets 2p mario, defaulting the init variables

extern int playSnake(void);  //Plays a snake "turn" returns 0 if terminating, 1 if not

extern void buildScroller(char *str); //Builds the internal variables of scroller based on an input string up to 20 chars of "A-Z", " ", and "0-9"

extern int scroll(int colorize, int color); //Scrolls 1 step, returning 0 if done, 1 if not. If colorize == 1 then colors to color instead of white, color is 0-6(no clear), if not then it
																						//randomizes the color every time it is called

extern void setLevel(int x); //Sets the internal variables for 2p mario to configure to each level input of 0-3
