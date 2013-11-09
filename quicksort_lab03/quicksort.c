#include "quicksort.h"

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