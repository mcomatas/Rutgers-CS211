#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	int length;
	int vowels = 0;
	int i;
	int j;

	for( j = 1; j < argc; j++ )
	{
		length = strlen(argv[j]);
		for( i = 0; i < length; i++ )
		{
			if( argv[j][i] == 'a' || argv[j][i] == 'e' || argv[j][i] == 'i' || argv[j][i] == 'o' || argv[j][i] == 'u' ||
			argv[j][i] == 'A' || argv[j][i] == 'E' || argv[j][i] == 'I' || argv[j][i] == 'O' || argv[j][i] == 'U' )
			{
				vowels++;
			}
		}
	}

	char vow[vowels];
	int k = 0;

	for( j = 1; j < argc; j++ )
	{
		length = strlen(argv[j]);
		for( i = 0; i < length; i++ )
		{
			if( argv[j][i] == 'a' || argv[j][i] == 'e' || argv[j][i] == 'i' || argv[j][i] == 'o' || argv[j][i] == 'u' ||
			argv[j][i] == 'A' || argv[j][i] == 'E' || argv[j][i] == 'I' || argv[j][i] == 'O' || argv[j][i] == 'U' )
			{
				vow[k] = argv[j][i];
				k++;
			}
		}
	}

	int vowLength = sizeof vow / sizeof vow[0];

	for( i = 0; i < vowLength; i++ )
	{
		printf( "%c", vow[i] );
	}
	printf( "\n" );

	return 0;
}
