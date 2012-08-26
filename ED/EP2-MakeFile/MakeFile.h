/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP2 - MAKEFILE
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * MakeFile, a lógica principal do programa, a serem
 * implementados no arquivo MakeFile.cpp.
 */

#ifndef MAKEFILE_H_
#define MAKEFILE_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <functional>
#include <locale>

#include "Target.h"
#include "Lista/Lista.h"

using namespace std;

/**
 * Código de erro retornado quando o arquivo MakeFile não foi encontrado
 * no sistema de arquivos.
 */
#define ERRO_ARQUIVO_INVALIDO -10
/**
 * Código de erro retornado quando é pedida a execução de um target inexistente
 * na tabela de targets.
 */
#define ERRO_TARGET_INVALIDO -11
/**
 * Código de erro retornado quando o programa é incapaz de gerar um ordenamento
 * topológico de targets para serem executados devido a um ciclo de dependências.
 */
#define ERRO_CICLO_DEPENDENCIAS -12
/**
 * Código de erro retornado quando alguma dependência de um target não pode ser
 * encontrada nem na tabela de targets nem no sistema de arquivos.
 */
#define ERRO_DEPENDENCIA_NAO_EXISTE -13

class MakeFile {
private:
	/**
	 * Tabela de targets, é a estrutura de dados definida no EP, cada Target
	 * da tabela contém um ponteiro para uma lista de dependências e outra dos
	 * comandos a serem executados para atualizar o target.
	 */
	Lista<Target> *MF;

	/**
	 * Este método recebe como parâmetro um target da lista de targets e tenta
	 * gerar um ordenamento topológico grande o suficiente para satisfazer todas
	 * as depencências do target passado em parâmetro, assim, não gera um
	 * ordenamento topológico total. Em caso de sucesso, retorna o ordenamnto,
	 * caso haja um ciclo de dependências retorna NULL.
	 */
	Lista<Target>* ordenarTopologicamente(Target *t);
	/**
	 * Este método usado por ordenarTopologicamente visita recursivamente
	 * todos os nodos que são dependências diretas ou indiretas do target "t" passado
	 * via parâmetro. Os nodos já visitados anteriormente são armazenados em flags
	 * nos targets da tabela (Normalmente false no início da execução). Ao fim
	 * do método todas as flags são resetadas para false. Ainda, para detectar
	 * ciclos, o método recebe em visRamo uma lista de todos os targets
	 * já visitados dentro de um mesmo ramo de recursão (Uma lista vazia normalmente
	 * na primeira chamada). O resultado da ordenação até o momento é armazenado em
	 * ordTop (Normalmente uma lista vazia na primeira chamada). O método retorna
	 * true caso tenha conseguido realizar um ordenamento topológico e false em caso
	 * contrário. Caso tenha retornado false, ordTop conterá uma ordenação incompleta.
	 */
	bool visitar(Target *t, Lista<Target> *visRamo, Lista<Target> *ordTop);

	/**
	 * Este método verifica se todas as dependências do target "t" que não são
	 * targets existem no sistema de arquivos. Em caso positivo retorna true,
	 * senão retorna false.
	 */
	bool verificarDependenciasExistem(Target *t);
	/**
	 * Este método verifica a necessidade de um target ser recomplilado comparando as
	 * datas de modificação do próprio target (se existir) e de suas dependências.
	 * Caso alguma dependência seja mais recente que o target o método exibirá na saída
	 * padrão os comandos extraídos do MakeFile para esse target específico.
	 */
	void atualizarTarget(Target *target);

	/**
	 * Este método recebe o nome de um target a ser buscado e retorna um ponteiro para
	 * o target correspondente ou NULL caso ele não tenha sido encontrado.
	 */
	Target* buscarTarget(string nome);

	/**
	 * Este método recebe como parâmetros um ifstream referente ao arquivo de MakeFile
	 * a ser parseado e opcionalmente uma linha lida previamente do arquivo mas ainda
	 * não parseada. O método não aceita dependências com espaços em seus nomes.
	 * Entre o nome do target e as dependências e entre targets o método aceita
	 * qualquer quantidade de espaços. Exemplos de MakeFiles parseáveis por este método
	 * estão no diretório Testes. Ao final do parseamento do target, retorna a primeira
	 * linha do próximo target a ser fornecida em uma nova chamada no parâmetro linhaAnt.
	 */
	string parsearTarget(ifstream &makeFile, string linhaAnt = "");

	/**
	 * Este método recebe uma string, remove espaços e tabs do início e do final dela
	 * e retorna a nova string resultante.
	 */
	string trim(string s);

public:
	/**
	 * Construtor do objeto MakeFile.
	 */
	MakeFile();
	/**
	 * Destrutor do objeto, invoca o destrutor na tabela de targets.
	 */
	virtual ~MakeFile();

	/**
	 * Exibe na saída padrão os targets parseados e armazenados pelo programa.
	 */
	void exibeTargets();
	/**
	 * Retorna o tamanho da tabela de targets.
	 */
	int obterNumTargets();
	/**
	 * Recebe como parâmetro o nome do target a ser executado ou uma string vazia
	 * para executar o primeiro target. Usando os métodos desta classe, busca o
	 * target a ser executado, invoca o ordenamento topológico, verifica se todas
	 * as dependências existem e verifica se um target precisa ser executado. Caso
	 * tudo tenha ocorrido com sucesso exibe na saída padrão os comandos necessários
	 * para executar o target e retorna 0 em caso de sucesso. Em caso de erro, informa
	 * o usuário do problema e retorna um código de erro definido acima.
	 */
	int executarTarget(string target = "");

	/**
	 * Recebe como parâmetro o caminho do arquivo MakeFile a ser parseado e realiza
	 * a leitura, armazenando os targets lidos na tabela de targets.
	 */
	void parsearArquivo(string arquivo);
};

#endif /* MAKEFILE_H_ */
