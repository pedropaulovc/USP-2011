/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP2 - MAKEFILE
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * Target, a lógica principal do programa, a serem
 * implementados no arquivo Target.cpp representando um target
 * parseado de um MakeFile.
 */

#ifndef TARGET_H_
#define TARGET_H_

#include <string>
#include "Lista/Lista.h"

using namespace std;

class Target {
private:
	/**
	 * Nome do target.
	 */
	string nome;
	/**
	 * Flag de target já visitado em um ordenamento topológico. Definido como
	 * false na construção do objeto.
	 */
	bool visitado;
	/**
	 * Lista duplamente ligada circular referente às dependências do target.
	 */
	Lista<Target> *dependencias;
	/**
	 * Lista duplamente ligada circular referente aos comandos necessários
	 * para atualizar um target.
	 */
	Lista<string> *comandos;

public:
	/**
	 * Construtor do objeto Target.
	 */
	Target(string target);
	/**
	 * Destrutor do objeto. Invoca os destrutores de "dependencias" e "comandos".
	 */
	virtual ~Target();

	/**
	 * Retorna um ponteiro para a lista de dependências do programa.
	 */
    Lista<Target>* obterDependencias();
    /**
     * Retorna um ponteiro para a lista de comandos do programa.
     */
    Lista<string>* obterComandos();
    /**
     * Recebe um objeto Target a ser inserido no final da lista de dependências.
     */
    void inserirDependencia(Target *dependencia);
    /**
     * Recebe um ponteiro para uma string a ser inserida na lista de comandos.
     */
    void inserirComando(string *comando);
    /**
     * Retorna o valor da flag "visitado".
     */
    bool obterVisitado();
    /**
     * Recebe e atualiza o valor da flag "visitado".
     */
    void definirVisitado(bool visitado);
    /**
     * Retorna o nome do target.
     */
    string obterNome() const;
    /**
     * Retorna true caso os nomes do objeto e do parâmetro sejam iguais e false
     * em caso contrário.
     */
    bool operator== (const Target &b) const;
};

#endif /* TARGET_H_ */
