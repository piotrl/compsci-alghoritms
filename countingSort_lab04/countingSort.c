// wskazowka do sortowania pozycyjnego
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MDN 254 // maks. dlugosc napisu
#define MN 10 // maks il napisow


#define DEBUG(var, type) \
  printf(" %i: " #var " == " #type " \n", __LINE__, var)


char **A,**B,**TMP;

void drukuj(char **A, int n) {
  // drukuje  drugie litery napisow i napisy  
  int i;
  for (i=0;i<n;i++){
    printf(" %s",A[i]);  
    // printf("%c %s",*(A[i]+1),A[i]);  
//czyli   printf("%c %s",*(*(A+i)+1),*(A+i));  
    printf("\n");
  }
}

void czytaj(char **A, int ilosc) {
  char slowo[MDN];
  int i = 0;
  for(i = 0; i < ilosc; i++) {
    scanf("%s",slowo);
    A[i] = (char*) malloc(sizeof(char)*MDN);
    strcpy(A[i], slowo);
  }
}

void countingSort(char **input, char **output, int k) {
  // k - najwiekszy element w tablicy input
  
  int i, j;
  char count[MDN+1]; // tablica pomocnicza, zmienia swoja zawartosc po kazdej petli

  // Zerujemy tablice zliczajaca ilosc powtorzen
  // wszystkich elementow tablicy input

  for(i = 0; i <= MDN; i++)
    count[i] = 0;

  // zliczanie powtorzen kazdej litery z input[j]
  // kiedy 'a' wystepuje dwa razy, to:
  // count['a'] == 2 || count[65] == 2

  for(j = 0; j < k; j++) {
    count[ (int) input[j][0] ] += 1;
  }

  // count[i] bedzie przechowywac ilosc elementow
  // mniejszych lub rownych od count[i]

  for(i = 1; i <= MDN; i++) {
    count[i] += count[i-1];
    // DEBUG( count[i], %i );
  }
  
  for(j = k-1; j >= 0; j--) {
    // T=A; A=B; B=T; // zamiana wskaznikow do tablic
    output[ (int) count[ (int) input[j][0] ]-1 ] = input[j];
    count[ (int) input[j][0] ] -= 1;
    // DEBUG( output[ (int) count[ (int) input[j][0] ] ], %i);
    // DEBUG( input[j][0], %i);
  }
}

int main() {
  int n=3;
  A=(char**) malloc(n*sizeof(char*));
  B=(char**) malloc(n*sizeof(char*));
  printf("tablica A: \n"); czytaj(A,n); 

  countingSort(A, B, n);

  printf("sorted: \n"); drukuj(B,n);

  return 0;
}
