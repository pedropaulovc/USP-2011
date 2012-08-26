/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * EP1: Backtracking e pilhas - 2011
 * Sobre o arquivo: Aqui são declarados os protótipos das funções a serem
 * implementadas em main.c, o tipo abstrato de dados "jogo" além de macros
 * e inclusões relevantes.
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "matriz.h"

#define BURACO -1
#define NADA 0
#define PINO 1
#define ERRO_MOVIMENTO_INVALIDO -3

/**
 * O TAD "jogo" contém todas as variáveis relevantes durante toda a
 * busca de solução de um dado tabuleiro. Contém a pilha de estados
 * candidatos a solução do problema, o tabuleiro objetivo ("obj"),
 * o tamanho do tabuleiro ("l" e "c") e o número máximo de movimentos
 * que podem ser executados até a localização de uma resposta.
 */
typedef struct {
	pilha *candidatos;
	int **obj;
	int l, c, maxMov;
} jogo;

void inicializaJogo(jogo *oJogo);
estado* leJogoEntrada(jogo *oJogo);
void encerraJogo(jogo oJogo);
movimento* buscaSolucao(jogo oJogo, estado *inicial);
int empilhaCandidatos(jogo oJogo, estado *atual);
movimento geraMovimento(int x, int y, char direcao);
int movimentoValido(jogo oJogo, estado *atual, movimento mov);
estado* executaMovimento(jogo oJogo, estado *atual, movimento mov);
void exibeSolucao(jogo oJogo, movimento *resp);

#endif /* MAIN_H_ */
