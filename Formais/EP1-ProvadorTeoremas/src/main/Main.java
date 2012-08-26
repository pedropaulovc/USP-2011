/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Esta classe contém o método main() do programa além de servir como interface
 * com o usuário.
 */

package main;

import java.util.Scanner;

import provadorTeoremas.ProvadorTeoremas;
import provadorTeoremas.Resultado;

public class Main {
	
	/**
	 * Método main() do programa responsável pela interface com o usuário.
	 * @param args Argumentos de linha de comando
	 */
	public static void main(String[] args){
		Scanner scanner = new Scanner(System.in);
		ProvadorTeoremas provador = new ProvadorTeoremas();
		
		String sequente;
		while(!(sequente = scanner.nextLine()).equals("#")){
			String[] sequenteDividido = sequente.split("\\s*#\\s*");
			String[] premissas = sequenteDividido[0].split("\\s*,\\s*");
			String[] conclusoes = sequenteDividido[1].split("\\s*,\\s*");
			
			Resultado resultado = provador.provar(premissas, conclusoes);
			
			if(resultado.ehValido()){
				System.out.println("Sequente válido");
			} else {
				System.out.print("Sequente inválido. ");
				System.out.println("Contra-exemplo: " + resultado.obterContraExemplo());
			}
		}
	}
}
