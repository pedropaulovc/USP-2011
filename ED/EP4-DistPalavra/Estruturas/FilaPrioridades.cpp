/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * FilaPrioridades (Implementado como heap binária) definidos
 * no arquivo FilaPrioridades.h.
 */

#include "FilaPrioridades.h"

FilaPrioridades::FilaPrioridades(int maxV, double *custo) :
	pq(new Vertice[maxV + 1]), N(0), qp(new Vertice[maxV]), custo(custo) {
}

FilaPrioridades::~FilaPrioridades() {
	delete[] pq;
	delete[] qp;
}

int FilaPrioridades::vazia() {
	return N == 0;
}

void FilaPrioridades::inserir(Vertice v) {
	qp[v] = ++N;
	pq[N] = v;
	subir(N);
}

Vertice FilaPrioridades::removerMin() {
	trocar(1, N);
	--N;
	rebaixar(1);
	return pq[N + 1];
}

void FilaPrioridades::decrementar(Vertice w) {
	subir(qp[w]);
}

void FilaPrioridades::trocar(int i, int j) {
	Vertice t;
	t = pq[i];
	pq[i] = pq[j];
	pq[j] = t;
	qp[pq[i]] = i;
	qp[pq[j]] = j;
}

void FilaPrioridades::subir(int k) {
	while (k > 1 && custo[pq[k / 2]] > custo[pq[k]]) {
		trocar(k / 2, k);
		k = k / 2;
	}
}

void FilaPrioridades::rebaixar(int k) {
	int j;
	while (2 * k <= N) {
		j = 2 * k;
		if (j < N && custo[pq[j]] > custo[pq[j + 1]])
			j++;
		if (custo[pq[k]] <= custo[pq[j]])
			break;
		trocar(k, j);
		k = j;
	}
}
