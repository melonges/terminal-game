#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#define Y 10
#define X 20
static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios() {
  tcgetattr(0, &old);              /* grab old terminal i/o settings */
  current = old;                   /* make new settings same as old settings */
  current.c_lflag &= ~ICANON;      /* disable buffered i/o */
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios() { tcsetattr(0, TCSANOW, &old); }

/* Read 1 character - echo defines echo mode */
char getch() {
  char ch;
  initTermios();
  ch = getchar();
  resetTermios();
  return ch;
}

char map[Y][X + 2];
int x = X >> 1;
int y = Y >> 1;
int dx, dy, i, ax = X / 3, ay = Y / 3, score = 0;
char key;

// void draw() {
//     system("clear");
//     for (i = 0; i < X; ++i)
//         map[0][i] = map[Y - 1][i] = '#';
//     map[0][X - 1] = map[Y - 1][X - 1] = '\n';
//
//     for (i = 1; i < Y - 1; i++) {
//        map[i][0] = map[i][X - 1] = '#';
//        map[i][X] = '\n';
//         for (int j = 1; j < X - 1; j++)
//             map[i][j] = ' ';
//     }
//
//     for (i = 0; i < Y; i++)
//         printf("%s", map[i]);
// }

void draw() {
  system("clear");
  printf("Score: %d\n", score);
  sprintf(map[0], "####################\n");
  sprintf(map[Y - 1], "####################\n");
  for (i = 1; i < Y - 1; i++)
    sprintf(map[i], "#                  #\n");

  map[y][x] = 'X';
  map[ay][ax] = '@';

  for (i = 0; i < Y; i++)
    printf("%s", map[i]);
}
void game_control() {
  key = getch();
  dx = x;
  dy = y;
  if (key == 'a')
    x--;
  if (key == 'd')
    x++;
  if (key == 'w')
    y--;
  if (key == 's')
    y++;
  if (map[y][x] == '#')
    x = dx, y = dy;
}

void game_logic() {
  if (ay == y && ax == x) {
    score++;
    ax = rand() % (X - 2) + 1;
    ay = rand() % (Y - 3) + 1;
  }
}

int main() {
  srand(time(NULL));
  do {
    draw();
    game_control();
    game_logic();
  } while (key != 'e');
  system("clear");
  return 0;
}
