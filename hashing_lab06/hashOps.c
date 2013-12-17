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

int hashSecondary(int key, int m) {
	// private api
  	return key % m;
}

Map* putNew(char* key, int value) {
	Map* el = newElement();

	el->value = value;
	strcpy(el->key, key);

	return el;
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

int hash(int key, int i, int m) {
	// public api
	// m - max length of array
	// i - iterator
	return (hashSecondary(key, m) + i*i) % m;
}

int hashInsert(Map** Array, Map* el, int m) {
	// public api
	int hashPosition, i = 0;
	unsigned int key = makeKey(el->key);

	while( i != m ) {
		hashPosition = hash(key, i, m);
		if( Array[hashPosition] == NULL ) {
			Array[hashPosition] = el;
			return hashPosition;
		} 
		else {
			i++;
		}
	}

	return -1;
}

void hashDelete(Map** Array, Map* el, int m) {
	// public api

}

int main() {
	int i, popularity, hashIndex;
	char surrname[MAX_WORD_LENGTH];
	Map* surrnames[WORDS];
	Map* tmp;

	for(i = 0; i < WORDS; i++) {
		scanf("%i %s", &popularity, surrname);
		tmp = putNew(surrname, popularity);
		hashIndex = hashInsert(surrnames, tmp, WORDS);
		printf("%i %s\n", surrnames[hashIndex]->value, surrnames[hashIndex]->key);
	}

	putchar('\n');
	return 0;
}