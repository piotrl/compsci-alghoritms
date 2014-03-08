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

#include <stdio.h>	// printf(), putchar()
#include <string.h>	// strcpy(), strlen()
#include <assert.h>

#define DEBUG(var, type) \
	printf(" %i: " #var " == " #type " \n", __LINE__, var)

#define UPLEFT 0
#define UP 1
#define LEFT 2

void printMatrix(int ilen, int jlen, int matrix[][100], char id)
{	// ilen - rows
	// jlen 
	printf("\n %c   ", id);

	for (int i = 0; i < jlen; ++i)
		printf("%i ", i);
	printf("\n ");
	for (int i = 0; i < jlen; ++i)
		printf("---");	

	printf("\n");

	for(int i = 0; i < ilen; i++)
	{
		printf(" %i | ", i);
		for (int j = 0; j < jlen; j++)
		{
			printf("%i ", matrix[i][j]);
		}
		putchar('\n');
	}
}

	int c[100][100],
		b[100][100];

int lcsLenght(	int ylen, int xlen, // lengths of strings
				char* y, char* x 	// strings
			 )
{	// x and y - strings to compare
	
	for (int i = 0; i <= ylen; ++i)
	{
		c[i][0] = 0;
		b[i][0] = 8;
	}
	for (int i = 0; i <= xlen; ++i)
	{
		c[0][i] = 0;
		b[0][i] = 8;
	}

	// filling arrays 
	for (int i = 1; i <= ylen; ++i)
	{
		for (int j = 1; j <= xlen; ++j)
		{
			if (x[j-1] == y[i-1])
			{
				c[i][j] = c[i-1][j-1]+1;
				b[i][j] = UPLEFT;		// get from up left
			}
			else if (c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j];
				b[i][j] = UP;			// get from up
			}
			else
			{
				c[i][j] = c[i][j-1];
				b[i][j] = LEFT;			// get from left			
			}
		}
	}

	return c[ylen][xlen];
}

void lcsPrint( 	int i, int j, // i == ylen, j == xlen
				char* x
			 )
{
	if (j == 0 || i == 0)
	{
		return;
	}

	if (b[i][j] == UPLEFT)			
	{
		// printf("UPLEFT \ti == %i, j == %i, b[%i][%i] == %i \n", i, j, i, j, b[i][j]);
		lcsPrint( i-1, j-1, x);	// go up left
		printf("%c", x[j-1]);
	} 
	else if (b[i][j] == UP) 	
	{
		// printf("UP: \ti == %i, j == %i, b[%i][%i] == %i \n", i, j, i, j, b[i][j]);
		lcsPrint(i-1, j, x);		// go up
	} 
	else
	{
		// printf("LEFT: \ti == %i, j == %i, b[%i][%i] == %i \n", i, j, i, j, b[i][j]);
		lcsPrint(i, j-1, x); 	// go left
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
	int xlen = strlen(argv[1]),
		ylen = strlen(argv[2]);

	char x[xlen], y[ylen];
	strcpy(x, argv[1]);
	strcpy(y, argv[2]);

	
	int longestSubString = lcsLenght(ylen, xlen, y, x);

	printf(" %s\n %s\n\n", x, y );
	printf("-----------------------------------\n");

	printMatrix(ylen+1, xlen+1, c, 'c');

	putchar('\n');
	printf("-----------------------------------\n");
	printf(" 0 - UPLEFT; 1 - UP; 2 - LEFT\n");

	printMatrix(ylen+1, xlen+1, b, 'b');

	putchar('\n');
	printf("-----------------------------------\n");

	printf(" length of longest substring: %i\n", longestSubString);
	while(xlen >= 0 && c[ylen][xlen] == longestSubString)
	{
		lcsPrint(ylen, xlen, x);
		putchar('\n');
		xlen--;
	}
	
	putchar('\n');
	putchar('\n');
	return 0;
}