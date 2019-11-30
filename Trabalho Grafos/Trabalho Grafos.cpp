#include <iostream>
#include <stdlib.h>
#include <list>
#include "Grafo.h"
#include "Controle.h"
#include "Vertice.h"

using namespace std;

int main()
{
	Grafo grafo;

	grafo.AdicionarAresta(1 - 1, 2 - 1, 20, 20);
	grafo.AdicionarAresta(2 - 1, 1 - 1, 2, 2);
	grafo.AdicionarAresta(1 - 1, 3 - 1, 15, 15);
	grafo.AdicionarAresta(3 - 1, 2 - 1, 4, 4);
	grafo.AdicionarAresta(3 - 1, 6 - 1, 10, 10);
	grafo.AdicionarAresta(2 - 1, 6 - 1, 30, 30);
	grafo.AdicionarAresta(2 - 1, 5 - 1, 10, 10);
	grafo.AdicionarAresta(6 - 1, 5 - 1, 10, 10);
	grafo.AdicionarAresta(5 - 1, 4 - 1, 15, 15);
	grafo.AdicionarAresta(6 - 1, 4 - 1, 4, 4);

	grafo.ExibirListaGrafo();
	//grafo.ExibirMatrizGrafoCusto();
	//grafo.ExibirMatrizGrafoTempo();

	int origem = 0;
	int fim = 2;

	//Resultado Busca em Largura
	cout << "\n\nBusca em Largura: " << endl;
	list<int> auxImpressao = grafo.buscaLargura(origem, fim);
	list<int> ::iterator it;

	for (it = auxImpressao.begin(); it != auxImpressao.end(); it++)
		cout  << " -> " << *it;
	cout << endl;

	//Resultado Menor Caminho
	cout << "\n\nMenor Caminho Dijkstra: " << endl;
	cout << grafo.menorCaminhoDijkstra(origem, fim, 0) << endl;

	//Resultado arvore Minima
	grafo.arvoreMinima();
}