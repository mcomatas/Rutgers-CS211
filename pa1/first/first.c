#include <stdio.h>

void printArray( int arr[], int n )
{
	int k = 0;
	for( k = 0; k < n; k++ )
	{
		printf( "%d\t",arr[k] );
	}
}

void evenSort( int arr[], int n )
{
	int i, j, min;
	for( i = 0; i < n-1; i++ )
	{
		min = i;
		for( j = i+1; j < n; j++ )
		{
			if( arr[j] < arr[min] )
			{
				min = j;
			}
		}
		int temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
	}
}

void oddSort( int arr[], int s, int e )
{
	int i, j, max;
	for( i = e-1; i > s; i-- )
	{
		max = i;
		for( j = i-1; j >= s; j-- )
		{
			if( arr[j] < arr[max] )
			{
				max = j;
			}
		}
		int temp = arr[max];
		arr[max] = arr[i];
		arr[i] = temp;
	}
}

int main(int argc, char** argv )
{
	int num;

	FILE* fl=fopen(argv[1],"r");
	fscanf(fl,"%d\n",&num);

	int arr[num];
	int i;
	for( i = 0; i < num; i++ )
	{
		fscanf(fl,"%d\t",&arr[i]);
	}


	//split even and odd
	int index = 0;

	for( i = 0; i < num; i++ )
	{
		if( arr[i] % 2 == 0 )
		{
			int temp = arr[i];
			arr[i] = arr[index];
			arr[index] = temp;
			index++;
		}
	}

	evenSort( arr, index );
	oddSort( arr, index, num );

	printArray( arr, num );

	return 0;
}





