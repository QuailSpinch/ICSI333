// Brayden Lappies
// lab02 - pointers
// This program will decalre 2 variables and two pointers. The pointers will point 
// at the variables. variable 1 will be set and variable 2 will be set by dereferencing
// its pointer. Both pointers and variables will be printed.
#include <stdio.h>

int main()
{
	int value1, value2, *pointer1, *pointer2;
	pointer1 = &value1;
	pointer2 = &value2; //assigns pointers to variables
	value1 = 5;
	*pointer2 = 39; // sets the memory address of variable 2 for pointer 2
	printf("The value of variable 1 is %d and the value of pointer 1 is %d.\n", value1, *pointer1);
	printf("The value of variable 2 is %d and the value of pointer 2 is %d.\n", value2, *pointer2);
	
	return 0;
}