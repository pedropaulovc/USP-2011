/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP3 - FREQUENCIA DE PALAVRA
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * Lista (Usando vetor, autoredimensionável) a serem
 * implementados no arquivo Lista.ipp.
 */

#ifndef LISTA_H_
#define LISTA_H_

#include <cstdlib>

/**
 * Código de erro retornado pela lista em caso de uma operação de
 * remoção de um elemento de uma lista vazia.
 */
#define ERRO_LISTA_VAZIA -1

/**
 * Código de erro retornado pela lista em caso de uma operação de
 * acesso, inserção ou remoção em posição fora dos limites da lista.
 */
#define ERRO_POSICAO_INVALIDA -2

/**
 * Tamanho inicial do vetor da lista.
 */
#define TAM_INICIAL 100

/**
 * Tamanho do incremento no tamanho da lista sempre que ela ficar cheia.
 */
#define TAM_INCREMENTO 20

class Ordenador {
public:
	virtual bool comparar(void *a, void *b) = 0;
};

template<class Tipo>
class Lista {
private:
	/**
	 * Ponteiro para a cabeça da lista duplamente ligada circular com cabeça
	 * de lista.
	 */
	Tipo *lista;
	/**
	 * Contador da posição do último elemento da lista.
	 */
	int ultimo;

	/**
	 * Contador da capacidade da lista;
	 */
	int capacidade;

	/**
	 * Método responsável por tentar vagar a posição passada via parâmetro
	 * movendo os elementos do vetor. Retorna 1 em caso de sucesso ou um
	 * código de erro em caso de fracasso.
	 */
	int vagarPosicao(int posicao);

	/**
	 * Método responsável por redimensionar o vetor que contém os elementos
	 * da lista para capacidade + TAM_INCREMENTO e copiar os valores antigos
	 * no novo vetor.
	 */
	void redimensionarLista();

	/**
	 * Método recursivo de ordenação do Quicksort. Realiza as comparações
	 * através do funtor "ord". Na primeira chamada limInf = 0 e limSup =
	 * ultimo.
	 */
	void ordenarRec(Tipo vetor[], int limInf, int limSup, Ordenador *ord);
	/**
	 * Método de particionamento utilizado pelo método ordenarRec do
	 * algoritmo Quicksort.
	 */
	int particionar(Tipo vetor[], int limInf, int limSup, Ordenador *ord);

public:
	/**
	 * Construtor do objeto Lista.
	 */
	Lista();
	/**
	 * Destrutor do objeto Lista. Desaloca todos os objetos Elemento contidos
	 * na lista invocando o destrutor de cada um deles.
	 */
	virtual ~Lista();

	/**
	 * Método responsável por retornar o tamanho da lista no momento.
	 */
	int tamanho();

	/**
	 * Método responsável por retornar true caso a lista esteja vazia e false em caso
	 * contrário.
	 */
	bool vazia();

	/**
	 * Método responsável por retornar true caso a lista esteja cheia e false em caso
	 * contrário.
	 */
	bool cheia();

	/**
	 * Este método adiciona, se possível, ao início da lista o novo elemento fornecido
	 * e retorna 1 caso haja sucesso ou um código de erro.
	 */
	int inserirInicio(Tipo info);
	/**
	 * Este método adiciona, se possível, a uma posição arbitrária o novo elemento
	 * fornecido e retorna 1 caso haja sucesso ou um código de erro.
	 */
	int inserir(Tipo info, int posicao);
	/**
	 * Este método adiciona, se possível, ao fim da lista o novo elemento
	 * fornecido e retorna 1 caso haja sucesso ou um código de erro.
	 */
	int inserirFim(Tipo info);

	/**
	 * Este método remove, se possível, o elemento da primeira posição da lista e
	 * retorna 1 em caso de sucesso ou um código de erro.
	 */
	int removerInicio();
	/**
	 * Este método remove, se possível, um elemento do fim da lista e retorna 1
	 * em caso de sucesso ou um código de erro.
	 */
	int removerFim();
	/**
	 * Este método remove, se possível, de uma posição arbitrária um elemento da
	 * lista e retorna 1 em caso de sucesso ou um código de erro.
	 */
	int remover(int posicao);

	/**
	 * Este método retorna, se possível, o primeiro elemento da lista dupla ou
	 * NULL em caso de erro.
	 */
	Tipo obterInicio();
	/**
	 * Este método retorna se possível o elemento que está no fim da lista dupla
	 * ou NULL em caso de erro.
	 */
	Tipo obterFim();
	/**
	 * Este método retorna, se possível, um elemento de uma posição arbitrária
	 * da lista ou NULL em caso de erro.
	 */
	Tipo obter(int posicao);

	/**
	 * Este método retorna, se possível, um elemento de uma posição arbitrária
	 * da lista ou NULL em caso de erro.
	 */
	Tipo operator[](int posicao);

	/**
	 * Este método recebe uma lista inicializada como parâmetro e inserem ao final
	 * da lista principal todos os elementos da lista enviada via parâmetro. Ao
	 * final da operação retorna 1.
	 */
	int concatenar(Lista<Tipo> *lista);

	/**
	 * Este método ordena os conteúdos da lista conforme o funtor passado no parâmetro
	 * ord.
	 */
	void ordenar(Ordenador *ord);
};

#include "Lista.ipp"

#endif /* LISTA_H_ */
