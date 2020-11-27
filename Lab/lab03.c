// Brayden Lappies
// lab03 - strings
// This program will accept a string from the user. It will then calculate the length of
// the string without using standard functions. The calulated length of the string will
// be printed followed by the length from the standard function.
#include <stdio.h>
#include <string.h>

int main()
{
	//declare the "string" (char array)
	char string[20];
	char *pt = string;
	int length = 0;
	printf("Please enter a string: ");
	scanf("%s", string); //only gets up to the first space
	while (*pt != '\0') //counts each charcater this isnt the '\0'
	{
		length++;
		pt++;
	}
	//print calculateded lenght and functional length
	printf("Calculated length of string is %d\n", length);
	printf("The Length of string is %ld\n", strlen(string)); //has to be ld for a long unsigned
	
	return 0;
}