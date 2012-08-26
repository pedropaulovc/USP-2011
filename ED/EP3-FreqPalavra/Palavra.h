/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUÊNCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos a serem implementados em
 * Palavra.h correspondentes ao objeto responsável por armazenar uma
 * palavra e contabilizar sua frequência no texto.
 */

#ifndef PALAVRA_H_
#define PALAVRA_H_

#include <string>
#include <sstream>

using namespace std;

class Palavra {
private:
	/**
	 * A própria palavra lida.
	 */
	string palavra;
	/**
	 * A frequência com que a palavra apareceu no texto.
	 */
	int frequencia;

public:
	/**
	 * Construtor do objeto, recebe como parâmetro uma string correspondente
	 * à palavra já separada como token.
	 */
	Palavra(string palavra);

	/**
	 * Destrutor do objeto.
	 */
	virtual ~Palavra();

	/**
	 * Retorna a frequência com que a palavra foi encontrada no texto.
	 */
    int obterFrequencia();

    /**
     * Retorna a string contendo a palavra armazenada no objeto.
     */
    string obterPalavra();

    /**
     * Retorna o tamannho da palavra armazenada.
     */
    int obterTamanho();

    /**
     * Incrementa em uma unidade a frequência que a palavra apareceu no texto.
     */
    void incrementarFreq();

    /**
     * Retorna true caso o tamanho da palavra passada via parâmetro seja maior
     * que o da palavra armazenada, false caso seja menor. Caso tenham o mesmo
     * tamanho, retorna true caso a palavra no objeto seja lexicograficamente
     * menor que a passada via parâmetro e false em aso contrário.
     */
    bool operator <(Palavra &p);

    /**
     * Retorna true caso as strings das palavras sejam diferentes e false em
     * caso contrário.
     */
    bool operator !=(Palavra &p);

    /**
     * Retorna false caso as strings das palavras sejam diferentes e true em
     * caso contrário.
     */
    bool operator ==(Palavra &p);

    /**
     * Retorna uma representação em string do objeto, na forma:
     * [frequencia] palavras
     */
    string paraString();
};

#endif /* PALAVRA_H_ */
