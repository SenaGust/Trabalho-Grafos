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

	void AdicionarAresta(int primeiroVertice, int segundoVertice, int pesoDistancia, int pesoCusto)
	{
		if (primeiroVertice != segundoVertice && segundoVertice < Controle::qtdeMaxVertice && primeiroVertice < Controle::qtdeMaxVertice)
		{
			AdicionarArestaMatrizPesoCusto(primeiroVertice, segundoVertice, pesoCusto);
			AdicionarArestaMatrizPesoDistancia(primeiroVertice, segundoVertice, pesoDistancia);
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
	void ExibirMatrizGrafoCusto()
	{
		cout << "Exibindo matriz" << endl;

		//Exibindo matriz
		for (size_t linha = 0; linha < Controle::qtdeMaxVertice; linha++)
		{
			for (size_t coluna = 0; coluna < Controle::qtdeMaxVertice; coluna++)
				cout << MatrizPesoCusto[linha][coluna] << " ";

			cout << "\n";
		}
	}
	void ExibirMatrizGrafoTempo()
	{
		cout << "Exibindo matriz" << endl;

		//Exibindo matriz
		for (size_t linha = 0; linha < Controle::qtdeMaxVertice; linha++)
		{
			for (size_t coluna = 0; coluna < Controle::qtdeMaxVertice; coluna++)
				cout << MatrizPesoTempo[linha][coluna] << " ";

			cout << "\n";
		}
	}

	//Em qualPeso use 0, para tempo; 1, para Custo.
	int menorCaminhoDijkstra(int verticeOrigem, int VerticeDestino, int qualPeso)
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
				int auxSoma = 0;

				//3.2.1
				if (qualPeso == 0)
					auxSoma = Vertices[V].auxDijkstra + MatrizPesoTempo[V][*it];
				else //if(qualPeso == 1)
					auxSoma = Vertices[V].auxDijkstra + MatrizPesoCusto[V][*it];

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
	list<int> buscaLargura(int verticeOrigem, int VerticeDestino)
	{
		/*
		Busca em largura

		1. Cria uma List<int> fila
		2. Cria uma List<int> fila_visitados
		3. Marca todos os v�rtices como n�o visitados
		4. Marca o v�rtice inicial como visitado
		5. Adiciona o vertice inicial na fila
		6. Enquanto a fila n�o estiver vazia e o v�rtice de destino n�o for visitado
			6.1 Tira o vertice inicial da fila
			6.2 Adiciona ele na lista visitados
			6.3 For com o iterator que eu n�o sei como funciona)
				6.3.1 Se o vertice(iterator) n�o estiver visitado
				6.3.1.1 Marca ele como visitado
				6.3.2 Coloca ele na fila
		*/

		//1
		list<int> resultadoBuscaLargura;

		//2
		list<int> listaBusca;

		//3
		for (size_t pos = 0; pos < Controle::qtdeMaxVertice; pos++)
			Vertices[pos].visitado = false;

		//4
		//[verticeOrigem].visitado = true;
		
		//5
		listaBusca.push_back(verticeOrigem);

		//6
		while (!Vertices[VerticeDestino].visitado && !listaBusca.empty())
		{
			//6.1 Retirando primeiro vertice da fila 
			int vertice = listaBusca.front();
			listaBusca.pop_front();

			//6.2
			if (!Vertices[vertice].visitado)
				resultadoBuscaLargura.push_back(vertice);

			Vertices[vertice].visitado = true;

			//Pr� 6.3
			list<int> vizinhos;
			list <int> ::iterator auxIterator;
			for (auxIterator = listaAdjascente[vertice].begin(); auxIterator != listaAdjascente[vertice].end(); auxIterator++)
				vizinhos.push_back(*auxIterator);

			//6.3
			while (!vizinhos.empty())
			{
				if (!Vertices[vizinhos.front()].visitado)
					listaBusca.push_back(vizinhos.front());
				
				vizinhos.pop_front();
			}
		}

		return resultadoBuscaLargura;
	}

private:
	list<int>* listaAdjascente = new list<int>[Controle::qtdeMaxVertice];
	int MatrizPesoTempo[Controle::qtdeMaxVertice][Controle::qtdeMaxVertice];
	int MatrizPesoCusto[Controle::qtdeMaxVertice][Controle::qtdeMaxVertice];

	void AdicionarArestaMatrizPesoCusto(int primeiroVertice, int segundoVertice, int peso)
	{
		MatrizPesoCusto[primeiroVertice][segundoVertice] = peso;
	}
	void AdicionarArestaMatrizPesoDistancia(int primeiroVertice, int segundoVertice, int peso)
	{
		MatrizPesoTempo[primeiroVertice][segundoVertice] = peso;
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