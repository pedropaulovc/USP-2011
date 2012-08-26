/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * TabelaHash (Usando endereçamento fechado) a serem implementados
 * no arquivo TabelaHash.ipp.
 */

#ifndef TABELAHASH_H_
#define TABELAHASH_H_

#include <cstdlib>
#include "Lista.h"
#include "Par.h"

using namespace std;

/**
 * Um objeto TabelaHash é definido como um mapeamento entre
 * objetos do tipo C para objetos do tipo V através do objeto
 * função Hash.
 *
 * A tabela hash armazena apenas ponteiros
 */
template<class C, class V, class Hash>
class TabelaHash {
private:
	/**
	 * Tabela de hash propriamente dita, implementada usando endereçamento
	 * fechado.
	 */
	Lista<Par<C, V> > **tabela;
	/**
	 * Variável representado número de objetos armazenados na tabela de hash.
	 */
	int qtdArmazenados;
	/**
	 * Variável representando o número de posições total da tabela de hash.
	 */
	int tamanho;
	/**
	 * Variável contadora do número de colisões até o momento na tabela hash.
	 */
	int colisoes;
	/**
	 * Objeto função Hash, responsável por mapear os objetos C em posições
	 * da tabela.
	 */
	Hash hasher;

public:
	/**
	 * Construtor do objeto, recebe o tamanho da tabela a ser utilizado.
	 */
	TabelaHash(int tamanho);
	/**
	 * Destrutor do objeto, desaloca a tabela.
	 */
	virtual ~TabelaHash();

	/**
	 * Função responsável por receber ponteiros para objetos chave e valor a serem
	 * armazenados na tabela hash.
	 */
	void inserir(C *chave, V *valor);
	/**
	 * Função responsável por receber um ponteiro para uma chave a ser buscada
	 * na tabela de hash e removida.
	 */
	void remover(C *chave);
	/**
	 * Função responsável por, dado um ponteiro para uma chave contida na tabela hash,
	 * retornar um ponteiro para o valor armazenado. Caso a chave não exista na tabela,
	 * retorna NULL.
	 */
	V* obter(C *chave);

	/**
	 * Função responsável por retornar o número de objetos armazenados na tabela hash.
	 */
	int obterQtdArmazenados();
	/**
	 * Função responsável por retornar o número de colisões até o momento na tabela hash.
	 */
	int obterNumColisoes();
};

#include "TabelaHash.ipp"

#endif /* TABELAHASH_H_ */
