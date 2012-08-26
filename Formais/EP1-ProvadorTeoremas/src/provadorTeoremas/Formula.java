/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Esta classe representa a uma fórmula da lógica proposicional na forma
 * de uma árvore binária de operadores.
 */

package provadorTeoremas;

import java.util.List;

public class Formula {

	private String info;
	private Formula dir;
	private Formula esq;
	private static int pos;

	/**
	 * Construtor de uma nó de uma fórmula com o campo info determinado. 
	 * @param info O valor do campo info (Ex: p, q, .I., .A. etc.)
	 */
	public Formula(String info) {
		this.info = info;
	}

	/**
	 * Construtor de nó de uma fórmula sem campo info determinado.
	 */
	public Formula() {
	}

	/**
	 * Método público de parseamento de uma fórmula.
	 * @param formula A fórmula a ser parseada (Parentetizada e bem formada).
	 * @return Uma árvore binária representando a fórmula passada por parâmetro.
	 */
	public static Formula parsearFormula(String formula) {
		pos = 0;
		return parsearFormulaRec(formula.substring(1, formula.length() - 1));
	}

	/**
	 * Método recursivo de parseamento de uma fórmula
	 * @param formula A fórmula a ser parseada sem os parênteses exteriores
	 * @return Uma (sub) fórmula representando a fórmula (ou parte dela) passada
	 * por parâmetro.
	 */
	private static Formula parsearFormulaRec(String formula) {
		Formula nodo = new Formula();
		while(formula.charAt(pos) == ' ')
			pos++;
		
		if (formula.charAt(pos) == '(') {
			pos++;
			nodo.alterarEsq(parsearFormulaRec(formula));
		} else if (formula.length() == 1) {
			nodo.alterarInfo(formula);
			return nodo;
		} else if (Character.isLowerCase(formula.charAt(pos))) {
			nodo.alterarEsq(new Formula(formula.substring(pos, pos + 1)));
		} else if (formula.charAt(pos) == '.') {
			nodo.alterarInfo(formula.substring(pos, pos + 3));
			pos += 2;
		}

		do {
			pos++;
		} while (formula.charAt(pos) == ' ');

		if (formula.charAt(pos) == '.') {
			nodo.alterarInfo(formula.substring(pos, pos + 3));
			pos += 2;
		} else if (Character.isLowerCase(formula.charAt(pos))) {
			// Captura (.N. p)
			nodo.alterarEsq(new Formula(formula.substring(pos, pos + 1))); 
		}

		do {
			if (formula.charAt(pos) != '(')
				pos++;
		} while (pos < formula.length() && formula.charAt(pos) == ' ');

		if (pos == formula.length() || formula.charAt(pos) == ')')
			return nodo;

		if (formula.charAt(pos) == '(') {
			pos++;
			if (nodo.info != null && nodo.obterInfo().equals(".N."))
				nodo.alterarEsq(parsearFormulaRec(formula));
			else
				nodo.alterarDir(parsearFormulaRec(formula));
		} else if (Character.isLowerCase(formula.charAt(pos)))
			nodo.alterarDir(new Formula(formula.substring(pos, pos + 1)));
		pos++;

		return nodo;
	}

	/**
	 * Grava no parâmetro um percurso inordem da fórmula enraizada pelo nó
	 * que teve o método invocado pela primeira vez.
	 * @param lista A lista onde será gravado o percurso.
	 */
	public void inordem(List<String> lista) {
		if (esq != null)
			esq.inordem(lista);
		lista.add(info);
		if (dir != null)
			dir.inordem(lista);
	}

	/**
	 * Grava no parâmetro um percurso preordem da fórmula enraizada pelo nó
	 * que teve o método invocado pela primeira vez.
	 * @param lista A lista onde será gravado o percurso.
	 */
	public void preordem(List<String> lista) {
		lista.add(info);
		if (esq != null)
			esq.preordem(lista);
		if (dir != null)
			dir.preordem(lista);
	}

	/**
	 * Grava no parâmetro um percurso posordem da fórmula enraizada pelo nó
	 * que teve o método invocado pela primeira vez.
	 * @param lista A lista onde será gravado o percurso.
	 */
	public void posordem(List<String> lista) {
		if (esq != null)
			esq.posordem(lista);
		if (dir != null)
			dir.posordem(lista);
		lista.add(info);
	}

	/**
	 * Retorna o tamanho da fórmula enraizada pelo nó que teve o método invocado
	 * pela primeira vez.
	 * @return O tamanho da fórmula.
	 */
	public int obterTamanho() {
		int tamanho = 1;
		if (esq != null)
			tamanho += esq.obterTamanho();
		if (dir != null)
			tamanho += dir.obterTamanho();
		return tamanho;
	}

	/**
	 * Método getter do atributo dir.
	 * @return O atributo dir.
	 */
	public Formula obterDir() {
		return dir;
	}
	
	/**
	 * Método setter do atributo dir.
	 * @return O atributo dir.
	 */
	public void alterarDir(Formula dir) {
		this.dir = dir;
	}

	/**
	 * Método getter do atributo esq.
	 * @return O atributo esq.
	 */
	public Formula obterEsq() {
		return esq;
	}

	/**
	 * Método setter do atributo esq.
	 * @return O atributo esq.
	 */
	public void alterarEsq(Formula esq) {
		this.esq = esq;
	}

	/**
	 * Método getter do atributo info.
	 * @return O atributo info.
	 */
	public String obterInfo() {
		return info;
	}

	/**
	 * Método setter do atributo info.
	 * @return O atributo info.
	 */
	public void alterarInfo(String info) {
		this.info = info;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((dir == null) ? 0 : dir.hashCode());
		result = prime * result + ((esq == null) ? 0 : esq.hashCode());
		result = prime * result + ((info == null) ? 0 : info.hashCode());
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
		Formula other = (Formula) obj;
		if (dir == null) {
			if (other.dir != null)
				return false;
		} else if (!dir.equals(other.dir))
			return false;
		if (esq == null) {
			if (other.esq != null)
				return false;
		} else if (!esq.equals(other.esq))
			return false;
		if (info == null) {
			if (other.info != null)
				return false;
		} else if (!info.equals(other.info))
			return false;
		return true;
	}

	public String toString() {
		StringBuilder sb = new StringBuilder();
		if (esq != null || dir != null)
			sb.append("(");
		if (!info.equals(".N.")) {
			if (esq != null)
				sb.append(esq.toString() + " ");
			sb.append(info);
		} else {
			sb.append(info + " " + esq.toString());
		}
		if (dir != null)
			sb.append(" " + dir.toString());
		if (esq != null || dir != null)
			sb.append(")");
		return sb.toString();

	}

}
