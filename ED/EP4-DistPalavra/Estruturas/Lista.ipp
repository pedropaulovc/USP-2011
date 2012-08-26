/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * Lista (Duplamente ligada circular com cabeça de lista) definidos
 * no arquivo Lista.h.
 */

template<class Tipo>
Lista<Tipo>::Lista() :
	cabeca(new Elemento<Tipo> (Tipo())), tamanho(0) {
	cabeca->alterarProximo(cabeca);
	cabeca->alterarAnterior(cabeca);
}

template<class Tipo>
Lista<Tipo>::~Lista() {
	Elemento<Tipo> *p = cabeca->obterProximo();

	while (p != cabeca) {
		p = p->obterProximo();
		delete p->obterAnterior();
	}

	delete cabeca;
}

template<class Tipo>
unsigned int Lista<Tipo>::obterTamanho() {
	return tamanho;
}

template<class Tipo>
int Lista<Tipo>::inserirInicio(Tipo info) {
	return inserir(info, 0);
}

template<class Tipo>
int Lista<Tipo>::inserir(Tipo info, unsigned int posicao) {
	Elemento<Tipo> *novo;
	Elemento<Tipo> *antigoPosicao;

	if (posicao > tamanho + 1)
		return ERRO_POSICAO_INVALIDA;

	novo = new Elemento<Tipo> (info);

	antigoPosicao = cabeca->obterProximo();

	for (unsigned int i = 0; i < posicao; i++)
		antigoPosicao = antigoPosicao->obterProximo();

	novo->alterarAnterior(antigoPosicao->obterAnterior());
	antigoPosicao->obterAnterior()->alterarProximo(novo);
	novo->alterarProximo(antigoPosicao);
	antigoPosicao->alterarAnterior(novo);

	tamanho++;

	return 1;
}

template<class Tipo>
int Lista<Tipo>::inserirFim(Tipo info) {
	Elemento<Tipo> *novo = new Elemento<Tipo>(info);

	novo->alterarAnterior(cabeca->obterAnterior());
	cabeca->obterAnterior()->alterarProximo(novo);
	novo->alterarProximo(cabeca);
	cabeca->alterarAnterior(novo);

	tamanho++;

	return 1;
}

template<class Tipo>
int Lista<Tipo>::removerInicio() {
	return remover(0);
}

template<class Tipo>
int Lista<Tipo>::remover(unsigned int posicao) {
	Elemento<Tipo>* sai;

	if(tamanho == 0)
		return ERRO_LISTA_VAZIA;

	if (posicao < 0 || posicao >= tamanho)
		return ERRO_POSICAO_INVALIDA;

	sai = cabeca->obterProximo();
	for (int i = 0; i < posicao; i++)
		sai = sai->obterProximo();

	sai->obterAnterior()->alterarProximo(sai->obterProximo());
	sai->obterProximo()->alterarAnterior(sai->obterAnterior());

	tamanho--;
	delete sai;

	return 1;
}

template<class Tipo>
int Lista<Tipo>::removerFim() {
	Elemento<Tipo> *sai = cabeca->obterAnterior()->obterInfo();

	if (tamanho == 0)
		return ERRO_LISTA_VAZIA;

	cabeca->alterarAnterior(sai->obterAnterior());
	sai->obterAnterior()->alterarProximo(cabeca);

	tamanho--;
	delete sai;

	return 1;
}

template<class Tipo>
int Lista<Tipo>::remover(Tipo info) {
	Elemento<Tipo> *p = cabeca->obterProximo();
	Tipo *infoP;

	while (p != cabeca) {
		infoP = p->obterInfo();
		if (infoP == info) {
			p->obterAnterior()->alterarProximo(p->obterProximo());
			p->obterProximo()->alterarAnterior(p->obterAnterior());
			delete p;
			tamanho--;
			return 1;
		}
		p = p->obterProximo();
	}

	return 0;
}

template<class Tipo>
int Lista<Tipo>::obterInicio(Tipo *resultado) {
	if (cabeca->obterProximo() == cabeca)
		return false;
	*resultado = cabeca->obterProximo()->obterInfo();
	return true;
}

template<class Tipo>
int Lista<Tipo>::obter(unsigned int posicao, Tipo *resultado) {
	Elemento<Tipo>* elemento;

	if (posicao >= tamanho)
		return false;

	elemento = cabeca->obterProximo();

	for (unsigned int i = 0; i < posicao; i++)
		elemento = elemento->obterProximo();

	*resultado = elemento->obterInfo();
	return true;
}

template<class Tipo>
int Lista<Tipo>::obterFim(Tipo *resultado) {
	if (cabeca->obterProximo() == cabeca)
		return false;
	*resultado = cabeca->obterAnterior()->obterInfo();
	return true;
}

template<class Tipo>
int Lista<Tipo>::obter(Tipo info, Tipo *resultado){
	Elemento<Tipo> *p = cabeca->obterProximo();
	Tipo infoP;

		while(p != cabeca){
			infoP = p->obterInfo();
			if (infoP == info){
				*resultado = infoP;
				return true;
			}

			p = p->obterProximo();
		}

		return false;
}

template<class Tipo>
bool Lista<Tipo>::contem(Tipo info){
	return obter(info);
}

template<class Tipo>
int Lista<Tipo>::concatenar(Lista<Tipo> *lista) {
	int nElemLista = lista->obterTamanho();

	for (int i = 0; i < nElemLista; i++)
		this->inserirFim(lista->obter(i));

	return 1;
}

template<class Tipo>
Lista<Tipo>* Lista<Tipo>::clona() {
	Lista<Tipo> *novo = new Lista<Tipo> ();
	Elemento<Tipo> *p = cabeca->obterProximo();

	while (p != cabeca) {
		novo->inserirFim(p->obterInfo());
		p = p->obterProximo();
	}

	return novo;
}
