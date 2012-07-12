all : console.o draw.o gameCheck.o main.o
	gcc -o tetris console.o draw.o gameCheck.o main.o
	
console.o : console.c
	gcc -c -o console.o console.c
	
draw.o : draw.c
	gcc -c -o draw.o draw.c
	
gameCheck.o : gameCheck.c
	gcc -c -o gameCheck.o gameCheck.c
	
main.o : main1.c
	gcc -c -o main.o main1.c
	

