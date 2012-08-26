/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo está definida função main do programa, responsável
 * pelo interfaceamento entre o usuário e o modelo lógico.
 */

#include <iostream>
#include <string>
#include "Estruturas/Lista.h"
#include "GrafoPalavras.h"

using namespace std;

int main() {
	int tamDict, qtdConsultas;
	cin >> tamDict;
	cin.ignore();

	string *dict = new string[tamDict];
	for (int i = 0; i < tamDict; i++)
		getline(cin, dict[i]);

	GrafoPalavras *gp = new GrafoPalavras(dict, tamDict);

	cin >> qtdConsultas;
	cin.ignore();

	string origem, destino;

	for (int i = 0; i < qtdConsultas; i++) {
		cin >> origem >> destino;

		int custo;
		Lista<string> *resp = gp->calcularCaminho(origem, destino, &custo);

		if (!resp) {
			cout << "Não existe caminho entre " << origem << " e " << destino
					 << "\n" << endl;
			continue;
		}

		cout << "O menor caminho entre " << origem << " e " << destino
				<< " tem custo " << custo << endl;

		string palavra;
		for(unsigned int i = 0; i < resp->obterTamanho() - 1; i++){
			resp->obter(i, &palavra);
			cout << palavra << " -> ";
		}

		resp->obterFim(&palavra);
		cout << palavra << "\n" << endl;
	}

	return 0;
}
