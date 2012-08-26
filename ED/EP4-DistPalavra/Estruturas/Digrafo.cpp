/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * Digrafo definidos no arquivo Digrafo.h.
 */

#include "Digrafo.h"

Digrafo::Digrafo(int V) :
	V(V), A(0), adj(new ElemListaAdj*[V]) {
	for (int v = 0; v < V; v++)
		adj[v] = NULL;
}

Digrafo::~Digrafo() {
	for (int i = 0; i < V; i++)
		if (adj[i])
			delete adj[i];
	delete[] adj;
}

void Digrafo::inserirAresta(Vertice v, Vertice w, double custo) {
	if (v == w)
		return;
	adj[v] = new ElemListaAdj(w, custo, adj[v]);

	A++;
}

void Digrafo::calcularCaminhoMinimo(Vertice s, Vertice pai[], double custo[]) {
	Vertice w, w0;
	ElemListaAdj *p;
	for (w = 0; w < V; w++) {
		pai[w] = -1;
		custo[w] = custoMaximo;
	}

	pai[s] = s;
	custo[s] = 0.0;

	for (p = adj[s]; p != NULL; p = p->prox){
		custo[p->w] = p->custo;
		pai[p->w] = s;
	}

	FilaPrioridades *fp = new FilaPrioridades(V, custo);
	for (w = 0; w < V; w++)
		if (w != s)
			fp->inserir(w);

	while (!fp->vazia()) {
		w0 = fp->removerMin();
		if (custo[w0] == custoMaximo)
			break;
		for (p = adj[w0]; p != NULL; p = p->prox) {
			w = p->w;
			if (custo[w] > custo[w0] + p->custo) {
				custo[w] = custo[w0] + p->custo;
				fp->decrementar(w);
				pai[w] = w0;
			}
		}
	}
}


string Digrafo::gerarNotacaoDOT() {
	stringstream ss(stringstream::in | stringstream::out | stringstream::app);

	ss << "graph {\n";

	for (int i = 0; i < V; i++) {
		ElemListaAdj *atual = adj[i];
		while (atual) {
			if (i < atual->w)
				ss << i << "--" << atual->w << "\n";
			atual = atual->prox;
		}
	}
	ss << "}";

	return ss.str();
}

int Digrafo::obterNumVertices(){
	return V;
}
