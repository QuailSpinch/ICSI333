// Brayden Lappies
// Lab 06 - bitwise 
// This program will accept an int in the command line and print it
// back out, but also print out the number of 0 and 1 bits in the number.
#include <stdio.h> 
#include <stdlib.h>

//int is 4 bytes of this machine, so a mask will have to be of four bytes size
void binary(unsigned int num)
{//						 		    |	 1	  |    2    |    3    |    4	
	unsigned int mask = 2147483648;//1000 0000 0000 0000 0000 0000 0000 0000
	int zero = 0, one = 0;
	while(mask > 0)
	{
		if ((num & mask) == 0)
			zero++;
		else
			one++;
		mask = mask >> 1; //right shift, moves the 1 down the line
	}
	printf("In %d, there are %d bits set to 0.\n", num, zero);
	printf("In %d, there are %d bits set to 1.\n", num, one);
}


int main(int argc, char *argv[])
{	
	unsigned int input;
	
	if (argc != 2)
	{
		printf("please call this program with an integer\n");
		exit(1);
	}
	
	input = atoi(argv[1]);
	printf("Your number was %d.\n", input);
	binary(input);
	return 0;
}