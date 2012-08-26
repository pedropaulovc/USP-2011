package ime.hirata.ep1;

/**
 * @author Pedro Paulo Vezza Campos    NUSP: 7538743
 * @author Daniel Huguenin             NUSP: 5118403
 * @author Antonio Rui Castro Junior   NUSP: 5984327
 * 
 * Esta classe constroi os nodes da lista circular do tipo generic, contendo
 * operacoes para manipulacao dos nodes 
 */

public class GenericNode<T> {

	private GenericNode<T> prox;
	private T elemento;
	
   /**
	* Construtor de node vazio 
	*/
	public GenericNode(){ 
		prox = null;
		elemento = null;
	}

   /**
	* Construtor de node já com elemento
	* @param elem  um elemento do tipo generico
	*/
	public GenericNode(T elem){ 
		prox = null;
		this.elemento = elem;
	}
	
   /**
	* Seta o apontador do node para o proximo elemento
	* @param  node  um node da lista
	*/
	public void setNext(GenericNode<T> node){ 
		prox = node;
	}
	
   /**
	* Retorna o apontador do node para o proximo elemento
	* @return proximo elemento da lista
	*/
	public GenericNode<T> getNext(){ 
		return prox;
	}
	
   /**
	* Retorna o conteudo do Node 
	*/
	public T getElement(){
		return elemento;
	}
	
   /**
	* Modifica o conteudo do Node
	* @param elem um elemento generico 
	*/
	public void setElement(T elem){
		this.elemento = elem;
	}
}
