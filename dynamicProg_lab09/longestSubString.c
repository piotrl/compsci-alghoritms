#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * Finding the longest substring.
 * Implemented with dynamic programming method.
 *
 * Program get strings from call parametrs
 *
 * @spec 	AL9.2 https://strony.ug.edu.pl/~zylinski/AL9.html
 * @author 	Piotr Lewandowski
 * @site	piotrl.net
 */

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		printf("Wymagane jest podanie dwoch argumentow. \n");
		printf("Wywolanie programu: %s 1111 1101 \n", argv[0]);
		return 2;
	}

	// geting arguments into variables
	int str1_length = strlen(argv[2]),
		str2_length = strlen(argv[3]);

	char str1[str1_length], str2[str2_length];
	strcpy(str1, argv[2]);
	strcpy(str2, argv[3]);


	int Array[str1_length][str2_length];

	// fill array

	for(int i = 1; i < str1_length; i++)
	{
		for(int j = 1; j < str2_length; j++)
		{
			Array[i][j] = 0;	// reset array
		}
	}

	for(int i = 1; i < str1_length; i++)
	{
		for(int j = 1; j < str2_length; j++)
		{
			if (str1[i] == str2[j])
			{
				Array[i][j] = Array[i][j-1]+1;
			}
			else
			{
				Array[i][j] = Array[i-1][j-1];	
			}

			printf("%i ", Array[i][j]);
		}
		putchar('\n');
	}

	return 0;
}