#include <stdio.h>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

int
weight ( int GRAPH[][4], int node, int past[], int past_amount, unordered_map<string, string> *PATH )
{
	if (past_amount > 0){

		int min = 0;
		int w;

		string paststr = "";
		string minpath = "";
		string path = "";

		for (int i = 0; i < past_amount; i++)
		{
			paststr += to_string(past[i]);

			//other past
			string pastpaststr = "";
			int ind = 0;
			int pastpast [past_amount -1];

			for (int j = 0; j < past_amount; j++)
			{
				if (i != j)
				{
					pastpast [ind] = past[j];
					ind++;

					pastpaststr += to_string(past[j]);// + ",";
				}
			}

			w = weight (GRAPH, past[i], pastpast, ind, PATH);
			w += GRAPH[node][past[i]];

			path = (*PATH)[ to_string(past[i]) + pastpaststr];
			//printf ("node:%i path:%s pps:%s\n", past[i], path.c_str(), pastpaststr.c_str());

			if ((w < min) || (min == 0))
			{
				min = w;
				minpath = path;
			}
		}

		//printf ("node: %i past(%i): {%s}  w: %i\n", node, past_amount, txt.c_str(), w);
		//printf ("%s : %s\n", (to_string(node)+paststr).c_str(), (to_string(node) + minpath).c_str());
		(*PATH) [to_string(node)+paststr] = to_string(node) + minpath;

		return min;
	}

	else
	{
		//printf ("node: %i past(%i): w: %i\n\n", node, past_amount, GRAPH[node][0]);
		(*PATH) [to_string(node)] = to_string(node);
		return ( GRAPH[node][0] );
	}
}

int
main ()
{

	//grafo bidireccional
	int GRAPH[4][4] = {{0,10,15,20},
					   {5, 0, 9,10},
					   {6,13, 0,12},
					   {8, 8, 9, 0}};

	unordered_map<string, string> PATH;

	//nodos recorridos
	int past_amount = 3;
	int past[] = {1, 2, 3};

	//calcular
	int w = weight (GRAPH, 0, past, past_amount, &PATH);

	//print graph
	printf("Graph:\n");

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf ("%i, ", GRAPH[i][j]);
		}
		printf("\n");
	}

	//print solution
	string path = "";
	for (char& c : PATH["0123"])
	{
		path.push_back(c);
		path += ", ";
	}

	printf ("\nBest path: %s \n", path.c_str());
	printf ("Distance: %i \n", w);

	return 0;
}
