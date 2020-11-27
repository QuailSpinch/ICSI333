// Brayden Lappies
// Minesweeper - 2
// This is the second iteration of the three part project of creating Minesweeper in C
// The program will have working (not finalised) functions to run the game from initialization
// to teardown. Commands are taken from the user in the comand line.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
To Do
Write an algarithm to give a near value to each square.

*/


struct Square
{
	int bomb;
	int flag;
	int reveal;
	int near; //bombs next to the square
};

struct Boxes
{
	char action;
	int horizontal;
	int vertical;
};

int height, width; //length is to horizontal co-ords as width is to vertical
struct Square **gameboard;


void initialize(int height, int width)
{
	int itrHeight, itrWidth, gridTotal, bombMax, bombs = 0, next; //next = bombs arround square
	printf("Setting up the game\n");
	
	gridTotal = height * width;
	bombMax = gridTotal / 4;
	
	//creates board and gives initial values
	gameboard = malloc(height * sizeof(struct Square *)); //gives the board the row pointer 
	for (itrHeight = 0; itrHeight < height; itrHeight++) //rows
	{
		gameboard[itrHeight] = malloc(width * sizeof(struct Square)); //gives column space
		for (itrWidth = 0; itrWidth < width; itrWidth++) //columns
		{
			gameboard[itrHeight][itrWidth].bomb = 0;
			gameboard[itrHeight][itrWidth].flag = 0;
			gameboard[itrHeight][itrWidth].reveal = 0;
			gameboard[itrHeight][itrWidth].near = 0;
		}
	}
	
	//Places bombs	
	srand(time(0));
	while (bombs < bombMax) 
	{
		itrHeight = rand() % height; //produces a random square from the game board
		itrWidth = rand() % width;
		if (gameboard[itrHeight][itrWidth].bomb == 0)
		{
			gameboard[itrHeight][itrWidth].bomb = 1;
			bombs++;
		}
	}
	
	//Calculates the near section for squares
	for (itrHeight = 0; itrHeight < height; itrHeight++)
		for (itrWidth = 0; itrWidth < width; itrWidth++)
		{
			next = 0;
			if (itrHeight != 0) //makes sure we aren't on board edge (won't go out of bound)
			{
				if (itrWidth != 0)
				{
					if (gameboard[itrHeight - 1][itrWidth].bomb)
						next++;
					if (gameboard[itrHeight - 1][itrWidth - 1].bomb)
						next++;
					if (gameboard[itrHeight][itrWidth - 1].bomb)
						next++;
				}
				if (itrWidth != (width-1)) // the uppoer bound (index is -1 of value)
				{
					if (gameboard[itrHeight - 1][itrWidth+1].bomb)
						next++;
					if (gameboard[itrHeight][itrWidth+1].bomb)
						next++;
				}
			}
			if (itrHeight != (height-1))
			{
				if (itrWidth != 0)
				{
					if (gameboard[itrHeight + 1][itrWidth].bomb)
						next++;
					if (gameboard[itrHeight + 1][itrWidth - 1].bomb)
						next++;
				}
				if (itrWidth != (width-1)) // the uppoer bound (index is -1 of value)
				{
					if (gameboard[itrHeight+1][itrWidth+1].bomb)
						next++;
				}
			}
			gameboard[itrHeight][itrWidth].near = next;
		}
}

void teardown(void)
{
	int i;
	printf("Destroying the game\n");
	for (i = 0; i < height; i ++)
		free(gameboard[i]);
	free(gameboard);
}

void getCommand(struct Boxes *box)
{
	int validCommand = 0, validHorizontal = 0, validVertical = 0, test = 0;
	char input[20];
	while (!validCommand)
	{
		printf("(F) toggle flag for a spot, (C) Check a spot for a mine, (Q) quit\n");
		scanf("%c", &box->action);
		if (box->action == 'F' || box->action == 'C' || box->action == 'Q')
		{
			validCommand = 1;
			if (box->action == 'F' || box->action == 'C') 
			{
				while (!validHorizontal)
				{
					printf("Enter the horizontal coordinate (1-10) and hit enter\n"); // anything not an int becomes 0
					scanf("%s", input); //this now ensures the value passed is an int, any non int returns 0, not in range of valid input!
					test = atoi(input);
					if (test < 1 || test >= 11) //ensured value is in range
						printf("The entered value is not valid\n");
					else		
					{
						box->horizontal = (test - 1); // -1 to align the values with the gameboard index range
						validHorizontal = 1;
					}
				}
				test = 0;
				while (!validVertical)
				{
					printf("Enter the vertical coordinate (1-10) and hit enter\n");
					scanf("%s", input);
					test = atoi(input);
					if (test < 1 || test >= 11) //ensured value is in range
						printf("The entered value is not valid\n");
					else		
					{
						box->vertical = (test - 1);
						validVertical = 1;
					}
				}
			}
		}
		else
			printf("The enetered command is not valid\n");
	}
}

void display (int confirm)
{
	//print game board
	if (confirm)
		printf("OK\n\n");
	else
	{
		printf("BOOM!\n");
		teardown();
		exit(1);
	}
}

void update(struct Boxes *box) // might end up being the actual values - depends on parts 2 and 3 specs
{
	int confirm;
	if (box->action == 'F') //toggle flag at coordinates
	{
		if (gameboard[box->horizontal][box->vertical].flag == 0)
			gameboard[box->horizontal][box->vertical].flag = 1;
		else
			gameboard[box->horizontal][box->vertical].flag = 0;
		confirm = 1;
	}
	else
	{
		if (gameboard[box->horizontal][box->vertical].bomb == 1) // if coords = bomb
			confirm = 0; //display the bomb
		else
		{
			gameboard[box->horizontal][box->vertical].reveal = 1; //square will be revealed in display
			confirm = 1; // if not a bomb, clear the square and reveal (parts 2&3)
		}
	}
	display(confirm);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Please call this with two integers for height and width of gameboard (larger than 0)\n");
		exit(1);
	}
	
	int keepGoing = 1;
	struct Boxes actionBox;
	struct Boxes * box_pointer;
	box_pointer = &actionBox;
	
	height = atoi(argv[1]);
	width = atoi(argv[2]);
	if(height > 0 && width > 0)
		initialize(height, width);
	else
	{
		printf("Command line arguments must be integers greater than 0.\n");
		exit(1);
	}
	while (keepGoing) //keeps the game in loop until game teardown occurs
	{
		getCommand(box_pointer);
		if (box_pointer->action == 'Q')
			keepGoing = 0;
		else
			update(box_pointer);
	}
	teardown();
}