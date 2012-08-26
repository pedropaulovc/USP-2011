/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUENCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão implementados os métodos do objeto
 * Lista (Usando vetor, autoredimensionável) definidos
 * no arquivo Lista.h.
 */

template<class Tipo>
Lista<Tipo>::Lista() :
	lista(new Tipo[TAM_INICIAL]), ultimo(-1), capacidade(TAM_INICIAL) {
}

template<class Tipo>
Lista<Tipo>::~Lista() {
	delete[] lista;
}

template<class Tipo>
int Lista<Tipo>::tamanho() {
	return ultimo + 1;
}

template<class Tipo>
bool Lista<Tipo>::vazia(){
	return ultimo == -1;
}

template<class Tipo>
int Lista<Tipo>::vagarPosicao(int posicao){
	if (vazia())
		return 1;

	if (posicao > ultimo + 1 || posicao < 0)
		return ERRO_POSICAO_INVALIDA;

	if (ultimo == capacidade - 1)
		redimensionarLista();

	int i;
	for (i = ultimo; i >= posicao; i--)
		lista[i + 1] = lista[i];
	return 1;
}

template<class Tipo>
void Lista<Tipo>::redimensionarLista(){
	capacidade += TAM_INCREMENTO;

	Tipo *antiga = lista, *nova = new Tipo[capacidade];

	for(int i = 0; i <= ultimo; i++)
		nova[i] = lista[i];

	lista = nova;
	delete[] antiga;
}

template<class Tipo>
int Lista<Tipo>::inserirInicio(Tipo info) {
	return inserir(info, 0);
}

template<class Tipo>
int Lista<Tipo>::inserir(Tipo info, int posicao) {
	int resultado = vagarPosicao(posicao);

	if (resultado != 1)
		return resultado;

	lista[posicao] = info;
	ultimo++;
	return 1;
}

template<class Tipo>
int Lista<Tipo>::inserirFim(Tipo info) {
	if (ultimo == capacidade - 1)
		redimensionarLista();

	ultimo++;
	lista[ultimo] = info;

	return 1;
}

template<class Tipo>
int Lista<Tipo>::removerInicio() {
	return remover(0);
}

template<class Tipo>
int Lista<Tipo>::remover(int posicao) {
	if(vazia())
		return ERRO_LISTA_VAZIA;

	if (posicao > ultimo || posicao < 0)
		return ERRO_POSICAO_INVALIDA;

	for (; posicao <= ultimo; posicao++)
		lista[posicao] = lista[posicao + 1];

	ultimo--;
	return 1;
}

template<class Tipo>
int Lista<Tipo>::removerFim() {
	return remover(ultimo);
}

template<class Tipo>
Tipo Lista<Tipo>::obterInicio() {
	return lista[0];
}

template<class Tipo>
Tipo Lista<Tipo>::obter(int posicao) {
	if(posicao <= ultimo && posicao >= 0)
		return lista[posicao];
	return Tipo();
}

template<class Tipo>
Tipo Lista<Tipo>::operator [](int posicao){
	return obter(posicao);
}

template<class Tipo>
Tipo Lista<Tipo>::obterFim() {
	if(ultimo >= 0)
		return lista[ultimo];
	return Tipo();
}

template<class Tipo>
int Lista<Tipo>::concatenar(Lista<Tipo> *lista) {
	int nElemLista = lista->tamanho();

	for (int i = 0; i < nElemLista; i++)
		inserirFim(lista->obter(i));

	return 1;
}

template<class Tipo>
void Lista<Tipo>::ordenar(Ordenador *ord){
	ordenarRec(lista, 0, ultimo, ord);
}

template<class Tipo>
void Lista<Tipo>::ordenarRec(Tipo vetor[], int limInf, int limSup, Ordenador *ord){
	int i;
	if(limInf >= limSup)
		return;
	i = particionar(vetor, limInf, limSup, ord);
	ordenarRec(vetor, limInf, i - 1, ord);
	ordenarRec(vetor, i + 1, limSup, ord);
}

template<class Tipo>
int Lista<Tipo>::particionar(Tipo vetor[], int limInf, int limSup, Ordenador *ord){
	Tipo pivo = vetor[limSup];
	Tipo temp;
	int baixo = limInf - 1;

	for(int i = limInf; i < limSup; i++){
		if(ord->comparar(vetor[i], pivo)){
			baixo++;
			temp = vetor[baixo];
			vetor[baixo] = vetor[i];
			vetor[i] = temp;
		}
	}
	vetor[limSup] = vetor[baixo + 1];
	vetor[baixo + 1] = pivo;
	return baixo + 1;
}
