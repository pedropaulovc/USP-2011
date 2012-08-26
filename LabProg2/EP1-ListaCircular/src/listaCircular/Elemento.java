package listaCircular;


class Elemento<E> {

	private E info;
	private Elemento<E> prox;

	public Elemento(E info, Elemento<E> prox) {
		this.info = info;
		this.prox = prox;
	}

	public Elemento<E> getProx() {
		return prox;
	}

	public void setProx(Elemento<E> prox) {
		this.prox = prox;
	}

	public E getInfo() {
		return info;
	}

}
