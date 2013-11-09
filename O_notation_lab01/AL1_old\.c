// kompilowac z opcjami -lrt -lm: gcc AL1.c -lrt -lm
#include <time.h>
#include <stdio.h>
#include <math.h>
#define MAX 60000l
#define MLD 1000000000.0 //10**9

double procedura1(int n){
  float x=0;
  int i,j,k;
  
  for(i=n-1;i>1;i--) {
    if((i % 2) == 1) {
      for(j=1;j<i+1;j++) ; 
      for(k=i+1;k<n+1;k++) x=x+1;
    }
  } 
  return x;
}

double procedura2(double A[], int n) {
  double x = 0.0, suma;
  int i, d, g;

  for(d = 1; d < n; d++) {
    for(g = d; g < n; g++) {
      suma = 0.0;
      for( i = d; i < g; i++ ) {
        suma += A[i];
      }
      x = x < suma ? suma : x; // max
    }
  }
  return x;
}

void procedura3(int n) {
  int i, j, max = sqrt(n), k = 0;
  for(i = 1; i < max; i++) {
    j = 1;
    while( j < max ) {
      j = j+j;
      // k++;
    }
  }
  // printf("-- %i\n", k);
}

main(){
  struct timespec tp0, tp1;
  double Tn,Fn,x;
  int n;
  double A[5000];
  for(n = 1; n <= 5000; n++ ) {
    A[n] = n;
    // printf(" %lf", A[n]);
  }

  for(n=2;n<5000;n=3*n) /2){
    

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    
    // przykladowe obliczenia
    // x = procedura1(n);
     x = procedura2(A, n+1);
    // procedura3(n);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);       
    
    // zgadywana funkcja
    //        Fn=5*n ; // np. funkcja liniowa
    //      Fn=20000*n ; // np. funkcja liniowa
    //      Fn=n*n; 
          // Fn=sqrt(n)*log2(sqrt(n)); // procedura3
    //      Fn=n*n*sqrt(n);
         Fn=n*n*n;     //procedura2
         // Fn=n*n/1000;  //procedura1
    
    
    
    Tn=(tp1.tv_sec+tp1.tv_nsec/MLD)-(tp0.tv_sec+tp0.tv_nsec/MLD);
    printf("n: %5d \tczas: %3.5lf \twspolczynnik: %3.5lf \t x = %lf \n",n,Tn, Fn/Tn, x);
  }
}
