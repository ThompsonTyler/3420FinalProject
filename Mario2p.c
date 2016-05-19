#include "Mario2p.h"

int MARIOLINE[4] = {52, 45, 53, 36}; //Ending line for each map
#define MARIOROW 4 //Height of each map

int xStarts[4] = {2, 2, 0, 0};	//Starting point [y][x] of each map
int yStarts[4] = {2, 2, 0, 2};
	
int levelMark; //Current level

int xMarTop = 2;	//xPosition of top player
int yMarTop = 8;	//yPosition of top player
int stateMarTop = 0;	//state of top player

int xMarBot = 2;	//xPosition of bottomPlayer
int yMarBot = 8;	//yPosition of bottomPlayer
int stateMarBot = 0;	//state of bottom player

int finishedFirst = 0;//Switch to player who wins


//Editable maps for 2p mario.
uint8_t marioBack[4][4][60] = {{{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7},                                                                                   
																{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7},
																{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7},
																{6, 6, 6, 6, 7, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 6, 7, 6, 7, 6, 7, 6, 7, 6, 7, 7, 7, 7, 7, 6, 6, 6, 6, 0, 7, 7, 7, 7, 7, 7, 7, 7}},

															 {{7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},                                                                                   
																{7, 7, 7, 7, 6, 6, 6, 6, 7, 7, 6, 7, 6, 7, 7, 7, 7, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 6, 7, 7, 6, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
																{7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 6, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
																{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}},

														   {{7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7},                                                                                   
																{6, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 6, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7},
																{6, 7, 7, 7, 7, 6, 7, 6, 7, 7, 7, 7, 6, 6, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7},
																{6, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 7, 7, 6, 6, 6, 6, 6, 7, 7, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 3, 7, 7, 7, 7, 7, 7, 7}},

															 {{7, 7, 7, 7, 7, 6, 7, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},                                                                                   
																{6, 6, 6, 6, 7, 6, 7, 7, 6, 7, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 7, 7, 7, 7, 6, 7, 7, 7, 7, 6, 7, 6, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
																{7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
																{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}}};
							
//backup storage of maps for 2p mario.																	
uint8_t marioBackup[4][4][60] = {{{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7},                                                                                   
																{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7},
																{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7},
																{6, 6, 6, 6, 7, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 6, 7, 6, 7, 6, 7, 6, 7, 6, 7, 7, 7, 7, 7, 6, 6, 6, 6, 0, 7, 7, 7, 7, 7, 7, 7, 7}},

															 {{7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},                                                                                   
																{7, 7, 7, 7, 6, 6, 6, 6, 7, 7, 6, 7, 6, 7, 7, 7, 7, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 6, 7, 7, 6, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
																{7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 6, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
																{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}},

														   {{7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7},                                                                                   
																{6, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 7, 6, 6, 7, 7, 6, 6, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 6, 7, 7, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7},
																{6, 7, 7, 7, 7, 6, 7, 6, 7, 7, 7, 7, 6, 6, 7, 7, 6, 6, 7, 7, 7, 7, 7, 6, 6, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7},
																{6, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 7, 7, 6, 6, 6, 6, 6, 7, 7, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 3, 7, 7, 7, 7, 7, 7, 7}},

															 {{7, 7, 7, 7, 7, 6, 7, 7, 6, 7, 7, 7, 6, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},                                                                                   
																{6, 6, 6, 6, 7, 6, 7, 7, 6, 7, 6, 6, 6, 6, 6, 6, 6, 7, 6, 6, 7, 7, 7, 7, 6, 7, 7, 7, 7, 6, 7, 6, 7, 7, 7, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
																{7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 7, 7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
																{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 6, 6, 6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 3, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}}};
															
void mario2pReset(void){ //Sets default variables (mostly just state and finishedFirst matter, positions are just for safety)
	xMarTop = 2;
	yMarTop = 2;
	stateMarTop = 0;
	
	xMarBot = 2;
	yMarBot = 2;
	stateMarBot = 0;
	
	finishedFirst = 0;
}
																
void setLevel(int x){	//Sets level to x
	levelMark = x;
}

void replaceAllMario(uint8_t base, uint8_t replace){ //Iterates through marioBack and sets all colors of base to color of replace
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < MARIOLINE[levelMark]; lineIndex++){
		for(rowIndex = 0; rowIndex < MARIOROW; rowIndex++){
			if(marioBack[levelMark][rowIndex][lineIndex] == base){  //Checks if it's the base color
				marioBack[levelMark][rowIndex][lineIndex] = replace;	//If so replace it
			}
		}
	}
}

void fixAllMario(void){ //Fixes a screen by restoring it to a backup version
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < MARIOLINE[levelMark]; lineIndex++){
		for(rowIndex = 0; rowIndex < MARIOROW; rowIndex++){
			marioBack[levelMark][rowIndex][lineIndex] = marioBackup[levelMark][rowIndex][lineIndex];
		}
	}
}

void loadtoBackBufferFullMario(int xBuffer, int yBuffer, int xBack, int yBack, int drawBeforex, int drawBeforey, int drawAfterx, int drawAftery, int drawBot){  //Loads the values from [yBuffer:yBuffer + 4][xBuffer:xBuffer + 7] to backdrop[yBack:8][xBack:8]
																																																								//Setting values before/outside bounds to clear if drawBefore == 1. and values after/outside bounds to clear if drawAfter == 1
																																																								//drawBot if 1 if drawing bottom of backdrop or 0 if top (bottom or top player)
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < 8; lineIndex++){
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			if(lineIndex < xBack){//If it's before the x position on backdrop
				if(drawBeforex == 1){ //If should draw before in x position
					backdrop[rowIndex][lineIndex] = CLEAR; //If so, draw clear
				}
			}
			else if(rowIndex < yBack){//Otherwise check if it's before on y position
				if(drawBeforey == 1){	//if should draw before in y position
					backdrop[rowIndex][lineIndex] = CLEAR;	//If so, draw clear
				}
			}
			else if(lineIndex + xBuffer >= MARIOLINE[levelMark]){	//Check if it's after the end of the level matrix
				if(drawAfterx == 1){	//if drawAfter for x 
					backdrop[rowIndex][lineIndex] = CLEAR;	//If so, draw clear
				}
			}
			else if(rowIndex + yBuffer >= MARIOROW + (drawBot * 4)){	//Check if it's after the end of the level matrix with drawBot for offset if drawing the bottom or top.
				if(drawAftery == 1){ //if drawAfter for y
					backdrop[rowIndex][lineIndex] = CLEAR;	//If so, draw clear
				}
			}
			else{
				backdrop[rowIndex][lineIndex] = marioBack[levelMark][rowIndex + yBuffer - (drawBot * 4)][lineIndex + xBuffer]; //Otherwise just set normally
			}
		}
	}

}

int play2pMario(void){ //Return 0 if terminating, 1 if not done, 2 if 1p wins, 3 if 2p wins
	int xDrawTop;//Drawing variables for x and y of top and bottom players
	int yDrawTop;
	int xDrawBot;
	int yDrawBot;
	int topDone = 0; //0 if not done, 1 if done
	int botDone = 0; //0 if not done, 1 if done
	
	
	//Player 1
	if(stateMarTop == 3){//Check if top player is done
		topDone = 1;//Set top player as done
		if(finishedFirst == 0){finishedFirst = 1;} //If top player finishes first, set finishedFirst to 1.
	}
	
	else if(stateMarTop == 0){//Walking state for player 1
		if(buttonsLast[0] == 1){ //move left if possible
			if((yMarTop < 0 && xMarTop != 0) || !(xMarTop == 0 || marioBack[levelMark][yMarTop][xMarTop - 1] == GREEN)){//Check for collision with green pixel or left border
				xMarTop--;
			}
		}
		if(buttonsLast[1] == 1){//Move right if possible
			if((yMarTop < 0 && xMarTop != MARIOLINE[levelMark] - 1) || !(xMarTop == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarTop][xMarTop + 1] == GREEN)){ //Check for collision with green
				xMarTop++;
			}
		}
		if(buttons[2] == 1){ //Jump if possible
			if(yMarTop <= 0 || marioBack[levelMark][yMarTop - 1][xMarTop] != GREEN){//Check for collision, if not then jump
				yMarTop--;
				stateMarTop = 1;
			}
		}
		if(stateMarTop == 0){//Check make sure still walking
			if(yMarTop < -1 || marioBack[levelMark][yMarTop + 1][xMarTop] != GREEN){//If so, then fall if no collision below
				yMarTop++;
			}
		}
	}
	
	else if(stateMarTop == 1){//Jumping state player 1
		if(buttonsLast[0] == 1){//Move left if possible
			if((yMarTop < 0 && xMarTop != 0) || !(xMarTop == 0 || marioBack[levelMark][yMarTop][xMarTop - 1]  == GREEN)){ //Check for collision/border
				xMarTop--;
			}
		}
		if(buttonsLast[1] == 1){//Move right if possible
			if((yMarTop < 0 && xMarTop != MARIOLINE[levelMark] - 1) || !(xMarTop == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarTop][xMarTop + 1] == GREEN)){ //Check for collision
				xMarTop++;
			}
		}
		if(yMarTop <= 0 || marioBack[levelMark][yMarTop - 1][xMarTop] != GREEN){ //Continue jumping if possible, if so go up 1 and then go into falling state, otherwise if collision go to falling state
				yMarTop--;
				stateMarTop = 2;
		}
		else{
			stateMarTop = 2;
		}
	}
	
	else if(stateMarTop == 2){ //Falling state for player 1
		if(buttonsLast[0] == 1){ //Move left if possible
			if((yMarTop < 0 && xMarTop != 0) || !(xMarTop == 0 || marioBack[levelMark][yMarTop][xMarTop - 1]  == GREEN)){//Check for collision/border
				xMarTop--;
			}
		}
		if(buttonsLast[1] == 1){ //Move right if possible
			if((yMarTop < 0 && xMarTop != MARIOLINE[levelMark] - 1) || !(xMarTop == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarTop][xMarTop + 1] == GREEN)){ //Check for collision
				xMarTop++;
			}
		}
		if(yMarTop < -1 || marioBack[levelMark][yMarTop + 1][xMarTop] != GREEN){ //Continue falling if no collision, otherwise set to walking state
			yMarTop++;
		}
		else{
			stateMarTop = 0;
		}
	}
	
	if(xMarTop == MARIOLINE[levelMark] - 1){//If reach end, set state to finished state
		stateMarTop = 3;
	}
	
	//Player 2(same as player 1)
	if(stateMarBot == 3){
		botDone = 1;
		if(finishedFirst == 0){finishedFirst = 2;}
	}
	
	else if(stateMarBot == 0){
		if(buttonsLast[3] == 1){
			if((yMarBot < 0 && xMarBot != 0) || !(xMarBot == 0 || marioBack[levelMark][yMarBot][xMarBot - 1] == GREEN)){
				xMarBot--;
			}
		}
		if(buttonsLast[4] == 1){
			if((yMarBot < 0 && xMarBot != MARIOLINE[levelMark] - 1) || !(xMarBot == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarBot][xMarBot + 1] == GREEN)){
				xMarBot++;
			}
		}
		if(buttons[5] == 1){
			if(yMarBot <= 0 || marioBack[levelMark][yMarBot - 1][xMarBot] != GREEN){
				yMarBot--;
				stateMarBot = 1;
			}
		}
		if(stateMarBot == 0){
			if(yMarBot < -1 || marioBack[levelMark][yMarBot + 1][xMarBot] != GREEN){
				yMarBot++;
			}
		}
	}
	
	else if(stateMarBot == 1){
		if(buttonsLast[3] == 1){
			if((yMarBot < 0 && xMarBot != 0) || !(xMarBot == 0 || marioBack[levelMark][yMarBot][xMarBot - 1]  == GREEN)){
				xMarBot--;
			}
		}
		if(buttonsLast[4] == 1){
			if((yMarBot < 0 && xMarBot != MARIOLINE[levelMark] - 1) || !(xMarBot == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarBot][xMarBot + 1] == GREEN)){
				xMarBot++;
			}
		}
		if(yMarBot <= 0 || marioBack[levelMark][yMarBot - 1][xMarBot] != GREEN){
				yMarBot--;
				stateMarBot = 2;
		}
		else{
			stateMarBot = 2;
		}
	}
	
	else if(stateMarBot == 2){
		if(buttonsLast[3] == 1){
			if((yMarBot < 0 && xMarBot != 0) || !(xMarBot == 0 || marioBack[levelMark][yMarBot][xMarBot - 1]  == GREEN)){
				xMarBot--;
			}
		}
		if(buttonsLast[4] == 1){
			if((yMarBot < 0 && xMarBot != MARIOLINE[levelMark] - 1) || !(xMarBot == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarBot][xMarBot + 1] == GREEN)){
				xMarBot++;
			}
		}
		if(yMarBot < -1 || marioBack[levelMark][yMarBot + 1][xMarBot] != GREEN){
			yMarBot++;
		}
		else{
			stateMarBot = 0;
		}
	}
	
	if(xMarBot == MARIOLINE[levelMark] - 1){
		stateMarBot = 3;
	}
	
	
	//Check if player 1 has fallen below map
	if(yMarTop >= 4){//If so, reset them based on level start
		yMarTop = yStarts[levelMark];
		xMarTop = xStarts[levelMark];
	}
	//Player 2 fallen below map reset check
	if(yMarBot >= 4){
		yMarBot = yStarts[levelMark];
		xMarBot = xStarts[levelMark];
	}
	
	
	fixAllMario();//Fix the map to base state
	if(yMarTop >= 0){//If top player can be drawn, set their pixel to blue
		marioBack[levelMark][yMarTop][xMarTop] = BLUE;
	}
	yDrawTop = 0;//Always draw at this y position
	xDrawTop = xMarTop - 3;	//x position slides to follow player
	if (xDrawTop < 0){xDrawTop = 0;}	//Make sure x position is clipped to matrix bounds (0)
	loadtoBackBufferFullMario(xDrawTop, yDrawTop, 0, 0, 0, 0, 1, 0, 0);//Draw map for player 1, drawing clear afterwards in the x position
	fixAllMario(); //Fix map for 2nd player
	if(yMarBot >= 0){ //Draw 2nd player if possible
		marioBack[levelMark][yMarBot][xMarBot] = BLUE;
	}
	yDrawBot = 0;//Y position is always 0 for drawing
	xDrawBot = xMarBot - 3;	//Set x position
	if (xDrawBot < 0) {xDrawBot = 0;}//clip as necessary
	loadtoBackBufferFullMario(xDrawBot, yDrawBot, 0, 4, 0, 0, 1, 0, 1);//Draw map for player 2, drawing clear afterwards in the x position, and marking that this is drawn for player 2 
																																		 //(drawBot = 1 and backdrop y position starts at 4)
	swapScreens(); //Load backdrop to screen
	delay(6000);
	if(topDone == 1 && botDone == 1){ //If both players are done, return the victor
		return finishedFirst + 1;
	}
	else{	//Otherwise say game isn't done yet
		return 1;
	}
}
