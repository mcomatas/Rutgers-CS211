#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int hit;
int miss;
int memReads;
int memWrites;

struct row** cache;

unsigned long int count;

typedef struct row
{
	unsigned long int tag;
	int valid;
	unsigned long int time;
}row;

row** create( int setNum, int assoc )
{
	int i, j;
	cache = (row**)malloc(setNum*sizeof(row*));
	for( i = 0; i < setNum; i++ )
	{
		cache[i] = (row*)malloc((assoc)*sizeof(row));
	}
	for( i = 0; i < setNum; i++ )
	{
		for( j = 0; j < assoc; j++ )
		{
			cache[i][j].valid = 0;
		}
	}
	return cache;
	
}

void empty( int setNum, int assoc )
{
	int i, j;
	for( i = 0; i < setNum; i++ )
	{
		for( j = 0; j < assoc; j++ )
		{
			cache[i][j].tag = 0;
			cache[i][j].valid = 0;
			cache[i][j].time = 0;
		}
	}
	memReads = 0;
	memWrites = 0;
	miss = 0;
	hit = 0;
	count = 0;
}

void read( unsigned long int tagIndex, unsigned long int setIndex, int assoc )
{
	int i, j, min;

	for( i = 0; i < assoc; i++ )
	{
		if( cache[setIndex][i].valid == 0 )
		{
			miss++;
			memReads++;
			count++;
			cache[setIndex][i].valid = 1;
			cache[setIndex][i].tag = tagIndex;
			cache[setIndex][i].time = count;
			return;
		}
		else
		{
			if( cache[setIndex][i].tag == tagIndex )
			{
				hit++;
				count++;
				cache[setIndex][i].time=count;
				return;
			}
			if( i == ( assoc - 1 ) )
			{
				miss++;
				memReads++;
				
				min = 0;
				for( j = 0; j < assoc; j++ )
				{
					if( cache[setIndex][j].time<=cache[setIndex][min].time )
					{
						min = j;
					}
				}
				cache[setIndex][min].valid = 1;
				cache[setIndex][min].tag = tagIndex;
				count++;
				cache[setIndex][min].time = count;
				return;
			}
		}
	}
	return;
}

void write( unsigned long int tagIndex, unsigned long int setIndex, int assoc )
{
	int i, j, min;

	for( i = 0; i < assoc; i++ )
	{
		if( cache[setIndex][i].valid == 0 )
		{
			miss++;
			memReads++;
			memWrites++;
			count++;
			cache[setIndex][i].valid = 1;
			cache[setIndex][i].tag = tagIndex;
			cache[setIndex][i].time = count;
			return;
		}
		else
		{
			if( cache[setIndex][i].tag == tagIndex )
			{
				hit++;
				memWrites++;
				count++;
				cache[setIndex][i].time = count;
				return;
			}
			if( i == ( assoc - 1 ) )
			{
				miss++;
				memReads++;
				memWrites++;
				min = 0;
				for( j = 0; j < assoc; j++ )
				{
					if( cache[setIndex][j].time <= cache[setIndex][min].time )
					{
						min = j;
					}
				}
				cache[setIndex][min].valid = 1;
				cache[setIndex][min].tag = tagIndex;
				count++;
				cache[setIndex][min].time = count;
				return;
			}
		}
	}
	return;
}

void prefetchrr( unsigned long int tagIndex, unsigned long int setIndex, int assoc )
{
	int i, j, min;

	for( i = 0; i < assoc; i++ )
	{
		if( cache[setIndex][i].valid == 0 )
		{
			memReads++;
			count++;
			cache[setIndex][i].valid = 1;
			cache[setIndex][i].tag = tagIndex;
			cache[setIndex][i].time = count;

			return;
		}
		else
		{
			if( cache[setIndex][i].tag == tagIndex )
			{
				return;
			}
			if( i == ( assoc - 1 ) )
			{
				memReads++;
				min = 0;
				for( j = 0; j < assoc; j++ )
				{
					if( cache[setIndex][j].time <= cache[setIndex][min].time )
					{
						min = j;
					}
				}
				cache[setIndex][min].valid = 1;
				cache[setIndex][min].tag = tagIndex;
				count++;
				cache[setIndex][min].time = count;
				return;
			}
		}
	}
}

void prefetchww( unsigned long int tagIndex, unsigned long int setIndex, int assoc )
{
	int i, j, min;
	
	for( i = 0; i < assoc; i++ )
	{
		if( cache[setIndex][i].valid == 0 )
		{
			memReads++;
			count++;
			cache[setIndex][i].valid = 1;
			cache[setIndex][i].tag = tagIndex;
			cache[setIndex][i].time = count;

			return;
		}
		else
		{
			if( cache[setIndex][i].tag == tagIndex )
			{
				return;
			}
			if( i == ( assoc - 1 ) )
			{
				memReads++;
				min = 0;
				for( j = 0; j < assoc; j++ )
				{
					if( cache[setIndex][j].time <= cache[setIndex][min].time )
					{
						min = j;
					}
				}
				cache[setIndex][min].valid = 1;
				cache[setIndex][min].tag = tagIndex;
				count++;
				cache[setIndex][min].time = count;
				return;
			}
		}
	}
	return;
}

void prefetchr( unsigned long int tagIndex, unsigned long int setIndex, int assoc, unsigned long int tagIndexN, unsigned long int setIndexN )
{
	int i, j, min;

	for( i = 0; i < assoc; i++ )
	{
		if( cache[setIndex][i].valid == 0 )
		{
			miss++;
			memReads++;
			count++;
			cache[setIndex][i].valid = 1;
			cache[setIndex][i].tag = tagIndex;
			cache[setIndex][i].time = count;

			prefetchrr( tagIndexN, setIndexN, assoc );
			return;
		}
		else
		{
			if( cache[setIndex][i].tag == tagIndex )
			{
				hit++;
				count++;
				cache[setIndex][i].time = count;
				return;
			}
			if( i == ( assoc - 1 ) )
			{
				miss++;
				memReads++;
				min = 0;
				for( j = 0; j < assoc; j++ )
				{
					if( cache[setIndex][j].time <= cache[setIndex][min].time )
					{
						min = j;
					}
				}
				cache[setIndex][min].valid = 1;
				cache[setIndex][min].tag = tagIndex;
				count++;
				cache[setIndex][min].time = count;
				prefetchrr( tagIndexN, setIndexN, assoc );
				return;
			}
		}
	}
	return;	
}

void prefetchw( unsigned long int tagIndex, unsigned long int setIndex, int assoc, unsigned long int tagIndexN, unsigned long int setIndexN )
{
	int i, j, min;
	
	for( i = 0; i < assoc; i++ )
	{
		if( cache[setIndex][i].valid == 0 )
		{
			miss++;
			memReads++;
			memWrites++;
			count++;
			cache[setIndex][i].valid = 1;
			cache[setIndex][i].tag = tagIndex;
			cache[setIndex][i].time = count;
			prefetchww( tagIndexN, setIndexN, assoc );
			return;
		}
		else
		{
			if( cache[setIndex][i].tag == tagIndex )
			{
				hit++;
				memWrites++;
				count++;
				cache[setIndex][i].time = count;
				return;
			}
			if( i == ( assoc - 1 ) )
			{
				miss++;
				memReads++;
				memWrites++;
				min = 0;
				for( j = 0; j < assoc; j++ )
				{
					if( cache[setIndex][j].time <= cache[setIndex][min].time )
					{
						min = j;
					}
				}
				cache[setIndex][min].valid = 1;
				cache[setIndex][min].tag = tagIndex;
				count++;
				cache[setIndex][min].time = count;
				prefetchww( tagIndexN, setIndexN, assoc );
				return;
			}
		}
	}
	return;
}

int main( int argc, char** argv )
{

	int assoc;
	int n; //assoc number
	int cacheSize = atoi( argv[1] );
	int blockSize = atoi( argv[4] );
	int setNum;	

	int bit;
	int s;

	char action;

	unsigned long int address;
	unsigned long int setMask;
	unsigned long int setIndex;
	unsigned long int tagIndex;
	unsigned long int newAddress;
	unsigned long int tagIndexN;
	unsigned long int setIndexN;
	

	FILE* fl;
	fl = fopen( argv[5], "r" );

	if( fl == NULL )
	{
		printf( "error\n" );
		return 0;
	}

	if( argv[3][0] != 'l' )
	{
		printf( "policy not correct\n" );
		return 0;
	}

	//handle mapping	
	if( argv[2][0] == 'd' )
	{
		assoc = 1;
		setNum = cacheSize / blockSize;
	}
	else if( argv[2][5] == ':' )
	{
		sscanf( argv[2], "assoc:%d", &n );
		assoc = n;
		setNum = cacheSize / blockSize / n;
	}
	else
	{
		setNum = 1;
		assoc = cacheSize / blockSize;
	}

	bit = log( blockSize ) / log( 2 );
	s = log( setNum ) / log( 2 );

	setMask = ( ( 1 << s ) - 1 );

	cache = create( setNum, assoc );

	while( fscanf( fl, "%*x: %c %lx", &action, &address ) == 2 )
	{

		setIndex = ( address >> bit ) & setMask;
		tagIndex = address >> ( bit + s ); 

		if( action == 'R' )
		{
			read( tagIndex, setIndex, assoc );
		}
		else if( action == 'W' )
		{
			write( tagIndex, setIndex, assoc );
		}
	}

	fclose( fl );
	fl = fopen( argv[5], "r" );
	if( fl == NULL )
	{
		printf( "error\n" );
		return 0;
	}

	printf( "no-prefetch\n" );
	printf( "Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", memReads, memWrites, hit, miss );

	empty( setNum, assoc );

	//with pre fetch
	while( fscanf( fl, "%*x: %c %lx", &action, &address ) == 2 )
	{

		setIndex = ( address >> bit ) & setMask;
		tagIndex = address >> ( bit + s );

		newAddress = address + blockSize;
		setIndexN = ( newAddress >> bit ) & setMask;
		tagIndexN = newAddress >> ( bit + s );

		if( action == 'R' )
		{
			prefetchr( tagIndex, setIndex, assoc, tagIndexN, setIndexN );
		}
		else if( action == 'W' )
		{
			prefetchw( tagIndex, setIndex, assoc, tagIndexN, setIndexN );
		}
	}

	printf( "with-prefetch\n" );
	printf( "Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", memReads, memWrites, hit, miss );

	return 0;
}
