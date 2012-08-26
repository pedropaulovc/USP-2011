/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * GrafoPalavras definidos no arquivo GrafoPalavras.h.
 */

#include <iostream>
#include "GrafoPalavras.h"

#define VOGAL(l) (l == 'a' || l == 'e' || l == 'i' || l == 'o' || l == 'u')
#define CONSOANTE(l) !VOGAL(l)

GrafoPalavras::GrafoPalavras(string *dict, int tamDict) :
	th(new TabelaHash<string, Vertice, Hasher> (3 * tamDict)), d(new Digrafo(
			tamDict)), dict(dict) {
	for(int i = 0; i < tamDict; i++)
		th->inserir(dict + i, new int(i));
	gerarVizinhos();
}

GrafoPalavras::~GrafoPalavras() {
	delete th;
	delete d;
	delete[] dict;
}

void GrafoPalavras::gerarVizinhos() {
	int tamDict = th->obterQtdArmazenados();

	int *vertice1, *vertice2, dist;
	for (int i = 0; i < tamDict; i++) {
		for (int j = i + 1; j < tamDict; j++) {
			if ((dist = calcularDistancia(dict[i], dict[j])) == -1)
				continue;

			vertice1 = th->obter(dict + i);
			vertice2 = th->obter(dict + j);

			d->inserirAresta(*vertice1, *vertice2, dist);
			d->inserirAresta(*vertice2, *vertice1, dist);
		}
	}
}

Lista<string>* GrafoPalavras::calcularCaminho(string origem, string destino,
		int *dist) {
	Vertice *pai = new Vertice[d->obterNumVertices()];
	double *custo = new double[d->obterNumVertices()];

	int *vOrigem, *vDestino;
	vOrigem = th->obter(&origem);
	vDestino = th->obter(&destino);

	d->calcularCaminhoMinimo(*vOrigem, pai, custo);

	if(pai[*vDestino] == -1){
		*dist = custoMaximo;
		return NULL;
	}

	Vertice v;
	Lista<string> *resposta = new Lista<string>;
	for (v = *vDestino; v != pai[v]; v = pai[v])
		resposta->inserirInicio(dict[v]);
	resposta->inserirInicio(dict[v]);

	*dist = custo[*vDestino];

	delete[] pai;
	delete[] custo;
	return resposta;
}

int GrafoPalavras::calcularDistancia(string p1, string p2) {
	int tam1 = p1.size(), tam2 = p2.size();
	int i, j, dif1 = -1, dif2 = -1;

	if (tam1 > tam2 + 1 || tam1 < tam2 - 1)
		return -1;

	if (tam1 == tam2) {
		i = 0;
		while (i < tam1 && p1[i] == p2[i])
			i++;

		if (i == tam1)
			return 0;

		dif1 = i;
		i++;
		while (i < tam1 && p1[i] == p2[i])
			i++;

		if (i == tam1) { //Substituição de letra
			if (VOGAL(p1[dif1]) && VOGAL(p2[dif1]))
				return 1;
			else if (CONSOANTE(p1[dif1]) && CONSOANTE(p2[dif1]))
				return 2;
			else
				return 3;
		}

		dif2 = i;
		i++;
		while (i < tam1 && p1[i] == p2[i])
			i++;

		if (i != tam1 || p1[dif1] != p2[dif2] || p1[dif2] != p2[dif1]) //Mais de uma substituição
			return -1;

		if (VOGAL(p1[dif1]) && VOGAL(p1[dif2])) //Troca de letra
			return 1;
		else if (CONSOANTE(p1[dif1]) && CONSOANTE(p1[dif2]))
			return 2;
		else
			return 3;
	}

	//Inserção/remoção de letra
	if (tam2 < tam1) {
		string tmp = p1;
		int tamTmp = tam1;
		p1 = p2;
		tam1 = tam2;
		p2 = tmp;
		tam2 = tamTmp;
	}

	int dif = -1;
	for (i = j = 0; i < tam1; i++, j++) {
		if (p1[i] == p2[j])
			continue;

		if (dif == -1) {
			dif = i;
			i--;
		} else {
			return -1;
		}
	}

	if (dif == -1)
		dif = tam1;

	if (VOGAL(p2[dif]))
		return 1;
	else
		return 2;
}
