/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP2 - MAKEFILE
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos definidos em MakeFile.h do objeto
 * MakeFile, a lógica principal do programa, definidos no arquivo MakeFile.h.
 */

#include "MakeFile.h"

MakeFile::MakeFile() :
	MF(new Lista<Target> ) {
}

MakeFile::~MakeFile() {
	delete MF;
}

int MakeFile::executarTarget(string nome) {
	Target *target;
	if (nome == "")
		target = MF->obterInicio();
	else
		target = buscarTarget(nome);

	if (!target) {
		cerr << "Não foi possível encontrar o target na lista de targets."
				<< endl;
		return ERRO_TARGET_INVALIDO;
	}

	Lista<Target> *ordTop = ordenarTopologicamente(target);
	if (!ordTop)
		return ERRO_CICLO_DEPENDENCIAS;

	int numTargets = ordTop->obterTamanho();

	int i = 0;
	while (i < numTargets && verificarDependenciasExistem(ordTop->obter(i))) {
		i++;
	}

	if (i != numTargets)
		return ERRO_DEPENDENCIA_NAO_EXISTE;

	for (int i = 0; i < numTargets; i++)
		atualizarTarget(ordTop->obter(i));

	return 0;
}

Lista<Target>* MakeFile::ordenarTopologicamente(Target *t) {
	if (!MF->contem(t))
		return NULL; //Target inválido

	Lista<Target> *visRamo = new Lista<Target> ;
	Lista<Target> *ordTop = new Lista<Target> ;
	bool resultado = visitar(t, visRamo, ordTop);

	delete visRamo;

	int numTargets = MF->obterTamanho();
	for(int i = 0; i < numTargets; i++)
		MF->obter(i)->definirVisitado(false);

	if (resultado)
		return ordTop;
	delete ordTop;
	return NULL;
}

bool MakeFile::visitar(Target *t, Lista<Target> *visRamo, Lista<Target> *ordTop) {
	//Dependência de arquivo simples (Não target)
	//Verificado posteriormente
	if (!MF->contem(t))
		return true;
	t = MF->obter(t);

	//Encontrou um ciclo
	if (visRamo->contem(t)) {
		cerr << "Ciclo detectado, compilação abortada." << endl;
		return false;
	}

	//Nada a fazer, target já visitado
	if (t->obterVisitado())
		return true;

	t->definirVisitado(true);
	visRamo->inserirFim(t);
	Lista<Target> *visRamoClone = visRamo->clona();

	Lista<Target> *adj = MF->obter(t)->obterDependencias();
	int numAdj = adj ? adj->obterTamanho() : 0;
	for (int i = 0; i < numAdj; i++) {
		if (!visitar(adj->obter(i), visRamoClone, ordTop)) {
			delete visRamoClone;
			return false;
		}
	}

	ordTop->inserirFim(t);

	delete visRamoClone;
	return true;
}

bool MakeFile::verificarDependenciasExistem(Target *target) {
	Lista<Target> *deps = target->obterDependencias();
	int numDeps = deps ? deps->obterTamanho() : 0;
	Target *dep;
	struct stat statDep;

	for (int i = 0; i < numDeps; i++) {
		dep = deps->obter(i);
		if (!MF->contem(dep) && stat(dep->obterNome().c_str(), &statDep) == -1) {
			cerr << "Arquivo \"" << dep->obterNome()
					<< "\" não foi encontrado. Compilação abortada." << endl;
			return false;
		}
	}

	return true;
}

void MakeFile::atualizarTarget(Target *target) {
	struct stat statTarget, statDep, statDepMaisNova;
	Lista<Target> *deps = target->obterDependencias();

	if (stat(target->obterNome().c_str(), &statTarget) == 0) {
		//Target existe, descobrir qual a dependência mais recente
		stat(deps->obterInicio()->obterNome().c_str(), &statDepMaisNova);

		int numDeps = deps->obterTamanho();
		for (int i = 1; i < numDeps; i++) {
			stat(deps->obter(i)->obterNome().c_str(), &statDep);
			if (statDep.st_mtim.tv_sec > statDepMaisNova.st_mtim.tv_sec)
				statDepMaisNova = statDep;
		}

		//Nada a fazer, target está atualizado
		if (statTarget.st_mtim.tv_sec > statDepMaisNova.st_mtim.tv_sec)
			return;
	}

	//Atualizando target
	Lista<string> *comandos = target->obterComandos();
	int numComandos = comandos ? comandos->obterTamanho() : 0;
	for (int i = 0; i < numComandos; i++)
		cout << *(comandos->obter(i)) << endl;
}

int MakeFile::obterNumTargets() {
	return MF->obterTamanho();
}

Target* MakeFile::buscarTarget(string nome) {
	Target *temp = new Target(nome);
	Target *localizado = MF->obter(temp);
	delete temp;
	return localizado;
}

void MakeFile::exibeTargets() {
	Target *target;
	Lista<Target> *deps;
	Lista<string> *comandos;
	int tamMF = MF->obterTamanho();
	for (int i = 0; i < tamMF; i++) {
		target = MF->obter(i);
		cout << target->obterNome() << "-";

		deps = target->obterDependencias();
		int numDependencias = deps ? deps->obterTamanho() : 0;
		for (int j = 0; j < numDependencias; j++)
			cout << deps->obter(j)->obterNome() << ",";
		cout << endl;

		comandos = target->obterComandos();
		int numComandos = comandos ? comandos->obterTamanho() : 0;
		for (int j = 0; j < numComandos; j++) {
			cout << "->" << *(comandos->obter(j)) << endl;
		}
	}
}

string MakeFile::trim(string s) {
	//Código adaptado de:
	//http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
	s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int> (
			isspace))));
	s.erase(
			find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int> (isspace))).base(),
			s.end());

	return s;
}

string MakeFile::parsearTarget(ifstream &arq, string linhaAnt) {
	Target *target;
	string linha = linhaAnt;
	string::size_type pos = linhaAnt.find_first_of(":", 0);

	while (arq.good() && pos == string::npos) {
		getline(arq, linha);
		pos = linha.find_first_of(":", 0);
	}

	if (pos == string::npos)
		return linha;

	target = new Target(trim(linha.substr(0, pos)));
	linha = trim(linha.substr(pos + 1));

	while ((pos = linha.find_first_of(" \t", 0)) != string::npos) {
		target->inserirDependencia(new Target(linha.substr(0, pos)));
		linha = trim(linha.substr(pos + 1));
	}

	if (linha.find_first_not_of(" \t") != string::npos)
		target->inserirDependencia(new Target(linha));

	while (getline(arq, linha) && linha[0] == '\t')
		target->inserirComando(new string(trim(linha)));

	MF->inserirFim(target);

	return linha;
}

void MakeFile::parsearArquivo(string nomeArq) {
	string linha = "";
	ifstream arq(nomeArq.c_str());

	if (!arq.is_open())
		return;

	while (arq.good())
		linha = parsearTarget(arq, linha);

	arq.close();
}
