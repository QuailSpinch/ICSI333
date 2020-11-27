// Brayden Lappies
// Minesweeper - 1
// This is the first iteration of the three part project of creating Minesweeper in C
// The program will have working (not finalised) functions to run the game from initialization
// to teardown. Commands are taken from the user in the comand line.
#include <stdio.h>
#include <string.h>

struct Boxes
{
	char action;
	int horizontal;
	int vertical;
};

void initialize(void)
{
	printf("Setting up the game\n");
}

void teardown(void)
{
	printf("Destroying the game\n");
}

void getCommand(struct Boxes *box)
{
	int validCommand = 0, validHorizontal = 0, validVertical = 0;
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
					printf("Enter the horizontal coordinate (0-10) and hit enter\n");
					scanf("%d", &box->horizontal);
					if (box->horizontal < 0 || box->horizontal >= 11) //ensured value is in range
						printf("The entered value is not valid\n");
					else		
						validHorizontal = 1;
				}
				while (!validVertical)
				{
					printf("Enter the vertical coordinate (0-10) and hit enter\n");
					scanf("%d", &box->vertical);
					if (box->vertical < 0 || box->vertical >= 11) //ensured value is in range
						printf("The entered value is not valid\n");
					else		
						validVertical = 1;
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
		printf("BOOM!\n\n");
}

void update(struct Boxes *box) // might end up being the actual values - depends on parts 2 and 3 specs
{
	int confirm;
	if (box->action == 'F') //toggle flag at coordinates
		confirm = 1;
	else
	{
		if (box->horizontal == 0 && box->vertical == 0) // if coords = bomb
			confirm = 0; //display the bomb
		else
			confirm = 1; // if not a bomb, clear the square and reveal (parts 2&3)
	}
	display(confirm);
}

int main()
{
	int boardWidth, boardLength;
	int keepGoing = 1;
	struct Boxes actionBox;
	struct Boxes * box_pointer;
	box_pointer = &actionBox;
	
	initialize();
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