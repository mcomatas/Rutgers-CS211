#include <stdio.h>
#include <stdlib.h>

typedef struct BSTnode
{
	int data;
	struct BSTnode* left;
	struct BSTnode* right;
}BSTnode;

BSTnode* newNode( int num )
{
	struct BSTnode* newNode = malloc(sizeof(BSTnode));
	newNode->data = num;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void traverse( BSTnode* root )
{
	if( root == NULL )
	{
		return;
	}
	traverse( root->left );
	printf("%d\t", root->data );
	traverse( root->right );
}

BSTnode* insert( int num, BSTnode* root )
{
	if( root == NULL )
	{
		return newNode( num );
	}

	if( num == root->data )
	{
		return root;
	}

	if( num < root->data )
	{
		root->left = insert( num, root->left );
	}
	else
	{
		root->right = insert( num, root->right );
	}
	return root;
}

int main(int argc, char** argv)
{	
	char x;
	int nodeNum;
	
	struct BSTnode *head = (BSTnode*)malloc(sizeof(BSTnode));
	head = NULL;

	FILE *fl;
	fl = fopen(argv[1], "r" );

	if( fl == NULL )
	{
		printf( "error\n" );
		return 0;
	}

	while( fscanf( fl, "%c\t%d\t", &x, &nodeNum ) != EOF )
	{
		if( x == 'i' )
		{
			head = insert( nodeNum, head );
		}
	}


	traverse( head );
	printf( "\n" );

	fclose( fl );

	return 0;
}
