/**
 * AL 6.3
 * http://zylinski.strony.ug.edu.pl/AL6.html
 * @author Piotr Lewandowski
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 30
#define WORDS 3

struct keyPair {
	int value;
	char key[MAX_WORD_LENGTH];
	// private api
	// Inner model of simple key-value map
} typedef Map;

Map* newElement() {
	// private api
	// allocation of memmory for pair of key-value

	return (Map*) malloc( sizeof(Map) );
}

Map* putNew(char* key, int value) {
	Map* el = newElement();

	el->value = value;
	strcpy(el->key, key);

	return el;
}

int hash(int key, int m) {
	// public api
  return key % m;
}

void hashInsert(int* Array, int key) {
	// public api

}

void hashDelete(int* Array, int key) {
	// public api

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

int main() {
	int i, popularity;
	char surrname[MAX_WORD_LENGTH];
	Map* surrnames[WORDS];

	for(i = 0; i < WORDS; i++) {
		scanf("%i %s", &popularity, surrname);
		surrnames[i] = putNew(surrname, popularity);
	}

	for(i = 0; i < WORDS; i++) {
		printf("%i %s\n", surrnames[i]->value, surrnames[i]->key);
	}

	putchar('\n');
	return 0;
}