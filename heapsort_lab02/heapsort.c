#include <stdio.h>
#define N 1000

void heapify(int A[], int heapSize, int i) {
  // A - tablica reprezentujaca kopiec,
  // i - pozycja w tej tablicy

  int l = 2*i,   // lewy syn
    r = 2*i + 1, // prawy syn
    largest,
    tmp;

  /**
   * wybieramy ktory element (ojciec, lewy syn, prawy syn) jest nawiekszy 
   * *********************************************************************
   */
  
  if( l <= heapSize && A[l] > A[i] ) {
    largest = l;
  } else {
    largest = i;
  }
  
  if(r <= heapSize && A[r] > A[largest]) {
    largest = r;
  }

  /**
   * jesli ojciec (i) nie jest najwiekszy, zemien go z najwiekszym synem
   * kolejny raz uszereguj kopiec (dopoki ojciec nie bedzie najwyzej)
   * *********************************************************************
   */
  if(largest != i) {
    tmp = A[i]; A[i] = A[largest]; A[largest] = tmp;
    heapify(A, heapSize, largest);
  }
}

void buildHeap(int A[], int heapSize) {
  // nadajemy porzadek kopcowy w tablicy A

  int  i;
  
  for(i = heapSize/2; i >= 1; i--) {
    // heapSize/2 -- id ojca w tablicy

    heapify(A, heapSize, i);
  }
}

void heapSort(int A[], int heapSize) {
  int i, tmp;
  
  buildHeap(A, heapSize);
  
  for(i = heapSize; i >= 2; i--) {
    tmp = A[1]; A[1] = A[heapSize]; A[heapSize] = tmp;
    heapSize = heapSize - 1;
    heapify(A, heapSize, 1);
  }
}

int main() {
  
  int A[N] = {0},
    heapSize = 0, i,
    pass = 1;

  /**
   * Odczyt z pliku
   * ****************************************************
   */

  do {
    // pass: Liczba udanych pobran ze scanfa
    pass = scanf("%i", &A[heapSize]);

    if (pass == 1) heapSize++;
  }
  while (pass == 1); 

  /**
   * Sortowanie
   * ****************************************************
   */

  heapSort(A-1, heapSize); // wczytuje od smiecia n = -1
                 // zeby sortowalo odpoczatku tab: n+1 = 0

  /**
   * Wydruk wyniku sortowania
   * ****************************************************
   */

  for(i = 0; i < heapSize; i++) {
    printf("%i ", A[i]);
  }
  
  putchar('\n');
  return 0;
}