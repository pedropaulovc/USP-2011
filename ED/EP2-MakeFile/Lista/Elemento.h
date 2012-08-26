/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP2 - MAKEFILE
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * Elemento (de lista duplamente ligada) a serem implementados no arquivo
 * Elemento.ipp.
 */

#ifndef ELEMENTO_H_
#define ELEMENTO_H_

#include <cstdlib>

template<class Tipo>
class Elemento {
private:
	/**
	 * Ponteiro para o próximo elemento na lista duplamente ligada. Definido
	 * como NULL na construção do objeto.
	 */
	Elemento<Tipo> *proximo;
	/**
	 * Ponteiro para o elemento anterior na lista duplamente ligada. Definido
	 * como NULL na construção do objeto.
	 */
	Elemento<Tipo> *anterior;
	/**
	 * Ponteiro para o dado referenciado na posição do elemento na lista
	 * duplamente ligada. Valor inicial recebido via parâmetro na construção
	 * do objeto.
	 */
	Tipo *info;

public:
	/**
	 * Construtor do objeto, recebe como parâmetro um ponteiro para o dado
	 * a ser referenciado.
	 */
	Elemento(Tipo *info);
	/**
	 * Destrutor do objeto Elemento, não desaloca o ponteiro info.
	 */
	virtual ~Elemento();

	/**
	 * Método "getter" do atributo info.
	 */
	Tipo* obterInfo();
	/**
	 * Método "getter" do atributo proximo.
	 */
	Elemento<Tipo>* obterProximo();
	/**
	 * Método "getter" do atributo anterior.
	 */
	Elemento<Tipo>* obterAnterior();

	/**
	 * Método "setter" do atributo proximo.
	 */
	void alterarProximo(Elemento<Tipo> *proximo);
	/**
	 * Método "setter" do atributo anterior.
	 */
	void alterarAnterior(Elemento<Tipo> *anterior);
};

#include "Elemento.ipp"

#endif /* ELEMENTO_H_ */
