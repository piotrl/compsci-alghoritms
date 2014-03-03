#include <stdio.h>
#include <stdlib.h>

/**
 * Generate random numbers (default) from -100 to 100
 * USAGE: generate FILE_NAME AMOUNT_OF_NUMBERS [optional FROM TO]
 * ------------------------------------------------------------
 */

#define NUMBER_TYPE double
#define PROCENT_TYPE_NOTATION %lf

/**
 * min: minimal range number
 * max: maximal range number
 */

NUMBER_TYPE frand(NUMBER_TYPE min, NUMBER_TYPE max) {
  return  min + (max-min)*(NUMBER_TYPE)rand()/(RAND_MAX+1.0);
}

/**
 * args[0]: name of running program
 * args[1]: filename, where put the data
 * args[2]: amount of data
 * args[3]: [optional] minimal random number
 * args[4]: [optional] maximal random number
 */

int main(int args, char* arg[])
{
    int i;

    if(args <= 2)
    {
        printf("Poprawne wywolanie: %s FILE_NAME ILOSC_LICZB\n", arg[0]);
        return 1;
    }

    FILE* output = fopen(arg[1], "w");

    for(i = 0; i < atoi(arg[2]); i++)
    {
        fprintf(output, "" PROCENT_TYPE_NOTATION "\n", frand(-100, 100));
    }

    fclose(output);

    putchar('\n');
    return 0;
}