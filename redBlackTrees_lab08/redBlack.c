/**
 * Red-Black Binary trees implementation 
 * (Adding new element to the tree)
 *
 * @spec 	AL8.3 https://strony.ug.edu.pl/~zylinski/AL8.html
 * @author 	Piotr Lewandowski
 * @site	piotrl.net
 */

#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

#define DEBUG(var, type) \
  printf(" %i: " #var " == " #type " \n", __LINE__, var)

#define SZER_EKR 80  /* szerokosc ekranu */
#define IL_POZ   5   /* ilosc poziomow drzewa, ktore be */

/**
 * TREE STRUCTURE
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */

struct node 
{
	int key;
	int color;
	struct node *parent;
	// sons
	struct node *left;
	struct node *right;
} 
typedef Elem;

//	Main tree fields

Elem* nil;
Elem* root;

Elem* newElement() 
{
	return (Elem*) malloc( sizeof(Elem) );
}

void init()
{
	nil = newElement();
	nil->key = 0;
	nil->color = BLACK;
	nil->parent = NULL;
	nil->left = NULL;
	nil->right = NULL;
	root = nil;
}

 /**
  * Testing functions
  * * * * * * * * * * * * * * * * * * * * * * * * 
  */

char wydruk[IL_POZ+1][SZER_EKR];

 void drukujost(Elem* w, int l, int p, int poziom){
             int srodek = (l+p)/2;
             if (w==nil)   return; 
             wydruk[poziom][srodek]='*';
}

void drukujwew(Elem* w, int l, int p, int poziom){
             int srodek = (l+p)/2;
             int i,dl;
             char s[19];
             if (w==nil)    return;
             if (w->color==BLACK)
                 dl=sprintf(s,"%d",w->key);
             else
             dl=sprintf(s,"%+d",w->key);
             for (i=0;i<dl;i++)
                 wydruk[poziom][srodek-dl/2+i]=s[i];
             if (++poziom<IL_POZ){
                 drukujwew(w->left,l,srodek,poziom) ;
                 drukujwew(w->right,srodek+1,p,poziom) ;
             }
             else {
                 drukujost(w->left,l,srodek,poziom) ;
                 drukujost(w->right,srodek+1,p,poziom) ;
             }
}

/* funkcja drukujaca drzewo binarne na ekranie (tutaj tylko deklaracja) */
/* funkcja drukuje drzewo o korzeniu "w"                                */

void rbPrint(Elem* w) {
    int j,i;
    for (i=0;i<=IL_POZ;i++)
        for (j=0;j<SZER_EKR;j++)
            wydruk[i][j] = ' ';
    drukujwew(w,0,SZER_EKR,0);
    for (i=0;i<=IL_POZ;i++){
            for (j=0;j<SZER_EKR;j++)
                putchar(wydruk[i][j]);
            printf("\n");
    }
}

/**
 * Red-Black tree API
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */

void leftRotate(Elem* x) 
{
	Elem* y = x->right;
	x->right = y->left;

	if (y->left != nil)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;

	if(x->parent == nil) {
		root = y;
	}
	else
	{
		if (x == x->parent->left)
		{
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}		
	}

	y->left = x;
	x->parent = y;
}

void rightRotate(Elem* y)
{
	Elem* x = y->left;
	y->left = x->right;

	if (x->right != nil)
	{
		x->right->parent = y;		
	}

	x->parent = y->parent;

	if(y->parent == nil) {
		root = x;
	}
	else
	{
		if (y == y->parent->left)
		{
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}
	}

	x->right = y;
	y->parent = x;
}

void rbInsertFixup(Elem* focusedEl)
{
	Elem* subtree;

	while (focusedEl != root && focusedEl->parent->color == RED)
	{

		if (focusedEl->parent == focusedEl->parent->parent->left)
		{
			subtree = focusedEl->parent->parent->right;

			if (subtree->color == RED)
			{
				focusedEl->parent->color = BLACK;
				subtree->color = BLACK;
				focusedEl->parent->parent->color = RED;

				focusedEl = focusedEl->parent->parent;
			}
			else 
			{
				if (focusedEl == focusedEl->parent->right) 
				{
					focusedEl = focusedEl->parent;
					leftRotate(focusedEl);					
				}

				focusedEl->parent->color = BLACK;
				focusedEl->parent->parent->color = RED;
				rightRotate(focusedEl->parent->parent);
			}
		}
		else
		{
			subtree = focusedEl->parent->parent->left;

			if (subtree->color == RED)
			{
				focusedEl->parent->color = BLACK;
				subtree->color = BLACK;
				focusedEl->parent->parent->color = RED;

				focusedEl = focusedEl->parent->parent;
			}
			else 
			{

				if (focusedEl == focusedEl->parent->left) 
				{
					focusedEl = focusedEl->parent;
					rightRotate(focusedEl);					
				}

				focusedEl->parent->color = BLACK;
				focusedEl->parent->parent->color = RED;
				leftRotate(focusedEl->parent->parent);
			}
		}
	}

	root->color = BLACK;
}

Elem* rbInsert(int value)
{

	Elem* newEl  = newElement();
	newEl->key   = value;
	newEl->left  = nil;
	newEl->right = nil;
	newEl->color = RED;

	Elem* tmp 	 = nil;
	Elem* x		 = root;

	while (x != nil)
	{
		tmp = x;

		if (newEl->key < x->key)
		{
			x = x->left;
		}
		else 
		{
			x = x->right;
		}
	}

	newEl->parent = tmp;

	if (tmp == nil)
	{
		root = newEl;
	}
	else if (newEl->key < newEl->parent->key)
	{
		newEl->parent->left = newEl;
	}
	else 
	{
		newEl->parent->right = newEl;
	}
	
	rbInsertFixup(newEl);

	return newEl;
}

void tree_min_max_path(Elem* elem, int* min, int* max, int* redNodes, int actual_length)
{
	if ( elem != nil )
	{
		actual_length++;
		if (elem->color == RED) (*redNodes)++;

		tree_min_max_path(elem->left, min, max, redNodes, actual_length);
		tree_min_max_path(elem->right, min, max, redNodes, actual_length);
	}
	else
	{
		if (actual_length > *max) *max = actual_length;
		if (actual_length < *min || *min == 0) *min = actual_length;
	}
}

int main(int argc, char const *argv[])
{
	int min_path_length, max_path_lenght, redNodes;

	min_path_length = 
	max_path_lenght = 
	redNodes 		= 0;

	init();

	rbInsert(38);
	rbInsert(31);
	rbInsert(22);
	rbInsert(8);
	rbInsert(20);
	rbInsert(5);
	rbInsert(10);
	rbInsert(9);
	rbInsert(21);
	rbInsert(27);
	rbInsert(29);
	rbInsert(25);
	rbInsert(28);

	rbPrint(root);

	tree_min_max_path(root, &min_path_length, &max_path_lenght, &redNodes, 0);

	printf(" Minimal path length:%i \n Maximal path length: %i \n Red nodes in tree: %i \n ", 
		min_path_length, max_path_lenght, redNodes);
	
	putchar('\n');
	return 0;
}