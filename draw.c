#include "main.h"

#include <stdlib.h> // system()
#include <stdio.h> // printf()

extern struct POS blocks[7][4][4]; // extern : already be decalered
static char *shape[3] = {".", "*", "#"}; // static : only use in this file

void drawHelp()
{
	int row, col;
	row = 5;
	col = (BC+4)*2;
	
	gotoRowCol(row, col); printf("Help");
	gotoRowCol(++row, col); printf(" - Left: j");
	gotoRowCol(++row, col); printf(" - Right: l");
	gotoRowCol(++row, col); printf(" - Change block: i");
	gotoRowCol(++row, col); printf(" - Down: k");
}

void drawBoard(int r, int c)
{
	int i, j;
	
	system("clear");
	for (i=0; i<r; i++) {
		for (j=0; j<c; j++) {
			gotoRowCol(i, j*2);
			printf("%s", shape[board[i][j]]);
		}
	}
	
	drawHelp();
}

void drawBlock(int cr, int cc, int cb, int cs, int flag)
// flag is draw or erase
{
	int i, blockOrBlnak;
	
	blockOrBlnak = (flag==1) ? BLOCK : EMPTY;
	gotoRowCol(cr, cc);
	for (i=0; i<4; i++) {
		gotoRowCol(cr+blocks[cb][cs][i].row, 2*(cc+blocks[cb][cs][i].col));
		printf("%s", shape[blockOrBlnak]);
	}	
	gotoRowCol(BR+2, 0); printf("");
}


