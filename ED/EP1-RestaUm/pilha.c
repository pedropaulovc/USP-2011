/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * EP1: Backtracking e pilhas - 2011
 * Sobre o arquivo: Aqui são implementados as funções de manipulação de
 * pilha necessárias durante o funcionamento do programa.
 *
 * Sobre a implementação: Foi implementada uma pilha encadeada usando alocação
 * dinâmica de memória para evitar possíveis problemas de estouro de pilha
 * ao usar uma versão com vetores de tamanho fixo.
 */

#include "pilha.h"

/**
 * Função responsável por, dado um ponteiro para uma pilha, inicializa seus
 * campos, tornando-a vazia e pronta para operar.
 */
void inicializarPilha(pilha *aPilha){
	aPilha->topo = NULL;
	aPilha->numElementos = 0;
}

/**
 * Função responsável por, caso a pilha não esteja vazia desempilhar o
 * elemento do topo da pilha e retornar um ponteiro para ele, senão,
 * retornar NULL.
 */
tInfo* desempilha(pilha *aPilha){
	tInfo *infoSai;
	tElemento *sai;

	if(pilhaVazia(aPilha)){
		return NULL;
	}

	sai = aPilha->topo;
	infoSai = sai->info;

	aPilha->topo = sai->proximo;
	aPilha->numElementos--;
	free(sai);

	return infoSai;
}

/**
 * Função responsável por, caso a pilha não esteja vazia retornar um ponteiro
 * para o elemento do topo da pilha, senão, retornar NULL.
 */
tInfo* verTopo(pilha *aPilha){
	if(!pilhaVazia(aPilha))
		return aPilha->topo->info;
	return NULL;
}


/**
 * Função responsável por, caso a pilha não esteja cheia empilhar ponteiro para
 * o elemento passado via parâmetro ("info") e retornar o número de elementos
 * atualmente na pilha, senão, retornar um código de erro.
 */
int empilha(pilha *aPilha, tInfo *info){
	tElemento *novo = (tElemento*) malloc(sizeof(tElemento));

	if(novo == NULL){
		return ERRO_MEMORIA_CHEIA;
	}

	novo->proximo = aPilha->topo;
	novo->info = info;

	aPilha->topo = novo;
	aPilha->numElementos++;

	return aPilha->numElementos;
}

/**
 * Função responsável por retornar verdadeiro caso a pilha esteja vazia
 * e falso em caso contrario.
 */
int pilhaVazia(pilha *aPilha){
	return aPilha->numElementos == 0;
}

/**
 * Função responsável por retornar o número de elementos de uma pilha ou
 * um código de erro caso ela seja nula.
 */
int obterNumElementos(pilha *aPilha){
	if(aPilha == NULL)
		return ERRO_PILHA_NULA;
	return aPilha->numElementos;
}
