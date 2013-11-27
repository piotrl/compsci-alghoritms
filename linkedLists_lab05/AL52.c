#include <stdio.h>
#include <stdlib.h>

struct node {
  int e;
  struct node *next;
} typedef Elem;

Elem* new() {
	return (Elem*)malloc(sizeof(Elem));
}

Elem* add(Elem* list, int value) {
	Elem *tmp = (Elem*)malloc(sizeof(Elem));
	
	tmp->e = value;
	tmp->next = NULL;
	
	return tmp;
}

int main() {
  Elem *head = (Elem*)malloc(sizeof(Elem));
  Elem *piec = (Elem*)malloc(sizeof(Elem));
  
  

  head->next = add(head, 4);  
    
  printf(" test: %i\n", head->next->e);
  
  putchar('\n');
  return 0;
}
