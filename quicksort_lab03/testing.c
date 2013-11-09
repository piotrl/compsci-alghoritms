#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "quicksort.h" // functions for quicksort implementation

#define MAX 60000l
#define MLD 1000000000.0 //10**9
#define ARRAY_MAX 50000
// #define ALGORITHM_PARAMETRS A, 0, 10
// #define ALGORITHM(name, parametr) quickSort(ALGORITHM_PARAMETRS)

/**
 * Compilation:
 * gcc -Wall testing.c quicksort_std.c -lrt -lm
 * TODO: write a make file
 */

int frand(int min, int max) {
  return min + (max-min)*(int)rand();
}

int main() {
  struct timespec tp0, tp1;
  double Tn,Fn;
  int A[ARRAY_MAX];
  int n, j;
  srand(time(NULL));

  /**
   * Testowanie roznych danych
   * ******************************************** 
   */

  printf("\n Pesymistyczny przypadek. O(n*n)\n");
  printf(" Tablica posortowana - rosnaca.\n");
  printf(" ---------------------------------------\n");

  for(n = 128; n < ARRAY_MAX; n=n*2) {
  
    for(j = 0; j < n; j++) {
      A[j] = j;
    }
    // check time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

    quickSort(A, 0, n);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);       
    // end of time measuring

    Fn = n*n;
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf(" n: %5d \tczas: %3.5lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
  }

  printf("\n Pesymistyczny przypadek. O( n*n )\n");
  printf(" Tablica posortowana - malejaco.\n");
  printf(" ---------------------------------------\n");

  for(n = 128; n < ARRAY_MAX; n=n*2) {
  
    for(j = 0; j < n; j++) {
      A[j] = n-j;
    }
    // check time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

    quickSort(A, 0, n);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);       
    // end of time measuring

    Fn = n*n;
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf(" n: %5d \tczas: %3.5lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
  }

  printf("\n Sredni przypadek. O( n*log2(n) )\n");
  printf(" Tablica z losowymi elementami.\n");
  printf(" ---------------------------------------\n");

  for(n = 128; n < ARRAY_MAX; n=n*2) {
  
    for(j = 0; j < n; j++) {
      A[j] = frand(-500, 500);
      
    }
    // check time
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);

    quickSort(A, 0, n);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);       
    // end of time measuring

    Fn = n*log2(n);
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf(" n: %5d \tczas: %3.5lf \twspolczynnik: %3.5lf\n",n,Tn, Fn/Tn);
  }
  
  putchar('\n');
  return 0;
}