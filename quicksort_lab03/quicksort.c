#include "quicksort.h"

int partition(int A[], int left, int right) {
  int
    x = A[right],   // Element wg ktorego dzielimy
    i = left-1,    // Indeks tuz przed tablica
    j,
    tmp;

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

void insertSort(int A[], int min, int n) {
  int j, tmp;
  
  int k = min+1;
  while(k <= n) {
    j = k-1;
    while( j>=min && ( A[j+1]<A[j] ) ) {
      tmp = A[j+1]; A[j+1] = A[j]; A[j] = tmp;
      j--;
    }
    k++;
  }
}

void ins_quickSort(int A[], int left, int right) {
  int mid;
  if ( right-left > 32 ) {
    mid = partition(A, left, right);
    ins_quickSort(A, left, mid);
    ins_quickSort(A, mid+1, right);
  } else {
    insertSort(A, left, right);
  }
}
