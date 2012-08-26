/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * Par definidos no arquivo Par.h.
 */

template<class P1, class P2>
Par<P1, P2>::Par() : p1(NULL), p2(NULL){
}

template<class P1, class P2>
Par<P1, P2>::Par(P1 *p1, P2 *p2) :
	p1(p1), p2(p2) {
}

template<class P1, class P2>
Par<P1, P2>::~Par() {
}

template<class P1, class P2>
P1* Par<P1, P2>::obterP1() {
	return p1;
}

template<class P1, class P2>
P2* Par<P1, P2>::obterP2() {
	return p2;
}

template<class P1, class P2>
bool Par<P1, P2>::operator==(Par<P1, P2> &par) {
	if(!p1 || !par.p1)
		return false;
	return *p1 == *(par.p1);
}

template<class P1, class P2>
bool Par<P1, P2>::operator!=(Par<P1, P2> &par) {
	if(!p1 || !par.p1)
		return false;
	return *p1 != *(par.p1);
}

template<class P1, class P2>
bool Par<P1, P2>::operator<(Par<P1, P2> &par) {
	if(!p1 || !par.p1)
		return false;
	return *p1 < *(par.p1);
}

template<class P1, class P2>
bool Par<P1, P2>::operator>(Par<P1, P2> &par) {
	if(!p1 || !par.p1)
		return false;
	return *p1 > *(par.p1);
}

template<class P1, class P2>
bool Par<P1, P2>::operator<=(Par<P1, P2> &par) {
	if(!p1 || !par.p1)
		return false;
	return *p1 <= *(par.p1);
}

template<class P1, class P2>
bool Par<P1, P2>::operator>=(Par<P1, P2> &par) {
	if(!p1 || !par.p1)
		return false;
	return *p1 >= *(par.p1);
}
