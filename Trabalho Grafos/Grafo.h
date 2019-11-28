#pragma once


#include <iostream>
#include <list>
#include< stdlib.h>
#include "Controle.h"


using namespace std;

class Grafo
{
public:
	Vertice Vertices[Controle::qtdeMaxVertice];

	void AdicionarAresta(int primeiroVertice, int segundoVertice, int peso)
	{
		if (primeiroVertice != segundoVertice && segundoVertice < Controle::qtdeMaxVertice && primeiroVertice < Controle::qtdeMaxVertice)
		{
			AdicionarArestaMatriz(primeiroVertice, segundoVertice, peso);
			AdicionarArestaListaAdjascente(primeiroVertice, segundoVertice);
		}
	}
	void ExibirListaGrafo()
	{
		cout << "Exibindo as listas adjacentes" << endl;
		for (size_t i = 0; i < Controle::qtdeMaxVertice; i++)
		{
			list <int> ::iterator it;
			cout << i;

			for (it = listaAdjascente[i].begin(); it != listaAdjascente[i].end(); it++)
				cout << " -> " << *it;
			cout << endl;
		}
	}
	void ExibirMatrizGrafo()
	{
		cout << "Exibindo matriz" << endl;

		//Exibindo matriz
		for (size_t linha = 0; linha < Controle::qtdeMaxVertice; linha++)
		{
			for (size_t coluna = 0; coluna < Controle::qtdeMaxVertice; coluna++)
				cout << Matriz[linha][coluna] << " ";

			cout << "\n";
		}
	}

	//Gustavo e Lorena
	int menorCaminhoDijkstra(int verticeOrigem, int VerticeDestino)
	{
		/*
		1. Todos os vértices possuem label auxDijkstra com infinito e Marcar todos como não analisados
		2. Origem.auxDijkstra recebe 0
		3. Enquanto o vertice de destino não for analisado
			3.0 Selecione o vertice V com menor valor de auxDijkstra
			3.1 Para todos os vizinhos i
				3.1.1 auxSoma = v.auxDijkstra + aresta(V, vizinho[i]);
				3.1.2 se vizinho.auxDijkstra for maior do que auxSoma,
					vizinho.auxDijkstra = auxSoma;
			3.2 Marque Vertice V como analisado
		4. Retorne auxDijkstra do vertice de destino
		*/

		for (size_t pos = 0; pos < Controle::qtdeMaxVertice; pos++)
		{
			Vertices[pos].auxDijkstra = 10000;
			Vertices[pos].visitado = false;
		}

		Vertices[verticeOrigem].auxDijkstra = 0;

		while (!Vertices[VerticeDestino].visitado)
		{
			int V = menorValorDijkstra();

			list <int> ::iterator it;
			for (it = listaAdjascente[V].begin(); it != listaAdjascente[V].end(); it++)
			{
				int auxSoma = Vertices[V].auxDijkstra + Matriz[V][*it];

				if (Vertices[*it].auxDijkstra > auxSoma)
					Vertices[*it].auxDijkstra = auxSoma;
			}
			Vertices[V].visitado = true;
			cout << "Acabou de ser analizado: " << V << endl;
		}

		return (Vertices[VerticeDestino].auxDijkstra);
	}

private:
	list<int>* listaAdjascente = new list<int>[Controle::qtdeMaxVertice];
	int Matriz[Controle::qtdeMaxVertice][Controle::qtdeMaxVertice];

	void AdicionarArestaMatriz(int primeiroVertice, int segundoVertice, int peso)
	{
		Matriz[primeiroVertice][segundoVertice] = peso;
	}
	void AdicionarArestaListaAdjascente(int primeiroVertice, int segundoVertice)
	{
		listaAdjascente[primeiroVertice].push_back(segundoVertice);
	}

	//Gustavo e Lorena
	int menorValorDijkstra()
	{
		int menor = INT_MAX;

		for (size_t pos = 1; pos < Controle::qtdeMaxVertice; pos++)
		{
			if (menor > Vertices[pos].auxDijkstra)
					menor = pos;
		}

		cout << "menor" << menor;
		return menor;
	}
};

