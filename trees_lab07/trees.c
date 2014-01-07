#include <stdio.h>
#include <stdlib.h>

/**
 * @author Piotr Lewandowski
 * @spec http://strony.ug.edu.pl/~zylinski/AL7.html
 * @desc Binary trees implementation
 */

// private
struct node 
{
	int key;
	struct node *parent;
	struct node *left;
	struct node *right;
} 
typedef Elem;

// private
Elem* newElement() 
{
	return (Elem*) malloc( sizeof(Elem) );
}

// private
Elem* treeMinimum(Elem* root) {
	while(root->right != NULL)
	{
		root = root->right;
	}

	return root;
}

// private
void transplant(Elem* root, Elem* u, Elem* v)
{
	if (u->parent == NULL)
	{
		root = v;
	}
	else if (u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}

	if (v != NULL)
	{
		v->parent = u->parent;
	}
}

void treePrintInOrder(Elem* node) 
{
	if (node != NULL)
	{
		treePrintInOrder(node->left);
		printf("%i ", node->key);
		treePrintInOrder(node->right);
	}
}

Elem* treeSearch(Elem* node, int value) 
{
	if (node == NULL || value == node->key)
	{
		return node;
	}
	else if (value < node->key)
	{
		return treeSearch(node->left, value);
	}
	else
	{
		return treeSearch(node->right, value);
	}
}

Elem* treeInsert(Elem* Tree, int value) 
{
	Elem* newEl = newElement();
	newEl->key = value;

	Elem* newElSuccesor = NULL;
	Elem* node = Tree;		// first element of Tree is root

	while (node != NULL)
	{	// find place for new element 
		newElSuccesor = node;
		node = (newEl->key < node->key) ? node->left : node-> right;
	}

	newEl->parent = newElSuccesor;

	if (newElSuccesor == NULL)
	{
		Tree = newEl;	// Tree is empty
	} 
	else if (newEl->key < newElSuccesor->key)
	{
		newElSuccesor->left = newEl;
	}
	else
	{
		newElSuccesor->right = newEl;
	}

	return newEl;
}

void treeRemove(Elem* root, Elem* node) 
{
	if (node->left == NULL)
	{
		transplant(root, node, node->right);
	}
	else if (node->right == NULL)
	{
		transplant(root, node, node->left);
	}
	else
	{
		Elem* y = treeMinimum(node->right);
		if (y->parent != node)
		{
			transplant(root, y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}

		transplant(root, node, y);
		y->left = node->left;
		y->left->parent = y;
	}
}

int main(int argc, char const *argv[])
{
	Elem* root = newElement();
	Elem* randomNode;

	treeInsert(root, 4);
	treeInsert(root, 2);
	treeInsert(root, 5);
	randomNode = treeInsert(root, 9);

	treePrintInOrder(root);

	treeRemove(root, randomNode);

	putchar('\n');
	treePrintInOrder(root);

	putchar('\n');
	return 0;
}