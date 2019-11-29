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
		1. Todos os v�rtices possuem label auxDijkstra com infinito e Marcar todos como n�o analisados
		2. Origem.auxDijkstra recebe 0
		3. Enquanto o vertice de destino n�o for analisado
			3.1 Selecione o vertice V com menor valor de auxDijkstra
			3.2 Para todos os vizinhos i
				3.2.1 auxSoma = v.auxDijkstra + aresta(V, vizinho[i]);
				3.2.2 se vizinho.auxDijkstra for maior do que auxSoma,
					vizinho.auxDijkstra = auxSoma;
			3.3 Marque Vertice V como analisado
		4. Retorne auxDijkstra do vertice de destino
		*/

		//1
		for (size_t pos = 0; pos < Controle::qtdeMaxVertice; pos++)
		{
			Vertices[pos].auxDijkstra = 10000;
			Vertices[pos].visitado = false;
		}

		//2
		Vertices[verticeOrigem].auxDijkstra = 0;

		//3
		while (!Vertices[VerticeDestino].visitado)
		{
			//3.1
			int V = menorValorDijkstra();

			//3.2
			list <int> ::iterator it;
			for (it = listaAdjascente[V].begin(); it != listaAdjascente[V].end(); it++)
			{
				//3.2.1
				int auxSoma = Vertices[V].auxDijkstra + Matriz[V][*it];

				//3.2.2
				if (Vertices[*it].auxDijkstra > auxSoma)
					Vertices[*it].auxDijkstra = auxSoma;
			}
			//3.3
			Vertices[V].visitado = true;
		}

		//4
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
		Vertice auxMenor;
		int posMenor = -1;
		auxMenor.auxDijkstra = INT16_MAX;

		for (size_t pos = 0; pos < Controle::qtdeMaxVertice; pos++)
		{
			if (auxMenor.auxDijkstra > Vertices[pos].auxDijkstra)
				if (!Vertices[pos].visitado)
				{
					auxMenor = Vertices[pos];
					posMenor = pos;
				}
		}

		return posMenor;
	}
};