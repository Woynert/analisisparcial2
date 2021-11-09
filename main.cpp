#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <math.h>
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


void
knapsack (int arr[], int capacity, int item[], int amount, uint16_t applied[])
{
	int auxarr [capacity+1];
	uint16_t auxapplied [capacity+1];
	arr[0] = 0;

	for (int j = 0; j < amount; j++) //items
	{
		for (int i = 0; i <= capacity; i++) //capacity 0 - 700
		{

			//fill first values
			if (j == 0){
				if (item[j] > i){
					arr[i] = 0;
				}
				else{
					arr[i] = item[j];
					applied[i] = ((int) pow(2, j));
				}
			}

			else{
				if (item[j] <= i)
				{
					//get max
					int w1 = item[j] + auxarr[i - item[j]];
					int w2 = arr[i];

					if (w1 >= w2){
						arr[i] = w1;
						applied[i] = ((int)pow(2, j)) + auxapplied[i - item[j]];
					}
				}
			}
		}

		//record previous state
		for (int i = 0; i <= capacity; i++){
			auxarr[i] = arr[i];
			auxapplied[i] = applied[i];
		}
	}
}

int
main ()
{

	//capacity
	int capacity = 700;
	int arr     [capacity+1];
	uint16_t applied [capacity+1] = {0};

	//available items
	int amount = 10;
	int item [amount] = {100, 155, 50, 112, 70, 80, 60, 118, 110 ,55};

	//sort items
	qsort (item, 0, amount-1);
	printf("Items:\n");
	for (int i = 0; i < amount; i++)
	{
		printf ("%i, ", item[i]);
	}


	//dynamic algorithm
	knapsack (arr, capacity, item, amount, applied);


	//list picked items
	printf("\n\nPicked Items:\n");

	int sum = 0;
	int testingbit = 0;
	uint16_t picked = applied[capacity];

	while (testingbit < amount)
	{

		if (picked & 0x01){
			printf("%i, ", item[testingbit]);
			sum += item[testingbit];
		}

		testingbit++;
		picked = picked >> 1;
	}

	printf("\n\nSumatory: %i\n", sum);

	return 0;
}
