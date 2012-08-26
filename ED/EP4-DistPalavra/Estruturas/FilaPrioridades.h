/**
 * MAC0323 - ESTRUTURAS DE DADOS
 * EP4 - DISTÂNCIA ENTRE PALAVRAS
 * ALUNO: PEDRO PAULO VEZZÁ CAMPOS - 7538743
 *
 * Neste arquivo estão definidos os métodos e atributos do objeto
 * FilaPrioridades (Implementado como min-heap binária)
 * a serem implementados no arquivo FilaPrioridades.cpp.
 */

#ifndef FILAPRIORIDADES_H_
#define FILAPRIORIDADES_H_

#define Vertice int

/**
 * A implementação da fila de prioridades segue o modelo apresentado por Sedgewick e Paulo
 * Feofiloff em http://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/prim.html#heap
 */
class FilaPrioridades {
private:
	/**
	 * Vetor responsável por armazenar a heap binária.
	 */
	Vertice *pq;
	/**
	 * Quantidade de elementos na fila de prioridades.
	 */
	int N;
	/**
	 * Vetor inverso de pq, para cada vértice v, qp[v] é o único índice tal que pq[qp[v]] == v.
	 */
	int *qp;
	/**
	 * Vetor de custos utilizado no cálculo das prioridades.
	 */
	double *custo;

	/**
	 * Função responsável por subir um elemento da posição k na fila de prioridades
	 * até a sua posição correta de acordo com a sua prioridade.
	 */
	void subir(int k);
	/**
	 * Função responsável por rebaixar um elemento da posição k na fila de prioridades
	 * até a sua posição correta de acordo com a sua prioridade.
	 */
	void rebaixar(int k);
	/**
	 * Função responsável por inverter as posições de dois elementos da fila de prioridades.
	 */
	void trocar(int i, int j);

public:
	/**
	 * Construtor do objeto, recebe o tamanho do heap e o vetor de custos.
	 */
	FilaPrioridades(int maxV, double *cost);
	/**
	 * Destrutor do objeto, desaloca o heap, e o vetor inverso qp.
	 */
	virtual ~FilaPrioridades();

	/**
	 * Função responsável por retornar se a fila está vazia.
	 */
	int vazia();
	/**
	 * Função responsável por remover o menor elemento da fila e o retornar.
	 */
	Vertice removerMin();
	/**
	 * Função responsável por decrementar a prioridade de o elemento passado por
	 * parâmetro da fila de prioridades.
	 */
	void decrementar(Vertice w);
	/**
	 * Função responsável por inserir o elemento na fila de prioridades.
	 */
	void inserir(Vertice v);
};

#endif /* FILAPRIORIDADES_H_ */
