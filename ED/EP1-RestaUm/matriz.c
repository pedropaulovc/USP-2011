/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * EP1: Backtracking e pilhas - 2011
 * Sobre o arquivo: Aqui são implementados as funções de manipulação de
 * matrizes necessárias durante o funcionamento do programa.
 */

#include "matriz.h"

/**
 * Função responsável por alocar dinamicamente uma matriz de inteiros com
 * dimensões "lin" X "col" e retornar um ponteiro para ela.
 */
int** alocaMatriz(int lin, int col) {
	int i;
	int **matriz;

	matriz = (int**) malloc(lin * sizeof(int*));
	if (matriz == NULL) {
		puts("Memória cheia!");
		return NULL;
	}
	for (i = 0; i < lin; i++) {
		matriz[i] = (int *) malloc(col * sizeof(int));
		if (matriz[i] == NULL) {
			puts("Memória cheia!");
			return NULL;
		}
	}

	return matriz;
}

/**
 * Função responsável por liberar a memória alocada por alocaMatriz previamente.
 */
void desalocaMatriz(int **matriz, int lin) {
	int i;

	for (i = 0; i < lin; i++)
		free(matriz[i]);
	free(matriz);
}

/**
 * Compara "matriz1" e  "matriz2" termo a termo, se ambas forem iguais retorna
 * TRUE, senão FALSE.
 */
int matrizesIguais(int **matriz1, int **matriz2, int lin, int col) {
	int i, j;
	for (i = 0; i < lin; i++)
		for (j = 0; j < col; j++)
			if (matriz1[i][j] != matriz2[i][j])
				return FALSE;

	return TRUE;
}

/**
 * Aloca uma nova matriz com as mesmas dimensões da original e copia os valores
 * termo a termo da original para a nova e por fim retorna um ponteiro para
 * nova matriz.
 */
int** clonaMatriz(int **original, int lin, int col) {
	int i, j;
	int **nova;

	nova = alocaMatriz(lin, col);

	for (i = 0; i < lin; i++)
		for (j = 0; j < col; j++)
			nova[i][j] = original[i][j];

	return nova;
}
