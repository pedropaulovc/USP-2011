/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUENCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * NodoRB (Nodo de árvore binária balanceada rubro-negra) definidos
 * no arquivo NodoRB.h.
 */

#include <iostream>
using namespace std;

template<class TipoInfo>
NodoRB<TipoInfo>::NodoRB(TipoInfo *info) :
	info(info), pai(NULL), esquerda(NULL), direita(NULL), cor(PRETO) {
}

template<class TipoInfo>
NodoRB<TipoInfo>::NodoRB(TipoInfo *info, bool cor) :
	info(info), pai(NULL), esquerda(NULL), direita(NULL), cor(cor) {
}

template<class TipoInfo>
NodoRB<TipoInfo>::~NodoRB() {
	if (esquerda)
		delete esquerda;
	if (direita)
		delete direita;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::insere(TipoInfo *info) {
	if (!info)
		return this;

	NodoRB<TipoInfo> *p = this, *pai = NULL, *novo = new NodoRB<TipoInfo> (
			info, VERMELHO);

	while (p != NULL) {
		pai = p;
		if (*info < *(p->obterInfo()))
			p = p->obterEsquerda();
		else
			p = p->obterDireita();
	}

	novo->alterarPai(pai);

	if (*info < *(pai->obterInfo()))
		pai->alterarEsquerda(novo);
	else
		pai->alterarDireita(novo);

	return ajustaInsercao(novo);
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::ajustaInsercao(NodoRB<TipoInfo> *novo) {
	NodoRB<TipoInfo> *pai = novo->obterPai(), *tio, *avo;
	do {
		if ((pai ? pai->obterCor() : PRETO) == PRETO)
			return this;
		avo = pai->obterPai(); //Pai é vermelho -> avô tem que existir e é preto

		if (avo->obterEsquerda() == pai) {
			tio = avo->obterDireita();

			if (tio && tio->obterCor() == VERMELHO) {
				pai->alterarCor(PRETO);
				tio->alterarCor(PRETO);
				avo->alterarCor(VERMELHO);

				if (!avo->obterPai()) {
					avo->alterarCor(PRETO);
					return this;
				}
				pai = avo->obterPai();
				novo = avo;
			} else {
				if (novo == pai->obterEsquerda())
					novo = rotacaoDireita(novo);
				else
					novo = rotacaoDuplaDireita(novo);

				if (!novo->obterPai())
					return novo;
				return this;
			}
		} else {
			tio = avo->obterEsquerda();

			if (tio && tio->obterCor() == VERMELHO) {
				pai->alterarCor(PRETO);
				tio->alterarCor(PRETO);
				avo->alterarCor(VERMELHO);

				if (!avo->obterPai()) {
					avo->alterarCor(PRETO);
					return this;
				}
				pai = avo->obterPai();
				novo = avo;
			} else {
				if (novo == pai->obterDireita())
					novo = rotacaoEsquerda(novo);
				else
					novo = rotacaoDuplaEsquerda(novo);

				if (!novo->obterPai())
					return novo;
				return this;
			}
		}
	} while (true);
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::remove(TipoInfo *info) {
	NodoRB<TipoInfo> *p = this, *y, *x, *pai, *irmao, *raiz = this;
	bool esq;

	if (!info)
		return this;

	p = buscaInsere(info);

	if (!p)
		return this;

	if (!p->obterEsquerda() || !p->obterDireita())
		y = p;
	else
		y = sucessor(p);

	if (!y->obterEsquerda())
		x = y->obterDireita();
	else
		x = y->obterEsquerda();

	pai = y->obterPai();
	if (x)
		x->alterarPai(pai);

	if (!pai) {
		raiz = x;
	} else if (y == pai->obterEsquerda()) {
		pai->alterarEsquerda(x);
		esq = true;
	} else {
		pai->alterarDireita(x);
		esq = false;
	}

	if (y != p)
		p->alterarInfo(y->obterInfo());

	if (y->obterCor() == VERMELHO) {
		delete y;
		return raiz;
	}

	do {
		if (!pai || (x && x->obterCor() == VERMELHO)) {
			if (x)
				x->alterarCor(PRETO);
			delete y;
			return raiz;
		}

		if (esq) {
			irmao = pai->obterDireita();

			if (irmao && irmao->obterCor() == VERMELHO) {
				irmao->alterarCor(PRETO);
				pai->alterarCor(VERMELHO);
				pai = rotacaoEsquerda(pai);
				irmao = pai->obterDireita();
			}

			if (!irmao->obterEsquerda() || (irmao->obterEsquerda()->obterCor()
					== PRETO && (!irmao->obterDireita()
					|| irmao->obterDireita()->obterCor() == PRETO))) {
				irmao->alterarCor(VERMELHO);
				x = pai;
				pai = x->obterPai();
			} else {
				if (!irmao->obterDireita() || irmao->obterDireita()->obterCor()
						== PRETO) {
					irmao->obterEsquerda()->alterarCor(PRETO);
					irmao->alterarCor(VERMELHO);
					irmao = rotacaoDireita(irmao);
					irmao = pai->obterDireita();
				}

				irmao->alterarCor(pai->obterCor());
				pai->alterarCor(PRETO);
				irmao->obterDireita()->alterarCor(PRETO);
				pai = rotacaoEsquerda(pai);
				if (!pai->obterPai())
					return pai;
				return raiz;
			}
		} else {
			irmao = pai->obterEsquerda();

			if (irmao && irmao->obterCor() == VERMELHO) {
				irmao->alterarCor(PRETO);
				pai->alterarCor(VERMELHO);
				pai = rotacaoDireita(pai);
				irmao = pai->obterEsquerda();
			}

			if (!irmao->obterDireita() || (irmao->obterDireita()->obterCor()
					== PRETO && (!irmao->obterEsquerda()
					|| irmao->obterEsquerda()->obterCor() == PRETO))) {
				irmao->alterarCor(VERMELHO);
				x = pai;
				pai = x->obterPai();
			} else {
				if (!irmao->obterEsquerda()
						|| irmao->obterEsquerda()->obterCor() == PRETO) {
					irmao->obterDireita()->alterarCor(PRETO);
					irmao->alterarCor(VERMELHO);
					irmao = rotacaoEsquerda(irmao);
					irmao = pai->obterEsquerda();
				}

				irmao->alterarCor(pai->obterCor());
				pai->alterarCor(PRETO);
				irmao->obterEsquerda()->alterarCor(PRETO);
				pai = rotacaoDireita(pai);
				if (!pai->obterPai())
					return pai;
				return raiz;
			}
		}
	} while (true);

}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::buscaInsere(TipoInfo *info, bool *inseriu) {
	if (!info)
		return this;

	NodoRB<TipoInfo> *p = this, *pai = NULL;

	while (p != NULL) {
		pai = p;
		if(*info == *(p->obterInfo())){
			*inseriu = false;
			return p;
		} else if (*info < *(p->obterInfo())) {
			p = p->obterEsquerda();
		} else {
			p = p->obterDireita();
		}
	}

	*inseriu = true;

	NodoRB<TipoInfo> *novo = new NodoRB<TipoInfo> (info, VERMELHO);
	novo->alterarPai(pai);

	if (*info < *(pai->obterInfo()))
		pai->alterarEsquerda(novo);
	else
		pai->alterarDireita(novo);

	return ajustaInsercao(novo);
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::sucessor(NodoRB<TipoInfo> *nodo) {
	NodoRB<TipoInfo> *sucessor;

	if (!nodo)
		return NULL;

	if (nodo->obterDireita()) {
		nodo = nodo->obterDireita();
		while (nodo) {
			sucessor = nodo;
			nodo = nodo->obterEsquerda();
		}
		return sucessor;
	}

	sucessor = nodo->obterPai();
	while (sucessor && nodo == sucessor->obterDireita()) {
		nodo = sucessor;
		sucessor = sucessor->obterPai();
	}

	return sucessor;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::rotacaoDireita(NodoRB<TipoInfo> *novo) {
	NodoRB<TipoInfo> *oPai = novo->obterPai(), *avo = oPai->obterPai(),
			*bisavo = avo->obterPai();

	avo->alterarEsquerda(oPai->obterDireita());
	if (avo->obterEsquerda())
		avo->obterEsquerda()->alterarPai(avo);
	oPai->alterarDireita(avo);
	avo->alterarPai(oPai);
	oPai->alterarCor(PRETO);
	avo->alterarCor(VERMELHO);
	oPai->alterarPai(bisavo);
	if (bisavo && bisavo->obterDireita() == avo)
		bisavo->alterarDireita(oPai);
	else if (bisavo && bisavo->obterEsquerda() == avo)
		bisavo->alterarEsquerda(oPai);
	return oPai;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::rotacaoEsquerda(NodoRB<TipoInfo> *novo) {
	NodoRB<TipoInfo> *oPai = novo->obterPai(), *avo = oPai->obterPai(),
			*bisavo = avo->obterPai();

	avo->alterarDireita(oPai->obterEsquerda());
	if (avo->obterDireita())
		avo->obterDireita()->alterarPai(avo);
	oPai->alterarEsquerda(avo);
	avo->alterarPai(oPai);
	oPai->alterarCor(PRETO);
	avo->alterarCor(VERMELHO);
	oPai->alterarPai(bisavo);
	if (bisavo && bisavo->obterDireita() == avo)
		bisavo->alterarDireita(oPai);
	else if (bisavo && bisavo->obterEsquerda() == avo)
		bisavo->alterarEsquerda(oPai);
	return oPai;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::rotacaoDuplaDireita(NodoRB<TipoInfo> *novo) {
	NodoRB<TipoInfo> *oPai = novo->obterPai(), *avo = oPai->obterPai(),
			*bisavo = avo->obterPai();

	avo->alterarEsquerda(novo->obterDireita());
	oPai->alterarDireita(novo->obterEsquerda());
	if (novo->obterDireita())
		novo->obterDireita()->alterarPai(avo);
	if (novo->obterEsquerda())
		novo->obterEsquerda()->alterarPai(oPai);
	novo->alterarEsquerda(oPai);
	oPai->alterarPai(novo);
	novo->alterarDireita(avo);
	avo->alterarPai(novo);
	avo->alterarCor(VERMELHO);
	novo->alterarCor(PRETO);
	novo->alterarPai(bisavo);
	if (bisavo && bisavo->obterDireita() == avo)
		bisavo->alterarDireita(novo);
	else if (bisavo && bisavo->obterEsquerda() == avo)
		bisavo->alterarEsquerda(novo);
	return novo;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::rotacaoDuplaEsquerda(NodoRB<TipoInfo> *novo) {
	NodoRB<TipoInfo> *oPai = novo->obterPai(), *avo = oPai->obterPai(),
			*bisavo = avo->obterPai();

	avo->alterarDireita(novo->obterEsquerda());
	oPai->alterarEsquerda(novo->obterDireita());
	if (novo->obterEsquerda())
		novo->obterEsquerda()->alterarPai(avo);
	if (novo->obterDireita())
		novo->obterDireita()->alterarPai(oPai);
	novo->alterarDireita(oPai);
	oPai->alterarPai(novo);
	novo->alterarEsquerda(avo);
	avo->alterarPai(novo);
	avo->alterarCor(VERMELHO);
	novo->alterarCor(PRETO);
	novo->alterarPai(bisavo);
	if (bisavo && bisavo->obterDireita() == avo)
		bisavo->alterarDireita(novo);
	else if (bisavo && bisavo->obterEsquerda() == avo)
		bisavo->alterarEsquerda(novo);
	return novo;

}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::minimo() {
	NodoRB<TipoInfo> *p = this;

	while(p->obterEsquerda())
		p = p->obterEsquerda();

	return p;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::maximo() {
	NodoRB<TipoInfo> *p = this;

	while(p->obterDireita())
		p = p->obterDireita();

	return p;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::obterPai() {
	return pai;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::obterDireita() {
	return direita;
}

template<class TipoInfo>
NodoRB<TipoInfo>* NodoRB<TipoInfo>::obterEsquerda() {
	return esquerda;
}

template<class TipoInfo>
TipoInfo* NodoRB<TipoInfo>::obterInfo() {
	return info;
}

template<class TipoInfo>
bool NodoRB<TipoInfo>::obterCor() {
	return cor;
}

template<class TipoInfo>
void NodoRB<TipoInfo>::alterarPai(NodoRB<TipoInfo> *nodo) {
	pai = nodo;
}

template<class TipoInfo>
void NodoRB<TipoInfo>::alterarEsquerda(NodoRB<TipoInfo> *nodo) {
	esquerda = nodo;
}

template<class TipoInfo>
void NodoRB<TipoInfo>::alterarDireita(NodoRB<TipoInfo> *nodo) {
	direita = nodo;
}

template<class TipoInfo>
void NodoRB<TipoInfo>::alterarCor(bool cor) {
	this->cor = cor;
}

template<class TipoInfo>
void NodoRB<TipoInfo>::alterarInfo(TipoInfo *info) {
	this->info = info;
}
