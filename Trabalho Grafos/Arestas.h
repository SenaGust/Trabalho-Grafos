#pragma once
class Arestas
{
public:
	int vertice1, vertice2, peso;

	Arestas()
	{
		vertice1 = 0;
		vertice2 = 0;
		peso = 0;
	}

	Arestas(int v1, int v2, int peso)
	{
		vertice1 = v1;
		vertice2 = v2;
		this->peso = peso;
	}

	// sobrescrita do operador "<"
	bool operator < (const Arestas& aresta2) const
	{
		return (peso < aresta2.peso);
	}
};

