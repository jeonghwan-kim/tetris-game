#include <stdio.h>
#include <stdlib.h> // rand()
#include <sys/time.h> // srand()
#include <unistd.h> // time()
#include "main.h"



struct POS blocks[7][4][4] = 
{{{-1,-1,0,-1,0,0,0,1},{-1,1,-1,0,0,0,1,0},{0,-1,0,0,0,1,1,1},{1,-1,1,0,0,0,-1,0}},
	{{-1,1,0,1,0,0,0,-1},{-1,0,0,0,1,0,1,1},{1,-1,0,-1,0,0,0,1},{-1,-1,-1,0,0,0,1,0}},
	{{-1,-1,0,-1,0,0,1,0},{0,-1,0,0,-1,0,-1,1},{-1,-1,0,-1,0,0,1,0},{0,-1,0,0,-1,0,-1,1}},
	{{-1,1,0,1,0,0,1,0},{-1,-1,-1,0,0,0,0,1},{-1,1,0,1,0,0,1,0},{-1,-1,-1,0,0,0,0,1}},
	{{-1,0,0,0,0,-1,0,1},{-1,0,0,0,0,1,1,0},{0,-1,0,0,0,1,1,0},{-1,0,0,0,1,0,0,-1}},
	{{-1,-1,-1,0,0,0,0,-1},{-1,-1,-1,0,0,0,0,-1},{-1,-1,-1,0,0,0,0,-1},{-1,-1,-1,0,0,0,0,-1}},
	{{-1,0,0,0,1,0,2,0},{0,-1,0,0,0,1,0,2},{-1,0,0,0,1,0,2,0},{0,-1,0,0,0,1,0,2}}};

void initBoard(int r, int c)
{
	int i, j;
	
	for (i=0; i<r; i++) {
		for (j=0; j<c; j++) {
			board[i][j] = (i==0 | i==r-1 | j==0 | j==c-1) ? WALL : EMPTY;
		}
	}
}

void insertBlockInBoard(int cr, int cc, int cb, int cs)
{
	int i;
	for (i=0; i<4; i++) {
		board[cr+blocks[cb][cs][i].row][cc+blocks[cb][cs][i].col] = BLOCK;
	}
}

void getNextBlock(int *cb, int *cs, int *cr, int *cc)
{
	*cb = rand()%7;
	*cs = 0;
	*cr = 2; 
	*cc = 5;
}

void processKey (int *cr, int *cc, int cb, int *cs)
{
	int key = getch();
	switch (key) {
		case LEFT:
			if (isEmpty(*cr, (*cc)-1, cb, *cs)) {
				drawBlock(*cr, *cc, cb, *cs, 0);
				drawBlock(*cr, --(*cc), cb, *cs, 1);		
			}
			break;
		case RIGHT:
			if (isEmpty(*cr, (*cc)+1, cb, *cs)) {
				drawBlock(*cr, *cc, cb, *cs, 0);
				drawBlock(*cr, ++(*cc), cb, *cs, 1);
			}
			break;
		case UP:
			if (isEmpty(*cr, *cc, cb, ((*cs)+1)%4)) {
				drawBlock(*cr, *cc, cb, *cs, 0);
				*cs = (++(*cs))%4;
				drawBlock(*cr, *cc, cb, *cs, 1);		
			}
			break;
		case DOWN:
			if (isEmpty((*cr)+1, *cc, cb, *cs)) {
				drawBlock(*cr, *cc, cb, *cs, 0);
				drawBlock(++(*cr), *cc, cb, *cs, 1);		
			}
			break;
		default:
			break;
	}
}

int main (int argc, const char * argv[]) 
{
	int cr, cc; // currentRow, currentCol
	int cb, cs; // currentBlock, currentShape
	
	srand(time(NULL));
	initBoard(BR+2, BC+2);
	drawBoard(BR+2, BC+2);	

	while (!isGameOver()) {
		getNextBlock(&cb, &cs, &cr, &cc);
		drawBlock(cr, cc, cb, cs, 1);
		while (1) {
			if (kbhit()) processKey(&cr, &cc, cb, &cs);
			if (isTimerDone()) {
				if (isEmpty(cr+1, cc, cb, cs)) {
					drawBlock(cr, cc, cb, cs, 0);
					drawBlock(++cr, cc, cb, cs, 1);
				} 
				else {
					insertBlockInBoard(cr, cc, cb, cs);
					testLineFull(cr, cc, cb, cs);
					drawBoard(BR+2, BC+2);	
					break; 
				}	
			}
		}
	}

	gotoRowCol(BR/2, 3*2);
	printf("G A M E  O V E R\n");
	getch();
    return 0;
}
