#include <stdio.h>
#include <vector>
using namespace std;

void
qsort (int arr[],
       int izq,
       int der)
{
    //indices
    int pivote = izq;
    int i      = izq;
    int j      = der;
    int aux;

    //pieces
    while (i < j)
    {
        while ((arr[i] <= arr[pivote]) && (i < j))
            i++;

        while (arr[pivote] < arr[j])
            j--;

        //intercambiar
        if (i < j)
        {
            aux    = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
        }
    }

    //pivote to j
    aux         = arr[pivote];
    arr[pivote] = arr[j];
    arr[j]      = aux;

    //dividir
    if (izq < j-1)
        qsort (arr, izq, j-1);

    if (der > j+1)
        qsort (arr, j+1, der);
}


int
main ()
{
	int capacity = 700;
	int amount = 10;
	int item[amount] = {100, 155, 50, 112, 70, 80, 60, 118, 110 ,55};

	//sort items
	qsort(item, 0, amount-1);

	for (int i = 0; i < amount; i++)
	{
		printf ("%i, ", item[i]);
	}

	return 0;
}
