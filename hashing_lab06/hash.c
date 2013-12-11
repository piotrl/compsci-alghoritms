/**
 * AL 6.2
 * http://zylinski.strony.ug.edu.pl/AL6.html
 */

#include <stdio.h>

int hash(int key, int m) {
  return key % m;
}

int main() {
  int 
    i, j,
    m = 3,
    T[m];
  unsigned int stringKey = 0;

  char string[20];

  for(i = 0; i < m; i++) {
    scanf("%s", string);
   
    j = 1;

    stringKey = (256 * string[j-1] ) + string[j];
    
    do {
      j += 2;
      stringKey = stringKey ^ (256 * string[j-1] + string[j]);
    }
    while(string[j] != '\0');

    printf("%i\n", stringKey);
  }
  
  putchar('\n');
}
