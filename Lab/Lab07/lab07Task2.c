// Brayden Lappies
// Lab 07 - Kernal Files - Task 2
// This program will look through a directory for any files starting with
// "numbers." read them, and print the sums of the numbers within the file,
// along with the name of the file proper

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

void handleFile(char* d)
{
	int sum = 0, i;
	char direc[80], tester[9]="numbers.", path[256], str[4], num[4], special []= "/";
	sprintf(direc, "%s", d);
	DIR* dirp;
	struct dirent *entry;
	
	if ((dirp = opendir(direc)) == NULL)
		perror("opendir() error");
	else
	{
		printf("Files called 'numbers.XXXX' and their sums:\n");
		while ((entry = readdir(dirp)) != NULL)
		{
			if ((strncmp(tester, entry->d_name, strlen(tester))) == 0)
			{
				sprintf(path, "%s%s%s", direc, special, entry->d_name);
				int f = open(path, O_RDONLY);
				if (f < 0)
				{
					perror("open() error");
				}
				else
				{
					sum = 0;
					for (i = 0; i < 100; i++)
					{
						read(f, str, 4);
						//num = strtok(str, " ");
						sum = sum + atoi(str); //not adding up properly
					}
					close(f);
				}
				
				printf("The file is %s and sums up to %d\n", entry->d_name, sum);
			}
		}
		closedir(dirp);
	}
}

int main()
{
	char directory[80];
	
	getcwd(directory, 80);
	
	handleFile(directory);
	
	return 0;
}