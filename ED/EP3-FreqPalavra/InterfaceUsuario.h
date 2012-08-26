/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUÊNCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os protótipos dos métodos a serem implementados
 * em InterfaceUsuario.cpp responsáveis pelo interfaceamento do
 * usuário com o programa além da delegação de tarefas de manipulação das
 * estruturas de dados usadas durante a execução do programa.
 */

#ifndef INTERFACEUSUARIO_H_
#define INTERFACEUSUARIO_H_

#include <iostream>
#include <string>
#include <algorithm>
#include "Estruturas/NodoRB.h"
#include "Estruturas/NodoSegmento.h"
#include "Estruturas/Lista.h"
#include "Palavra.h"

using namespace std;

#define DELIM " .,:"

class InterfaceUsuario {
private:
	NodoRB<Palavra> *palavras;
	NodoSegmento *intervalos;

public:
	/**
	 * Construtor do objeto, contém a lógica essencial do programa, delegando
	 * a construção e manipulação das estruturas de dados aos objetos
	 * responsáveis.
	 */
	InterfaceUsuario();

	/**
	 * Destrutor do objeto.
	 */
	virtual ~InterfaceUsuario();

	/**
	 * Método responsável por ler da entrada padrão o texto a ser analisado
	 * segundo a convenção determinada na especificação do EP e construir
	 * gradualmente a árvore de busca binária de palavras balanceada
	 * (Atributo NodoRB<Palavra> *palavras).
	 */
	void lerTexto();

	/**
	 * Método responsável por ler uma linha de texto passada via parâmetro e
	 * adicionar as palavras devidamente separadas na árvore de busca
	 * "palavras".
	 */
	void lerLinhaPalavras(string linha);

	/**
	 * Método responsável por inserir eficientemente uma palavra já separada
	 * como token na árvore de busca binária "palavras" ou atualizar sua
	 * frequência caso já tenha sido inserida anteriormente.
	 */
	void inserePalavra(string nova);


	/**
	 * Este método recebe como parâmetro uma árvore de busca binária de palavras
	 * ("palavras") completa e duas listas inicializadas e vazias ("tam" e "tab").
	 * Ao final da execução, serão construídas duas tabelas em "tam" e "tab" da
	 * seguinte forma:
	 *
	 *  - "tam" conterá em cada posição um tamanho de palavra lido do texto de
	 *  entrada distinto.
	 *  - "tab" conterá em cada posição correspondente a "tam" uma lista contendo
	 *  ponteiros para todas as palavras lidas do texto de entrada que possuem o
	 *  tamanho definido em "tam".
	 *
	 * Ex: tam = [3, 5, 7]; tab = [[aaa, abc], [12345, abcde, cinco], [7777777]]
	 *
	 */
	void gerarTabelaPalavras(NodoRB<Palavra> *palavras, Lista<int> *tam, Lista<Lista<Palavra*>*> *tab);

	/**
	 * Método responsável por ler da entrada padrão e realizar as consultas à
	 * árvore de intervalos "intervalos", sendo essa responsável por exibir os
	 * resultados ao usuário.
	 */
	void exibirConsultas();

};

#endif /* INTERFACEUSUARIO_H_ */
