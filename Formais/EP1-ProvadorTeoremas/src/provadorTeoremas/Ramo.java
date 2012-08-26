/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Classe responsável por encapsular os dados a serem armazenados na pilha
 * de ramos conforme descrito no exemplo de implementação apresentado pela 
 * professora, ou seja, o tamanho do ramo no momento da expansão, a segunda 
 * fórmula $\beta$ da expansão e o vetor de regras $\beta$ ainda por serem 
 * expandidas quando o programa retornar a esse	ramo.
 */

package provadorTeoremas;

import java.util.List;

public class Ramo {
	private FormulaMarcada beta2;
	private int tamAtual;
	private List<Boolean> betas;
	
	/**
	 * Método construtor do Ramo.
	 * @param beta2 A segunda fórmula marcada da expansão beta.
	 * @param tamAtual O tamanho do ramo no momento da expansão.
	 * @param betas O vetor betas no momento da expansão.
	 */
	public Ramo(FormulaMarcada beta2, int tamAtual, List<Boolean> betas){
		this.beta2 = beta2;
		this.tamAtual = tamAtual;
		this.betas = betas;
	}

	/**
	 * Método getter do campo beta2
	 * @return O campo beta2
	 */
	public FormulaMarcada obterBeta2() {
		return beta2;
	}

	/**
	 * Método getter do campo tamAtual
	 * @return O campo tamAtual
	 */	
	public int obterTamAtual() {
		return tamAtual;
	}

	/**
	 * Método getter do campo betas
	 * @return O campo betas
	 */
	public List<Boolean> obterBetas() {
		return betas;
	}
	
	public String toString(){
		return "<" + beta2 + ", " + tamAtual + ", " + betas + ">";
	}
}
