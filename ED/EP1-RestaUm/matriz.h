/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * EP1: Backtracking e pilhas - 2011
 * Sobre o arquivo: Aqui são declarados os protótipos das funções a serem
 * implementadas em matriz.c além de macros e inclusões relevantes.
 */

#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int** alocaMatriz(int linhas, int colunas);
void desalocaMatriz(int **matriz, int linhas);
int** clonaMatriz(int** original, int numLinhas, int numColunas);
int matrizesIguais(int **matriz1, int **matriz2, int numLinhas, int numColunas);
void exibeMatriz(int **matriz, int numLinhas, int numColunas);

#endif /* MATRIZ_H_ */
