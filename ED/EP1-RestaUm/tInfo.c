/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * EP1: Backtracking e pilhas - 2011
 * Sobre o arquivo: Para melhorar a portabilidade do código de implementação da
 * pilha, aqui são implementados as funções de manipulação de estados
 * necessárias durante o funcionamento do programa.
 */

#include "tInfo.h"

/**
 * Função responsável por tentar alocar memória suficiente para um estado
 * que possui um vetor de passos realizados de tamanho "numMov". Caso não
 * haja memória suficiente, retorna NULL.
 */
estado* alocaEstado(int numMov){
	estado *novo = (estado*) malloc(sizeof(estado));
	movimento *passos = (movimento*) malloc(sizeof(movimento) * numMov);

	if (novo == NULL || passos == NULL){
		puts("Estado não alocado, memória cheia.");
		return NULL;
	}

	novo->numMov = numMov;
	novo->passos = passos;

	return novo;
}

/**
 * Função responsável por desalocar todas as estruturas contidas em um estado
 * (matriz representando o tabuleiro, vetor de passos executados) além do
 * próprio estado.
 */
void desalocaEstado(estado *info, int l) {
	desalocaMatriz(info->tabuleiro, l);
	free(info->passos);
	free(info);
}

/**
 * Função responsável por alocar um novo estado e replicar todas as informações
 * contidas nele (tabuleiro e passos executados até o instante). O estado
 * clonado possui uma posição a mais (vaga) no vetor de passos executados
 * para uso posterior. O número de movimentos do estado clonado é 1 a mais
 * que o original.
 */
estado* clonaEstado(estado *original, int l, int c){
	int i;

	estado *novo = alocaEstado(original->numMov + 1);

	if(novo == NULL)
		return NULL;

	novo->tabuleiro = clonaMatriz(original->tabuleiro, l, c);
	for(i = 0; i < original->numMov; i++)
		novo->passos[i] = original->passos[i];

	return novo;
}
