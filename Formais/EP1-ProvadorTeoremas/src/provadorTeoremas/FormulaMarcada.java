/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Classe ``Fachada'' do provador. Contém o laço principal do programa e 
 * é responsável por escolher ramos a expandir além de verificar o fechamento
 * e saturação desses ramos. Por fim, realiza as alfa-expansões e beta-expansões.
 */

package provadorTeoremas;

public class FormulaMarcada {

	private boolean marca;
	private Formula formula;

	/**
	 * Construtor privado de uma fórmula marcada
	 * @param marca A marca booleana da fórmula
	 * @param formula A fórmula já parseada.
	 */
	private FormulaMarcada(boolean marca, Formula formula) {
		this.marca = marca;
		this.formula = formula;
	}

	/**
	 * Construtor público de uma fórmula marcada
	 * @param marca A marca booleana da fórmula
	 * @param formula A fórmula a ser parseada.
	 */
	public FormulaMarcada(boolean marca, String formula) {
		this.marca = marca;
		this.formula = Formula.parsearFormula(formula);
	}

	/**
	 * Método getter do atributo marca.
	 * @return O atributo marca
	 */
	public boolean obterMarca() {
		return marca;
	}

	/**
	 * Método getter do atributo formula.
	 * @return O atributo formula
	 */
	public Formula obterFormula() {
		return formula;
	}
	
	/**
	 * Método responsável por informar se a fórmula marcada é alfa.
	 * @return true caso seja regra alfa ou negação, false em caso contrário.
	 */
	public boolean ehRegraAlfa() {
		String operador = formula.obterInfo();

		if (operador.equals(".A.") && marca)
			return true;
		if (operador.equals(".O.") && !marca)
			return true;
		if (operador.equals(".I.") && !marca)
			return true;
		//Computacionalmente é mais interessante dizer que negação é regra alfa
		if (operador.equals(".N."))  
			return true;
		return false;
	}

	/**
	 * Método responsável por informar se a fórmula marcada é beta.
	 * @return true caso seja regra beta (Exceto negação), false em caso contrário.
	 */
	public boolean ehRegraBeta() {
		if (formula.obterTamanho() == 1)
			return false;
		return !ehRegraAlfa();
	}

	/**
	 * Responsável por dividir a fórmula na sua primeira subfórmula com
	 * a marca correta
	 * @return A primeira subfórmula.
	 */
	public FormulaMarcada obterPrimeiraSubformula() {
		if (formula.obterEsq() == null)
			return null;

		String operador = formula.obterInfo();
		boolean novaMarca = false;
		if (ehRegraAlfa()) {
			if (operador.equals(".A.") && marca)
				novaMarca = true;
			else if (operador.equals(".I.") && !marca)
				novaMarca = true;
			else if (operador.equals(".N.") && !marca)
				novaMarca = true;
		} else {
			if (operador.equals(".O.") && marca)
				novaMarca = true;
		}

		return new FormulaMarcada(novaMarca, formula.obterEsq());

	}

	/**
	 * Responsável por dividir a fórmula na sua segunda subfórmula com
	 * a marca correta
	 * @return A segunda subfórmula.
	 */
	public FormulaMarcada obterSegundaSubformula() {
		if (formula.obterDir() == null)
			return null;

		String operador = formula.obterInfo();
		boolean novaMarca = false;
		if (ehRegraAlfa()) {
			if (operador.equals(".A.") && marca)
				novaMarca = true;
			else if (operador.equals(".N.") && !marca)
				novaMarca = true;
		} else {
			novaMarca = true;
			if (operador.equals(".A.") && !marca)
				novaMarca = false;
		}

		return new FormulaMarcada(novaMarca, formula.obterDir());

	}

	/**
	 * Método responsável por fornecer o tamanho da fórmula marcada.
	 * @return O tamanho da fórmula
	 */
	public int obterTamanho() {
		return formula.obterTamanho();
	}
	
	/**
	 * Método responsável por verificar se uma outra fórmula é conjugada desta.
	 * @param outra A outra subfórmula a ser analisada.
	 * @return true caso a sejam conjugadas, false em caso contrário.
	 */
	public boolean ehFormulaConjugada(FormulaMarcada outra){
		if(marca != outra.obterMarca() && formula.equals(outra.obterFormula()))
			return true;
		return false;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((formula == null) ? 0 : formula.hashCode());
		result = prime * result + (marca ? 1231 : 1237);
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		FormulaMarcada other = (FormulaMarcada) obj;
		if (formula == null) {
			if (other.formula != null)
				return false;
		} else if (!formula.equals(other.formula))
			return false;
		if (marca != other.marca)
			return false;
		return true;
	}
	
	public String toString(){
		return (marca ? "T" : "F") + formula.toString();
	}
	
}
