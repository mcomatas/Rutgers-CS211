#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get( int x, int n )
{
	int k;
	k = x >> n & 1;
	return k;
}

int main( int argc, char** argv )
{
	char *p;

	unsigned short int x = strtol( argv[1], &p, 10 );

	int i;
	int j = 15;
	for( i = 0; i < 8; i++ )
	{
		if( get( x, i ) != get( x, j ) )
		{
			printf( "Not-Palindrome\n" );
			return 0;
		}
		j--;
	}
	printf( "Is-Palindrome" );
	return 0;
}
