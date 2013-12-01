// wskazowka do sortowania pozycyjnego
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MDN 254 // maks. dlugosc napisu
#define MN 10 // maks il napisow


#define DEBUG(var, type) \
  printf(" %i: " #var " == " #type " \n", __LINE__, var)

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

void czytaj(char **A, int strSize[], int ilosc) {
  char slowo[MDN];
  int i = 0;
  for(i = 0; i < ilosc; i++) {
    scanf("%s",slowo);
    A[i] = (char*) malloc( MDN * sizeof(char) );
    strcpy(A[i], slowo);
    strSize[i] = strlen(A[i]);
  }
}


 int check(char** A, int strLen, int strNum, int charPos){
   return (charPos <= strLen) ? (int) A[strNum][charPos] : 0;
 }

void countingSort(char **input, int strSizes[], int sorted_elements, int charPos) {
  // k - najwiekszy element w tablicy input
  
  int i, j;
  char count[MDN+1]; // tablica pomocnicza, zmienia swoja zawartosc po kazdej petli
  char **tmp = (char**) malloc(sorted_elements*sizeof(char*));
  // Zerujemy tablice zliczajaca ilosc powtorzen
  // wszystkich elementow tablicy input

  for(i = 0; i <= MDN; i++)
    count[i] = 0;

  // zliczanie powtorzen kazdej litery z input[j]
  // kiedy 'a' wystepuje dwa razy, to:
  // count['a'] == 2 || count[65] == 2

  for(j = 0; j < sorted_elements; j++) {
    count[ check(input, strSizes[j], j, charPos ) ] += 1;
  }

  // count[i] bedzie przechowywac ilosc elementow
  // mniejszych lub rownych od count[i]

  for(i = 1; i <= MDN; i++) {
    count[i] += count[i-1];
    // DEBUG( count[i], %i );
  }
  
  for(j = sorted_elements-1; j >= 0; j--) {
    // T=A; A=B; B=T; // zamiana wskaznikow do tablic
    tmp[ (int) count[ check(input, strSizes[j], j, charPos ) ]-1 ] = input[j];
    count[ check(input, strSizes[j], j, charPos ) ] -= 1;
    // DEBUG( (int) count[ (int) input[j][charPos] ], %i);
    // DEBUG( input[j][charPos], %c);
  }

  for(j = sorted_elements-1; j >= 0; j--) {
    input[j] = tmp[j];
  } 
  free(tmp);
}

int main() {
  int i, n=3, max_length;
  char** A = (char**) malloc(n*sizeof(char*));
  int strSizes[n];

  printf(" tablica A: \n"); czytaj(A, strSizes, n); 

  max_length = strSizes[0];
  for(i = 1; i < n-1; i++) {
    if(max_length < strSizes[i+1]) 
      max_length = strSizes[i+1];
  }

  for(i = max_length-1; i >= 0; i--) {
    countingSort(A, strSizes, n, i);
    printf("Pozycja: %i\n", i+1);
    drukuj(A,n);
  }

  printf("\n sorted: \n"); drukuj(A,n);

  return 0;
}
