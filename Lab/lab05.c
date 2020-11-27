// Brayden Lappies
// Lab 05 - Linked Lists
// This program will create a Linked List of randomly genertaged integer values 
// between o and 50. If the random number generated is a 49 the list will stop
// being created and print the list and free the memory.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
	int random;
	struct node *next;
};

void insert_node (struct node **h, struct node **t, int v) // node with val v at end of list whose first and last are *h and *t (respectively)
{	
	struct node *temp;
	if ((temp = (struct node *)malloc(sizeof(struct node))) == NULL) 
	{
		printf("Node allocation failed. \n");
		exit(1); /* Stop program */
	}
	// Space for node obtained. Copy the random v into the node 
	// and insert the node at the end of the list. 
	temp->random = v; temp->next = NULL;
	if (*h == NULL) // List is currently empty. 
		*h = *t = temp;
	else 
	{ 
		// The list is not empty. *t adds the node at the end
		(*t)->next = temp; *t = (*t)->next;
	}
}

void print_list (struct node *h) // prints values of the nodes of the list pointed at by h
{
	if(h == NULL) // the list is empyt
	{
		printf("The list is empty.\n");
	}
	else
	{
		printf("Values in the list are:\n");
		while(h != NULL)
		{
			printf("%d\n", h->random);
			h = h->next;
		}
	}
}

void free_list (struct node *h) // frees all nodes in list pointed at by h
{
	struct node *temp;
	
	while (h != NULL)
	{
		temp = h; //puts head in temp
		h = h->next; //sets head to the next item in list
		temp->next = NULL;
		free(temp); // frees temp, the "original" head
	}
}

int main()
{
	int value;
	struct node *head, *tail;
	
	head = tail = NULL;
	
	srand(time(0)); //seeds rand with time
	value = rand() % 51; // range 0-50
	while (value != 49)
	{
		insert_node(&head, &tail, value);
		value = rand() % 51;
	}
	
	print_list(head);
	//free_list(head);
	
	return 0;
}