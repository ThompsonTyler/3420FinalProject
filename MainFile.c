#include "MainFile.h"

#define PTA1 1 //Pin Definitions for ease of use
#define PTA2 2
#define PTB9 3
#define PTB23 4
#define PTC2 5
#define HIGH 1
#define LOW 0

#define RESET	PTC2 //Pin location definitions
#define CLOCK PTA2
#define LATCH PTB23
#define DATA_OUTPUT_ENABLE PTA1
#define DATA PTB9

int buttons[6] = {0,0,0,0,0,0}; //Global variables for buttons. P1L, P1R, P1C. P2L, P2R, P2C. Becomes 1 on a rising edge
int buttonsLast[6] = {0,0,0,0,0,0}; //Real-time globals for buttons

int gamestate; //Integer representing game state:
							 /*
							 0: Start screens
							 1: Game (levels for 2p mario)
               2: End Screen (animation)
							 3: LGame (for 2p mario)
							 */
int end; //Integer representing conditional loop in final animation stage
int selector; //Integer representing the current game to select.
							/*
							0: Mario
							1: 2p Mario
							2: Snake
							*/

int selector_maps; //Integer representing current map for mario 2p.

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
																 {3,3,0,0,0,0,3,3}},

																 {{7,7,7,7,7,7,7,7}, //Snake
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {7,6,7,3,2,2,7,7},
																 {7,7,7,7,7,2,7,7},
																 {7,7,7,7,7,2,7,7},
																 {7,7,7,7,7,2,2,7},
																 {7,7,7,7,7,7,7,7}}};

uint8_t map_screens[4][8][8] = {{{7,7,7,7,7,7,7,7}, //Platform Level
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,6,7,7,7,7},
																 {6,6,7,7,7,6,7,6}},

																{{7,7,7,7,7,7,7,7}, //Paths Level
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {6,6,6,6,6,6,6,7},
																 {7,7,7,7,7,7,6,7},
																 {7,6,6,6,6,6,6,7},
																 {7,7,7,7,7,7,7,7},
																 {6,6,6,6,6,6,6,6}},
																
																{{7,7,7,7,7,7,7,7}, //Runner Level
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,7,7,7,7},
																 {7,7,7,7,6,7,7,7},
																 {7,7,7,6,7,6,7,7},
																 {6,6,6,7,7,7,6,6}},
																
																{{7,7,7,7,7,6,6,6}, //Maze Level
																 {7,7,7,7,7,6,7,7},
																 {7,7,7,7,7,6,7,6},
																 {7,6,6,6,6,6,7,6},
																 {6,6,7,7,7,7,7,6},
																 {7,7,7,6,6,6,6,6},
																 {7,7,7,7,7,7,7,6},
																 {6,6,6,6,6,6,6,6}}};

void delay(int count){	//Delays as needed
	int j;
	for(j = 0; j < count; j++);
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
	PIT->CHANNEL[0].TCTRL = 1;
	
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
	PIT->CHANNEL[0].TCTRL = 3;
}

void clearBack(void){ //Set backdrop to empty/clear
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < 8; lineIndex++){
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			backdrop[rowIndex][lineIndex] = CLEAR;
		}
	}
}

void clearScreen(void){ //Set screen to empty/clear
	uint8_t lineIndex;
	uint8_t rowIndex;
	
	for(lineIndex = 0; lineIndex < 8; lineIndex++){
		for(rowIndex = 0; rowIndex < 8; rowIndex++){
			Screen[rowIndex][lineIndex] = CLEAR;
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

void setupPins(void){ //Setups the pins starting position for controlling shift registers
	pinTrigger(DATA_OUTPUT_ENABLE, LOW);
	pinTrigger(RESET, HIGH);
	pinTrigger(CLOCK, LOW);
	pinTrigger(LATCH, LOW);
	pinTrigger(DATA, LOW);
}

void checkButtons(){  //Checks the state of all buttons, setting buttons to 1 on rising edge and buttonsLast to the real-time state
	__disable_irq();
	if(PTB->PDIR & 8){ //Button PTB3, P1L
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
	
	if(PTB->PDIR & 4){ //Button PTB2, P1R
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
	__enable_irq();
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

void maptoBack(void){ //Sets backdrop to the map_screen represented by the global variable selector_maps
	uint8_t lineIndex;
  uint8_t rowIndex;

  for(lineIndex = 0; lineIndex < 8; lineIndex++){
    for(rowIndex = 0; rowIndex < 8; rowIndex++){	
			backdrop[rowIndex][lineIndex] = map_screens[selector_maps][rowIndex][lineIndex];
    }
  }
}

void PIT0_IRQHandler(void){ //Handler for interrupt for displaying to matrix
	PIT->CHANNEL[0].TFLG = 1;
	sendDataFromArray();
	PIT -> CHANNEL[0].LDVAL = 0x85EA;
}

int main(void){
	int modLoads = sizeof(load_screens) / sizeof(load_screens[0]); //Get size of load screens
	int modMaps = sizeof(map_screens) / sizeof(map_screens[0]); //Get size of maps
	int statusGame;
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
	end = 1;
	selector = 0;
	while(1){ //Check if game is done or not
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
			if(selector == 0){//Mario 1p
				statusGame = play1pMario();//Run mario game engine
				if(statusGame != 1){//Check if game is done
					if(statusGame == 5){
						buildScroller("1P MARIO NEEDS RESET");
					}
					else{
						buildScroller("YOU WIN");
					}
					gamestate = 2; //Move to final animation
				}
			}
			else if(selector == 1){ //Mario 2p Maps
				if(buttons[0] == 1){//Move Left
					selector_maps--;
				}
				if(buttons[1] == 1){//Move Right
					selector_maps++;
				}
				if(buttons[2] == 1){//Select Map
					setLevel(selector_maps);//Set map as destination
					gamestate = 3;//Move to 2p Mario
				}
				selector_maps = mod(selector_maps, modMaps); //Clip to bounds of 2p mario maps
				maptoBack();	//Push map to backdrop
				swapScreens();	//update screen to map
			}
			else if(selector == 2){//Snake
				statusGame = playSnake(); 
				if(statusGame != 1){//Check if done yet
					gamestate = 2;
				}
			}
		}
		else if (gamestate == 3){ //2p Mario
			statusGame = play2pMario();//Play 2p Mario
			if(statusGame != 1){//Check if done
				mario2pReset();//Reset for next time
				if(statusGame == 2){//Player 1 wins
					buildScroller("P1 WINS");
				}
				else{//Player 2 wins
					buildScroller("P2 WINS");
				}
				gamestate = 2;//Go to final animation
			}
		
		}
		else if(gamestate == 2){//Finishing animation
			if(buttons[2] == 1){//Check for select button 
				gamestate = 0;//Go to game select
			}
			else{
				if(end == 1){//Wait for scroll to end
					end = scroll(1, BLUE);
				}
				else{//Once it does, update player that they can press select to play again
					buildScroller("CLICK TO PLAY AGAIN");
					end = 1;
				}
			}
		}
	}
	
}
