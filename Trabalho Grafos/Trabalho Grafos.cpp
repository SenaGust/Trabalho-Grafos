#include <iostream>
#include <stdlib.h>
#include "Grafo.h"
#include "Controle.h"
#include "Vertice.h"

using namespace std;

int main()
{
	Grafo grafo;

	grafo.AdicionarAresta(1 - 1, 2 - 1, 20);
	grafo.AdicionarAresta(2 - 1, 1 - 1, 2);
	grafo.AdicionarAresta(1 - 1, 3 - 1, 15);
	grafo.AdicionarAresta(3 - 1, 2 - 1, 4);
	grafo.AdicionarAresta(3 - 1, 6 - 1, 10);
	grafo.AdicionarAresta(2 - 1, 6 - 1, 30);
	grafo.AdicionarAresta(2 - 1, 5 - 1, 10);
	grafo.AdicionarAresta(6 - 1, 5 - 1, 10);
	grafo.AdicionarAresta(5 - 1, 4 - 1, 15);
	grafo.AdicionarAresta(6 - 1, 4 - 1, 4);

	grafo.ExibirListaGrafo();
	grafo.ExibirMatrizGrafo();

	cout << "Resultado: " << grafo.menorCaminhoDijkstra(0,4) << endl;
}