/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * TabelaHash definidos no arquivo TabelaHash.h.
 */

template<class C, class V, class Hash>
TabelaHash<C, V, Hash>::TabelaHash(int tamanho) :
	tabela(new Lista<Par<C, V> >*[tamanho]), qtdArmazenados(0), tamanho(tamanho), colisoes(0),
			hasher(Hash()) {
	for (int i = 0; i < tamanho; i++)
		tabela[i] = NULL;
}

template<class C, class V, class Hash>
TabelaHash<C, V, Hash>::~TabelaHash() {
	for (int i = 0; i < qtdArmazenados; i++)
		if (tabela[i])
			delete tabela[i];
	delete[] tabela;
}

template<class C, class V, class Hash>
void TabelaHash<C, V, Hash>::inserir(C *chave, V *valor) {
	if(!chave)
		return;

	int pos = hasher(*chave) % tamanho;

	if (!tabela[pos])
		tabela[pos] = new Lista<Par<C, V> > ;
	else
		colisoes++;

	tabela[pos]->inserirInicio(Par<C, V>(chave, valor));
	qtdArmazenados++;
}

template<class C, class V, class Hash>
void TabelaHash<C, V, Hash>::remover(C *chave) {
	if(!chave)
		return;

	tabela[hasher(*chave) % tamanho]->remover(Par<C, V>(chave, NULL));
}

template<class C, class V, class Hash>
V* TabelaHash<C, V, Hash>::obter(C *chave) {
	if(!chave)
		return NULL;

	Lista<Par<C, V> > *balde = tabela[hasher(*chave) % tamanho];
	Par<C, V> resultado;

	if (balde){
		int encontrou = balde->obter(Par<C, V>(chave, NULL), &resultado);
		if(!encontrou)
			return NULL;
		return resultado.obterP2();
	}

	return NULL;
}

template<class C, class V, class Hash>
int TabelaHash<C, V, Hash>::obterQtdArmazenados(){
	return qtdArmazenados;
}

template<class C, class V, class Hash>
int TabelaHash<C, V, Hash>::obterNumColisoes(){
	return colisoes;
}
