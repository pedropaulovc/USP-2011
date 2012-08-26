/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * Digrafo (Implementado usando lista de adjacências) a serem
 * implementados no arquivo Digrafo.cpp.
 */

#ifndef DIGRAFO_H_
#define DIGRAFO_H_

#include <cstdlib>
#include <limits>
#include <iostream>
#include <sstream>

#include "FilaPrioridades.h"

using namespace std;

/**
 * Tal como ensinado em aula e seguindo o modelo apresentado por Sedgewick,
 * vértices do digrafo são ints.
 */
#define Vertice int

/**
 * Valor "infinito" para a distância de um caminho em um grafo.
 */
#define custoMaximo numeric_limits<double>::max()

/**
 * Classe representante de um elemento de da lista de adjacências do digrafo.
 */
class ElemListaAdj {
public:
	Vertice w;
	double custo;
	ElemListaAdj *prox;

	/**
	 * Construtor do objeto, recebe o vértice que é adjacente, o peso (custo) da aresta
	 * e um ponteiro para o próximo elemento da lista de adjacências.
	 */
	ElemListaAdj(Vertice w, double custo, ElemListaAdj *prox):
		w(w), custo(custo), prox(prox){
	}

	/**
	 * Destrutor do objeto, remove todos os elementos posteriores na lista de adjacências.
	 */
	~ElemListaAdj(){
		if(prox)
			delete prox;
	}
};

class Digrafo {
private:
	/**
	 * Número de vértices do digrafo.
	 */
	int V;
	/**
	 * Número de arestas do digrafo.
	 */
	int A;
	/**
	 * Vetor de tamanho V, em que cada posição aponta para a lista de adjacências
	 * do vértice correspondente.
	 */
	ElemListaAdj **adj;

public:
	/**
	 * Construtor do digrafo, recebe o número de vértices.
	 */
	Digrafo(int V);
	/**
	 * Destrutor, desaloca a lista de adjacências.
	 */
	virtual ~Digrafo();

	void inserirAresta(Vertice v, Vertice w, double custo);


	/* Recebe digrafo G com custos não negativos nos arcos e um vértice s. Calcula uma SPT
	 * com origem s. A SPT é armazenada no vetor parent. As distâncias em relação a s são
	 * armazenadas no vetor cost. */

	/* A implementação supõe que a soma dos custos de todos os arcos é estritamente menor
	 * que maxCOST.  Supõe também que o digrafo tem no máximo V vértices.  (O código
	 * abaixo é uma versão modificada dos Programas 20.4, p.242, e 21.1, p.284,
	 * de Sedgewick.) */

	/**
	 * Função responsável por calcular o menor caminho entre o vértice s passado por parâmetro
	 * até todos os outros vértices usando o algoritmo de Dijkstra. O digrafo não pode conter
	 * arestas de pesos negativos. Ao final da execução é calculada uma SPT que é armazenada
	 * no vetor (de tamanho mínimo V) pai. As distâncias em relação a s são armazenadas no vetor
	 * custo. A soma de todos os pesos das arestas deve ser menor que custoMaximo.
	 *
	 * Esta implementação é uma adaptação do algoritmo apresentado por Sedgewick e Paulo Feofiloff
	 * em www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dijkstra.html
	 */
	void calcularCaminhoMinimo(Vertice s, Vertice pai[], double custo[]);
	/**
	 * Esta função retorna uma representação em string simplificada do grafo usando a notação DOT.
	 */
	string gerarNotacaoDOT();

	/**
	 * Método "getter" do atributo V.
	 */
	int obterNumVertices();
};

#endif /* DIGRAFO_H_ */
