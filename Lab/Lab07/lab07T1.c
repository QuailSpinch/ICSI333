// Brayden Lappies
// Lab 07 - Kernel files - Creator
// This program will Create an array of random integers and then write them into a file.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int sum = 0, i =0, num[100];
	char path[55] = "numbers.", numbers[5], name[9]="numbers.", str[4];
	char dir[]=""; //INSERT DIRECTORY PATH HERE
	srand(time(0)); //seeds rand with time
	
	for (i = 0; i < 100; i++)
	{
		num[i] = (rand()%100); //value 0-99
		sum = sum + num[i];
	}
	
	sprintf(numbers, "%d", sum);
	sprintf(path, "%s%s", name, numbers);
	//printf("%s\n", path);
	int f = open(path, O_WRONLY | O_CREAT);
	if (f < 1)
	{
		printf("File couldn't be created\n");
		return 1;
	}
	
	for (i=0; i < 100; i++)
	{
		sprintf(str, "%d", num[i]);
		write(f, str, 4);
	}
	
	close(f);
	
	printf("Sum is %d\n", sum);
	return 0;
}