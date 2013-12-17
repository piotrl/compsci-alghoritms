/**
 * AL 6.2
 * http://zylinski.strony.ug.edu.pl/AL6.html
 */

#include <stdio.h>

int hash(int key, int m) {
  return key % m;
}

int makeKey(char *string) {
  int j = 1;
  unsigned int stringKey = 0;

  stringKey = (256 * string[j-1] ) + string[j];

  do {
    j += 2;
    stringKey = stringKey ^ (256 * string[j-1] + string[j]);
  }
  while(string[j-1] && string[j]); 
  return stringKey;
}

void testHashArray(int m) {
  int i, zeros, collisionSum, max, T[m];
  unsigned int stringKey = 0;
  char* string;

  // reset array and counters
  zeros = collisionSum = 0;
  for(i = 0; i < m; i++) { T[i] = 0; } 

  for(i = 0; i < 2*m; i++) {
    scanf("%s", string);
   
    stringKey = makeKey(string);
    T[hash(stringKey, m)] += 1;
  }

  max = T[0];

  for(i = 0; i < m; i++) {
    if(T[i] == 0) zeros++;
    if(T[i] > max) max = T[i];
    collisionSum += T[i];
  }

  printf("\n M: %i\n Zer: %i\n Avg: %.2lf\n Max: %i\n", m, zeros, ((double)collisionSum)/(m-zeros), max);
}

int main() {
  int 
    i,
    m[] = { 1021, 1024, 2048, 1321, 1777, 2670 };
    
  for(i = 0; i < 6; i++) {
    testHashArray(m[i]);
  }
  
  putchar('\n');
  return 0;
}