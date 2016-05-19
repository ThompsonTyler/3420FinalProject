#include "list.h"
const int gridWidth = 8;
const int gridLength = 8;
char scorez[8];

typedef struct {
  int x;
  int y;
} coordinate;

coordinate *head;
coordinate *fruit;
int score = 0;
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

void coordinate_destroy(coordinate *coord) { free(coord); }

/*Initializes the snake game*/
void initGame(void) {
  coordinate *tail1;
  coordinate *tail2;
  gameState = 1;
  direction = 1;
  score = 0;

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

/*Moves every node to its previous node's location*/
void moveBody(void) {
  ListNode *temp = snake->last;
  while (temp->prev != NULL) {
    ((coordinate *)temp->value)->x = ((coordinate *)temp->prev->value)->x;
    ((coordinate *)temp->value)->y = ((coordinate *)temp->prev->value)->y;
    temp = temp->prev;
  }
}

/*Updates the head of and body of the snake in current direction*/
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

/*Generates a fruit in an open location*/
void generateFruit(void) {
  ListNode *temp;
  int overlap;

  do {
    temp = snake->first;
    fruit->x = rand() % 7;
    fruit->y = rand() % 7;
    overlap = 0;
    while (temp != NULL) {
      if (fruit->x == ((coordinate *)temp->value)->x &&
          fruit->y == ((coordinate *)temp->value)->y) {
        overlap = 1;
      }
      temp = temp->next;
    }
  } while (overlap);
}

/*appends a segment to the snake*/
void growSnake(void) {
  int x = ((coordinate *)snake->last->value)->x;
  int y = ((coordinate *)snake->last->value)->y;
  coordinate *coord = coordinate_create(x, y);
  List_push(snake, coord);
  score++;
}

/*Returns 1 if the head of the snake touches its body, 0 otherwise*/
int selfCollision(void) {
  ListNode *temp = snake->first->next;
  while (temp != NULL) {
    if (((coordinate *)temp->value)->x == head->x &&
        ((coordinate *)temp->value)->y == head->y) {
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}
/*Updates the gameState depending on collision or eating fruit*/
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

/*updates the backdrop to reflect current game configuration*/
void updateBoard(void) {

  ListNode *temp;
  temp = snake->first;
  clearBack();

  backdrop[((coordinate *)(temp->value))->x][((coordinate *)(temp->value))->y] =
      3;
  temp = temp->next;

  while (temp != NULL) {
    int x = ((coordinate *)(temp->value))->x;
    int y = ((coordinate *)(temp->value))->y;
    backdrop[x][y] = 2;
    temp = temp->next;
  }

  backdrop[fruit->x][fruit->y] = 6;
}

/*Cleans up the games memory*/
void endGame(void) {
  List_clear_destroy(snake);
  coordinate_destroy(fruit);
}

/*Checks if buttons were pressed and updates the current direction*/
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

/*Snake game loop*/
int playSnake(void) {
  if (!gameState) {
    initGame();
  }
  checkUpdate();
  move();
  checkState();
  if (gameState == 0) {
    endGame();
    sprintf(scorez, "SCORE %d", score);
    buildScroller(scorez);
  } else {
    updateBoard();
  }

  swapScreens();
  delay(40000);

  return gameState;
}
