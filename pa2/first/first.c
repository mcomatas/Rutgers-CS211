#include <stdio.h>
#include <string.h>

int power( int p, int q )
{
	int total = 1;
	int i;
	for( i = 0; i < q; i++ )
	{
		total *= p;
	}
	return total;
}

int get( int x, int n )
{
	int k;
	k = x >> n & 1;
	return k;
}

int comp( int x, int n )
{
	int k;
	int y = power( 2, n );

	if( get( x, n ) == 0 )
	{
		k = x | y;
		return k;
	}
	k = x ^ y;
	return k;
}

int set( int x, int n, int v )
{
	if( get( x, n ) == 0 && v == 0 )
	{
		return x;
	}
	if( get( x, n ) == 1 && v == 1 )
	{
		return x;
	}
	int k = comp( x, n );
	return k;
}

int main( int argc, char** argv )
{
	int num;
	char cmd[10];
	//char * cmd = malloc(4 * sizeof(char));
	int a, b;

	/*char g[4] = "get ";
	char s[4] = "set ";
	char c[4] = "comp";*/

	FILE *fl;
	fl = fopen( argv[1], "r" );

	if( fl == NULL )
	{
		printf( "error\n" );
		return 0;
	}

	fscanf( fl, "%d\n", &num );
	while( fscanf( fl, "%s\t%d\t%d\n", cmd, &a, &b ) != EOF )
	{
		if( strcmp( cmd, "get" ) == 0 )
		{
			printf( "%d\n", get( num, a ) );
		}
		if( strcmp( cmd, "set" ) == 0 )
		{
			num = set( num, a, b );
			printf( "%d\n", num );
		}
		if( strcmp( cmd, "comp" ) == 0 )
		{
			num = comp( num, a );
			printf( "%d\n", num );
		}
	}
	return 0;
}
