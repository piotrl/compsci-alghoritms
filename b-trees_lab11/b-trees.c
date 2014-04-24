#include <stdio.h>

#define T 2  // stopien B-drzewa

#define DEBUG(var, type) \
  printf(" %i: " #var " == " #type " \n", __LINE__, var)

#define DUMP(var) #var


/* -- FIELDS ------------------------------------------------------------------------ */

typedef struct 
{
	short n;            // ilosc kluczy (-1 oznacza wezel usuniety)
	short leaf;         // czy lisc
	int   ownPos;		// position in file
	int   k[2*T-1];     // klucze
	int   c[2*T];       // wskazniki do synow (pozycje w pliku: 0,1,2 ...)
	int   info[2*T-1];  // wskazniki do informacji skojarzonej z kluczem
						// (pozycje w innym pliku); tutaj nie beda uzyte
} Node;

int rozmiarw = sizeof (Node); // rozmiar wezla w bajtach
int __nextFreePos = 0;
FILE *drzewo;  // plik drzewa (zawierajacy wezly)


/* -- PRIVATE METHODS PROTOTYPES ---------------------------------------------------- */

// operacje dyskowe
void zapisz   (int i, Node *w); // zapisuje *w jako i-ty zapis w pliku drzewa
void odczytaj (int i, Node *w); // odczytuje i-ty zapis w pliku drzewa i wpisuje do *w
void usun     (int i);          // usuwa i-ty zapis w pliku drzewa

// operacje na drzewie
void bTreeSplitChild (Node $father, int index);
void bTreeInsertNonFull (Node $x, int k);
void printFields (Node $x, char *name);


/* -- PUBLIC METHODS ---------------------------------------------------------------- */

int budujB (int g, int n) 
{
	// buduje B-drzewo o wysokosci g, w kazdym wezle jest n kluczy
	// wynikiem jest pozycja korzenia w pliku - jest to ostatni 
	// zapis w pliku, co jest wazne dla dalszych zapisow do pliku
	// ktore trzeba robic zaczynajac od kolejnej pozycji

	static int klucz = 0;   // kolejny klucz
	static int pozycja = 0; // wolna pozycja w pliku
	Node w;
	int i;

	w.n = n;

	if (g == 0) // lisc
	{  
		for (i = 0; i < n; i++) 
		{
			w.c[i] = -1; // w lisc
			w.k[i] = klucz++;
		}

		w.c[n] = -1;
		w.leaf = 1;
	}
	else // Node wewnetrzny
	{  
		for (i = 0; i < n; i++)
		{
			w.c[i] = budujB (g - 1, n);
			w.k[i] = klucz++;
		}

		w.c[n] = budujB (g - 1, n);
		w.leaf = 0;
	}

	zapisz (pozycja++, &w);

	return pozycja-1;
}


/* ---------------------------------------------------------------------------------- */

void drukujB (int root, int p) 
{
	// drukuje B-drzewo o korzeniu root (pozycja w pliku)
	// wydruk przesuniety o p w prawo

	Node w;
	int i, j;
	
	odczytaj (root, &w);

	if (w.leaf) 
	{
		for (i = 0; i < p; i++)
			printf (" ");

		for (i = 0; i < w.n; i++)
			printf ("%d ",w.k[i]);
		
		printf ("\n");
	}
	else 
	{
		drukujB (w.c[w.n], p + 4);	// last key in node

		for (i = w.n - 1; i >= 0; i--) 
		{
			for (j = 0; j < p; j++)
				printf (" ");		// shift in right
			
			printf ("%d\n", w.k[i]);
			drukujB (w.c[i], p + 4);
		}
	}
}


/* ---------------------------------------------------------------------------------- */

int bTreeSearch (int root, int key)
{
	Node node;
	int i = 0;
	
	odczytaj (root, &node);

	while (i < node.n && key > node.k[i])
	{
		i++;
	}

	if (i < node.n && key == node.k[i])
	{
		return root;
	}
	
	if (node.leaf)
	{
		return -1;
	}
	else
	{
		return bTreeSearch(node.c[i], key);
	}
}


/* ----------------------------------------------------------------------------------- */

void bTreeInsert(int *rPos, int k)
{
	Node root;
	odczytaj (*rPos, &root);

	if (root.n == 2 * T - 1)
	{	// Node is full, we have to reorganize structure
		Node s;

		s.leaf = 0;
		s.n = 0;
		s.ownPos = __nextFreePos++;
		s.c[0] = root.ownPos;
		*rPos = s.ownPos;

		bTreeSplitChild (s, 0);
		bTreeInsertNonFull (s, k);
	}
	else
	{	// node is not full, so we just add next element to it
		bTreeInsertNonFull (root, k);
	}
}

int initBTree()
{
	Node root;
	root.n = 0;
	root.leaf = 1;
	root.ownPos = __nextFreePos++;

	for (int i = 0; i < 2*T; i++) 
	{
		root.c[i] = -1; // w lisc
	}

	zapisz(root.ownPos, &root);

	return root.ownPos;
}

/* -- MAIN --------------------------------------------------------------------------- */

int main ()
{
	int *root, root_val;
	int find = 3;

	drzewo = fopen ("bdrzewo", "w+");
	root_val = initBTree();
	root = &root_val;

	bTreeInsert(root, 5);
	bTreeInsert(root, 9);
	bTreeInsert(root, 3);
	bTreeInsert(root, 7);
	bTreeInsert(root, 1);
	bTreeInsert(root, 2);
	bTreeInsert(root, 8);
	bTreeInsert(root, 6);
	bTreeInsert(root, 10);
	bTreeInsert(root, 11);
	bTreeInsert(root, 12);
	bTreeInsert(root, 13);
	bTreeInsert(root, 14);
	bTreeInsert(root, 16);
	bTreeInsert(root, 17);

	int n = bTreeSearch(*root, find);
	
	if (n != -1)
	{
		printf (" Znaleziono %i w wezle nr %i\n", find, n);
		drukujB (n, 2);
	}
	else
	{
		printf(" Nie odnaleziono klucza: %i. \n", find);
	}

	drukujB (*root, 0);

	printf("\n T = %i\n Max rozmiar wezla: %i\n Min rozmiar wezla: %i", T, 2 * T - 1, T - 1);

	fclose (drzewo);
	putchar('\n');
	return 0;
}


/* -- PRIVATE METHODS ---------------------------------------------------------------- */

void bTreeSplitChild (Node $father, int index)
{
	Node $new; 	// x - father of y, [not full]
	Node $son;
	odczytaj($father.c[index], &$son);		  	// y - full son of x; y = x.c[index];
			  	// $new - new additional node, next son of $father

	$new.leaf = $son.leaf; // create sibling in the same node
	$new.n = T - 1;
	$new.ownPos = __nextFreePos++;

	for (int i = 0; i < T - 1; ++i)
	{
		$new.k[i] = $son.k[i];	// copy right half side of full node
		$son.k[i] = $son.k[i+T];
	}


	for (int i = 0; i < T; ++i)
	{
		$new.c[i] = $son.c[i];
		$son.c[i] = $son.c[i+T];
	}

	// split $son
	$son.n = T - 1;

	// make space for $new pointer
	for (int i = $father.n; i >= index; --i) // buggy--
	{
		$father.c[i + 1] = $father.c[i];
	}

	$father.c[index] = $new.ownPos;
	for (int i = $father.n; i > index; --i)
	{
		$father.k[i + 1] = $father.k[i];
	}

	$father.k[index] = $son.k[T-1];
	$father.n++;

	zapisz ($son.ownPos, &$son);
	zapisz ($new.ownPos, &$new);
	zapisz ($father.ownPos, &$father);
}


/* ----------------------------------------------------------------------------------- */

void bTreeInsertNonFull (Node $x, int k)
{
	int i = $x.n-1;

	if ($x.leaf)
	{
		while (i >= 0 && k < $x.k[i])
		{
			$x.k[i + 1] = $x.k[i];
			i--;
		}

		$x.k[i + 1] = k;
		$x.n++;
		zapisz ($x.ownPos, &$x);
	}
	else
	{

		while (i >= 0 && k < $x.k[i])
		{
			i--;
		}
		
		i++;
		Node $tmp;
		odczytaj($x.c[i], &$tmp);

		if ($tmp.n == 2 * T - 1)
		{
			bTreeSplitChild($x, i);
			if (k > $x.k[i-1])
			{
				odczytaj($x.c[i], &$tmp);
			}
		}

		bTreeInsertNonFull($tmp, k);
	}
}


/* ----------------------------------------------------------------------------------- */

void printFields(Node $x, char *name)
{
	printf("-------------------------------------\n");
 	printf(" %s: n = %i, isLeaf = %i, ownPos = %i \n c = [", name, $x.n, $x.leaf, $x.ownPos);
	
	for (int i = 0; i <= $x.n; ++i)
	{
		printf("%i, ", $x.c[i]);
	}
	
	printf("];\n k = [");

	for (int i = 0; i < $x.n; ++i)
	{
		printf("%i, ", $x.k[i]);	
	}
	printf("];\n");
	printf("-------------------------------------\n");
}


/* ----------------------------------------------------------------------------------- */


void zapisz (int i, Node *w) 
{
	// zapisuje *w jako i-ty zapis w pliku drzewa

	fseek (drzewo, (long) i * rozmiarw, SEEK_SET);
	fwrite (w, rozmiarw, 1, drzewo);
	//  printf("z%d ",i);
}


/* ---------------------------------------------------------------------------------- */

void odczytaj (int i, Node *w) 
{
	// odczytuje i-ty zapis w pliku drzewa i wpisuje do *w

	fseek (drzewo, (long) i * rozmiarw, SEEK_SET);
	fread (w, rozmiarw, 1, drzewo);
	//  printf("o%d ",i);
}


/* ---------------------------------------------------------------------------------- */

void usun (int i) 
{
	// usuwa i-ty zapis w pliku drzewa
	// w tej wersji nie wykorzystujemy usunietych pozycji,
	// tylko zaznaczamy jako usuniete

	Node w;

	odczytaj (i,&w);
	w.n = -1;
	zapisz (i,&w);
}