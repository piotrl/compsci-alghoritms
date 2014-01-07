/**
 * Binary trees implementation 
 * (with switchers to handle repeating values)
 *
 * @spec AL7.5 http://strony.ug.edu.pl/~zylinski/AL7.html
 * @author 	Piotr Lewandowski
 * @site	piotrl.net
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG(var, type) \
  printf(" %i: " #var " == " #type " \n", __LINE__, var)

/**
 * PRIVATE TREE API
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */

struct node 
{
	int key;
	bool needSwitch;
	struct node *parent;
	// sons
	struct node *left;
	struct node *right;
} 
typedef Elem;

Elem* newElement() 
{
	return (Elem*) malloc( sizeof(Elem) );
}

Elem* treeMinimum(Elem* root) {
	while(root->right != NULL)
	{
		root = root->right;
	}

	return root;
}

void transplant(Elem* root, Elem* u, Elem* v)
{	// transplant node V in place of node U
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

/**
 * PUBLIC API
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */
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
	newEl->needSwitch = false;

	Elem* newElSuccesor = NULL;
	Elem* node = Tree;			// first element of Tree is root

	while (node != NULL)
	{	// find place for new element 
		newElSuccesor = node;

		if (node->key == newEl->key)
		{
			node->needSwitch = !node->needSwitch;
			node = (node->needSwitch == true) ? node->left : node-> right;
		} 
		else 
		{
			node = (newEl->key < node->key) ? node->left : node-> right;
		}
	}

	newEl->parent = newElSuccesor;

	if (newEl->key == newElSuccesor->key)
	{
		if (newElSuccesor->needSwitch == true) 
		{
			newElSuccesor->left = newEl;
		} 
		else 
		{
			newElSuccesor->right = newEl;
		}

		newElSuccesor->needSwitch = !newElSuccesor->needSwitch;
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

/**
 * MAIN: TESTING TREES-API PROGRAM
 * * * * * * * * * * * * * * * * * * * * * * * * 
 */

int main(int argc, char const *argv[])
{

	Elem* root = newElement();
	root->key = 100;

	Elem* randomNode;

	treeInsert(root, 4);
	treeInsert(root, 3);
	treeInsert(root, 4);
	treeInsert(root, 8);
	treeInsert(root, 3);

	treePrintInOrder(root);

	randomNode = treeSearch(root, 4);
	treeRemove(root, randomNode);

	putchar('\n');
	treePrintInOrder(root);

	putchar('\n');
	return 0;
}