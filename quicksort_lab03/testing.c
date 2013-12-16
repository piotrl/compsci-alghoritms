#include <math.h>
#include "quicksort.h" // functions for quicksort implementation

#define MLD 1000000000.0  //10**9
#define ARRAY_MAX 50000   // maksimum length of array

#define GET_RANDOM 1
#define GET_SORTED 0

#define FN_N 3
#define FN_NN 2
#define FN_NNN 1
#define FN_NLOGN 0

#define ALG_STANDARD_QUICKSORT 1
#define ALG_INSERTED_QUICKSORT 0

/**
 * Compilation:
 * gcc -Wall testing.c quicksort_std.c -lrt -lm
 * 
 */

int frand(int min, int max) {
  return min + (int)rand() % (max-min);
}

void sort(int A[], int n, int algorithm) {
  // algorithm : 1 - standard quickSort, 2 - randomized, 3 - median

  if(algorithm == ALG_STANDARD_QUICKSORT)
    quickSort(A, 0, n);
  else if(algorithm == ALG_INSERTED_QUICKSORT)
    ins_quickSort(A, 0, n);
}

void test_complexity(int A[], int isRandom, int Fn, int alg) {

  struct timespec tp0, tp1;
  double Tn;
  int n, j;
  srand(4);

  for(n = 128; n < ARRAY_MAX; n=n*2) {
    
    for(j = 0; j < n; j++) {
      A[j] = (isRandom) ? frand(-500, 500) : n-j;
      // if(n == 128)
      //   printf("%i ", A[j]);
    }
    // check time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

    sort(A, n, alg);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);
    // end of time measuring

    // if(n == 128) {
    // printf("\n\n");

    //     for(j = 1; j <= n; j++) {
    //       printf("%i ", A[j]);
    //   }
    //   printf("\n");
    // }

    if(Fn == FN_N)
      Fn = n;
    else if(Fn == FN_NN)
      Fn = n*n;
    else 
      Fn = n*log2(n);

    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf(" n: %5d \tczas: %3.5lf \twspolczynnik: %3.5lf\n", n, Tn, Fn/Tn);
  }
}

int main() {
  int A[ARRAY_MAX]; 

  /**
   * Testowanie roznych danych
   * ******************************************** 
   */
  printf("\n Pesymistyczny przypadek. O( n*n )\n");
  printf(" quickSort.\n");
  printf(" ---------------------------------------\n");

  test_complexity(A, GET_SORTED, FN_NN, ALG_STANDARD_QUICKSORT);

  printf("\n Sredni przypadek. O( n*log2(n) )\n");
  printf(" quickSort.\n");
  printf(" ---------------------------------------\n");

  test_complexity(A, GET_RANDOM, FN_NLOGN, ALG_STANDARD_QUICKSORT);

  /* ******************************************** */

  printf("\n Pesymistyczny przypadek. O( n*n )\n");
  printf(" quickSort && insertedSort.\n");
  printf(" ---------------------------------------\n");

  test_complexity(A, GET_SORTED, FN_NN, ALG_INSERTED_QUICKSORT);

  printf("\n Sredni przypadek. O( n*log2(n) )\n");
  printf(" quickSort && insertedSort.\n");
  printf(" ---------------------------------------\n");

  test_complexity(A, GET_RANDOM, FN_NLOGN, ALG_INSERTED_QUICKSORT);
  
  putchar('\n');
  return 0;
}