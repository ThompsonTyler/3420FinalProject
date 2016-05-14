#include "Mario1p.h"

#define MARIOLINE 20 //Matrix size definitions. [Row][Line]
#define MARIOROW 8

int xMar = 2; //Variable representing xPosition for mario 1p(Left = 0)
int yMar = 6; //Variable representing yPosition for mario 1p(Top = 0)
int stateMar = 0; // State diagram:
// 0: Walk.   1: JumpState 1. 2: JumpState 2.5.  3:Jumpstate 1.5   4: Jumpstate 2 6: End

uint8_t marioBack[8][20] = {{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,3},  //Map for mario
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,3},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,6,3},
														{7,7,7,7,7,7,7,6,6,6,6,6,7,6,6,7,7,7,7,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,6,3},
														{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0}};
														
void replaceAllMario(uint8_t base, uint8_t replace){ //Iterates through marioBack and sets all colors of base to color of replace
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < MARIOLINE; lineIndex++){
		for(rowIndex = 0; rowIndex < MARIOROW; rowIndex++){
			if(marioBack[rowIndex][lineIndex] == base){
				marioBack[rowIndex][lineIndex] = replace;
			}
		}
	}
}

void loadtoBackBufferFullMario(int xBuffer, int yBuffer, int xBack, int yBack, int drawBefore, int drawAfter){  //Loads the values from [yBuffer:yBuffer + 7][xBuffer:xBuffer + 7] to backdrop[yBack:8][xBack:8]
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
					backdrop[rowIndex][lineIndex] = marioBack[rowIndex + yBuffer][lineIndex + xBuffer];
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
		if(buttons[0] == 1){ //Move left if possible
			if(xMar == 0 || marioBack[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttons[1] == 1){ //Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		if(buttons[2] == 1){ //Begin jumping if possible 
			if(yMar == 0 || marioBack[yMar - 1][xMar] == GREEN){}
			else{
				yMar--;
				stateMar = 1;
			}
		}
		if(stateMar == 0){ //Fall if space below
			if(yMar == MARIOROW - 1 || marioBack[yMar + 1][xMar] == GREEN){}
			else{
				yMar++;
			}
		}	
	}
	
	else if(stateMar == 1){//Check if position 1 for jumping
		if(buttons[0] == 1){//Move left if possible
			if(xMar == 0 || marioBack[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttons[1] == 1){//Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		
		stateMar = 3; //Step to position 1.5 of jumping
	}
	
	else if(stateMar == 2){//Check if position 2.5 of jumping
		if(buttons[0] == 1){//Move left if possible
			if(xMar == 0 || marioBack[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttons[1] == 1){//Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		if(yMar == MARIOROW - 1 || marioBack[yMar + 1][xMar] == GREEN){//Fall if possible, if hit ground set back to walking state
			stateMar = 0;
		}
		else{
			yMar++;
		}
		
	}
	
	else if(stateMar == 3){ //Check if position 1.5 of jumping
		if(buttons[0] == 1){//Move left if possible
			if(xMar == 0 || marioBack[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttons[1] == 1){//Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		
		if(yMar == 0 || marioBack[yMar - 1][xMar] == GREEN){//Go up if possible and move to state 2 for jumping, if hitting roof then change to falling position(2.5)
			stateMar = 2;
		}
		else{
			yMar--;
			stateMar = 4;
		}
	}
	
	else if(stateMar == 4){//Check if jump position 2
		if(buttons[0] == 1){//Move left if possible
			if(xMar == 0 || marioBack[yMar][xMar - 1] == GREEN){}
			else{
				xMar--;
			}
		}
		if(buttons[1] == 1){//Move right if possible
			if(xMar == MARIOLINE - 1 || marioBack[yMar][xMar + 1] == GREEN){}
			else{
				xMar++;
			}
		}
		
		stateMar = 2; //Peak of jump, so move to falling state
	}
	
	if(xMar == MARIOLINE - 1){ //If reach end, terminate
		stateMar = 6;
	}
	
	replaceAllMario(BLUE, CLEAR); //Clear old position
	marioBack[yMar][xMar] = BLUE; //Draw new position
	yDraw = 0; //Draw from start of marioBack
	xDraw = xMar - 3; //Draw starting with 3 left of mario (to have camera follow player)
	if (xDraw < 0){xDraw = 0;}//Don't draw before the screen, if camera would go left of map just clip it back to edge
	loadtoBackBufferFullMario(xDraw, yDraw, 0, 0, 1, 1); //Load marioBack area to backdrop
	swapScreens(); //Push update to screen.
	return 1;//Not terminating yet
}
