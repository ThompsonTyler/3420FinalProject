#include "Mario1p.h"

#define MARIOLINE 20 //Matrix size definitions. [Row][Line]
#define MARIOROW 8

int xMar = 2; //Variable representing xPosition for mario 1p(Left = 0)
int yMar = 6; //Variable representing yPosition for mario 1p(Top = 0)
int stateMar = 0; // State diagram:
// 0: Walk.   1: JumpState 1. 2: JumpState 2.5.  3:Jumpstate 1.5   4: Jumpstate 2 6: End

uint8_t marioBack1p[8][20] = {{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,3},  //Map for mario
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,3},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,6,3},
														{7,7,7,7,7,7,7,6,6,6,6,6,7,6,6,7,7,7,7,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,6,3},
														{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0}};
														
void replaceAllMario1p1p(uint8_t base, uint8_t replace){ //Iterates through marioBack1p and sets all colors of base to color of replace
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < MARIOLINE; lineIndex++){
		for(rowIndex = 0; rowIndex < MARIOROW; rowIndex++){
			if(marioBack1p[rowIndex][lineIndex] == base){
				marioBack1p[rowIndex][lineIndex] = replace;
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
			if((lineIndex < xBack || rowIndex < yBack) && drawBefore == 1){
				backdrop[rowIndex][lineIndex] = CLEAR;
			}
			else{
				if((lineIndex + xBuffer >= MARIOLINE || rowIndex + yBuffer >= MARIOROW) && drawAfter == 1){
					backdrop[rowIndex][lineIndex] = CLEAR;
				}
				else{
					backdrop[rowIndex][lineIndex] = marioBack1p[rowIndex + yBuffer][lineIndex + xBuffer];
				}
			}
		}
	}
	
}

int play1pMario(void){ //Return 0 if terminate, 1 if not done yet
	int xDraw;
	int yDraw;
	
	if(stateMar == 6){ //Test if terminated
		return 0; //Return that game is done
	}
	else if(stateMar == 0){  //Test if walking
		if(buttonsLast[0] == 1){ //Move left if possible
			if(xMar == 0 || marioBack1p[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttonsLast[1] == 1){ //Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack1p[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		if(buttons[2] == 1){ //Begin jumping if possible 
			if(yMar == 0 || marioBack1p[yMar - 1][xMar] == GREEN){}
			else{
				yMar--;
				stateMar = 3;
			}
		}
		if(stateMar == 0){ //Fall if space below
			if(yMar == MARIOROW - 1 || marioBack1p[yMar + 1][xMar] == GREEN){}
			else{
				yMar++;
			}
		}	
	}
	
	else if(stateMar == 1){//Check if position 1 for jumping
		if(buttonsLast[0] == 1){//Move left if possible
			if(xMar == 0 || marioBack1p[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttonsLast[1] == 1){//Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack1p[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		
		stateMar = 3; //Step to position 1.5 of jumping
	}
	
	else if(stateMar == 2){//Check if position 2.5 of jumping
		if(buttonsLast[0] == 1){//Move left if possible
			if(xMar == 0 || marioBack1p[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttonsLast[1] == 1){//Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack1p[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		if(yMar == MARIOROW - 1 || marioBack1p[yMar + 1][xMar] == GREEN){//Fall if possible, if hit ground set back to walking state
			stateMar = 0;
		}
		else{
			yMar++;
		}
		
	}
	
	else if(stateMar == 3){ //Check if position 1.5 of jumping
		if(buttonsLast[0] == 1){//Move left if possible
			if(xMar == 0 || marioBack1p[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttonsLast[1] == 1){//Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack1p[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		
		if(yMar == 0 || marioBack1p[yMar - 1][xMar] == GREEN){//Go up if possible and move to state 2 for jumping, if hitting roof then change to falling position(2.5)
			stateMar = 2;
		}
		else{
			yMar--;
			stateMar = 2;
		}
	}
	
	else if(stateMar == 4){//Check if jump position 2
		if(buttonsLast[0] == 1){//Move left if possible
			if(xMar == 0 || marioBack1p[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttonsLast[1] == 1){//Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack1p[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		
		stateMar = 2; //Peak of jump, so move to falling state
	}
	
	if(xMar == MARIOLINE - 1){ //If reach end, terminate
		stateMar = 6;
	}
	
	replaceAllMario1p1p(BLUE, CLEAR); //Clear old position
	marioBack1p[yMar][xMar] = BLUE; //Draw new position
	yDraw = 0; //Draw from start of marioBack1p
	xDraw = xMar - 3; //Draw starting with 3 left of mario (to have camera follow player)
	if (xDraw < 0){xDraw = 0;}//Don't draw before the screen, if camera would go left of map just clip it back to edge
	loadtoBackBufferFullMario1p(xDraw, yDraw, 0, 0, 1, 1); //Load marioBack1p area to backdrop
	swapScreens(); //Push update to screen.
	delay(3000);
	return 1;//Not terminating yet
}
