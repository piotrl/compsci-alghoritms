#include <stdlib.h>
#include <time.h>
#include <stdio.h>


int frand(int min, int max);

int partition(int A[], int left, int right);
void quickSort(int A[], int left, int right);

// int randomized_partition(int A[], int left, int right);
// void randomized_quickSort(int A[], int left, int right);

void insertSort(int A[], int min, int n);
void ins_quickSort(int A[], int left, int right);