#include <stdio.h>
#include <unordered_map>
using namespace std;


void
printTree (int  tree[][3],
		   int  size,
		   bool printchar)
{
	for (int i = 0; i < size; i++)
	{
		if (printchar)
		{
			printf ("(%c,"   , tree[i][0]);
	        printf (" %c)"   , tree[i][1]);
		}
		else
		{
			printf ("(%i,"   , tree[i][0]);
	        printf (" %i)"   , tree[i][1]);
		}

        printf (" : %i\n", tree[i][2]);
    }

    printf ("\n");
}


void
qsort (int arr[][3],
       int izq,
       int der)
{
	//indices
    int pivote = izq;
    int i      = izq;
    int j      = der;
    int aux [3];

    //pieces
    while (i < j)
    {
        while ((arr[i][2] <= arr[pivote][2]) && (i < j))
            i++;

        while (arr[pivote][2] < arr[j][2])
            j--;

        //intercambiar
        if (i < j)
        {
            copy (begin(arr[i]), end(arr[i]), begin(aux)   );
            copy (begin(arr[j]), end(arr[j]), begin(arr[i]));
            copy (begin(aux)   , end(aux)   , begin(arr[j]));
        }
    }

    //pivote to j
    copy (begin(arr[pivote]), end(arr[pivote]), begin(aux)        );
    copy (begin(arr[j])     , end(arr[j])     , begin(arr[pivote]));
    copy (begin(aux)        , end(aux)        , begin(arr[j])     );

    //dividir
    if (izq < j-1)
        qsort (arr, izq, j-1);

    if (der > j+1)
        qsort (arr, j+1, der);
}


char
find_root (unordered_map<char, char> *PARENT,
		   char                       node)
{
	if ((*PARENT) [node] == node)
		return node;
	else
		return find_root (PARENT, (*PARENT) [node]);
}


void
kruskal (int  tree[][3],
		 int  size,
		 int  min_tree[][3],
		 int* mt_size)
{

	int  ind;
	char root1;
	char root2;
	unordered_map<char, char> PARENT;

	//make individual joints
	for (int i = 0; i < size; i++)
	{
		PARENT [tree [i][0]] = tree [i][0];
		PARENT [tree [i][1]] = tree [i][1];
	}


	//iterate node paths
	ind = 0;

	for (int i = 0; i < size; i++)
	{
		root1 = find_root (&PARENT, tree [i][0]);
		root2 = find_root (&PARENT, tree [i][1]);

		//detect not joined
		if (root1 == root2)
            continue;

        copy (begin(tree[i]), end(tree[i]), begin(min_tree[ind]));
        ind++;

		//join
		PARENT[root2] = root1;
	}

	//return new size
	*mt_size = ind;
	return;
}

int
main ()
{
	//fill relations (NodeA, NodeB, Distance)
	bool printchar = true;
	const int size = 11;
	int tree [size][3] = {
		{'a','b',2},
		{'a','c',3},
		{'b','d',2},
		{'c','d',1},
		{'d','e',2},
		{'d','f',4},
		{'e','f',1},
		{'e','g',2},
		{'f','g',2},
		{'f','h',1},
		{'g','h',3},
	};

	int min_tree[size][3];
	int* mt_size;


	//print tree
	printf ("Original:\n");
	printTree (tree, size, printchar);

	//sort by distance
	qsort (tree, 0, size - 1);

	//kruskal
	kruskal (tree, size, min_tree, mt_size);

	//now print
	printf ("Minimum Spanning Tree:\n");
	printTree (min_tree, *(mt_size), printchar);

	return 0;
}
