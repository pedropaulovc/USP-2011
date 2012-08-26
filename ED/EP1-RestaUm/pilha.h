/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * EP1: Backtracking e pilhas - 2011
 * Sobre o arquivo: Aqui são declarados os protótipos das funções a serem
 * implementadas em pilha.c além de macros e inclusões relevantes.
 */

#include <stdlib.h>
#include <stdio.h>
#include "tInfo.h"

#define ERRO_MEMORIA_CHEIA -1
#define ERRO_PILHA_NULA -2

/**
 * tElemento é uma célula da pilha contendo um ponteiro para o elemento
 * empilhado e outro para a próxima célula da pilha (mais distante do topo).
 */
struct tElemento {
	tInfo *info;
	struct tElemento *proximo;
};

typedef struct tElemento tElemento;

/**
 * pilha é o TAD representante da pilha, contendo um ponteiro para o topo e
 * ainda o número de elementos atualmente armazenados.
 */
typedef struct {
	tElemento *topo;
	int numElementos;
} pilha;

void inicializarPilha(pilha *aPilha);
tInfo* desempilha(pilha *aPilha);
tInfo* verTopo(pilha *aPilha);
int empilha(pilha *aPilha, tInfo *dado);
int pilhaVazia(pilha *aPilha);
int obterNumElementos(pilha *aPilha);
