/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP2 - MAKEFILE
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os método do objeto
 * Target definidos no arquivo Target.h representando um target
 * parseado de um MakeFile.
 */

#include "Target.h"

Target::Target(string target) :
	nome(target), visitado(false), dependencias(NULL), comandos(NULL) {
}

Target::~Target() {
	if(dependencias)
		delete dependencias;
	if(comandos)
		delete comandos;
}

Lista<Target>* Target::obterDependencias() {
	return dependencias;
}

Lista<string>* Target::obterComandos() {
	return comandos;
}

string Target::obterNome() const {
	return nome;
}

void Target::inserirComando(string *comando){
	if(!comandos)
		comandos = new Lista<string>();
	comandos->inserirFim(comando);
}

void Target::inserirDependencia(Target *dependencia){
	if(!dependencias)
		dependencias = new Lista<Target>();
	dependencias->inserirFim(dependencia);
}

bool Target::obterVisitado(){
	return visitado;
}

void Target::definirVisitado(bool visitado){
	this->visitado = visitado;
}

bool Target::operator==(const Target &b) const {
	return b.obterNome() == nome;
}
