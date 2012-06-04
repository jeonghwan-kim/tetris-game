#include <stdio.h> // EOF
#include <unistd.h> 
#include <termios.h> // getch()
#include <fcntl.h> // kbhit()
#include <stdlib.h> // calloc()

#include "main.h"

int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;
	
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	
	ch = getchar();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	
	if(ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}
	
	return 0;
}

void gotoRowCol(int r, int c)
{
	int maxScreenArea;
	char *scr;
	maxScreenArea = 255;
	scr = calloc(sizeof(char), maxScreenArea);
	sprintf(scr, "\033[%d;%df", r+1, c+1);
	printf("%s", scr);
}

int getch() 
{ 
	int ch; 
	struct termios buf; 
	struct termios save; 
	
	tcgetattr(0, &save); 
	buf = save; 
	
	buf.c_lflag &= ~(ICANON|ECHO); 
	buf.c_cc[VMIN] = 1; 
	buf.c_cc[VTIME] = 0; 
	
	tcsetattr(0, TCSAFLUSH, &buf); 
	ch = getchar(); 
	tcsetattr(0, TCSAFLUSH, &save); 
	
	return ch; 
}