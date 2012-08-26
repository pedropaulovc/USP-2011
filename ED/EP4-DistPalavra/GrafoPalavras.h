/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * GrafoPalavras a serem implementados no arquivo GrafoPalavras.cpp.
 */

#ifndef GRAFOPALAVRAS_H_
#define GRAFOPALAVRAS_H_

#include <string>
#include <cstdlib>

#include "Estruturas/TabelaHash.h"
#include "Estruturas/Lista.h"
#include "Estruturas/Digrafo.h"

/**
 * Classe responsável por prover uma função de hash para strings a ser utilizada
 * pela TabelaHash.
 */
class Hasher {
public:
	unsigned long operator()(string palavra) {
		int tam = palavra.size();
		unsigned long hash = 0;
		for(int i = 0; i < tam; i++)
			hash = (hash << 5) - hash + palavra[i];
		return hash;
	}
};

class GrafoPalavras {
private:
	/**
	 * Objeto tabela hash, responsável por mapear palavras do dicionário recebido
	 * do usuário para Vertices do digrafo d através da classe Hasher definida acima.
	 */
	TabelaHash<string, Vertice, Hasher> *th;
	/**
	 * Objeto responsável por conter o digrafo representando as palavras do dicionário
	 * e suas vizinhanças.
	 */
	Digrafo *d;
	/**
	 * O dicionário de palavras lidas do usuário.
	 */
	string *dict;

	/**
	 * Função responsável por varrer o dicionário de palavras, encontrar palavras vizinhas
	 * através da função calcularDistancia e inserir as arestas convenientes no digrafo.
	 */
	void gerarVizinhos();

public:
	/**
	 * Construtor do objeto, recebe o dicionário de palavras e seu tamanho.
	 */
	GrafoPalavras(string *dict, int tamDict);
	/**
	 * Destrutor do objeto, desaloca a tabela hash, o digrafo e o dicionário.
	 */
	virtual ~GrafoPalavras();

	/**
	 * Função responsável por, dadas duas palavras pertencentes ao dicionário, origem
	 * e destino, retornar uma lista de palavras do dicionário representando o menor
	 * caminho entre origem e destino. O custo total desse caminho será gravado na
	 * variável apontada por dist. Caso não haja caminho possível, a função retornará
	 * NULL e dist terá seu valor alterado para o valor da macro maiorDistancia definida
	 * em Digrafo.h
	 */
	Lista<string>* calcularCaminho(string origem, string destino, int *dist);

	/**
	 * Função responsável por dadas duas palavras, p1 e p2, retornar a distância de edição
	 * tal como especificada no EP. Caso as palavras não sejam vizinhas retorna -1.
	 */
	static int calcularDistancia(string p1, string p2);
};

#endif /* GRAFOPALAVRAS_H_ */
