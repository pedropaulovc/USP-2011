/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP2 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403
 *
 * Neste arquivo estão definidos os protótipos a serem implementados em
 * lista.c referentes à estrutura de dados lista duplamente encadeada com
 * cabeça de lista além de definições de constantes usadas ao longo do programa.
 */

#ifndef LISTA_H_
#define LISTA_H_

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include "tInfo.h"

/**
 * Código de erro retornado pela lista em caso de uma operação inválida de
 * remover um elemento de uma fila vazia.
 */
#define ERRO_LISTA_VAZIA -1

/**
 * Código de erro retornado pela lista em caso de tentar alocar espaço para uma
 * variável mas não haver memória suficiente.
 */
#define ERRO_MEMORIA_CHEIA -2

/**
 * Código de erro retornado pela lista em caso de uma operação inválida de
 * adicionar, obter ou remover	um elemento de uma posição inválida da lista.
 */
#define ERRO_POSICAO_INVALIDA -3

/**
 * Código de erro retornado pela lista em caso do parâmetro enviado à função
 * ser NULL.
 */
#define ERRO_LISTA_NULA -4

/**
 * Definição de um elemento de uma lista duplamente encadeada, contendo ponteiros
 * para os elementos antecessor e sucessor na lista e um ponteiro para o dado
 * armazenado no elemento.
 */
typedef struct tElemento{
	struct tElemento *antecessor;
	struct tElemento *sucessor;
	tInfo *info;
} tElemento;

/**
 * Definição de uma lista duplamente encadeada com cabeça de lista, contendo um
 * ponteiro para a cabeça da lista e a sua quantidade de elementos.
 */
typedef struct {
	tElemento* cabeca;
	int numElementos;
} tLista;

/**
 * Esta função retorna uma nova lista alocada dinamicamente usando malloc.
 * Retorna um ponteiro para a nova lista ou NULL caso não seja possível.
 *
 */
tLista* criaLista();

/**
 * Esta função remove todos os elementos contidos na lista inclusive ela mesma,
 * liberando o espaço de memória utilizado.
 */
void destroiLista(tLista *lista);

/**
 * Esta função retorna 1 se a lista está vazia ou 0 em caso contrário.
 */
int listaVazia(tLista *lista);

/**
 * Esta função adiciona, se possível, ao início da lista o novo elemento fornecido
 * e retorna 1 caso haja sucesso ou um código de erro.
 */
int adicionarInicio(tLista *lista, tInfo* info);

/**
 * Esta função adiciona, se possível, a uma posição arbitrária o novo elemento
 * fornecido e retorna 1 caso haja sucesso ou um código de erro.
 */
int adicionarPosicao(tLista *lista, tInfo* info, int posicao);

/**
 * Esta função adiciona, se possível, ao fim da lista o novo elemento
 * fornecido e retorna 1 caso haja sucesso ou um código de erro.
 */
int adicionarFim(tLista *lista, tInfo* info);

/**
 * Esta função adiciona, se possível, e assumindo que esteja previamente ordenada
 * o novo elemento fornecido preservando a ordem anterior através da comparação
 * dos elementos com a função maior() definida em tInfo.h. Ela retorna 1 caso haja
 * sucesso ou um código de erro.s
 */
int adicionarOrdem(tLista *lista, tInfo* info);

/**
 * Esta função remove, se possível, o elemento da primeira posição da lista e
 * retorna 1 em caso de sucesso ou um código de erro.
 */
int removerInicio(tLista *lista);

/**
 * Esta função remove, se possível, de uma posição arbitrária um elemento da
 * lista e retorna 1 em caso de sucesso ou um código de erro.
 */
int removerPosicao(tLista *lista, int posicao);

/**
 * Esta função remove, se possível, um elemento do fim da lista e retorna 1
 * em caso de sucesso ou um código de erro.
 */
int removerFim(tLista *lista);

/**
 * Esta função retorna, se possível, o primeiro elemento da lista dupla ou
 * NULL em caso de erro.
 */
tInfo* obterInicio(tLista *lista);

/**
 * Esta função retorna, se possível, um elemento de uma posição arbitrária
 * da lista ou NULL em caso de erro.
 */
tInfo* obterPosicao(tLista *lista, int posicao);

/**
 * Esta função retorna se possível o elemento que está no fim da lista dupla
 * ou NULL em caso de erro.
 */
tInfo* obterFim(tLista *lista);

/**
 * Esta função invoca destroiInfo() definido em tInfo.h para realizar a operação
 * conveniente de remoção do dado armazenado em elemento e posteriormente executa
 * a função free() no parâmetro passado.
 */
void destroiElemento(tElemento *elemento);
#endif /* LISTA_H_ */
