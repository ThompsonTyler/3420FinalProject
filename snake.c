#include "list.h"
const int gridWidth = 8;
const int gridLength = 8;

typedef struct {
  int x;
  int y;
} coordinate;

coordinate *head;
coordinate *intermediate;
coordinate *fruit;
int gamestate = 0;

/*Directions
   1: Up
   2: Right
   3: Down
   4: Left

 */
int direction = 2;

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
  coordinate *coord = malloc(sizeof(coordiate));
  coord->x = x;
  coord->y = y;
  return coord;
}

void coordinate_destroy(coordinate *coord) {
  assert(coord != NULL);

  free(coord);
}

void initGame(void) {
  int gamestate = 1;

  backdrop = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 2, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
              {0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};

  snake = List_create();

  /*Create inital snake of 3 length at bottom left of display*/
  fruit = cooridate_create(5, 1);
  head = coordinate_create(4, 6);
  intermediate = coordinate_create(4, 6);

  List_push(snake, head);
  coordinate *tail1 = coordinate_create(3, 6);
  List_push(snake, tail1);
  coordinate *tail2 = coordinate_create(2, 6);
  List_push(snake, tail2);
}

void moveBody(void) {
  ListNode *temp = snake->first->next;
  while (temp != NULL) {
    int tempx = temp->value->x;
    int tempy = temp->value->y;
    temp->value->x = intermediate->x;
    temp->value->y = intermediate->y;
    intermediate->x = tempx;
    intermediate->y = tempy;
    temp = temp->next;
  }
}

void move(void) {
  switch (direction) {
  case 1:
    head->y++;
    moveBody(snake);
    break;
  case 2:
    head->x++;
    moveBody(snake);
    break;
  case 3:
    head->y--;
    moveBody(snake);
    break;
  case 4:
    head->x--;
    moveBody(snake);
  default:
  }
}

void generateFruit(void) {
  srand(time());
  fruit->x = rand() % 7;
  fruit->y = rand() % 7;
}

void growSnake(void) {
  int x = snake->last->value->x;
  int y = snake->last->value->y;
  coordinate *coord = coordinate_create(x, y);
  List_push(snake, coord);
}

int selfCollision(void) {
  ListNode *temp = snake->first->next;
  while (temp != NULL) {
    if (temp->value->x == head->x && temp->value->y == head->y) {
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

void checkState(void) {

  // snake out of bounds
  if (head->x < 0 || head->x > 7 || head->y < 0 || head->y > 7) {
    gamestate = 0;
  } else if (head->x == fruit->x && head->y == fruit->y) {
    generateFruit();
    growSnake();
  } else if (selfCollision()) {
    gamestate = 0;
  }
}

void updateBoard(void) {
  clearBack();
  LIST_FOREACH(snake, first, next, cur) { board[cur->x][cur->y] = 1; }

  backdrop[fruit->x][fruit->y] = 2;
}

void endGame(void) {
  List_destroy(snake);
  coordinate_destroy(intermediate);
  coordinate_destroy(fruit);
}

void checkUpdate(void) {
  int left = buttons[0];
  int right = buttons[1];
  if (left) {
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
    default:
      direction = 1;
    }
  } else if (right) {
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
    default:
      direction = 1;
    }
  }
}

int playSnake(void) {
  if (!gamestate) {
    initGame();
  }
  checkUpdate();
  move();
  checkState();
  if (gamestate == 0) {
    endGame();
  } else {
    updateBoard();
    delay(1000);
  }

  swapScreens();

  return gamestate;
}
