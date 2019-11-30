#pragma once
#include <iostream>
#include <list>
#include< stdlib.h>
#include "Controle.h"
#include "Arestas.h"
#include <algorithm>

using namespace std;

class Grafo
{
public:
	Vertice Vertices[Controle::qtdeMaxVertice];

	void AdicionarAresta(int primeiroVertice, int segundoVertice, int pesoDistancia, int pesoCusto)
	{
		//Verificamos se os valores est�o corretos
		if (primeiroVertice != segundoVertice && segundoVertice < Controle::qtdeMaxVertice && primeiroVertice < Controle::qtdeMaxVertice)
		{
			//Como o grafo � n�o-direcionado, inserimos em ambas as dire��es
			AdicionarArestaMatrizPesoCusto(primeiroVertice, segundoVertice, pesoCusto);
			AdicionarArestaMatrizPesoDistancia(primeiroVertice, segundoVertice, pesoDistancia);
			AdicionarArestaListaAdjascente(primeiroVertice, segundoVertice);

			AdicionarArestaMatrizPesoCusto(segundoVertice, primeiroVertice, pesoCusto);
			AdicionarArestaMatrizPesoDistancia(segundoVertice, primeiroVertice, pesoDistancia);
			AdicionarArestaListaAdjascente(segundoVertice, primeiroVertice);
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
		1. Criamos lista chamada resultadoBuscaLargura
		2. Criamos outra lista chamada listaBusca usada na busca em largura
		3. Marcamos todos os v�rtices como n�o visitados
		4. Inserimos a origem na listaBusca
		5. Enquanto o destino n�o for visitado ou a listaBusca n�o estiver vazia
			5.1 Retiramos o primeiro v�rtice V
			5.2 Se V n�o foi visitado, marcamos como visitado 
			5.3 inserimos na lista resultadoBuscaLargura
			5.4 Criamos uma lista vizinhos contendo todos os vizinhos de V
			5.5 Enquanto existir vizinhos de V
				5.5.1 Retiramos o vizinho W
				5.5.2 Se o vizinho W n�o for visitado, inserimos na listaBusca
		6. Se o destino n�o for encontrado, retornamos a lista vazia para mostrar que n�o � poss�vel chegar no local
		*/

		//1
		list<int> resultadoBuscaLargura;

		//2
		list<int> listaBusca;

		//3
		for (size_t pos = 0; pos < Controle::qtdeMaxVertice; pos++)
			Vertices[pos].visitado = false;

		//4
		listaBusca.push_back(verticeOrigem);

		//5
		while (!Vertices[VerticeDestino].visitado && !listaBusca.empty())
		{
			//5.1
			int vertice = listaBusca.front();
			listaBusca.pop_front();

			//5.2
			if (!Vertices[vertice].visitado)
				resultadoBuscaLargura.push_back(vertice);
			//5.3
			Vertices[vertice].visitado = true;

			//5.4
			list<int> vizinhos;
			list <int> ::iterator auxIterator;
			for (auxIterator = listaAdjascente[vertice].begin(); auxIterator != listaAdjascente[vertice].end(); auxIterator++)
				vizinhos.push_back(*auxIterator);

			//5.5
			while (!vizinhos.empty())
			{
				//A ordem foi invertida por causa da linguagem
				//5.5.2
				if (!Vertices[vizinhos.front()].visitado)
					listaBusca.push_back(vizinhos.front());
				
				//5.5.1
				vizinhos.pop_front();
			}
		}

		//6.
		if (!Vertices[VerticeDestino].visitado)
			resultadoBuscaLargura.clear();

		//7. 
		return resultadoBuscaLargura;
	}
	
	Grafo arvoreMinima()
	{
		/*
		1. Criando subgrafo com todas as arestas
		2. Ordenando todas as arestas  de forma n�o decrescente
		3. Enquanto n�o incluirmos (|v| - 1) v�rtices
			3.1 Retiramos a primeira aresta
			3.2 Verificamos se os dois v�rtices fazem parte do mesmo grupo conexo utilizando busca em largura
			3.3 Se n�o encontrarmos na busca em largura, inserimos essa aresta no subgrafo
		4. Retornamos o subgrafo criado
		*/

		//1.
		Grafo arvoreMinima;
		
		//2.
		list<Arestas> todasArestas;

		for (int coluna = 0; coluna < Controle::qtdeMaxVertice; coluna++)
			for (int linha = 0; linha < Controle::qtdeMaxVertice; linha++)
				if (MatrizPesoTempo[linha][coluna] > 0)
				{
					Arestas aux(linha, coluna, MatrizPesoTempo[linha][coluna]);
					todasArestas.push_back(aux);
				}

		todasArestas.sort();

		//3.
		int nIncluidos = 0;
		while (nIncluidos < Controle::qtdeMaxVertice - 1)
		{
			//3.1
			Arestas aux = todasArestas.front();
			todasArestas.pop_front();

			//3.2
			list<int> auxBusca = arvoreMinima.buscaLargura(aux.vertice1, aux.vertice2);

			//3.3
			if(auxBusca.size() == 0) //se n�o encontrou na busca em lagura
			{
				arvoreMinima.AdicionarAresta(aux.vertice1, aux.vertice2, aux.peso, 0);
				nIncluidos++;
			}
		}

		//4.
		return arvoreMinima;
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