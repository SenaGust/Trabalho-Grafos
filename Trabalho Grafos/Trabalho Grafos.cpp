#include <iostream>
#include <stdlib.h>
#include <list>
#include "Grafo.h"
#include "Controle.h"
#include "Vertice.h"

using namespace std;

void ExibindoTodosAeroportos(Grafo& teste);
Grafo CriandoGrafo();
int Menu();

int main()
{
	Grafo grafo = CriandoGrafo();

	int opcao = Menu(), inicio = 0, qualPeso = 0, fim = Controle::qtdeMaxVertice-1;

	while (opcao != 7)
	{
		switch (opcao)
		{
		case 1:
			//existe caminho de A para B
			ExibindoTodosAeroportos(grafo);

			cout << "\nQual o Aeroporto de origem (de 0 até " << Controle::qtdeMaxVertice-1 << "): ";
			cin >> inicio;
			
			cout << "\nQual o Aeroporto de destino (de 0 até " << Controle::qtdeMaxVertice - 1 << "): ";
			cin >> fim;

			cout << "\n\nResultado: " << endl;

			cout << "Existem " << grafo.buscaLargura(inicio, fim).size() - 2 << " escalas para um voo entre " << grafo.Vertices[inicio].nomeAeroporto  << " e " << grafo.Vertices[fim].nomeAeroporto <<"." << endl;

			break;
		case 2:
			//menor caminho de A para B
			ExibindoTodosAeroportos(grafo);

			cout << "\nQual o Aeroporto de origem (de 0 até " << Controle::qtdeMaxVertice - 1 << "): ";
			cin >> inicio;

			cout << "\nQual o Aeroporto de destino (de 0 até " << Controle::qtdeMaxVertice - 1 << "): ";
			cin >> fim;

			cout << "\nQual filtro sera usado (use 0 para tempo e 1 para custo): ";
			cin >> qualPeso;

			cout << "\n\nResultado: " << endl;
			cout << "Custo Final de " << grafo.Vertices[inicio].nomeAeroporto << " para " << grafo.Vertices[fim].nomeAeroporto << ": " << grafo.menorCaminhoDijkstra(inicio, fim, qualPeso) << endl;

			break;
		case 3:
			//Criando arvore minima
			cout << "\n\nResultado: " << endl;
			cout << "Mostrando Lista Adjascente da Arvore Minima: " << endl;
			grafo.arvoreMinima().ExibirListaGrafo();

			break;
		case 4:

			cout << "\n\nResultado: " << endl;
			grafo.ExibirListaGrafo();

			break;
		case 5:

			cout << "\n\nResultado: " << endl;
			grafo.ExibirMatrizGrafoTempo();
			
			break;
		case 6:

			cout << "\n\nResultado: " << endl;
			grafo.ExibirMatrizGrafoCusto();

			break;
		default:
			cout << "Opção inválida. Tente novamente." << endl;
			break;
		}

		system("PAUSE");
		system("CLS");

		opcao = Menu();
	}
}

int Menu()
{
	int resposta;
	cout << ".:Menu:." << endl;
	cout << "\t1. Quantas escalas existem entre dois voos pre-definidos" << endl;
	cout << "\t2. Qual o melhor caminho entre dois aeroportos" << endl;
	cout << "\t3. Menor caminho que faz a conexão entre todos os aeroportos disponiveis" << endl;
	cout << "\t4. Exibe lista adjascente do grafo principal" << endl;
	cout << "\t5. Exibe matriz de custo baseado em tempo" << endl;
	cout << "\t6. Exibe matriz de custo baseado em valor da passagem" << endl;
	cout << "\t7. Sair" << endl;
	cout << "Escolha a opcao desejada: ";
	cin >> resposta;

	return resposta;
}

void ExibindoTodosAeroportos(Grafo &teste)
{
	cout << ".:Todos os Aeroportos:." << endl;
	for (size_t i = 0; i < Controle::qtdeMaxVertice; i++)
	{
		cout << i << ": " << teste.Vertices[i].nomeAeroporto << endl;
	}
}

Grafo CriandoGrafo()
{
	Grafo auxCriacao;

	auxCriacao.Vertices[0].nomeAeroporto = "A";
	auxCriacao.Vertices[1].nomeAeroporto = "B";
	auxCriacao.Vertices[2].nomeAeroporto = "C";
	auxCriacao.Vertices[3].nomeAeroporto = "D";
	auxCriacao.Vertices[4].nomeAeroporto = "E";
	auxCriacao.Vertices[5].nomeAeroporto = "F";

	int reaisPorTempo = 10;

	auxCriacao.AdicionarAresta(0, 1, 3, 3 * reaisPorTempo);
	auxCriacao.AdicionarAresta(0, 2, 5, 5 * reaisPorTempo);
	auxCriacao.AdicionarAresta(0, 3, 1, 1 * reaisPorTempo);
	auxCriacao.AdicionarAresta(1, 4, 4, 4 * reaisPorTempo);
	auxCriacao.AdicionarAresta(2, 3, 4, 4 * reaisPorTempo);
	auxCriacao.AdicionarAresta(2, 4, 8, 8 * reaisPorTempo);
	auxCriacao.AdicionarAresta(3, 5, 3, 3 * reaisPorTempo);
	auxCriacao.AdicionarAresta(4, 5, 7, 7 * reaisPorTempo);

	return auxCriacao;
}