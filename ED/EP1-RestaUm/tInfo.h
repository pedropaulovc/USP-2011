/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * EP1: Backtracking e pilhas - 2011
 * Sobre o arquivo: Para melhorar a portabilidade do código de implementação da
 * pilha, aqui são declarados os protótipos das funções a serem implementadas
 * em tInfo.c além de macros e inclusões relevantes.
 */

#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

#ifndef TINFO_H_
#define TINFO_H_

/**
 * movimento contém tanto as coordenadas e direção de movimento da peça de
 * origem ("x" e "y") quanto as coordenadas da peça de destino ("destX" e
 * "destY"). Isso permite o código de verificação de movimentos tornar-se
 * mais genérico e simples.
 */
typedef struct {
	int x, y;
	int destX, destY;
	char direcao;
} movimento;

/**
 * estado é o elemento que é inserido e removido da pilha (tInfo) e representa
 * uma fotografia de um tabuleiro após a execução de "numMov" movimentos, cada
 * um deles listados no vetor "passos".
 */
typedef struct {
	int **tabuleiro;
	int numMov;
	movimento *passos;
} estado;

typedef estado tInfo;

estado* alocaEstado(int numMov);
void desalocaEstado(estado *info, int l);
estado* clonaEstado(estado *original, int l, int c);

#endif /* TINFO_H_ */
