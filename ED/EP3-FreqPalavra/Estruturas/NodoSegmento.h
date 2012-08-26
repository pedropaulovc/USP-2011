/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUÊNCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os protótipos dos métodos a serem implementados
 * em NodoSegmento.cpp responsáveis por representar um nodo de uma árvore
 * binária balanceada de segmentos.
 */

#ifndef NODOSEGMENTO_H_
#define NODOSEGMENTO_H_

#include <iostream>
#include <cstdlib>

#include "Lista.h"
#include "../Palavra.h"

using namespace std;

class NodoSegmento {
private:
	/**
	 * Limite mínimo do escopo do nodo
	 */
	int min;
	/**
	 * Limite máximo do escopo do nodo
	 */
	int max;

	/**
	 * Filho da esquerda (Contém a metade menor do intervalo [min, max])
	 */
	NodoSegmento *esquerda;

	/**
	 * Filho da direita (Contém a metade maior do intervalo [min, max])
	 */
	NodoSegmento *direita;

	/**
	 * Nodo pai, contém o nodo atual.
	 */
	NodoSegmento *pai;

	/**
	 * Lista de apontadores para todas as palavras contidas nesse intervalo.
	 */
	Lista<Palavra*> *palavras;

public:

	/**
	 * Construtor do objeto, recebe os limites mínimos e máximos do nodo.
	 */
	NodoSegmento(int min, int max);

	/**
	 * Destrutor do objeto.
	 */
	virtual ~NodoSegmento();

	/**
	 * Este método recebe como parâmetros os intervalos mínimo e máximo (min <= max)
	 * de busca na árvore de segmentos e uma lista de apontadores de Palavra
	 * inicializada onde será armazenada a resposta. Após a execução, no
	 * parâmetro "resp" estarão armazenadas todas as palavras contidas na árvore
	 * enraizada neste nó atual que atendem ao requisito do intervalo passado
	 * via parâmetro.
	 */
	void obterConteudo(int min, int max, Lista<Palavra*> *resp);

	/**
	 * Este método estático é responsável por construir e retornar uma árvore de
	 * segmentos balanceada recebendo como parâmetros:
	 *
	 *  - inf e sup, os limites das listas, na primeira chamada ao método, inf = 0 e
	 *  sup = tamanho das listas
	 *  - "tam", lista contendo em cada posição um tamanho de palavra lido do texto de
	 *  entrada distinto.
	 *  - "tab", lista contendo em cada posição correspondente a "tam" uma lista contendo
	 *  ponteiros para todas as palavras lidas do texto de entrada que possuem o
	 *  tamanho definido em "tam".
	 *
	 * Ex: tam = [3, 5, 7]; tab = [[aaa, abc], [12345, abcde, cinco], [7777777]]
	 *
	 * Ao final da execução é retornada uma árvore de segmentos balanceada com limites
	 * dados pelos valores extremos de "tam". No exemplo, [3-7].
	 */
	static NodoSegmento* criarArvoreSegmentos(Lista<int> *tam, Lista<Lista<
			Palavra*>*> *pal, int inf, int sup);

	/**
	 * Este método é responsável por exibir na saída padrão conforme determina
	 * a especificação do EP o resultado de uma busca na árvore de segmentos
	 * através do método obterConteudo();
	 */
	void exibirConteudo(int min, int max);

	/**
	 * Método "setter" para o atributo "esquerda" do objeto.
	 */
	void alterarEsquerda(NodoSegmento* filho);

	/**
	 * Método "setter" para o atributo "direita" do objeto.
	 */
	void alterarDireita(NodoSegmento* filho);

	/**
	 * Método "setter" para o atributo "pai" do objeto.
	 */
	void alterarPai(NodoSegmento* pai);

	/**
	 * Este método é responsável por armazenar na lista de apontadores de Palavra
	 * "palavras" os apontadores da lista enviada por parâmetro.
	 */
	void inserirPalavras(Lista<Palavra*> *pal);

	/**
	 * Método "getter" do atributo "esquerda" do objeto.
	 */
	NodoSegmento* obterEsquerda();

	/**
	 * Método "getter" do atributo "direita" do objeto.
	 */
	NodoSegmento* obterDireita();

	/**
	 * Método "getter" do atributo "pai" do objeto.
	 */
	NodoSegmento* obterPai();
};

#endif /* NODOSEGMENTO_H_ */
