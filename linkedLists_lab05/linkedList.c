#include <stdio.h>
#include <stdlib.h>

struct node {
  int val;
  struct node *next;
  struct node *prev;
} typedef Elem;

Elem* newElement() {
	return (Elem*) malloc( sizeof(Elem) );
}

void initGuard(Elem* guard) {
  guard->next = guard;
  guard->prev = guard;

  guard->val = 0;   // number of elements in list
}

Elem* list_add(Elem* guard, int value) {
	Elem *newEl = newElement();
  newEl->val = value;

  newEl->next = guard->next;
  guard->next->prev = newEl;
  guard->next = newEl;

  newEl->prev = guard;
  guard->val++;

  return newEl;	
}

void list_delete(Elem* guard, Elem* element) {
  element->prev->next = element->next;
  element->next->prev = element->prev;
  free(element);
  guard->val--;
}

Elem* list_Search(Elem* guard, int x) {
  Elem* tmp = guard->next;

  while( tmp != guard && tmp->val == x ) {
    tmp = tmp->next;
  } 

  return tmp;
}

void list_print_all(Elem* guard) {
  Elem* iterator = guard->next;
  printf(" %i elementy: ", guard->val);  // print number of elements in list

  while( iterator != guard ) {
    printf("%i ", iterator->val );
    iterator = iterator->next;
  } 

  putchar('\n');
}

void list_delete_all(Elem* guard) {
  Elem* i = guard->next;
  while( i != guard ) {
    i = i->next;
    free(i->prev);
    guard->val -= 1;
  }
  free(guard->next);  // remove first element of the list

  initGuard(guard);   // remove linking guard to empty sectors in memory
}

void list_merge(Elem* guard1, Elem* guard2) {
    guard2->next->prev = guard1->prev;
    guard2->prev->prev = guard1->prev;
    guard2->prev->next = guard1;

    guard1->prev->next = guard2->next;
    guard1->prev = guard2->prev;

    guard1->val += guard2->val;
    free(guard2);
}

int main() {
  Elem *guard = newElement();
  Elem *guard2 = newElement();
  Elem *tmp;

  printf("Lista nr 1\n");
  initGuard(guard);

  list_add(guard, 11);  
  tmp = list_add(guard, 12);  
  list_add(guard, 13); 

  list_print_all(guard);
  list_delete(guard, tmp);
  list_print_all(guard);

  /** guard 2 **/
  printf("Lista nr 2\n");
  initGuard(guard2);

  list_add(guard2, 21);
  list_add(guard2, 22);
  list_print_all(guard2);

  printf("Scalone listy: \n");
  list_merge(guard, guard2);
  list_print_all(guard);
  
  putchar('\n');
  return 0;
}
