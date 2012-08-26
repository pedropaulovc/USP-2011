/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUÊNCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos definidos em InterfaceUsuario.h
 * responsáveis pelo interfaceamento do usuário com o programa além da delegação
 * de tarefas de manipulação das estruturas de dados usadas durante a execução
 * do programa.
 */

#include "InterfaceUsuario.h"

InterfaceUsuario::InterfaceUsuario() {
	lerTexto();

	Lista<int> *tamanhos = new Lista<int> ;
	Lista<Lista<Palavra*>*> *tabela = new Lista<Lista<Palavra*>*> ;
	gerarTabelaPalavras(palavras, tamanhos, tabela);

	intervalos = NodoSegmento::criarArvoreSegmentos(tamanhos, tabela, 0,
			tamanhos->tamanho() - 1);

	exibirConsultas();
}

InterfaceUsuario::~InterfaceUsuario() {
	delete palavras;
	delete intervalos;
}

void InterfaceUsuario::exibirConsultas() {
	int numConsultas, min, max;
	cin >> numConsultas;
	cin.ignore();

	for (int i = 0; i < numConsultas; i++) {
		cin >> min >> max;
		intervalos->exibirConteudo(min, max);
	}
}

void InterfaceUsuario::gerarTabelaPalavras(NodoRB<Palavra> *palavras,
		Lista<int> *tam, Lista<Lista<Palavra*>*> *tab) {
	Palavra *p = palavras->obterInfo();

	if (palavras->obterEsquerda())
		gerarTabelaPalavras(palavras->obterEsquerda(), tam, tab);

	if (tam->vazia() || tam->obterFim() != p->obterTamanho()) {
		tam->inserirFim(p->obterTamanho());
		tab->inserirFim(new Lista<Palavra*> ());
	}
	tab->obterFim()->inserirFim(p);

	if (palavras->obterDireita())
		gerarTabelaPalavras(palavras->obterDireita(), tam, tab);
}

string trim(string s) {
	//Código adaptado de:
	//http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
	s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int> (
			isspace))));
	s.erase(
			find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int> (isspace))).base(),
			s.end());

	return s;
}

void InterfaceUsuario::lerTexto() {
	int numLinhas;
	string linha;
	string::size_type pos;

	cin >> numLinhas;
	cin.ignore();
	getline(cin, linha);

	pos = linha.find_first_of(DELIM, 0);
	palavras = new NodoRB<Palavra> (new Palavra(linha.substr(0, pos)));
	if (pos != string::npos)
		lerLinhaPalavras(trim(linha.substr(pos + 1)));

	for (int i = 1; i < numLinhas; i++) {
		getline(cin, linha);
		lerLinhaPalavras(trim(linha));
	}
}

void InterfaceUsuario::lerLinhaPalavras(string linha) {
	string::size_type pos;

	while ((pos = linha.find_first_of(DELIM, 0)) != string::npos) {
		inserePalavra(linha.substr(0, pos));
		linha = trim(linha.substr(pos + 1));
	}

	if (linha.find_first_not_of(" ") != string::npos)
		inserePalavra(linha);
}

void InterfaceUsuario::inserePalavra(string nova) {
	bool inseriu;
	Palavra *p = new Palavra(nova);
	NodoRB<Palavra> *nodo = palavras->buscaInsere(p, &inseriu);

	if (inseriu) {
		palavras = nodo;
	} else {
		nodo->obterInfo()->incrementarFreq();
		delete p;
	}
}

