#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memcpy()

struct node 
{
	char key;
	int value;
	struct node *parent;
	struct node *left;
	struct node *right;
} typedef Elem;

char code[256][8] = {{0}};

Elem* newElement();
int cmpEl(Elem* x, Elem* y);

/**
 * public methods - used in main
 * ************************************************ */

Elem* initLeaf(int key, int frequency)
{
	Elem* node 	= newElement();
	node->key 	= key;
	node->value = frequency;
	node->parent= NULL;
	node->left 	= NULL;
	node->right	= NULL;

	return node;
}

int isLeaf(Elem* node)
{
	return node->left == NULL && node->right == NULL;
}

void treePrintInOrder(Elem* node) 
{
	if (node != NULL)
	{
		treePrintInOrder(node->left);
		printf("%c: %i ", node->key, node->value);
		treePrintInOrder(node->right);
	}
}

void sort(int freqlen, Elem* freq[])
{
	int i, j;
	Elem* tmp;
	for (i = 0; i < freqlen; ++i)
	{
		for (j = 1; j < freqlen-i; ++j)
		{
			if (cmpEl(freq[j-1], freq[j]) > 0)
			{
				tmp = freq[j-1];
				freq[j-1] = freq[j];
				freq[j] = tmp;
			}
		}
	}
}

Elem* huffman(int len, Elem* Query[])
{
	for (int i = 0; i < len-1; ++i)
	{
		Elem* root = newElement();
		root->left = Query[i];
		root->right = Query[i+1];
		root->value = root->right->value + root->left->value;
		root->key = 0;

		Query[i+1] = root;
		sort(len-i, Query+i);
	}
	return Query[len-1];
}

void build_code(Elem* node, char* s, int len)
{
		if (isLeaf(node))
		{
			s[len] = '\0';
			strcpy(code[(int) node->key], s);
			return;
		}

		s[len] = '1'; build_code(node->left, s, len+1);
		s[len] = '0'; build_code(node->right, s, len+1);
}

void printTreeCodes(int ls)
{
	printf("Ilosc znakow alfabetu: %i\n", ls);
	for (int i = 'a'; i <= 'z'; ++i)
	{
		printf("%c: %s\n", i, code[i]);
	}
}

int main(int argc, char const *argv[])
{

	int every_leters[256] = {0};

	char c = 0;
	int i, j, ls = 0;
	while (c != EOF)
	{
		c = getchar();
		every_leters[ (int) c]++;
	}

	for (i = 0; i < 256; i++)
	{
		if (every_leters[i] != 0)
			ls++;
	}

	Elem *letters[ls],
		 *nodes[ls];
	Elem *tree;
	char string[8];

	for (i = 0, j = 0; i < 256 && j < ls; i++)
	{
		if (every_leters[i] != 0)
		{
			letters[j++] = initLeaf(i, every_leters[i]);
		}
	}

	sort(ls, letters);

	memcpy(&nodes, &letters, sizeof(letters));

	tree = huffman(ls, nodes);

	build_code(tree, string, 0);

	printTreeCodes(ls);

	putchar('\n');
	return 0;
}

/**
 * private methods
 * ************************************************ */

Elem* newElement() 
{
	return (Elem*) malloc( sizeof(Elem) );
}

int cmpEl(Elem* x, Elem* y) {
	return x->value - y->value;
}