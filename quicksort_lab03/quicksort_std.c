#include <stdio.h>

int partition(int A[], int left, int right) {
  int
    x = A[right],   // Element wg ktorego dzielimy
    i = left-1,    // Tuz przed tablica
    j; // Tuz za tablica
  int tmp;
  
  for(j = left; j <= right; j++) {
    if( A[j] <= x ) {
      i++;
      tmp = A[i]; A[i] = A[j]; A[j] = tmp;
    }
  }
  
  if( i < right) {
    return i;
  } else {
    return i-1;
  }
}

void quickSort(int A[], int left, int right) {
  int mid;
  if (left < right) {
    mid = partition(A, left, right);
    quickSort(A, left, mid);
    quickSort(A, mid+1, right);
  }
}

int main() {
  /**
   * Testowanie roznych danych
   * ******************************************** 
   */

  int A[10] = {0};
  int i, j;

  // generowanie liczb
  // 1) losowych
  // 2) posortowanych
  for(i = 2; i < 1000; i++) {
    int A[i] = {0};
    for(j = 0; j < 1000; j++) {
      A[j] = i+j;
    }
    // check time
    QuickSort(A, 0, 1000);
    // end time
  }

  // 3) posortowanych odwrotnie

  for(i = 0; i < 10; i++) {
    A[i] = 10-i+1;
  }
  A[0] = 1;
  A[3] = -1; A[5] = 0;

  /**
   * Sortowanie
   * ******************************************** 
   */
  
  quickSort(A, 0, 10);
  
  putchar('\n');
  for(i = 0; i < 10; i++) {
    printf("%i ", A[i]);
  }

  
  putchar('\n');
  return 0;
}
