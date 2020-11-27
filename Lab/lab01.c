// Brayden Lappies
// lab01.c
// This program will prompt two numbers and give the dividend and remainder (after dividing)
#include <stdio.h>

int main()
{
	int numerator = 0, denominator = 0, dividend = 0, remainder = 0;
	
	printf("Enter a value to be the numerator: ");
	scanf("%d", &numerator);
	printf("Enter a value for the denominator: ");
	scanf("%d", &denominator);
	//Test: printf("The value of you num is %d and your den is %d\n", numerator, denominator);
	dividend = numerator / denominator;
	remainder = numerator % denominator;
	printf("The dividend is %d with a remainder of %d\n", dividend, remainder);
	
	return 0;
}