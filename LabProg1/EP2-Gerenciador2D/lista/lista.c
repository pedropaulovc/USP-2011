/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP2 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403
 *
 * Neste arquivo estão implementados os protótipos definidos em
 * lista.h referentes às operações de manipulação de uma lista
 * duplamente ligada com cabeça de lista.
 */

#include "lista.h"

tLista* criaLista() {
	tLista *lista = (tLista*) malloc(sizeof(tLista));
	tElemento *cabeca = (tElemento*) malloc(sizeof(tElemento));

	if (lista == NULL || cabeca == NULL)
		return NULL;

	cabeca->antecessor = cabeca;
	cabeca->sucessor = cabeca;
	cabeca->info = NULL;

	lista->numElementos = 0;
	lista->cabeca = cabeca;

	return lista;
}


void destroiLista(tLista *lista) {
	if (lista == NULL)
		return;

	tElemento *iter = lista->cabeca->sucessor;

	while (iter != lista->cabeca) {
		iter = iter->sucessor;
		destroiElemento(iter->antecessor);
	}

	destroiElemento(lista->cabeca);
	free(lista);
}


int listaVazia(tLista *lista) {
	if (lista->numElementos > 0)
		return FALSE;
	return TRUE;
}


int adicionarInicio(tLista *lista, tInfo *info) {
	return adicionarPosicao(lista, info, 0);
}


int adicionarPosicao(tLista *lista, tInfo *info, int posicao) {
	tElemento* novo;
	tElemento* antigoPosicao;

	int i;

	if (lista == NULL)
		return ERRO_LISTA_NULA;
	if (posicao > lista->numElementos + 1)
		return ERRO_POSICAO_INVALIDA;

	novo = (tElemento*) malloc(sizeof(tElemento));
	if (novo == NULL)
		return ERRO_MEMORIA_CHEIA;

	antigoPosicao = lista->cabeca->sucessor;

	for (i = 0; i < posicao; i++)
		antigoPosicao = antigoPosicao->sucessor;

	novo->info = info;
	novo->antecessor = antigoPosicao->antecessor;
	antigoPosicao->antecessor->sucessor = novo;
	novo->sucessor = antigoPosicao;
	antigoPosicao->antecessor = novo;

	lista->numElementos++;

	return 1;
}

int adicionarFim(tLista *lista, tInfo *info) {
	if (lista == NULL)
		return ERRO_LISTA_NULA;

	tElemento *novo = (tElemento*) malloc(sizeof(tElemento));
	if (novo == NULL)
		return ERRO_MEMORIA_CHEIA;

	novo->info = info;

	novo->antecessor = lista->cabeca->antecessor;
	novo->sucessor = lista->cabeca;
	lista->cabeca->antecessor->sucessor = novo;
	lista->cabeca->antecessor = novo;

	lista->numElementos++;

	return 1;
}

int adicionarOrdem(tLista *lista, tInfo *info){
	tElemento *p;
	if(lista == NULL)
		return ERRO_LISTA_NULA;

	if(listaVazia(lista))
		return adicionarInicio(lista, info);

	tElemento *novo = (tElemento*) malloc(sizeof(tElemento));
	if (novo == NULL)
		return ERRO_MEMORIA_CHEIA;

	novo->info = info;
	p = lista->cabeca;

	while(p->sucessor != lista->cabeca && maior(info, p->sucessor->info))
		p = p->sucessor;

	novo->sucessor = p->sucessor;
	novo->antecessor = p;
	p->sucessor->antecessor = novo;
	p->sucessor = novo;

	(lista->numElementos)++;
	return 1;
}


int removerInicio(tLista *lista) {
	return removerPosicao(lista, 0);
}


int removerPosicao(tLista *lista, int posicao) {
	int i;
	tElemento* sai;

	if (posicao < 0 || posicao >= lista->numElementos)
		return ERRO_POSICAO_INVALIDA;

	sai = lista->cabeca->sucessor;
	for (i = 0; i < posicao; i++)
		sai = sai->sucessor;

	sai->antecessor->sucessor = sai->sucessor;
	sai->sucessor->antecessor = sai->antecessor;
	lista->numElementos--;
	destroiElemento(sai);
	return 1;
}


int removerFim(tLista *lista) {
	if (lista == NULL)
		return ERRO_LISTA_NULA;
	return removerPosicao(lista, lista->numElementos - 1);
}


tInfo* obterInicio(tLista *lista) {
	return obterPosicao(lista, 0);
}


tInfo* obterPosicao(tLista *lista, int posicao) {
	int i;
	tElemento* elemento;

	if (posicao < 0 || posicao >= lista->numElementos)
		return NULL;

	elemento = lista->cabeca->sucessor;

	for (i = 0; i < posicao; i++)
		elemento = elemento->sucessor;

	return elemento->info;
}


tInfo* obterFim(tLista *lista) {
	if (lista == NULL)
		return NULL;
	return obterPosicao(lista, lista->numElementos - 1);
}

void destroiElemento(tElemento *elemento){
	if(elemento == NULL)
		return;

	destroiInfo(elemento->info);
	free(elemento);
}
