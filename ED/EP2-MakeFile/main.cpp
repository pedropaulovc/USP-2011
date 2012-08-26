/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP2 - MAKEFILE
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo está implementada a função main do programa responsável por
 * receber a entrada do usuário e delegá-la aos métodos do programa adequados.
 */

#include "MakeFile.h"

using namespace std;

int main() {
	string linha;
	string::size_type pos;
	MakeFile *makeFile = new MakeFile;
	makeFile->parsearArquivo("./MakeFile");

	if (makeFile->obterNumTargets() == 0) {
		cerr << "Arquivo MakeFile não encontrado ou não reconhecido." << endl;
		return ERRO_ARQUIVO_INVALIDO;
	}

	cout << "Informe o comando (make, make target, make limpa...)" << endl;
	getline(cin, linha);

	pos = linha.find_first_not_of("make", 0);
	pos = linha.find_first_not_of(" \t", pos);
	if (pos == string::npos)
		return makeFile->executarTarget();
	else
		return makeFile->executarTarget(linha.substr(pos));

	return 0;
}
