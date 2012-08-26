package ime.hirata.ep1;

/**
 * @author Pedro Paulo Vezza Campos    NUSP: 7538743
 * @author Daniel Huguenin             NUSP: 5118403
 * @author Antonio Rui Castro Junior   NUSP: 5984327
 * 
 * Esta classe implementa uma lista circular, contendo
 * varias operacoes para a manipulacao da mesma 
 */

public class ListaCircular<T extends Comparable<T>> {

	public int tamanho; /*Contem o numero de elementos da lista*/
	public GenericNode<T> tail; /*Aponta para o ultimo elemento (cauda) da lista*/

	ListaCircular() { /* Construtor de lista vazia */
		tamanho = 0;
	}

	ListaCircular(T elem) { /* Construtor de lista com um elemento */
		tail = new GenericNode<T>(elem);
		tail.setNext(tail);
		tamanho = 1;
	}

   /**
	* Insere um elemento no tail (cauda) da lista
	* @param t um elemento generico                     
	*/
	void Insere(T t) { 
		GenericNode<T> novo = new GenericNode<T>(t);
		if (tail == null) {  /*Caso a lista esteja lista vazia*/
			novo.setNext(novo);
			tail = novo;
		} else {
			novo.setNext(tail.getNext()); /* Seta o proximo do novo para o proximo do tail*/
			tail.setNext(novo);
			tail = novo;
		}
		tamanho++; 
	}
	
	
	/**
	* Insere um novo elemento t apos elemento elem ou apos tail caso nao for encontrado elem na lista
	* @param t um elemento generico                     
	* @param elem um elemento generico
	*/
	void Insere(T t, T elem) {
		GenericNode<T> aux = BuscaElem(elem);

		if (aux == null) { /*Caso a busca por elem resultar em null insere-se o novo elemento t apos tail*/
			Insere(t);
			return;
		}

		GenericNode<T> novo = new GenericNode<T>(t);

		novo.setNext(aux.getNext()); /*Insercao do novo elemento apos elem*/
		aux.setNext(novo);
		if (aux == tail) /* Caso elem for o ultimo elemento da lista, tail aponta para o novo ultimo elemento da lista*/
			tail = tail.getNext();
		tamanho++;

	}

	/**
	* Procura pelo elemento t na lista
	* @param t um elemento generico
	* @return um elemento do tipo generico
	*/
	private GenericNode<T> BuscaElem(T t) {
		GenericNode<T> aux;
		aux = tail;
		
		if (tail == null) /*Lista vazia*/
			return null;
		
		aux = aux.getNext();
		for (int i = 0; i < tamanho; i++) { /*Enquanto nao for excedido o tamanho da lista ou nao for encontrado o elemento t*/
			if (aux.getElement().equals(t))
				return aux; /* Retorna o elemento procurado*/
			else
				aux = aux.getNext();
		}
		return null; /*Elemento t nao foi encontrado*/
	}

   /**
	* Remove a primeira ocorrencia de elem na lista
 	* @param elem um node da lista de tipo generico  
	*/
	void Remove(T elem) {
		GenericNode<T> aux, ant;
		ant = tail.getNext();
		aux = ant.getNext();

		if (tamanho == 0)
			return;

		if ((tamanho == 1) && (tail.getElement().equals(elem))) {
			tail = null;
			tamanho--;
			return;
		}

		for (int i = 0; i < tamanho; i++) {
			if (aux.getElement().equals(elem)) {
				if (aux != tail) {
					ant.setNext(aux.getNext());
				} else {
					ant.setNext(aux.getNext());
					tail = ant;
				}
				tamanho--;
				return;
			}
			ant = ant.getNext();
			aux = ant.getNext();

		}
	}

   /**
	* Remove todos os elementos da lista que forem iguais a elem
  	* @param elem um node da lista de tipo generico                                      
	*/
	void RemoveTodos(T elem) {
		GenericNode<T> aux, ant;
		aux = tail.getNext();
		ant = null;

		if (tamanho == 0)
			return;

		if ((tamanho == 1) && (tail.getElement().equals(elem))) {
			tail = null;
			tamanho = 0;
			return;
		}

		for (int i = 0; i < tamanho && aux != tail; i++) {
			if (aux.getElement().equals(elem)) {
				if(ant == null){
					aux = aux.getNext();
					tail.setNext(aux);
			    }
				else{
					ant.setNext(aux.getNext());
					aux = ant.getNext();
				}
				tamanho--;
			}
			else{
				ant = aux;
				aux = aux.getNext();
			}
		}
		
		if (tail.getElement().equals(elem)){
			aux = tail.getNext();
			tail = ant;
			tail.setNext(aux);
			tamanho--;
		}	
	}

   /**                          
    * Devolve o numero de elementos da lista
    * @return inteiro
    */
	int Tamanho() {
		return tamanho;
	}

	
   /**
    * Devolve o elemento apontado por tail                                     
    * @return Generic elemento 
    */
	T getTail() { 
		return tail.getElement();
	}

   /**
	* Muda o apontador tail para o proximo elemento                                      
	*/
	void nextTail() { 
		tail = tail.getNext();
	}

   /**
	* Ordena a lista                                      
	*/
	void Ordena() {
		boolean swapped = false;

		GenericNode<T> aux = tail.getNext();
		
		do{
			swapped = false;
			for (int i = 0; i < tamanho-1; i++) {
				if (aux.getElement().compareTo(aux.getNext().getElement()) > 0) {
					swapped = true;
					T temp = aux.getElement();
					aux.setElement(aux.getNext().getElement());
					aux.getNext().setElement(temp);
				}
				aux = aux.getNext();
				
			}
			aux = tail.getNext();
		} while(swapped);
		
	}		
		
	/**
	* Cria uma lista de string
	* @return uma lista de string                                      
	*/
	String ToString() {
		StringBuffer saida = new StringBuffer("{ ");

		GenericNode<T> aux = tail.getNext();

		for (int i = 0; i < tamanho && aux != tail; i++) {
			saida.append(aux.getElement().toString() + ", ");
			aux = aux.getNext();
		}
		saida.append(tail.getElement().toString());
		saida.append(" }");

		return saida.toString();
	}
}
