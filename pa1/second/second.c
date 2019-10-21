#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int num;
	struct node* next;
}node;

node* newNode( int num, node* head )
{
	struct node* newNode = malloc(sizeof(node));
	newNode->num = num;
	newNode->next = head;
	return newNode;
}

node* selectionSort( node* head )
{
	struct node* ptr1;
	struct node* ptr2;
	struct node* min;
	int temp;
	
	ptr1 = head;
	while( ptr1 != NULL )
	{
		ptr2=ptr1->next;
		min = ptr1;
		while( ptr2 != NULL )
		{
			if( ptr2->num < min->num )
			{
				min = ptr2;
			}	
			ptr2 = ptr2->next;
		}
		temp = ptr1->num;
		ptr1->num = min->num;
		min->num = temp;
		ptr1=ptr1->next;
	}
	return head;
}

int countNodes( node* head )
{
	int count = 0;
	if( head == NULL )
	{
		return count;
	}
	struct node* ptr = head;
	while( ptr != NULL )
	{
		count++;
		ptr = ptr->next;
	}
	return count;
}

node* deleteNode( int num, node* head )
{
	if( head == NULL )
	{
		return head;
	}

	if( head->num  == num )
	{
		if( head->next == NULL )//size of 1
		{
			head = head->next;
			return head;
		}
		head = head->next;
		return head;
	}
	struct node* ptr = head->next;
	struct node* prev = head;

	while( ptr != NULL )
	{
		if( ptr->num == num )
		{
			prev->next = ptr->next;
			return head;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return head;
}

node* delSameNodes( node* head )
{
	struct node* ptr1 = head;
	struct node* ptr2 = head->next;
	struct node* prev = ptr1;

	while( ptr1 != NULL )
	{
		ptr2 = ptr1->next;
		prev = ptr1;
		while( ptr2 != NULL )
		{
			if( ptr1->num == ptr2->num )
			{
				prev->next = ptr2->next;
			}
			prev = ptr2;
			ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
	return head;
}

int main(int argc, char** argv)
{
	int count;
	int nodeNum;
	char x;

	struct node* ptr = NULL;
	struct node* head = NULL;

	FILE *fl;
	fl = fopen(argv[1], "r" );

	if( fl == NULL )
	{
		printf( "error\n" );
		return 0;
	}

	while( fscanf( fl, "%c\t%d\n", &x, &nodeNum ) != EOF )
	{
		if( x == 'i' )
		{
			head = newNode( nodeNum, head );
		}
		else if( x == 'd' )
		{
			head = deleteNode( nodeNum, head );
		}
	}

	ptr = head;

	count = countNodes( ptr );

	if( count == 0 )
	{
		printf( "%d\n", count );
		return 0;
	}
	printf( "%d\n", count );


	head = delSameNodes( head ); 
	head = selectionSort( head );
	
	ptr = head;
	while( ptr != NULL )
	{
		printf( "%d\t", ptr->num );
		ptr = ptr->next;
	}

	fclose(fl);	

	return 0;
}
