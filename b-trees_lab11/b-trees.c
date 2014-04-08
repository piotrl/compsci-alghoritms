// struktura wezla B-drzewa i przyklad zapisu i odczytu na plik
// budowanie B-drzewa o zadanej wysokosci i drukowanie w dwoch
// wersjch tekstowo i graficznie
//                                     pmp@inf.ug.edu.pl 2007, 2013

#include <stdio.h>
#define T 3   // stopien B-drzewa

typedef struct 
{
	short n;            //ilosc kluczy (-1 oznacza wezel usuniety)
	short leaf;         // czy lisc
	int   k[2*T-1];     // klucze
	int   c[2*T];       // wskazniki do synow (pozycje w pliku: 0,1,2 ...)
	int   info[2*T-1];  // wskazniki do informacji skojarzonej z kluczem
						// (pozycje w innym pliku); tutaj nie beda uzyte
} Node;

int rozmiarw = sizeof (Node); // rozmiar wezla w bajtach
FILE *drzewo;  // plik drzewa (zawierajacy wezly)


/* -- PRIVATE METHODS --------------------------------------------------------------- */

void zapisz   (int i, Node *w); // zapisuje *w jako i-ty zapis w pliku drzewa
void odczytaj (int i, Node *w); // odczytuje i-ty zapis w pliku drzewa i wpisuje do *w
void usun     (int i);          // usuwa i-ty zapis w pliku drzewa


/* -- PUBLIC METHODS ---------------------------------------------------------------- */

int budujB (int g, int n) 
{
	// buduje B-drzewo o wysokosci g, w kazdym wezle jest n kluczy
	// wynikiem jest pozycja korzenia w pliku - jest to ostatni 
	// zapis w pliku, co jest wazne dla dalszych zapisow do pliku
	// ktore trzeba robic zaczynajac od kolejnej pozycji

	static int klucz = 0; 	// kolejny klucz
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

void drukujB (int r, int p) 
{
	// drukuje B-drzewo o korzeniu r (pozycja w pliku)
	// wydruk przesuniety o p w prawo

	Node w;
	int i, j;
	
	odczytaj (r, &w);

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
		drukujB (w.c[w.n], p + 4);

		for (i = w.n - 1; i >= 0; i--) 
		{
			for (j = 0; j < p; j++)
				printf (" ");
			
			printf ("%d\n", w.k[i]);
			drukujB (w.c[i], p + 4);
		}
	}
}


/* -- MAIN --------------------------------------------------------------------------- */

int main ()
{
	int root;

	drzewo = fopen ("bdrzewo", "w+");
	root = budujB (2, 2);

	printf ("\n");
	drukujB (root, 0);
	fclose (drzewo);

	putchar('\n');
	return 0;
}


/* -- PRIVATE METHODS ---------------------------------------------------------------- */

void zapisz (int i,Node *w) 
{
	// zapisuje *w jako i-ty zapis w pliku drzewa

	fseek (drzewo, (long) i * rozmiarw, SEEK_SET);
	fwrite (w, rozmiarw, 1, drzewo);
	//  printf("z%d ",i);
}


/* ---------------------------------------------------------------------------------- */

void odczytaj (int i,Node *w) 
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
