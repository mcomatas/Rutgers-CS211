#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int num;
	struct node* next;
}node;

node* newNode( int num, struct node* head )
{
	struct node* temp = malloc(sizeof(node));
	temp->num = num;
	temp->next = head;
	head = temp;
	
	return head;
}

typedef struct hashtable{
	int size;
	struct node** row;
}hashtable;

int hash( int key )
{
	int num = key % 10000;
	
	if( num < 0 )
	{
		num += 10000;
	}

	return num;
}

int search( struct hashtable* table, int num )
{
	int key = hash( num );

	if( table->row[key] == NULL )
	{
		return 0;
	}
	else
	{
		struct node* ptr = table->row[key];
		while( ptr != NULL )
		{
			if( ptr->num == num )
			{
				return 1;
			}
			ptr = ptr->next;
		}
	}
	return 0;
}

int insert( struct hashtable* table, struct node* flip )
{
	int key = hash( flip->num );

	struct node* ptr;

	if( table->row[key] == NULL )
	{
		table->row[key] = flip;
		return 0;//inserted no collision
	}

	if( table->row[key]->num == flip->num )
	{
		return 1;//first is a dup
	}
	ptr = table->row[key];
	while( ptr->next != NULL )
	{
		if( ptr->next->num == flip->num )
		{
			return 1;//dup
		}
		ptr = ptr->next;
	}
	ptr->next=flip;
	return 1;//inserted w/ collision
}

int main(int argc, char** argv)
{
	int collisionCount = 0;
	int searchCount = 0;
	int nodeNum;
	char x;
	struct node* flip = NULL;
	
	struct hashtable* table = (hashtable*)malloc(sizeof(hashtable));
	table->size = 10000;
	table->row = malloc(table->size*sizeof(node*));
	int i;
	for( i = 0; i < table->size; i++ )
	{
		table->row[i] = NULL;
	}//creates hashtable of size 10k

	FILE* fl;
	fl = fopen(argv[1], "r" );

	if( argv[1] == NULL )
	{
		printf( "error\n" );
		return 0;
	}

	while( fscanf( fl, "%c\t%d\n", &x, &nodeNum ) != EOF )
	{
		if( x == 'i' )
		{
			int k;
			flip = NULL;
			flip = newNode( nodeNum, flip );
			k = insert( table, flip );
			if( k == 1 )
			{
				collisionCount++;
			}
		}
		if( x == 's' )
		{
			int k;
			k = search( table, nodeNum );
			if( k == 1 )
			{
				searchCount++;
			}
		}
	}

	printf( "%d\n%d", collisionCount, searchCount );

	return 0;
}
