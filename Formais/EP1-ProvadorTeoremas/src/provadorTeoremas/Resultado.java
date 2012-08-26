/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Classe que encapsula o resultado booleano da prova do sequente além de possivelmente 
 * um contra-exemplo para um sequente falsificável.
 */

package provadorTeoremas;

import java.util.HashSet;
import java.util.Set;

public class Resultado {
	private boolean valido;
	private Set<FormulaMarcada> contraExemplo;
	
	/**
	 * Método construtor do objeto Resultado.
	 * @param valido true caso o sequente seja válido e false em caso contrário.
	 * @param ramo Um contra-exemplo caso o sequente seja falsificável ou null caso
	 * o sequente seja válido.
	 */
	public Resultado(boolean valido, Set<FormulaMarcada> ramo){
		this.valido = valido;
		this.contraExemplo = ramo;
	}

	/**
	 * Método construtor do objeto Resultado
	 * @param valido true caso o sequente seja válido e false em caso contrário.
	 * @param ramo Um contra-exemplo em forma de string caso o sequente seja
	 * falsificável ou null caso o sequente seja válido.
	 */
	public Resultado(boolean valido, String ramo){
		this.valido = valido;
		this.contraExemplo = new HashSet<FormulaMarcada>();
		
		for(String elemento : ramo.split("\\s*,\\s*")){
			boolean marca = elemento.charAt(0) == 'T' ? true : false;
			contraExemplo.add(new FormulaMarcada(marca, elemento.substring(1)));
		}
	}
	
	/**
	 * Método construtor do objeto Resultado
	 * @param valido true caso o sequente seja válido e false em caso contrário.
	 */
	public Resultado(boolean valido) {
		this.valido = valido;
	}

	/**
	 * Método getter do atributo valido
	 * @return O atributo valido
	 */
	public boolean ehValido() {
		return valido;
	}

	/**
	 * Método getter do atributo contraExemplo
	 * @return O atributo contraExemplo
	 */
	public Set<FormulaMarcada> obterContraExemplo() {
		return contraExemplo;
	}
	
	public String toString(){
		if(valido)
			return "Sequente válido";
		return "Sequente inválido. Contra-exemplo: " + contraExemplo.toString();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result
				+ ((contraExemplo == null) ? 0 : contraExemplo.hashCode());
		result = prime * result + (valido ? 1231 : 1237);
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
		Resultado other = (Resultado) obj;
		if (contraExemplo == null) {
			if (other.contraExemplo != null)
				return false;
		} else if (!contraExemplo.equals(other.contraExemplo))
			return false;
		if (valido != other.valido)
			return false;
		return true;
	}
	
	
}
