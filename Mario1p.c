#include "Mario1p.h"

#define MARIOLINE 190 //Matrix size definitions. [Row][Line]
#define MARIOROW 8

int xMar = 1; //Variable representing xPosition for mario 1p(Left = 0)
int yMar = 2; //Variable representing yPosition for mario 1p(Top = 0)
int xStart[4] = {5,2,5,1};
int yStart[4] = {6,6,6,2};
int stateMar = 0; // State diagram:
// 0: Walk.   1: JumpState 1. 2: JumpState 2.5.  3:Jumpstate 1.5   4: Jumpstate 2 6: End
int level = 0;//Current level, 0-3
int animation = 0; //If in animation or not (0 no, 1 yes)
int animationCounter; //Counter used by animation to count steps
int finished = 0; //Has mario been run before this reset or no?


//Matrices representing the maps 0-3 from World 1 of Super Mario Bros.
uint8_t marioBack1p[4][8][190] = {{{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 2, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 3, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 3, 7, 3, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 2, 2, 7, 7, 7, 2, 7, 7, 2, 7, 7, 2, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 2, 2, 2, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 7, 3, 3, 3, 3, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 7, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 7, 3, 3, 3, 3, 7, 7, 7},
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},

{{5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
{5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 5, 5, 5, 5, 5, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 5, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 6, 7, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 7, 5, 5, 5, 7, 5, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 5, 7, 5, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 7, 6, 5, 5, 5, 5, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 3, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
{5, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 5, 7, 5, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 7, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 7, 5, 5, 7, 7, 5, 5, 5, 7, 7, 7, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 7, 5, 7, 5, 7, 5, 7, 7, 7, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 7, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 7, 5, 7, 5, 7, 5, 7, 5, 7, 7, 7, 5, 7, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 7, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}},

{{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 7, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 3, 7, 3, 7, 3, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 6, 6, 6, 7, 7, 0, 0, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 7, 7, 7, 6, 6, 6, 6, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 3, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 0, 0, 7, 7, 6, 6, 6, 7, 7, 0, 0, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 7, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 0, 0, 7, 6, 6, 6, 6, 2, 2, 7, 7, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 7, 0, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 0, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 3, 3, 3, 3, 7, 3, 3, 3, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 7, 0, 0, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 0, 0, 7, 7, 0, 0, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 7, 7, 0, 7, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 0, 0, 7, 7, 7, 0, 7, 7, 7, 0, 0, 7, 7, 7, 0, 0, 7, 7, 7, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}},

{{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 5, 7, 7, 7, 7, 7, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 7, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 3, 0, 3, 0, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 3, 0, 2, 0, 3, 0, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 3, 7, 7, 7, 3, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 2, 0, 7, 2, 7, 0, 2, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 7, 5, 7, 5, 7, 5, 7, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 4, 7, 7, 7, 7, 7, 7, 7, 7, 2, 7, 7, 0, 0, 0, 7, 7, 2, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 5, 5, 7, 7, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 0, 7, 3, 7, 7, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 7, 7, 5, 5, 5, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}}};
															
	
void emptyBlock(int row, int line){ //Clear the desired space of [row][line] in current level
	marioBack1p[level][row][line] = CLEAR;
}
														
void replaceAllMario1p1p(uint8_t base, uint8_t replace){ //Iterates through marioBack1p and sets all colors of base to color of replace of current level
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < MARIOLINE; lineIndex++){
		for(rowIndex = 0; rowIndex < MARIOROW; rowIndex++){
			if(marioBack1p[level][rowIndex][lineIndex] == base){
				marioBack1p[level][rowIndex][lineIndex] = replace;
			}
		}
	}
}

void fixMar(void){  //Goes through and fixes any magenta(player) pixels in current level
	int lineIndex;
	int rowIndex;
	
	for(lineIndex = xMar - 4; lineIndex < xMar + 3; lineIndex++){
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			if(lineIndex < 0){ //Only want matrix bounds
				lineIndex = 0;
			}
			if(marioBack1p[level][rowIndex][lineIndex] == MAGENTA){ //If it is a player color
				if(rowIndex == 7){ //If it's on bottom row
					if(marioBack1p[level][rowIndex - 1][lineIndex] == WHITE){ //If above pixel is white, set to white
						marioBack1p[level][rowIndex][lineIndex] = WHITE;
					}
					else{ //Else clear
						marioBack1p[level][rowIndex][lineIndex] = CLEAR;
					}
				}
				else if (rowIndex == 0){ //If top row
					if(marioBack1p[level][rowIndex + 1][lineIndex] == WHITE){ //If below pixel is white, set to white
						marioBack1p[level][rowIndex][lineIndex] = WHITE;
					}
					else{ //Else clear
						marioBack1p[level][rowIndex][lineIndex] = CLEAR;
					}
				}
				else{
					if(marioBack1p[level][rowIndex - 1][lineIndex] == WHITE || marioBack1p[level][rowIndex + 1][lineIndex] == WHITE){ //If it is in the middle, check above and below are white
						marioBack1p[level][rowIndex][lineIndex] = WHITE;//If so, set white
					}
					else{
						marioBack1p[level][rowIndex][lineIndex] = CLEAR;//Else clear
					}
				}
			}
		}
	}
}

void loadtoBackBufferFullMario1p(int xBuffer, int yBuffer, int xBack, int yBack, int drawBefore, int drawAfter){  //Loads the values from [yBuffer:yBuffer + 7][xBuffer:xBuffer + 7] to backdrop[yBack:8][xBack:8]
																																																								//Setting values before/outside bounds to clear if drawBefore == 1. and values after/outside bounds to clear if drawAfter == 1
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < 8; lineIndex++){
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			if((lineIndex < xBack || rowIndex < yBack) && drawBefore == 1){ //Draw before to clear if drawBefore == 1  if before the backdrop spaces desired to write in
				backdrop[rowIndex][lineIndex] = CLEAR;
			}
			else{
				if((lineIndex + xBuffer >= MARIOLINE || rowIndex + yBuffer >= MARIOROW) && drawAfter == 1){ //Draw after to clear if drawAfter == 1 if after the backdrop spaces desired to write in
					backdrop[rowIndex][lineIndex] = CLEAR;
				}
				else{
					backdrop[rowIndex][lineIndex] = marioBack1p[level][rowIndex + yBuffer][lineIndex + xBuffer]; //Otherwise set it to the pixels in the matrix
				}
			}
		}
	}
	
}

int play1pMario(void){ //Return 0 if terminate, 1 if not done yet
	int flag = 0; //Flag for if they had to reset or not.
	int xDraw;	//Represents x pixel to draw for player
	int yDraw;	//Represents y pixel to draw for player
	if (finished == 1){ //Check if Mario has been played before
		delay(2000);
		return 5;
	}
	if(animation == 0){ //Check if animation is not running
		if(stateMar == 0){	//Check for walking
			if(buttonsLast[0] == 1){	//Move right if possible
																//Collisions allowed include clear(nothing), red(fire), cyan(finish flag), white(pass-through-able)
				if((yMar < 0 && xMar != 0) || !(xMar == 0 || (marioBack1p[level][yMar][xMar - 1] != CLEAR && marioBack1p[level][yMar][xMar - 1] != RED && marioBack1p[level][yMar][xMar - 1] != CYAN && marioBack1p[level][yMar][xMar - 1] != WHITE))){
					xMar--;
				}
			}
			if(buttonsLast[1] == 1){	//Move left is possible
				if((yMar < 0 && xMar != MARIOLINE - 1) || !(xMar == MARIOLINE - 1 || (marioBack1p[level][yMar][xMar + 1] != CLEAR && marioBack1p[level][yMar][xMar + 1] != RED && marioBack1p[level][yMar][xMar + 1] != CYAN && marioBack1p[level][yMar][xMar + 1] != WHITE))){
					xMar++;
				}
			}
			if(buttons[2] == 1){ //Jump if possible
				if(yMar <= 0){ //If above screen, can always jumps
					yMar--;
					stateMar = 1;
				}
				else if (marioBack1p[level][yMar - 1][xMar] == YELLOW || marioBack1p[level][yMar - 1][xMar] == BLUE){//Check if hit blue or yellow block, if so, break it
					emptyBlock(yMar -1, xMar);
				}//Otherwise, check for collision
				else if (marioBack1p[level][yMar - 1][xMar] == CLEAR || marioBack1p[level][yMar - 1][xMar] == RED || marioBack1p[level][yMar - 1][xMar] == WHITE || marioBack1p[level][yMar - 1][xMar] == CYAN){
					yMar--;
					stateMar = 1;
				}
			}
			if(stateMar == 0){ //Fall if nothing to support player(clear, white, red, or cyan)
				if(yMar < -1 || marioBack1p[level][yMar + 1][xMar] == CLEAR || marioBack1p[level][yMar + 1][xMar] == WHITE || marioBack1p[level][yMar + 1][xMar] == RED || marioBack1p[level][yMar + 1][xMar] == CYAN){
					yMar++;
				}
			}
	}
	
	else if(stateMar == 1){//Mid-Jump, follows same as walking, but no jump allowed (forcibly going to jump), if hits something go into fall state otherwise go up one
		if(buttonsLast[0] == 1){
			if((yMar < 0 && xMar != 0) || !(xMar == 0 || (marioBack1p[level][yMar][xMar - 1] != CLEAR && marioBack1p[level][yMar][xMar - 1] != RED && marioBack1p[level][yMar][xMar - 1] != CYAN && marioBack1p[level][yMar][xMar - 1] != WHITE))){
				xMar--;
			}
		}
		if(buttonsLast[1] == 1){
			if((yMar < 0 && xMar != MARIOLINE - 1) || !(xMar == MARIOLINE - 1 || (marioBack1p[level][yMar][xMar + 1] != CLEAR && marioBack1p[level][yMar][xMar + 1] != RED && marioBack1p[level][yMar][xMar + 1] != CYAN && marioBack1p[level][yMar][xMar + 1] != WHITE))){
				xMar++;
			}
		}
		if(yMar <= 0){
				yMar--;
				stateMar = 2;
		}
		else if(marioBack1p[level][yMar - 1][xMar] == YELLOW || marioBack1p[level][yMar - 1][xMar] == BLUE){
			emptyBlock(yMar - 1, xMar);
			stateMar = 2;
		}
		else if (marioBack1p[level][yMar - 1][xMar] == CLEAR || marioBack1p[level][yMar - 1][xMar] == RED || marioBack1p[level][yMar - 1][xMar] == WHITE || marioBack1p[level][yMar - 1][xMar] == CYAN){
				yMar--;
				stateMar = 2;
			}
		else{
			stateMar = 2;
		}
	}
	
	else if(stateMar == 2){//Final jump state, follows same as mid-jump. but if hit something go to fall state, otherwise go up one and go into fall state
		if(buttonsLast[0] == 1){
			if((yMar < 0 && xMar != 0) || !(xMar == 0 || (marioBack1p[level][yMar][xMar - 1] != CLEAR && marioBack1p[level][yMar][xMar - 1] != RED && marioBack1p[level][yMar][xMar - 1] != CYAN && marioBack1p[level][yMar][xMar - 1] != WHITE))){
				xMar--;
			}
		}
		if(buttonsLast[1] == 1){
			if((yMar < 0 && xMar != MARIOLINE - 1) || !(xMar == MARIOLINE - 1 || (marioBack1p[level][yMar][xMar + 1] != CLEAR && marioBack1p[level][yMar][xMar + 1] != RED && marioBack1p[level][yMar][xMar + 1] != CYAN && marioBack1p[level][yMar][xMar + 1] != WHITE))){
				xMar++;
			}
		}
		if(yMar <= 0){
				yMar--;
				stateMar = 3;
		}
		else if(marioBack1p[level][yMar - 1][xMar] == YELLOW || marioBack1p[level][yMar - 1][xMar] == BLUE){
			emptyBlock(yMar - 1, xMar);
			stateMar = 3;
		}
		else if (marioBack1p[level][yMar - 1][xMar] == CLEAR || marioBack1p[level][yMar - 1][xMar] == RED || marioBack1p[level][yMar - 1][xMar] == WHITE || marioBack1p[level][yMar - 1][xMar] == CYAN){
				yMar--;
				stateMar = 3;
			}
		else{
			stateMar = 3;
		}
	}
	
	else if(stateMar == 3){ //Fall state, allows left and right movement, and once a collision is made below, go into walking state
		if(buttonsLast[0] == 1){
			if((yMar < 0 && xMar != 0) || !(xMar == 0 || (marioBack1p[level][yMar][xMar - 1] != CLEAR && marioBack1p[level][yMar][xMar - 1] != RED && marioBack1p[level][yMar][xMar - 1] != CYAN && marioBack1p[level][yMar][xMar - 1] != WHITE))){
				xMar--;
			}
		}
		if(buttonsLast[1] == 1){
			if((yMar < 0 && xMar != MARIOLINE - 1) || !(xMar == MARIOLINE - 1 || (marioBack1p[level][yMar][xMar + 1] != CLEAR && marioBack1p[level][yMar][xMar + 1] != RED && marioBack1p[level][yMar][xMar + 1] != CYAN && marioBack1p[level][yMar][xMar + 1] != WHITE))){
				xMar++;
			}
		}
		if(yMar < -1 || marioBack1p[level][yMar + 1][xMar] == CLEAR || marioBack1p[level][yMar + 1][xMar] == RED || marioBack1p[level][yMar + 1][xMar] == WHITE || marioBack1p[level][yMar + 1][xMar] == CYAN){
				yMar++;
		}
		else{
			stateMar = 0;
		}
	}
	
		if(marioBack1p[level][yMar][xMar] == CYAN){ //Check if player is on the finish flag
			animation = 1;	//Indicate animation should take over
		}
	
		fixMar(); //Clear old position
		if (yMar >= 7 || (yMar >= 0 && marioBack1p[level][yMar][xMar] == RED)){ //If player is below screen or hits red, reset them
			xMar = xStart[level];
			yMar = yStart[level];
			flag = 1;
		}
		if (yMar >= 0){ //If player is in a valid position
			marioBack1p[level][yMar][xMar] = MAGENTA; //Draw new position
		}
	
	}
	else{ //In animation state
		if(animationCounter > 0){//If their counter is above 0 (started)
			if(animationCounter < 11){ //Check if they have moved right enough yet or not
				animationCounter--;//If so, wait at door until counts down
				if(animationCounter == 0){//If at door long enough, trigger next level
					if(level == 3){//If on last level, indicate mario has been played and return that game is done
						finished = 1;
						return 0;
					}
					else{//Otherwise set defaults, shut off animation, and increment level counter
						level++;
						xMar = xStart[level];
						yMar = yStart[level];
						animation = 0;
					}
				}
			}
			else{//If player still needs to move to door, move them and decrement the animation Counter
				animationCounter--;
				marioBack1p[level][yMar][xMar] = RED;
				xMar++;
				marioBack1p[level][yMar][xMar] = MAGENTA;
			}
		}
		else{//Animation hasn't begun yet to walk, so may be dynamic
			if(marioBack1p[level][yMar+1][xMar] == CYAN){//Check if there is still flag below them, if so, move them down a step
				marioBack1p[level][yMar][xMar] = CYAN;
				yMar = yMar + 1;
				marioBack1p[level][yMar][xMar] = MAGENTA;
			}
			else if(marioBack1p[level][yMar][xMar + 1] == RED){	//Check if they have hit the castle yet, if not, move them right a step
				animationCounter = 14;
				marioBack1p[level][yMar][xMar] = CLEAR;
				xMar++;
				marioBack1p[level][yMar][xMar] = MAGENTA;
			}
			else if(marioBack1p[level][yMar][xMar + 1] == CLEAR){ //Check if they have a clear space in front of them
				if(marioBack1p[level][yMar - 1][xMar] == CYAN){//If still on flag, then move down and to right one to get off flag
					marioBack1p[level][yMar][xMar] = CYAN;
					yMar++;
					xMar++;
					marioBack1p[level][yMar][xMar] = MAGENTA;
				}
				else{//Otherwise not on flag, so move 1 step towards castle
					marioBack1p[level][yMar][xMar] = CLEAR;
					xMar++;
					marioBack1p[level][yMar][xMar] = MAGENTA;
				}
			}
			else if(marioBack1p[level][yMar+1][xMar] == YELLOW){//If at bottom of flag, move down and right one to get off flag
				marioBack1p[level][yMar][xMar] = CYAN;
				yMar++;
				xMar++;
				marioBack1p[level][yMar][xMar] = MAGENTA;
			}
		}
	}
	
	
	yDraw = 0; //Draw from start of marioBack1p
	xDraw = xMar - 3; //Draw starting with 3 left of mario (to have camera follow player)
	if (xDraw < 0){xDraw = 0;}//Don't draw before the screen, if camera would go left of map just clip it back to edge
	if(flag == 1){
		clearBack();
		flag = 0;
	}
	else{
		loadtoBackBufferFullMario1p(xDraw, yDraw, 0, 0, 1, 1); //Load marioBack1p area to backdrop
	}
	swapScreens(); //Push update to screen.
	delay(4000);
	return 1;//Not terminating yet
}
