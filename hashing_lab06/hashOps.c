/**
 * AL 6.3 	HashMap: Insert and Remove operations
 * http://zylinski.strony.ug.edu.pl/AL6.html
 *
 * @author 	Piotr Lewandowski
 * @site	piotrl.net
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 30
#define WORDS 6


/**
 * PRIVATE MAP API
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */

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

/**
 * PRIVATE HASH API
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */

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

/**
 * PUBLIC API
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */

int hash(int key, int i, int m) {
	// m - max length of array
	// i - iterator
	return (hashSecondary(key, m) + i*i) % m;
}

int hashInsert(Map** Array, Map* el, int m) {
	int hashPosition, i = 0;
	unsigned int key = makeKey(el->key);

	while( i <= m ) {
		hashPosition = hash(key, i, m);

		if( Array[hashPosition] ==  NULL ) {
			Array[hashPosition] = el;
			return hashPosition;
		} 
		else {
			i++;
		}
	}

	return -1;
}

int hashDelete(Map** Array, char* string, int m) {

	int hashPosition, i = 0;
	unsigned int key = makeKey(string),
				 tmpKey;

	while( i <= m ) {
		hashPosition = hash(key, i, m);
		tmpKey = makeKey(Array[hashPosition]->key);

		if(tmpKey == key ) {
			free(Array[hashPosition]);
			Array[hashPosition] = NULL;
			return hashPosition;
		} 
		else {
			i++;
		}
	}

	return -1;

}

/**
 * MAIN: TESTING HASH-API PROGRAM
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */

int main() {
	int i, popularity, hashIndex;
	char surrname[MAX_WORD_LENGTH];
	Map* surrnames[WORDS];
	Map* tmp;

	// Initialize HashMap
	for(i = 0; i < WORDS; i++) surrnames[i] = NULL;

	// Load map elements and hash
	for(i = 0; i < WORDS; i++) {
		scanf("%i %s", &popularity, surrname);
		tmp = putNew(surrname, popularity);
		hashIndex = hashInsert(surrnames, tmp, WORDS);

		if(hashIndex < 0) {
			printf("%s: %s\n", "Not found hash position for", surrname);
		}
	}

	// Log operations results
	printf("\n%s:\n", "Saved elements");

	for (i = 0; i < WORDS; ++i)
	{
		if(surrnames[i] != NULL) {
			printf("HashMap[%i]: %6i %s\n", i, surrnames[i]->value, surrnames[i]->key);
		} else {
			printf("HashMap[%i]: ------\n", i);
		}
	}

	hashDelete(surrnames, "Nowak", WORDS);

	printf("\n%s: %s\n", "Deleted position", "Nowak");

	for (i = 0; i < WORDS; ++i)
	{
		if(surrnames[i] != NULL) {
			printf("HashMap[%i]: %6i %s\n", i, surrnames[i]->value, surrnames[i]->key);
		} else {
			printf("HashMap[%i]: ------\n", i);
		}
	}

	putchar('\n');
	return 0;
}