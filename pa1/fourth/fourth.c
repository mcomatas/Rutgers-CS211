#include <stdio.h>
#include <stdlib.h>
int main( int argc,char**argv  )
{

	int a, b, p, q, x;
	
	FILE* fl;
	fl = fopen( argv[1], "r" );

	if( fl == NULL )
	{
		printf( "error\n" );
	}

	fscanf( fl, "%d\t", &a );
	fscanf( fl, "%d\n", &b );

	int** A = (int**)malloc(a*sizeof(int*));
	int i;
	for( i = 0; i < a; i++ )
	{
		A[i]=(int*)malloc(b*sizeof(int*));
	}

	int r, c;
	for( r = 0; r < a; r++ )
	{
		for( c = 0; c < b; c++ )
		{
			fscanf( fl, "%d\t", &x );
			A[r][c] = x;
		}
		fscanf(fl, "\n");
	}

	fscanf( fl, "%d\t", &p );
	fscanf( fl, "%d\n", &q );

	int** B = (int**)malloc(p* sizeof(int*));
	for( i = 0; i < p; i++ )
	{
		B[i]=(int*)malloc(q* sizeof(int));
	}
	
	for( r = 0; r < p; r++ )
	{
		for( c = 0; c < q; c++ )
		{
			fscanf( fl, "%d\t", &x );
			B[r][c] = x;
		}
		fscanf(fl, "\n");
	}

	if( b != p )
	{
		printf( "bad-matrices\n" );
		return 0;
	}

	int sum = 0;
	i = 0;
	int C[a][q];
	for( r = 0; r < a; r++ )
	{
		for( c = 0; c < q; c++ )
		{
			for( i = 0; i < b; i++ )
			{
				sum += A[r][i] * B[i][c];
			}
			C[r][c] = sum;
			sum = 0;
			printf( "%d\t", C[r][c] );
		}
		printf( "\n" );
	}
	return 0;
}
