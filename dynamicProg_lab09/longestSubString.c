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

void printMatrix(int ilen, int jlen, int matrix[ilen][jlen])
{	// ilen - rows
	// jlen 
	printf("\n id  ");

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

int lcsLenght(	int ylen, int xlen, // lengths of strings
				char* y, char* x, 	// strings
				int c[ylen+1][xlen+1], int b[ylen][xlen]	// arrays with NWP
			 )
{	// x and y - strings to compare
	
	for (int i = 0; i <= ylen; ++i)
		c[i][0] = 0;
	for (int i = 0; i <= xlen; ++i)
		c[0][i] = 0;

	// filling arrays 
	for (int i = 1; i <= ylen; ++i)
	{
		for (int j = 1; j <= xlen; ++j)
		{
			if (x[j-1] == y[i-1])
			{
				c[i][j] = c[i-1][j-1]+1;
				b[i-1][j-1] = UPLEFT;		// get from up left
			}
			else if (c[i-1][j] >= c[i][j-1])
			{
				c[i][j] = c[i-1][j];
				b[i-1][j-1] = UP;			// get from up
			}
			else
			{
				c[i][j] = c[i][j-1];
				b[i-1][j-1] = LEFT;			// get from left			
			}
		}
	}

	return c[ylen][xlen];
}

void lcsPrint( 	int i, int j, // i == ylen, j == xlen
				int b[i][j],  // i,j == initial position of path 
				char* x
			 )
{
	if (j == 0 || i == 0)
	{
		return;
	}

	if (b[i][j] == UPLEFT)			
	{
		printf(" i == %i, j == %i \n", i, j);
		lcsPrint( i-1, j-1, b, x);	// go up left
		printf("%c", x[j]);
	} 
	else if (b[i][j] == UP) 	
	{
		lcsPrint(i-1, j, b, x);		// go up
	} 
	else
	{
		lcsPrint(i, j-1, b, x); 	// go left
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


	int c[ylen+1][xlen+1],
		b[ylen][xlen];
	
	int longestSubString = lcsLenght(ylen, xlen, y, x, c, b);

	printf(" %s\n %s\n\n", x, y );
	printf("-----------------------------------\n");

	printMatrix(ylen+1, xlen+1, c);

	putchar('\n');
	printf("-----------------------------------\n");
	printf(" 0 - UPLEFT; 1 - UP; 2 - LEFT\n");

	printMatrix(ylen, xlen, b);

	putchar('\n');
	printf("-----------------------------------\n");

	printf(" length of longest substring: %i\n", longestSubString);
	// while(xlen >= 0 && c[ylen][xlen] == longestSubString)
	// {
		lcsPrint(ylen-1, xlen-1, b, x);
	// 	putchar('\n');
	// 	xlen--;
	// }
	
	putchar('\n');
	putchar('\n');
	return 0;
}