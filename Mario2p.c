#include "Mario2p.h"

int MARIOLINE[4] = {52, 45, 53, 36};
#define MARIOROW 4

int xStarts[4] = {2, 2, 0, 0};
int yStarts[4] = {2, 2, 0, 2};
	
int levelMark;

int xMarTop = 2;
int yMarTop = 8;
int stateMarTop = 0;

int xMarBot = 2;
int yMarBot = 8;
int stateMarBot = 0;

int finishedFirst = 0;//Switch to player who wins

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
															
void mario2pReset(void){
	xMarTop = 2;
	yMarTop = 2;
	stateMarTop = 0;
	
	xMarBot = 2;
	yMarBot = 2;
	stateMarBot = 0;
	
	finishedFirst = 0;
}
																
void setLevel(int x){
	levelMark = x;
}

void replaceAllMario(uint8_t base, uint8_t replace){ //Iterates through marioBack and sets all colors of base to color of replace
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < MARIOLINE[levelMark]; lineIndex++){
		for(rowIndex = 0; rowIndex < MARIOROW; rowIndex++){
			if(marioBack[levelMark][rowIndex][lineIndex] == base){
				marioBack[levelMark][rowIndex][lineIndex] = replace;
			}
		}
	}
}

void fixAllMario(void){ //Iterates through marioBack and sets all colors of base to color of replace
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
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < 8; lineIndex++){
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			if(lineIndex < xBack){
				if(drawBeforex == 1){
					backdrop[rowIndex][lineIndex] = CLEAR;
				}
			}
			else if(rowIndex < yBack){
				if(drawBeforey == 1){
					backdrop[rowIndex][lineIndex] = CLEAR;
				}
			}
			else if(lineIndex + xBuffer >= MARIOLINE[levelMark]){
				if(drawAfterx == 1){
					backdrop[rowIndex][lineIndex] = CLEAR;
				}
			}
			else if(rowIndex + yBuffer >= MARIOROW + (drawBot * 4)){
				if(drawAftery == 1){
					backdrop[rowIndex][lineIndex] = CLEAR;
				}
			}
			else{
				backdrop[rowIndex][lineIndex] = marioBack[levelMark][rowIndex + yBuffer - (drawBot * 4)][lineIndex + xBuffer];
			}
		}
	}

}

int play2pMario(void){ //Return 0 if terminating, 1 if not done, 2 if 1p wins, 3 if 2p wins
	int xDrawTop;
	int yDrawTop;
	int xDrawBot;
	int yDrawBot;
	int topDone = 0; //0 if not done, 1 if done
	int botDone = 0; //0 if not done, 1 if done
	
	if(stateMarTop == 3){
		topDone = 1;
		if(finishedFirst == 0){finishedFirst = 1;}
	}
	
	else if(stateMarTop == 0){
		if(buttonsLast[0] == 1){
			if((yMarTop < 0 && xMarTop != 0) || !(xMarTop == 0 || marioBack[levelMark][yMarTop][xMarTop - 1] == GREEN)){
				xMarTop--;
			}
		}
		if(buttonsLast[1] == 1){
			if((yMarTop < 0 && xMarTop != MARIOLINE[levelMark] - 1) || !(xMarTop == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarTop][xMarTop + 1] == GREEN)){
				xMarTop++;
			}
		}
		if(buttons[2] == 1){
			if(yMarTop <= 0 || marioBack[levelMark][yMarTop - 1][xMarTop] != GREEN){
				yMarTop--;
				stateMarTop = 1;
			}
		}
		if(stateMarTop == 0){
			if(yMarTop < -1 || marioBack[levelMark][yMarTop + 1][xMarTop] != GREEN){
				yMarTop++;
			}
		}
	}
	
	else if(stateMarTop == 1){
		if(buttonsLast[0] == 1){
			if((yMarTop < 0 && xMarTop != 0) || !(xMarTop == 0 || marioBack[levelMark][yMarTop][xMarTop - 1]  == GREEN)){
				xMarTop--;
			}
		}
		if(buttonsLast[1] == 1){
			if((yMarTop < 0 && xMarTop != MARIOLINE[levelMark] - 1) || !(xMarTop == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarTop][xMarTop + 1] == GREEN)){
				xMarTop++;
			}
		}
		if(yMarTop <= 0 || marioBack[levelMark][yMarTop - 1][xMarTop] != GREEN){
				yMarTop--;
				stateMarTop = 2;
		}
		else{
			stateMarTop = 2;
		}
	}
	
	else if(stateMarTop == 2){
		if(buttonsLast[0] == 1){
			if((yMarTop < 0 && xMarTop != 0) || !(xMarTop == 0 || marioBack[levelMark][yMarTop][xMarTop - 1]  == GREEN)){
				xMarTop--;
			}
		}
		if(buttonsLast[1] == 1){
			if((yMarTop < 0 && xMarTop != MARIOLINE[levelMark] - 1) || !(xMarTop == MARIOLINE[levelMark] - 1 || marioBack[levelMark][yMarTop][xMarTop + 1] == GREEN)){
				xMarTop++;
			}
		}
		if(yMarTop < -1 || marioBack[levelMark][yMarTop + 1][xMarTop] != GREEN){
			yMarTop++;
		}
		else{
			stateMarTop = 0;
		}
	}
	
	if(xMarTop == MARIOLINE[levelMark] - 1){
		stateMarTop = 3;
	}
	
	
	
	
	
	
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
	
	if(yMarTop >= 4){
		yMarTop = yStarts[levelMark];
		xMarTop = xStarts[levelMark];
	}
	
	if(yMarBot >= 4){
		yMarBot = yStarts[levelMark];
		xMarBot = xStarts[levelMark];
	}
	
	
	fixAllMario();
	if(yMarTop >= 0){
		marioBack[levelMark][yMarTop][xMarTop] = BLUE;
	}
	yDrawTop = 0;
	xDrawTop = xMarTop - 3;
	if (xDrawTop < 0){xDrawTop = 0;}
	loadtoBackBufferFullMario(xDrawTop, yDrawTop, 0, 0, 0, 0, 1, 0, 0);
	fixAllMario();
	if(yMarBot >= 0){
		marioBack[levelMark][yMarBot][xMarBot] = BLUE;
	}
	yDrawBot = 0;
	xDrawBot = xMarBot - 3;
	if (xDrawBot < 0) {xDrawBot = 0;}
	loadtoBackBufferFullMario(xDrawBot, yDrawBot, 0, 4, 0, 0, 1, 0, 1);
	swapScreens();
	delay(6000);
	if(topDone == 1 && botDone == 1){
		return finishedFirst + 1;
	}
	else{
		return 1;
	}
}
