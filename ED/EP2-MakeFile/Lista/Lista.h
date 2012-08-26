/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP2 - MAKEFILE
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * Lista (Duplamente ligada circular com cabeça de lista) a serem
 * implementados no arquivo Lista.ipp.
 */

#ifndef LISTA_H_
#define LISTA_H_

#include <cstdlib>

#include "Elemento.h"

/**
 * Código de erro retornado pela lista em caso de uma operação de
 * remoção de um elemento de uma lista vazia.
 */
#define ERRO_LISTA_VAZIA -1

/**
 * Código de erro retornado pela lista em caso de uma operação de
 * acesso, inserção ou remoção em posição fora dos limites da lista.
 */
#define ERRO_POSICAO_INVALIDA -2

template<class Tipo>
class Lista {
private:
	/**
	 * Ponteiro para a cabeça da lista duplamente ligada circular com cabeça
	 * de lista.
	 */
	Elemento<Tipo> *cabeca;
	/**
	 * Contador do tamanho da lista.
	 */
	int tamanho;

public:
	/**
	 * Construtor do objeto Lista.
	 */
	Lista();
	/**
	 * Destrutor do objeto Lista. Desaloca todos os objetos Elemento contidos
	 * na lista invocando o destrutor de cada um deles.
	 */
	virtual ~Lista();

	/**
	 * Método responsável por retornar o tamanho da lista no momento.
	 */
	int obterTamanho();

	/**
	 * Este método adiciona, se possível, ao início da lista o novo elemento fornecido
	 * e retorna 1 caso haja sucesso ou um código de erro.
	 */
	int inserirInicio(Tipo *info);
	/**
	 * Este método adiciona, se possível, a uma posição arbitrária o novo elemento
	 * fornecido e retorna 1 caso haja sucesso ou um código de erro.
	 */
	int inserir(Tipo *info, int posicao);
	/**
	 * Este método adiciona, se possível, ao fim da lista o novo elemento
	 * fornecido e retorna 1 caso haja sucesso ou um código de erro.
	 */
	int inserirFim(Tipo *info);

	/**
	 * Este método remove, se possível, o elemento da primeira posição da lista e
	 * retorna 1 em caso de sucesso ou um código de erro.
	 */
	int removerInicio();
	/**
	 * Este método remove, se possível, um elemento do fim da lista e retorna 1
	 * em caso de sucesso ou um código de erro.
	 */
	int removerFim();
	/**
	 * Este método remove, se possível, de uma posição arbitrária um elemento da
	 * lista e retorna 1 em caso de sucesso ou um código de erro.
	 */
	int remover(int posicao);
	/**
	 * Este método remove, se possível, a primeira posição da lista que contiver
	 * um objeto igual ao passado em parâmetro (Usando operador == aos valores
	 * dos ponteiros ou então aos valores referenciados) . Retorna 1
	 * em caso de sucesso e 0 caso não tenha sido encontrado nenhum elemento que
	 * atendesse ao critério.
	 */
	int remover(Tipo *info);

	/**
	 * Este método retorna, se possível, o primeiro elemento da lista dupla ou
	 * NULL em caso de erro.
	 */
	Tipo* obterInicio();
	/**
	 * Este método retorna se possível o elemento que está no fim da lista dupla
	 * ou NULL em caso de erro.
	 */
	Tipo* obterFim();
	/**
	 * Este método retorna, se possível, um elemento de uma posição arbitrária
	 * da lista ou NULL em caso de erro.
	 */
	Tipo* obter(int posicao);
	/**
	 * Este método retorna, se possível, a primeira posição da lista que contiver
	 * um objeto igual ao passado em parâmetro (Usando operador == aos valores
	 * dos ponteiros ou então aos valores referenciados). Caso não seja encontrado
	 * nenhum candidato é retornado NULL/
	 */
	Tipo* obter(Tipo *info);

	/**
	 * Este método retorna true caso haja algum objeto na lista que obedeça aos
	 * mesmos critérios definidos em obter(Tipo *info) ou false em caso contrário.
	 */
	bool contem(Tipo *info);

	/**
	 * Este método recebe uma lista inicializada como parâmetro e inserem ao final
	 * da lista principal todos os elementos da lista enviada via parâmetro. Ao
	 * final da operação retorna 1.
	 */
	int concatenar(Lista<Tipo> *lista);

	/**
	 * Este método cria uma nova instância da lista e copia todos os conteúdos para
	 * a nova lista. Ao final retorna um ponteiro para a nova instância.
	 */
	Lista<Tipo>* clona();
};

#include "Lista.ipp"

#endif /* LISTA_H_ */
