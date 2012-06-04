#include "main.h"

extern struct POS blocks[7][4][4];

int isTimerDone()
{
	static int timer;
	int maxValue = 50000;
	
	timer++;
	
	if (timer == maxValue) {
		timer = 0;
		return 1;
	} else {
		return 0;
	}
}

int isEmpty(int cr, int cc, int cb, int cs)
{
	int i;
	for (i=0; i<4; i++) {
		if (board[cr+blocks[cb][cs][i].row][cc+blocks[cb][cs][i].col] != EMPTY) {
			return 0;
		}
	}
	return 1;
}

void testLineFull(int cr, int cc, int cb, int cs)
{
	int i, c, r, sum;
	
	for (i=0; i<4; i++) {
		for (c=1, sum=0; c<BC+1; c++) 
			sum += board[cr+blocks[cb][cs][i].row][c];
		if (sum == BC*BLOCK) 
			for (r=cr+blocks[cb][cs][i].row; r>1; r--) 
				for (c=1; c<BC+1; c++) 
					board[r][c] = board[r-1][c];
	}
}

int isGameOver()
{
	int i;
	
	for (i=1; i<BC+1; i++) {
		if (board[1][i] == BLOCK) {
			return 1;
		}
	}
	return 0;
}
