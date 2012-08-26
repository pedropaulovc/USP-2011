/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * Par a serem implementados no arquivo Par.ipp.
 */

#ifndef PAR_H_
#define PAR_H_

#include <cstdlib>

/**
 * O objeto Par é um template para duas classes P1 e P2 em que todas as operações
 * de comparação são realizadas com o primeiro elemento.
 */
template<class P1, class P2>
class Par {
private:
	/**
	 * Ponteiro para o primeiro elemento do par.
	 */
	P1 *p1;
	/**
	 * Ponteiro para o segundo elemento do par.
	 */
	P2 *p2;

public:
	/**
	 * Construtor padrão do objeto, define p1 e p2 como NULL.
	 */
	Par();
	/**
	 * Construtor do objeto, recebe dois ponteiros, com o primeiro diferente de NULL
	 * para os objetos a serem referenciados pelo par.
	 */
	Par(P1 *p1, P2 *p2);
	/**
	 * Destrutor do objeto.
	 */
	virtual ~Par();

	/**
	 * Função "getter" do atributo p1.
	 */
	P1* obterP1();
	/**
	 * Função "getter" do atributo p2.
	 */
	P2* obterP2();

	/**
	 * Função de comparação == entre os dois objetos p1 derreferenciados. Caso p1 ou par.p1
	 * sejam NULL retorna false.
	 */
	bool operator==(Par<P1, P2> &par);
	/**
	 * Função de comparação != entre os dois objetos p1 derreferenciados. Caso p1 ou par.p1
	 * sejam NULL retorna false.
	 */
	bool operator!=(Par<P1, P2> &par);
	/**
	 * Função de comparação < entre os dois objetos p1 derreferenciados. Caso p1 ou par.p1
	 * sejam NULL retorna false.
	 */
	bool operator<(Par<P1, P2> &par);
	/**
	 * Função de comparação > entre os dois objetos p1 derreferenciados. Caso p1 ou par.p1
	 * sejam NULL retorna false.
	 */
	bool operator>(Par<P1, P2> &par);
	/**
	 * Função de comparação <= entre os dois objetos p1 derreferenciados. Caso p1 ou par.p1
	 * sejam NULL retorna false.
	 */
	bool operator<=(Par<P1, P2> &par);
	/**
	 * Função de comparação >= entre os dois objetos p1 derreferenciados. Caso p1 ou par.p1
	 * sejam NULL retorna false.
	 */
	bool operator>=(Par<P1, P2> &par);
};

#include "Par.ipp"

#endif /* PAR_H_ */
