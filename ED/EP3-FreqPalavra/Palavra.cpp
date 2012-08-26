/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUÊNCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto definidos em
 * Palavra.h responsável por armazenar uma palavra e contabilizar sua
 * frequência no texto.
 */

#include "Palavra.h"

Palavra::Palavra(string palavra) :
	palavra(palavra), frequencia(1) {
}

Palavra::~Palavra() {
}

int Palavra::obterFrequencia() {
	return frequencia;
}

string Palavra::obterPalavra() {
	return palavra;
}

int Palavra::obterTamanho() {
	return palavra.size();
}

void Palavra::incrementarFreq() {
	frequencia++;
}

bool Palavra::operator <(Palavra &p) {
	if (palavra.size() != p.palavra.size())
		return palavra.size() < p.palavra.size();
	return palavra.compare(p.palavra) < 0;
}

bool Palavra::operator !=(Palavra &p) {
	return palavra != p.palavra;
}

bool Palavra::operator ==(Palavra &p) {
	return palavra == p.palavra;
}

string Palavra::paraString() {
	stringstream ss(stringstream::in | stringstream::out | stringstream::app);
	ss << "[" << frequencia << "] " << palavra;
	return ss.str();
}
