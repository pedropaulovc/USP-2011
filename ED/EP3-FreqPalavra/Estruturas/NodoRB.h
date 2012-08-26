/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUENCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * NodoRB (Nodo de árvore binária balanceada rubro-negra) a serem
 * implementados no arquivo NodoRB.ipp.
 */

#ifndef NODORB_H_
#define NODORB_H_

#include <cstdlib>

#define PRETO false
#define VERMELHO true

template<class TipoInfo>
class NodoRB {
private:

	/**
	 * Atributo apontador do conteúdo do nodo.
	 */
	TipoInfo *info;

	/**
	 * Atributo apontador para o nodo pai.
	 */
	NodoRB<TipoInfo> *pai;

	/**
	 * Atributo apontador para o nodo esquerda.
	 */
	NodoRB<TipoInfo> *esquerda;

	/**
	 * Atributo apontador para o nodo direita.
	 */
	NodoRB<TipoInfo> *direita;

	/**
	 * Atributo da cor do nodo, false como preto e true como vermelho.
	 */
	bool cor;

	/**
	 * Construtor privado do nodo, permite predefinir a cor.
	 */
	NodoRB(TipoInfo *info, bool cor);

	/**
	 * Este método realiza uma rotação para a direita a partir do nodo "novo",
	 * retornando a nova subárvore após a rotação.
	 */
	NodoRB<TipoInfo>* rotacaoDireita(NodoRB<TipoInfo> *novo);

	/**
	 * Este método realiza uma rotação para a esquerda a partir do nodo "novo",
	 * retornando a nova subárvore após a rotação.
	 */
	NodoRB<TipoInfo>* rotacaoEsquerda(NodoRB<TipoInfo> *novo);

	/**
	 * Este método realiza uma rotação dupla para a direita a partir do nodo "novo",
	 * retornando a nova subárvore após a rotação.
	 */
	NodoRB<TipoInfo>* rotacaoDuplaDireita(NodoRB<TipoInfo> *novo);

	/**
	 * Este método realiza uma rotação dupla para a esquerda a partir do nodo "novo",
	 * retornando a nova subárvore após a rotação.
	 */
	NodoRB<TipoInfo>* rotacaoDuplaEsquerda(NodoRB<TipoInfo> *novo);

	/**
	 * Método setter do atributo "pai" do objeto.
	 */
	void alterarPai(NodoRB<TipoInfo> *nodo);

	/**
	 * Método setter do atributo "esquerda" do objeto.
	 */
	void alterarEsquerda(NodoRB<TipoInfo> *nodo);

	/**
	 * Método setter do atributo "direita" do objeto.
	 */
	void alterarDireita(NodoRB<TipoInfo> *nodo);

	/**
	 * Método setter do atributo "cor" do objeto.
	 */
	void alterarCor(bool cor);

	/**
	 * Método setter do atributo "info" do objeto.
	 */
	void alterarInfo(TipoInfo *info);

	/**
	 * Método responsável por analisar a necessidade de realizar trocas
	 * de cores de nós, rotações, etc. após a inserção do nodo "nodo" e
	 * executá-las quando for preciso. Retorna a nova raíz da árvore após
	 * as modificações.
	 */
	NodoRB<TipoInfo>* ajustaInsercao(NodoRB<TipoInfo> *nodo);

public:

	/**
	 * Construtor público do objeto, recebe como parâmetro um ponteiro para
	 * o conteúdo a ser armazenado no nodo.
	 */
	NodoRB(TipoInfo *info);

	/**
	 * Destrutor do nodo, destroi ambas as subárvores direita e esquerda.
	 */
	~NodoRB();

	/**
	 * Método responsável por inserir um novo dado passado por parâmetero
	 * na árvore. Ao final da execução retorna a nova raíz da árvore.
	 */
	NodoRB<TipoInfo>* insere(TipoInfo *info);

	/**
	 * Método responsável por buscar ou inserir um novo elemento na árvore.
	 * Caso seja encontrado um nodo cujo valor do campo info seja igual (segundo
	 * operator ==()) ao parametro info derreferenciado então será retornado esse
	 * nodo, o parâmetro "inseriu" será definido como false e não será inserido
	 * novo elemento na árvore. Em caso contrário, o comportamento do método é
	 * idêntico ao insere(), definindo o parâmetro "inseriu" como true.
	 */
	NodoRB<TipoInfo>* buscaInsere(TipoInfo *info, bool *inseriu);

	/**
	 * Método responsável por buscar um elemento na árvore que tenha valor
	 * igual ao passado via parâmetro e removê-lo da árvore, realizando os
	 * reajustes necessários.
	 */
	NodoRB<TipoInfo>* remove(TipoInfo *info);

	/**
	 * Método "getter" do atributo "pai"
	 */
	NodoRB<TipoInfo>* obterPai();

	/**
	 * Método "getter" do atributo "esquerda"
	 */
	NodoRB<TipoInfo>* obterEsquerda();

	/**
	 * Método "getter" do atributo "direita"
	 */
	NodoRB<TipoInfo>* obterDireita();

	/**
	 * Método "getter" do atributo "info"
	 */
	TipoInfo* obterInfo();

	/**
	 * Método "getter" do atributo "cor"
	 */
	bool obterCor();

	/**
	 * Método responsável por retornar o nodo sucessor inordem do nodo
	 * passado via parâmetro, ou NULL caso não haja sucessor.
	 */
	NodoRB<TipoInfo>* sucessor(NodoRB<TipoInfo> *nodo);

	/**
	 * Método responsável por retornar o menor nodo da subárvore do objeto.
	 */
	NodoRB<TipoInfo>* minimo();

	/**
	 * Método responsável por retornar o maior nodo da subárvore do objeto.
	 */
	NodoRB<TipoInfo>* maximo();

};

#include "NodoRB.ipp"
#endif /* NODORB_H_ */
