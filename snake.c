#include "list.h"
#include "time.h" 
const int gridWidth = 8;
const int gridLength = 8;

typedef struct {
  int x;
  int y;
} coordinate;

coordinate *head;
coordinate *fruit;
int gameState = 0;

/*Directions
   1: Up
   2: Right
   3: Down
   4: Left

 */
int direction = 1;

List *snake;
coordinate *coordinate_create(int x, int y);
void coordinate_destroy(coordinate *coord);
void initGame(void);

void updateBoard(void);
void moveBody(void);
void move(void);
void checkUpdate(void);
void generateFruit(void);
void growSnake(void);
int selfCollision(void);
void endGame(void);
void clearGame(void);
void resetGame(void);
int playSnake(void);

coordinate *coordinate_create(int x, int y) {
  coordinate *coord = malloc(sizeof(coordinate));
  coord->x = x;
  coord->y = y;
  return coord;
}

void coordinate_destroy(coordinate *coord) {
  free(coord);
}

void initGame(void) {
	coordinate *tail1;
  coordinate *tail2;
  gameState = 1;


  snake = List_create();

  /*Create inital snake of 3 length at bottom left of display*/
  fruit = coordinate_create(5, 1);
  head = coordinate_create(4, 6);
	tail1 = coordinate_create(4, 6);
	tail2 = coordinate_create(4, 6);
  
	List_push(snake, head);
  List_push(snake, tail1);
  List_push(snake, tail2);
}

void moveBody(void){
	ListNode *temp = snake->last;
	while(temp->prev != NULL){
		((coordinate *)temp->value)->x = ((coordinate*)temp->prev->value)->x;
		((coordinate *)temp->value)->y = ((coordinate*)temp->prev->value)->y;
		temp = temp->prev;
	}
}

void move(void) {
  switch (direction) {
  case 1:
    moveBody();
		head->y--;
    break;
  case 2:
		moveBody();
    head->x++;
    break;
  case 3:
    moveBody();
		head->y++;
    break;
  case 4:
    moveBody();
		head->x--;
  }
}

void generateFruit(void) {
	int overlap = 0;
	time_t t = time(NULL);
	srand(t);
	
	do {
		fruit->x = rand() % 7;
		fruit->y = rand() % 7;
		ListNode *temp = snake->first;
		while(temp != NULL){
			if(fruit->x == ((coordinate *)temp->value)->x && fruit->y == ((coordinate *)temp->value)->y){
				overlap = 1;
			}
			temp = temp->next;
		}
	} while( overlap );	
}

void growSnake(void) {
  int x = ((coordinate *)snake->last->value)->x;
  int y = ((coordinate * )snake->last->value)->y;
  coordinate *coord = coordinate_create(x, y);
  List_push(snake, coord);
}

int selfCollision(void) {
  ListNode *temp = snake->first->next;
  while (temp != NULL) {
    if (((coordinate*) temp->value)->x == head->x && ((coordinate *)temp->value)->y == head->y) {
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

void checkState(void) {

  // snake out of bounds
  if (head->x < 0 || head->x > 7 || head->y < 0 || head->y > 7) {
    gameState = 0;
  } else if (head->x == fruit->x && head->y == fruit->y) {
    generateFruit();
    growSnake();
  } else if (selfCollision()) {
    gameState = 0;
  }
}

void updateBoard(void) {
	
	ListNode *temp; 
	temp = snake->first;
  clearBack();
	
	while(temp != NULL){
		int x = ((coordinate *)(temp->value))->x;
		int y = ((coordinate *)(temp->value))->y;
		backdrop[x][y] = 1;
		temp = temp->next;
	}

  backdrop[fruit->x][fruit->y] = 2;
}

void endGame(void) {
  List_clear_destroy(snake);
  coordinate_destroy(fruit);
}

void checkUpdate(void) {
  int left = buttonsLast[0];
  int right = buttonsLast[1];
  if (left) {
    switch (direction) {
    case 1:
      direction = 2;
      break;
    case 2:
      direction = 3;
      break;
    case 3:
      direction = 4;
      break;
    case 4:
      direction = 1;
			break;
    default:
      direction = 4;
    }
  } else if (right) {
    switch (direction) {
    case 1:
      direction = 4;
      break;
    case 2:
      direction = 1;
      break;
    case 3:
      direction = 2;
      break;
    case 4:
      direction = 3;
			break;
    default:
      direction = 4;
    }
  }
}

int playSnake(void) {
  if (!gameState) {
    initGame();
  }
  checkUpdate();
  move();
  checkState();
  if (gameState == 0) {
    endGame();
  } else {
    updateBoard();
  }

  swapScreens();
	delay(60000);

  return gameState;
}
