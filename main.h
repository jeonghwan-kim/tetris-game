#ifndef __MY_MAIN_H
#define __MY_MAIN_H

enum {EMPTY, WALL, BLOCK};
enum {BR=15, BC=10}; // BoardRow, BoardCol
enum {LEFT=106, RIGHT=108, UP=105, DOWN=107}; // key value
int board[BR+2][BC+2]; // cause of wall 
struct POS {
	int row, col;
};

// draw.c
void drawBoard(int r, int c);
void drawBlock(int cr, int cc, int cb, int cs, int flag);

// gamecheck.c
int isTimerDone();
int isGameOver();
int isEmpty(int cr, int cc, int cb, int cs);
void testLineFull(int cr, int cc, int cb, int cs);

// console.c
int kbhit();
void gotoRowCol(int r, int c);
int getch();

// main.c
void initBoard(int r, int c);
void insertBlockInBoard(int cr, int cc, int cb, int cs);
void getNextBlock(int *, int *, int *, int *);
void processKey(int *, int *, int, int *);

#endif
