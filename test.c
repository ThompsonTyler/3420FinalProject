#include "MK64F12.h"

#define PTA1 1 //Pin Definitions for ease of use
#define PTA2 2
#define PTB9 3
#define PTB23 4
#define PTC2 5
#define HIGH 1
#define LOW 0

#define WHITE  0 //Color Definitions
#define MAGENTA 1
#define YELLOW 2
#define RED 3
#define CYAN 4
#define BLUE 5
#define GREEN 6
#define CLEAR 7

#define RESET	PTC2 //Pin location definitions
#define CLOCK PTA2
#define LATCH PTB23
#define DATA_OUTPUT_ENABLE PTA1
#define DATA PTB9

#define MARIOLINE 20 //Matrix size definitions. [Row][Line]
#define MARIOROW 8

int buttons[6] = {0,0,0,0,0,0}; //Global variables for buttons. P1L, P1R, P1C. P2L, P2R, P2C. Becomes 1 on a rising edge
int buttonsLast[6] = {0,0,0,0,0,0}; //Real-time globals for buttons

int gamestate; //Integer representing game state:
							 /*
							 0: Start screens
							 1: Game
               2: End Screen (animation)
							 */
int end; //Integer representing overall conditional loop for exit set to 1.
int selector; //Integer representing the current game to select.
							/*
							0: Mario
							*/


 uint8_t Screen[8][8] = {{0,0,0,0,0,0,0,0}, //Screen that is displayed from sendDataFromArray()
												 {0,0,0,0,0,0,0,0},
												 {0,0,0,0,0,0,0,0},
												 {0,0,0,0,0,0,0,0},
												 {0,0,0,0,0,0,0,0},
												 {0,0,0,0,0,0,0,0},
												 {0,0,0,0,0,0,0,0},
												 {0,0,0,0,0,0,0,0}};
 
uint8_t backdrop[8][8] = {{0,0,0,0,0,0,0,0}, //Screen reprsenting the back end, edit this and when complete set screen equal
													{0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0},
													{0,0,0,0,0,0,0,0}};

uint8_t marioBack[8][20] = {{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,3},  //Map for mario
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,3},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,6,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,6,3},
														{7,7,7,7,7,7,7,6,6,6,6,6,7,6,6,7,7,7,7,0},
														{7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,7,7,7,6,3},
														{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,0}};
										
uint8_t load_screens[3][8][8] = {{{CLEAR,CLEAR,CLEAR,RED,RED,RED,WHITE,CLEAR}, //Mario Character
																 {CLEAR,CLEAR,CLEAR,RED,RED,RED,RED,RED},
																 {CLEAR,CLEAR,YELLOW,WHITE,YELLOW,GREEN,WHITE,CLEAR},
																 {CLEAR,CLEAR,YELLOW,WHITE,WHITE,YELLOW,YELLOW,WHITE},
																 {CLEAR,CLEAR,CLEAR,YELLOW,WHITE,WHITE,WHITE,CLEAR},
																 {CLEAR,RED,RED,CYAN,BLUE,BLUE,RED,CLEAR},
																 {WHITE,CLEAR,BLUE,BLUE,BLUE,CYAN,CYAN, WHITE},
																 {CLEAR,CLEAR,MAGENTA,CLEAR,CLEAR,CLEAR,MAGENTA,CLEAR}},

																 {{3,3,0,0,0,0,3,3}, //Red and white M
																 {3,3,3,0,0,3,3,3},
																 {3,3,3,0,0,3,3,3},
																 {3,3,3,3,3,3,3,3},
																 {3,3,0,3,3,0,3,3},
																 {3,3,0,0,0,0,3,3},
																 {3,3,0,0,0,0,3,3},
																 {3,3,0,0,0,0,3,3}}};										
										
uint8_t Scene[12][8][8] = {{{0,7,7,7,7,7,7,7}, //Clear animation- Cyan/white scroller
													 {4,0,7,7,7,7,7,7},
													 {4,0,7,7,7,7,7,7},
													 {4,0,7,7,7,7,7,7},
													 {4,0,7,7,7,7,7,7},
													 {4,0,7,7,7,7,7,7},
												 	 {4,0,7,7,7,7,7,7},
													 {0,7,7,7,7,7,7,7}},

													{{7,7,7,7,7,7,7,7},
													 {0,0,7,7,7,7,7,7},
													 {4,4,0,7,7,7,7,7},
													 {4,4,4,0,7,7,7,7},
													 {4,4,4,0,7,7,7,7},
													 {4,4,0,7,7,7,7,7},
													 {0,0,7,7,7,7,7,7},
													 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,7},
													 {7,7,7,7,7,7,7,7},
													 {0,0,0,0,7,7,7,7},
													 {4,4,4,4,0,7,7,7},
													 {4,4,4,4,0,7,7,7},
                    			 {0,0,0,0,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,0,0,0,0,7,7},
                    			 {7,0,4,4,4,4,0,7},
                    			 {7,0,4,4,4,4,0,7},
                   			   {7,7,0,0,0,0,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,0,0,0,0},
                    			 {7,7,7,0,4,4,4,4},
                    			 {7,7,7,0,4,4,4,4},
                    			 {7,7,7,7,0,0,0,0},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,0,0},
                    			 {7,7,7,7,7,0,4,4},
                    			 {7,7,7,7,0,4,4,4},
                    			 {7,7,7,7,0,4,4,4},
                    			 {7,7,7,7,7,0,4,4},
                    			 {7,7,7,7,7,7,0,0},
                    			 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,0},
                    			 {7,7,7,7,7,7,0,4},
                    			 {7,7,7,7,7,7,0,4},
                    			 {7,7,7,7,7,7,0,4},
                    			 {7,7,7,7,7,7,0,4},
                    			 {7,7,7,7,7,7,0,4},
                    			 {7,7,7,7,7,7,0,4},
                    			 {7,7,7,7,7,7,7,0}},
										
													{{7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,0,0},
                    			 {7,7,7,7,7,0,4,4},
                    			 {7,7,7,7,0,4,4,4},
                    			 {7,7,7,7,0,4,4,4},
                    			 {7,7,7,7,7,0,4,4},
                    			 {7,7,7,7,7,7,0,0},
                    			 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,0,0,0,0},
                    			 {7,7,7,0,4,4,4,4},
                    			 {7,7,7,0,4,4,4,4},
                    			 {7,7,7,7,0,0,0,0},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,0,0,0,0,7,7},
                    			 {7,0,4,4,4,4,0,7},
                    			 {7,0,4,4,4,4,0,7},
                    			 {7,7,0,0,0,0,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {0,0,0,0,7,7,7,7},
                    			 {4,4,4,4,0,7,7,7},
                    			 {4,4,4,4,0,7,7,7},
                    			 {0,0,0,0,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7}},
										
													{{7,7,7,7,7,7,7,7},
                    			 {0,0,7,7,7,7,7,7},
                    			 {4,4,0,7,7,7,7,7},
                    			 {4,4,4,0,7,7,7,7},
                    			 {4,4,4,0,7,7,7,7},
                    			 {4,4,0,7,7,7,7,7},
                    			 {0,0,7,7,7,7,7,7},
                    			 {7,7,7,7,7,7,7,7}}};

													 
void delay(void){	//Delay for animation
	int j;
	for(j = 0; j < 5000; j++);
}
 
int mod (int a, int b){//Modulo operator to act correctly with negative numbers, not remainder as c does with %
   int ret;
	 if(b < 0)
     return mod(-a, -b);   
   ret = a % b;
   if(ret < 0)
     ret+=b;
   return ret;
}

void PIN_Initialize(void){
	SIM->SCGC5    |= (1 << 9) | (1 << 10) | (1 << 11); // Enable clock to port A, B, C
	PORTA->PCR[1]  = (1 << 8); //Pin A1  GPIO
	PORTA->PCR[2]  = (1 << 8); //Pin A2  GPIO
	PORTB->PCR[2]  = (1 << 8); //Pin B2  GPIO
	PORTB->PCR[3]  = (1 << 8); //Pin B3  GPIO
	PORTB->PCR[9]  = (1 << 8); //Pin B9  GPIO
	PORTB->PCR[10] = (1 << 8); //Pin B10 GPIO
	PORTB->PCR[11] = (1 << 8); //Pin B11 GPIO
	PORTB->PCR[23] = (1 << 8); //Pin B23 GPIO
	PORTC->PCR[2]  = (1 << 8); //Pin C2  GPIO
	PORTC->PCR[10] = (1 << 8); //Pin C10 GPIO
	PORTC->PCR[11] = (1 << 8); //Pin C11 GPIO
	
	PTA->PDDR = (1 << 1 | 1 << 2); //PTA1,2 OUTPUT
	PTB->PDDR = (1 << 9 | 1 << 23 | 0 << 2 | 0 << 3 | 0 << 10 | 0 << 11); //PTB9,23 OUTPUT. PTB2,3,10,11 INPUT
	PTC->PDDR = (1 << 2 | 0 << 10 | 0 << 11); //PTC2 OUTPUT. PTC10, 11 INPUT
}

void pinTrigger(int pin, int level){ //Function to ease setting outputs, Pin is based on definitions above, level is HIGH/LOW
	switch(pin){
		case 1:
			if (level == 1){
				PTA->PSOR = (1 << 1);
			}
			else{
				PTA->PCOR = (1 << 1);
			}
			break;
		
		case 2:
			if (level == 1){
				PTA->PSOR = (1 << 2);
			}
			else{
				PTA->PCOR = (1 << 2);
			}
			break;
		
		case 3:
			if (level == 1){
				PTB->PSOR = (1 << 9);
			}
			else{
				PTB->PCOR = (1 << 9);
			}
			break;
		
		case 4:
			if (level == 1){
				PTB->PSOR = (1 << 23);
			}
			else{
				PTB->PCOR = (1 << 23);
			}
			break;
		
		case 5:
			if (level == 1){
				PTC->PSOR = (1 << 2);
			}
			else{
				PTC->PCOR = (1 << 2);
			}
			break;
	}
}

void sendBit(int data){ //Function that sends 1 bit along shift register
	pinTrigger(DATA, data);
	pinTrigger(CLOCK, HIGH);
	pinTrigger(CLOCK, LOW);
	pinTrigger(DATA, LOW);
}

void sendDataFromArray(void){ //Iterates through screen and displays to matrix
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < 8; lineIndex++){
		//Ground anode
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			if(lineIndex == rowIndex){
				sendBit(HIGH);
			}
			else{
				sendBit(LOW);
			}
		}
		
		//Green Line
		for(rowIndex = 0; rowIndex < 8; rowIndex ++){
			if ((Screen[rowIndex][lineIndex] & 1)){
				sendBit(HIGH);
			}
			else{
				sendBit(LOW);
			}
		}
		
		//Red Line
		for(rowIndex = 0; rowIndex < 8; rowIndex ++){
			if ((Screen[rowIndex][lineIndex] & 2)){
				sendBit(HIGH);
			}
			else{
				sendBit(LOW);
			}
		}
		
		//Blue Line
		for(rowIndex = 0; rowIndex < 8; rowIndex ++){
			if ((Screen[rowIndex][lineIndex] & 4)){
				sendBit(HIGH);
			}
			else{
				sendBit(LOW);
			}
		}
		
		//Force data
		pinTrigger(LATCH, HIGH);
		pinTrigger(LATCH, LOW);
	}
}

void clearScreen(void){ //Set screen to empty/clear
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < 8; lineIndex++){
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			backdrop[rowIndex][lineIndex] = CLEAR;
		}
	}
}

void swapScreens(void){ //Writes the content of the backdrop to screen
	uint8_t lineIndex;
	uint8_t rowIndex;
	__disable_irq();
	
	for(lineIndex = 0; lineIndex < 8; lineIndex++){
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			Screen[rowIndex][lineIndex] = backdrop[rowIndex][lineIndex];
		}
	}
	__enable_irq();
}

void rainbowTest(void) //Writes a rainbow to backdrop
{  
  uint8_t lineIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    backdrop[lineIndex][0] = 0;
    backdrop[lineIndex][1] = 1;
    backdrop[lineIndex][2] = 2;
    backdrop[lineIndex][3] = 3;
    backdrop[lineIndex][4] = 4;
    backdrop[lineIndex][5] = 5;
    backdrop[lineIndex][6] = 6;
    backdrop[lineIndex][7] = 7;
  }
}

void setupPins(void){ //Setups the pins starting position for controlling shift registers
	pinTrigger(DATA_OUTPUT_ENABLE, LOW);
	pinTrigger(RESET, HIGH);
	pinTrigger(CLOCK, LOW);
	pinTrigger(LATCH, LOW);
	pinTrigger(DATA, LOW);
}

void checkButtons(){  //Checks the state of all buttons, setting buttons to 1 on rising edge and buttonsLast to the real-time state
	if(PTB->PDIR & 4){ //Button PTB2, P1L
		if(buttonsLast[0]){
			buttons[0] = 0;
		}
		else{
			buttons[0] = 1;
		}
		buttonsLast[0] = 1;
	}
	else{
		buttons[0] = 0;
		buttonsLast[0] = 0;
	}
	
	if(PTB->PDIR & 8){ //Button PTB3, P1R
		if(buttonsLast[1]){
			buttons[1] = 0;
		}
		else{
			buttons[1] = 1;
		}
		buttonsLast[1] = 1;
	}
	else{
		buttons[1] = 0;
		buttonsLast[1] = 0;
	}
	
	if(PTB->PDIR & 1024){ //Button PTB10, P1C
		if(buttonsLast[2]){
			buttons[2] = 0;
		}
		else{
			buttons[2] = 1;
		}
		buttonsLast[2] = 1;
	}
	else{
		buttons[2] = 0;
		buttonsLast[2] = 0;
	}
	
	if(PTB->PDIR & 2048){ //Button PTB11, P2L
		if(buttonsLast[3]){
			buttons[3] = 0;
		}
		else{
			buttons[3] = 1;
		}
		buttonsLast[3] = 1;
	}
	else{
		buttons[3] = 0;
		buttonsLast[3] = 0;
	}
	
	if(PTC->PDIR & 2048){ //Button PTC11, P2R
		if(buttonsLast[4]){
			buttons[4] = 0;
		}
		else{
			buttons[4] = 1;
		}
		buttonsLast[4] = 1;
	}
	else{
		buttons[4] = 0;
		buttonsLast[4] = 0;
	}
	
	if(PTC->PDIR & 1024){ //Button PTC10, P2C
		if(buttonsLast[5]){
			buttons[5] = 0;
		}
		else{
			buttons[5] = 1;
		}
		buttonsLast[5] = 1;
	}
	else{
		buttons[5] = 0;
		buttonsLast[5] = 0;
	}
}


void updateSheet(int state, uint8_t color){ //Iterates through animation held in Scene with state being the animation frame and color being the background color
	uint8_t lineIndex;
  uint8_t rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++)
  {
    for(rowIndex = 0; rowIndex < 8; rowIndex++)
    {	
			if (Scene[state][rowIndex][lineIndex] == 7){
				backdrop[rowIndex][lineIndex] = color;
			}
			else{
				backdrop[rowIndex][lineIndex] = Scene[state][rowIndex][lineIndex];
			}
    }
  }
}

void loadtoBack(void){ //Sets backdrop to the load_screen represented by the global variable selector
	uint8_t lineIndex;
  uint8_t rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++){
    for(rowIndex = 0; rowIndex < 8; rowIndex++){	
			backdrop[rowIndex][lineIndex] = load_screens[selector][rowIndex][lineIndex];
    }
  }
}

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

int xMar = 2; //Variable representing xPosition for mario 1p(Left = 0)
int yMar = 6; //Variable representing yPosition for mario 1p(Top = 0)
int stateMar = 0; // State diagram:
// 0: Walk.   1: JumpState 1. 2: JumpState 2.5.  3:Jumpstate 1.5   4: Jumpstate 2 6: End

int playMario(void){ //Return 0 if terminate, 1 if not done yet
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

int main(void){
	int modLoads = sizeof(load_screens) / sizeof(load_screens[0]);
	int statusGame;
	int i;
	//Interrupt and basic setups, do not remove
	SIM -> SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT -> MCR = 0;
	PIT -> CHANNEL[0].LDVAL = 0x85EA;
	PIT -> CHANNEL[0].TCTRL = 3;
	PIN_Initialize();
	setupPins();
	NVIC_EnableIRQ(PIT0_IRQn);
	//End of interrupt/basic setups
	gamestate = 0; //Default values
	end = 0;
	selector = 0;
	while(!end){ //Check if game is done or not
		checkButtons();//Update buttons
		if(gamestate == 0){ //Check if we are in loadscreen position
			if(buttons[0] == 1){//Move right
				selector--;
			}
			if(buttons[1] == 1){//Move left
				selector++;
			}
			if(buttons[2] == 1){//Select game
				gamestate = 1;
			}
			selector = mod(selector, modLoads); //Clip to bounds of loadscreens
			loadtoBack(); //Push loadscreen to backdrop
			swapScreens();//update screen to loadscreen
		}
		else if(gamestate == 1){ //Game being played
			if(selector == 0 || 1){//Mario 1p
				statusGame = playMario();//Run mario game engine
				for(i = 0; i < 1000; i ++){};//Slight delay to allow for human interaction
				if(statusGame == 0){//Check if game is done
					end = 1;
				}
			}
		}
	}
	
	while(1){ //Display Winning animation
		delay(); 
		selector++;
		selector = mod(selector, 12);
		updateSheet(selector, RED);
		swapScreens();
	}
}	

void PIT0_IRQHandler(void){
	PIT->CHANNEL[0].TFLG = 1;
	sendDataFromArray();
}