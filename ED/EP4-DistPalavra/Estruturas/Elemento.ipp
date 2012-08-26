/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * Elemento (De lista duplamente ligada) definidos no arquivo
 * Elemento.h.
 */

template<class Tipo>
Elemento<Tipo>::Elemento(Tipo info) :
	proximo(NULL), anterior(NULL), info(info) {
}

template<class Tipo>
Elemento<Tipo>::~Elemento() {
}

template<class Tipo>
Tipo Elemento<Tipo>::obterInfo() {
	return this->info;
}

template<class Tipo>
Elemento<Tipo>* Elemento<Tipo>::obterProximo() {
	return this->proximo;
}

template<class Tipo>
Elemento<Tipo>* Elemento<Tipo>::obterAnterior() {
	return this->anterior;
}

template<class Tipo>
void Elemento<Tipo>::alterarProximo(Elemento<Tipo> *proximo) {
	this->proximo = proximo;
}

template<class Tipo>
void Elemento<Tipo>::alterarAnterior(Elemento<Tipo> *anterior) {
	this->anterior = anterior;
}
