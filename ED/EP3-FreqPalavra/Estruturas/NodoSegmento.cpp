/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUÊNCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto NodoSegmento
 * responsável por representar um nodo de uma árvore binária balanceada
 * de segmentos.
 */

#include "NodoSegmento.h"

NodoSegmento::NodoSegmento(int min, int max) :
	min(min), max(max), esquerda(NULL), direita(NULL), pai(NULL), palavras(
			new Lista<Palavra*> ) {
}

NodoSegmento::~NodoSegmento() {
	if(esquerda)
		delete esquerda;
	if(direita)
		delete direita;
	delete palavras;
}

//Funcao exige que min < max
void NodoSegmento::obterConteudo(int min, int max, Lista<Palavra*> *resp) {
	//Expurgando pedidos com resposta vazia
	if (min > this->max || max < this->min)
		return;

	//Ajusta entrada ao máximo possível de ser atendido
	//pela árvore
	if (min < this->min)
		min = this->min;
	if (max > this->max)
		max = this->max;

	if (min == this->min && this->max == max) {
		resp->concatenar(palavras);
	} else {
		if (esquerda)
			esquerda->obterConteudo(min, max, resp);
		if (direita)
			direita->obterConteudo(min, max, resp);
	}
}


class OrdenadorFrequencia: public Ordenador {
	bool comparar(void* a, void* b) {
		Palavra *p1 = (Palavra*) a, *p2 = (Palavra*) b;
		if (p1->obterFrequencia() != p2->obterFrequencia())
			return p1->obterFrequencia() < p2->obterFrequencia();
		return p1->obterPalavra().compare(p2->obterPalavra()) < 0;
	}
};

void NodoSegmento::exibirConteudo(int min, int max) {
	Lista<Palavra*> *resp = new Lista<Palavra*> ;
	obterConteudo(min, max, resp);

	OrdenadorFrequencia *ord = new OrdenadorFrequencia;
	resp->ordenar(ord);
	delete ord;

	cout << "Contém " << resp->tamanho() << " elementos:" << endl;

	int numResp = resp->tamanho();
	for (int i = 0; i < numResp; i++)
		cout << resp->obter(i)->paraString() << endl;

	cout << endl;
}

NodoSegmento* NodoSegmento::criarArvoreSegmentos(Lista<int> *tam, Lista<
		Lista<Palavra*>*> *pal, int inf, int sup) {
	NodoSegmento *filho, *nodo = new NodoSegmento(tam->obter(inf),
			tam->obter(sup));
	for (int i = inf; i <= sup; i++)
		nodo->inserirPalavras(pal->obter(i));

	if (inf == sup)
		return nodo;

	filho = criarArvoreSegmentos(tam, pal, inf, (sup + inf) / 2);
	filho->alterarPai(nodo);
	nodo->alterarEsquerda(filho);

	filho = criarArvoreSegmentos(tam, pal, (sup + inf) / 2 + 1, sup);
	filho->alterarPai(nodo);
	nodo->alterarDireita(filho);
	return nodo;
}

void NodoSegmento::alterarEsquerda(NodoSegmento* filho) {
	this->esquerda = filho;
}

void NodoSegmento::alterarDireita(NodoSegmento* filho) {
	this->direita = filho;
}

void NodoSegmento::alterarPai(NodoSegmento* pai) {
	this->pai = pai;
}

void NodoSegmento::inserirPalavras(Lista<Palavra*> *pal) {
	this->palavras->concatenar(pal);
}

NodoSegmento* NodoSegmento::obterEsquerda() {
	return this->esquerda;
}

NodoSegmento* NodoSegmento::obterDireita() {
	return this->direita;
}

NodoSegmento* NodoSegmento::obterPai() {
	return this->pai;
}
