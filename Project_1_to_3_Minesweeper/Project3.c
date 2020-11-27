// Brayden Lappies
// Minesweeper - 3
// This is the third iteration of the three part project of creating Minesweeper in C
// The program will have be finalised with  functions to run the game from initialization
// to teardown. Commands are taken from the user in the comand line.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void reveal(int horizontal, int vertical, int h, int w);

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
			/* OLD CODE - DIDN'T FULLY WORK, KEPT FOR REFERENCE
			
			
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
				if (itrWidth != (width-1)) // the upper bound (index is -1 of value)
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
				if (itrWidth != (width-1)) // the upper bound (index is -1 of value)
				{
					if (gameboard[itrHeight+1][itrWidth+1].bomb)
						next++;
				}
			} */
			
			if (itrHeight != 0)
			{
				if (itrWidth != 0)
				{
					if (gameboard[itrHeight - 1][itrWidth].bomb)
						next++;
					if (gameboard[itrHeight - 1][itrWidth - 1].bomb)
						next++;
					if (gameboard[itrHeight][itrWidth - 1].bomb)
						next++;
					
					if (itrHeight != (height-1))
					{
						if (itrWidth != (width-1))
						{
							if (gameboard[itrHeight - 1][itrWidth + 1].bomb)
								next++;
							if (gameboard[itrHeight][itrWidth + 1].bomb)
								next++;
							if (gameboard[itrHeight + 1][itrWidth - 1].bomb)
								next++;
							if (gameboard[itrHeight + 1][itrWidth].bomb)
								next++;
							if (gameboard[itrHeight + 1][itrWidth + 1].bomb)
								next++;
						}
						else // at right boarder - can'thave width + 1
						{
							if (gameboard[itrHeight + 1][itrWidth - 1].bomb)
								next++;
							if (gameboard[itrHeight + 1][itrWidth].bomb)
								next++;
						}
					}
					else // at bottom border - can't have height + 1
					{
						if (itrWidth != (width-1))
						{
							if (gameboard[itrHeight - 1][itrWidth + 1].bomb)
								next++;
							if (gameboard[itrHeight][itrWidth + 1].bomb)
								next++;
						}
					}
				}
				else //at left border - can't have width - 1
				{
					if (itrHeight != (height-1))
					{
						if (gameboard[itrHeight - 1][itrWidth].bomb)
							next++;
						if (gameboard[itrHeight - 1][itrWidth + 1].bomb)
							next++;
						if (gameboard[itrHeight][itrWidth + 1].bomb)
							next++;
						if (gameboard[itrHeight + 1][itrWidth].bomb)
							next++;
						if (gameboard[itrHeight + 1][itrWidth + 1].bomb)
							next++;
					}
					else // at bottom - cant have height + 1 or width - 1
					{
						if (gameboard[itrHeight - 1][itrWidth].bomb)
							next++;
						if (gameboard[itrHeight - 1][itrWidth + 1].bomb)
							next++;
						if (gameboard[itrHeight][itrWidth + 1].bomb)
							next++;
					}
				}
			}
			else //at top, cant have height - 1
			{
				if (itrWidth != 0)
				{
					if (gameboard[itrHeight][itrWidth - 1].bomb)
						next++;
					if (gameboard[itrHeight + 1][itrWidth - 1].bomb)
						next++;
					if (gameboard[itrHeight + 1][itrWidth].bomb)
						next++;
					
					if (itrWidth != (width - 1))
					{
						if (gameboard[itrHeight][itrWidth + 1].bomb)
							next++;
						if (gameboard[itrHeight + 1][itrWidth + 1].bomb)
							next++;
					}
				}
				else // at left, cant have width - 1
				{
					if (gameboard[itrHeight][itrWidth + 1].bomb)
						next++;
					if (gameboard[itrHeight + 1][itrWidth + 1].bomb)
						next++;
					if (gameboard[itrHeight + 1][itrWidth].bomb)
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

void display (int confirm, int h, int w)
{
	//print game board
	int vertical = h, horizontal = w, itrVert, itrHoriz, flaggedBombs=0;
	if (confirm)
	{
		for (itrVert = 0; itrVert < vertical; itrVert++)
		{
			for (itrHoriz = 0; itrHoriz < horizontal; itrHoriz++)
			{
				if (gameboard[itrVert][itrHoriz].reveal == 0) 
					if (gameboard[itrVert][itrHoriz].flag == 0) //the square is not revealed, denoted by []
						printf(" [] ");
					else
						printf(" |^ "); //the square is flagged, denoted by |^
				else
					printf( " %d  ", gameboard[itrVert][itrHoriz].near);
				
				//checks to see if all bombs are flagged, if yes the game ends
				if  (gameboard[itrVert][itrHoriz].flag == 1 && gameboard[itrVert][itrHoriz].bomb == 1)
					flaggedBombs++;
			}
			printf("\n");
		}
		if (flaggedBombs == ((vertical*horizontal) / 4))
		{
			printf("All bombs flagged! YOU WIN!!!\n");
			teardown();
			exit(1);
		}
	}
	else
	{
		printf("BOOM!\n");
		teardown();
		exit(1);
	}
}

void update(struct Boxes *box, int h, int w) // might end up being the actual values - depends on parts 2 and 3 specs
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
			confirm = 0; //display the bomb - print game over!
		else
		{
			gameboard[box->horizontal][box->vertical].reveal = 1; //square will be revealed in display
			confirm = 1; // if not a bomb, clear the square and reveal (parts 2&3)
			if (gameboard[box->horizontal][box->vertical].near == 0)
				reveal(box->horizontal, box->vertical, h, w);
		}
	}
	display(confirm, h, w);
}


/*
Reveal Alogrithm:
For a square s with a vertical coordinate x and horizontal coordinate y, if the near field = 0 all quares in range of 
([x-1,x+1], [y-1,y+1]) that exist and have a reveal status = 0 will have their reveal status set to 1, one at a time. 
If the near field of a revealed square = 0 then that square is run through the same process.
*/

void reveal(int horizontal, int vertical, int h, int w)
{
	int height = h, width = w;
	if (horizontal != 0)
	{
		if (vertical != 0)
		{
			if (gameboard[horizontal - 1][vertical].reveal != 1) // Won't infinit loop on already revealed squares
			{
				gameboard[horizontal - 1][vertical].reveal = 1;
				if (gameboard[horizontal - 1][vertical].near == 0) // near = 0 so the square must be run through the process
					reveal((horizontal-1), vertical, height, width);
			}
			if (gameboard[horizontal - 1][vertical-1].reveal != 1)
			{
				gameboard[horizontal - 1][vertical-1].reveal = 1;
				if (gameboard[horizontal - 1][vertical-1].near == 0)
					reveal((horizontal-1), (vertical-1), height, width);
			}
			if (gameboard[horizontal][vertical-1].reveal != 1)
			{
				gameboard[horizontal][vertical-1].reveal = 1;
				if (gameboard[horizontal][vertical-1].near == 0)
					reveal(horizontal, (vertical-1), height, width);
			}
			
			if (horizontal != (height-1))
			{
				if (vertical != (width-1))
				{
					if (gameboard[horizontal - 1][vertical+1].reveal != 1)
					{
						gameboard[horizontal - 1][vertical+1].reveal = 1;
						if (gameboard[horizontal - 1][vertical+1].near == 0)
							reveal((horizontal-1), (vertical+1), height, width);
					}
					if (gameboard[horizontal][vertical+1].reveal != 1)
					{
						gameboard[horizontal][vertical+1].reveal = 1;
						if (gameboard[horizontal][vertical+1].near == 0)
							reveal(horizontal, (vertical+1), height, width);
					}
					if (gameboard[horizontal + 1][vertical-1].reveal != 1)
					{
						gameboard[horizontal + 1][vertical-1].reveal = 1;
						if (gameboard[horizontal + 1][vertical-1].near == 0)
							reveal((horizontal+1), (vertical-1), height, width);
					}
					if (gameboard[horizontal + 1][vertical].reveal != 1)
					{
						gameboard[horizontal + 1][vertical].reveal = 1;
						if (gameboard[horizontal + 1][vertical].near == 0)
							reveal((horizontal+1), vertical, height, width);
					}
					if (gameboard[horizontal + 1][vertical+1].reveal != 1)
					{
						gameboard[horizontal + 1][vertical+1].reveal = 1;
						if (gameboard[horizontal + 1][vertical+1].near == 0)
							reveal((horizontal+1), (vertical+1), height, width);
					}
				}
				else // at right boarder - can'thave width + 1
				{
					if (gameboard[horizontal + 1][vertical-1].reveal != 1)
					{
						gameboard[horizontal + 1][vertical-1].reveal = 1;
						if ( gameboard[horizontal + 1][vertical-1].near == 0)
							reveal((horizontal+1), (vertical-1), height, width);
					}
					if (gameboard[horizontal + 1][vertical].reveal != 1)
					{
						gameboard[horizontal + 1][vertical].reveal = 1;
						if (gameboard[horizontal + 1][vertical].near == 0)
							reveal((horizontal+1), vertical, height, width);
					}
				}
			}
			else // at bottom border - can't have height + 1
			{
				if (vertical != (width-1))
				{
					if (gameboard[horizontal - 1][vertical+1].reveal != 1)
					{
						gameboard[horizontal - 1][vertical+1].reveal = 1;
						if (gameboard[horizontal - 1][vertical+1].near == 0)
							reveal((horizontal-1), (vertical+1), height, width);
					}
					if (gameboard[horizontal][vertical+1].reveal != 1)
					{
						gameboard[horizontal][vertical+1].reveal = 1;
						if (gameboard[horizontal][vertical+1].near == 0)
							reveal(horizontal, (vertical+1), height, width);
					}
				}
			}
		}
		else //at left border - can't have width - 1
		{
			if (horizontal != (height-1))
			{
				if (gameboard[horizontal - 1][vertical].reveal != 1)
				{
					gameboard[horizontal - 1][vertical].reveal = 1;
					if (gameboard[horizontal - 1][vertical].near == 0)
						reveal((horizontal-1), vertical, height, width);
				}
				if (gameboard[horizontal - 1][vertical+1].reveal != 1)
				{
					gameboard[horizontal - 1][vertical+1].reveal = 1;
					if (gameboard[horizontal - 1][vertical+1].near == 0)
						reveal((horizontal-1), (vertical+1), height, width);
				}
				if (gameboard[horizontal][vertical+1].reveal != 1)
				{
					gameboard[horizontal][vertical+1].reveal = 1;
					if (gameboard[horizontal][vertical+1].near == 0)
						reveal(horizontal, (vertical+1), height, width);
				}
				if (gameboard[horizontal + 1][vertical].reveal != 1)
				{
					gameboard[horizontal + 1][vertical].reveal = 1;
					if (gameboard[horizontal + 1][vertical].near == 0)
						reveal((horizontal+1), vertical, height, width);
				}
				if (gameboard[horizontal + 1][vertical+1].reveal != 1)
				{
					gameboard[horizontal + 1][vertical+1].reveal = 1;
					if (gameboard[horizontal + 1][vertical+1].near == 0)
						reveal((horizontal+1), (vertical+1), height, width);
				}
			}
			else // at bottom - cant have height + 1 or width - 1
			{
				if (gameboard[horizontal - 1][vertical].reveal != 1)
				{
					gameboard[horizontal - 1][vertical].reveal = 1;
					if (gameboard[horizontal - 1][vertical].near == 0)
						reveal((horizontal-1), vertical, height, width);
				}
				if (gameboard[horizontal - 1][vertical+1].reveal != 1)
				{
					gameboard[horizontal - 1][vertical+1].reveal = 1;
					if (gameboard[horizontal - 1][vertical+1].near == 0)
						reveal((horizontal-1), (vertical+1), height, width);
				}
				if (gameboard[horizontal][vertical+1].reveal != 1)
				{
					gameboard[horizontal][vertical+1].reveal = 1;
					if (gameboard[horizontal][vertical+1].near == 0)
						reveal(horizontal, (vertical+1), height, width);
				}
			}
		}
	}
	else //at top, cant have height - 1
	{
		if (vertical != 0)
		{
			if (gameboard[horizontal][vertical-1].reveal != 1)
			{
				gameboard[horizontal][vertical-1].reveal = 1;
				if (gameboard[horizontal][vertical-1].near == 0)
					reveal(horizontal, (vertical-1), height, width);
			}
			if (gameboard[horizontal + 1][vertical-1].reveal != 1)
			{
				gameboard[horizontal + 1][vertical-1].reveal = 1;
				if (gameboard[horizontal + 1][vertical-1].near == 0)
					reveal((horizontal+1), (vertical-1), height, width);
			}
			if (gameboard[horizontal + 1][vertical].reveal != 1)
			{
				gameboard[horizontal + 1][vertical].reveal = 1;
				if (gameboard[horizontal + 1][vertical].near == 0)
					reveal((horizontal+1), vertical, height, width);
			}
			
			if (vertical != (width - 1))
			{
				if (gameboard[horizontal][vertical+1].reveal != 1)
				{
					gameboard[horizontal][vertical+1].reveal = 1;
					if (gameboard[horizontal][vertical+1].near == 0)
						reveal(horizontal, (vertical+1), height, width);
				}
				if (gameboard[horizontal + 1][vertical+1].reveal != 1)
				{
					gameboard[horizontal + 1][vertical+1].reveal = 1;
					if (gameboard[horizontal + 1][vertical+1].near == 0)
						reveal((horizontal+1), (vertical+1), height, width);
				}
			}
		}
		else // at left, cant have width - 1
		{
			if (gameboard[horizontal][vertical+1].reveal != 1)
			{
				gameboard[horizontal][vertical+1].reveal = 1;
				if (gameboard[horizontal][vertical+1].near == 0)
					reveal(horizontal, (vertical+1), height, width);
			}
			if (gameboard[horizontal + 1][vertical+1].reveal != 1)
			{
				gameboard[horizontal + 1][vertical+1].reveal = 1;
				if (gameboard[horizontal + 1][vertical+1].near == 0)
					reveal((horizontal+1), (vertical+1), height, width);
			}
			if (gameboard[horizontal + 1][vertical].reveal != 1)
			{
				gameboard[horizontal + 1][vertical].reveal = 1;
				if (gameboard[horizontal + 1][vertical].near == 0)
					reveal((horizontal+1), vertical, height, width);
			}
		}
	}
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
			update(box_pointer, height, width);
	}
	teardown();
}