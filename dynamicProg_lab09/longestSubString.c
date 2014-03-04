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

 void lcsPrint(int **b, char *x, int i, int j)
 {
 	if (i == 0 || j == 0)
 	{
 		return;
 	}

 	if (b[i][j] == 0)
 	{
 		lcsPrint(b, x, i-1, j-1);
 		printf("%c\n", x[i]);
 	}
 }

int main(int argc, char const *argv[])
{
	putchar('\n');

	if (argc != 3)
	{
		printf("[ERROR] Wymagane jest podanie dwoch argumentow. \n");
		printf("[INFO]  Wywolanie programu: %s 1111 1101 \n", argv[0]);

		putchar('\n');
		return 2;
	}

	// geting arguments into variables
	int str1_length = strlen(argv[1]),
		str2_length = strlen(argv[2]);

	char str1[str1_length], str2[str2_length];
	strcpy(str1, argv[1]);
	strcpy(str2, argv[2]);


	int Array[str1_length][str2_length],
		b[str1_length][str2_length];

	for(int i = 0; i <= str1_length; i++)
	{
		for(int j = 0; j <= str2_length; j++)
		{
			Array[i][j] = 0;	// reset array
		}
	}

	// fill array

	for(int i = 0; i <= str1_length; i++)
	{
		for(int j = 0; j <= str2_length; j++)
		{
			if (j != 0 && i != 0)
			{
				if(str1[i] == str2[j])
				{
					Array[i][j] = Array[i-1][j-1]+1;
					b[i][j] = 0;	// up left
				}
				else if (Array[i-1][j] >= Array[i][j-1])
				{
					Array[i][j] = Array[i-1][j];
					b[i][j] = 1;	// up
				}
				else
				{
					Array[i][j] = Array[i][j-1];
					b[i][j] = 2;	// left
				}
			}

			printf("%i ", Array[i][j]);
		}
		putchar('\n');
	}

	putchar('\n');
	return 0;
}