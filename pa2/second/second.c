#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char** argv )
{
	char *p;
	
	unsigned short int x = strtol( argv[1], &p, 10 ); 

	int k, y;
	int pairCount = 0;
	int oneCount = 0;

	while( x != 0 )
	{
		k = x & 1;
		y = ( x >> 1 ) & 1;
		if( k == 0 && y == 0 )
		{
			x = x >> 2;
		}
		if( k == 1 && y == 1 )
		{
			pairCount++;
			oneCount += 2;
			x = x >> 2;
		}
		if( k == 1 && y == 0 )
		{
			oneCount++;
			x = x >> 2;
		}
		if( k == 0 && y == 1 )
		{
			x = x >> 1;
		}
	}

	if( oneCount % 2 == 0 )
	{
		printf( "Even-Parity\t" );
	}
	else
	{
		printf( "Odd-Parity\t" );
	}

	printf( "%d\n", pairCount );
	return 0;
}
