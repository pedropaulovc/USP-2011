/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Esta classe contém o método main() do programa além de servir como interface
 * com o usuário.
 */

package provadorTeoremas;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.Stack;

public class ProvadorTeoremas {

	private Stack<Ramo> pilhaRamos;
	private List<Boolean> betas;
	private List<FormulaMarcada> ramo;
	private boolean debug = false;

	/**
	 * Método responsável por inicializar as estruturas de dados a serem utilizadas 
	 * na prova e popular o ramo com as premissas e conclusões devidamente marcados.
	 * @param premissas Uma lista de premissas a serem inseridas no ramo
	 * @param conclusoes Uma lista de conclusões a serem inseridas no ramo
	 */
	private void inicializar(List<String> premissas, List<String> conclusoes) {
		pilhaRamos = new Stack<Ramo>();
		betas = new ArrayList<Boolean>();
		ramo = new ArrayList<FormulaMarcada>();

		FormulaMarcada atual;
		for (String p : premissas) {
			if(p.length() == 0)
				continue;
			atual = new FormulaMarcada(true, p);
			if (debug)
				System.out.println("Prem: " + atual);
			ramo.add(atual);
			betas.add(atual.ehRegraBeta());
		}

		for (String c : conclusoes) {
			if(c.length() == 0)
				continue;
			atual = new FormulaMarcada(false, c);
			if (debug)
				System.out.println("Conc: " + atual);
			ramo.add(atual);
			betas.add(atual.ehRegraBeta());
		}
	}

	/**
	 * Método principal para a prova de um sequente.
	 * @param premissas Vetor de premissas do sequente
	 * @param conclusoes Vetor de conclusões do sequente
	 * @return Um objeto Resultado com campo valido == true se sequente válido ou
	 * valido == false e um contra-exemplo no campo contraExemplo em caso contrário.
	 */
	public Resultado provar(String[] premissas, String[] conclusoes) {
		return provar(Arrays.asList(premissas), Arrays.asList(conclusoes));
	}

	/**
	 * Método principal para a prova de um sequente.
	 * @param premissas Lista de premissas do sequente
	 * @param conclusoes Lista de conclusões do sequente
	 * @return Um objeto Resultado com campo valido == true se sequente válido ou
	 * valido == false e um contra-exemplo no campo contraExemplo em caso contrário.
	 */
	public Resultado provar(List<String> premissas, List<String> conclusoes) {
		if (premissas.size() == 0 && conclusoes.size() == 0)
			return new Resultado(true);

		inicializar(premissas, conclusoes);

		boolean ramoFechado = verificarFechamento();
		while (!pilhaRamos.empty() || !ramoFechado) {
			if (debug){
				System.out.println("Início laço: " + ramo);
				System.out.println("Betas: " + betas);
			}
				
			while (ramoFechado && !pilhaRamos.empty()) {
				obterNovoRamo();
				ramoFechado = verificarFechamento();
			}

			if (verificarSaturacao() && !ramoFechado)
				return new Resultado(false, gerarContraExemplo());

			expandirAlfa();
			if (debug)
				System.out.println("Após alfa: " + ramo + "\n" + "Betas: " + betas);

			expandirBeta();
			if (debug) {
				System.out.println("Após beta: " + ramo + "\n" + "Betas: " + betas);
				System.out.println("Pilha: " + pilhaRamos + "\n");
			}

			ramoFechado = verificarFechamento();
		}

		return new Resultado(true);
	}

	/**
	 * Método responsável por transformar um ramo saturado e aberto em um contra-exemplo
	 * a ser apresentado ao usuário. 
	 * @return Um conjunto de átomos marcados representando um contra-exemplo.
	 */
	private Set<FormulaMarcada> gerarContraExemplo() {
		Set<FormulaMarcada> contraExemplo = new HashSet<FormulaMarcada>();

		for (FormulaMarcada f : ramo) {
			if (f.obterTamanho() == 1)
				contraExemplo.add(f);
		}

		return contraExemplo;
	}

	/**
	 * Método responsável por desempilhar um ramo da pilhaRamos e alterar
	 * as estruturas de dados de forma a tornar o ramo desempilhado o atual.
	 */
	private void obterNovoRamo() {
		Ramo novo = pilhaRamos.pop();
		betas = novo.obterBetas();

		for (int i = ramo.size() - 1; i >= novo.obterTamAtual(); i--)
			ramo.remove(i);

		FormulaMarcada beta2 = novo.obterBeta2();

		ramo.add(beta2);
		betas.add(beta2.ehRegraBeta());
		if (debug)
			System.out.println("\nNovo ramo: " + ramo);
	}

	/**
	 * Método responsável por realizar o máximo possível de expansões alfa no
	 * ramo atual.
	 */
	private void expandirAlfa() {
		FormulaMarcada subformula;
		boolean expandiu;

		List<FormulaMarcada> inseridas = new ArrayList<FormulaMarcada>();
		List<FormulaMarcada> removidas = new ArrayList<FormulaMarcada>();
		
		do {
			expandiu = false;
			int tamRamo = ramo.size();
			
			for (int i = 0; i < tamRamo; i++) {
				FormulaMarcada f = ramo.get(i);
				if (f.ehRegraBeta()	|| f.obterTamanho() == 1)
					continue;
				
				removidas.add(f);

				subformula = f.obterPrimeiraSubformula();
				inseridas.add(subformula);

				subformula = f.obterSegundaSubformula();
				if (subformula != null) {
					inseridas.add(subformula);
				}
				expandiu = true;
			}

			for(FormulaMarcada f : inseridas){
				betas.add(f.ehRegraBeta());
				ramo.add(f);
			}
						
			for(FormulaMarcada f : removidas){
				betas.remove(ramo.indexOf(f));
				ramo.remove(f);
			}
			
			inseridas.clear();
			removidas.clear();
			
		} while (expandiu);
	}

	/**
	 * Método responsável por realizar uma expansão beta possível, empilhando um
	 * ramo na pilhaRamos ou nada caso não haja expansões possíveis.
	 */
	private void expandirBeta() {
		int i;
		for (i = betas.size() - 1; i >= 0; i--)
			if (betas.get(i))
				break;
		if (i == -1)
			return;

		FormulaMarcada escolhida = ramo.get(i);

		betas.set(i, false);

		FormulaMarcada subformula1 = escolhida.obterPrimeiraSubformula();
		FormulaMarcada subformula2 = escolhida.obterSegundaSubformula();

		int tamAntes = ramo.size();
		List<Boolean> betasAntes = new ArrayList<Boolean>(betas);

		ramo.add(subformula1);
		betas.add(subformula1.ehRegraBeta());

		Ramo empilha = new Ramo(subformula2, tamAntes, betasAntes);
		pilhaRamos.push(empilha);
	}

	/**
	 * Método responsável por verificar se o ramo está fechado.
	 * @return true caso o ramo esteja fechado e false em caso contrário.
	 */
	private boolean verificarFechamento() {
		for (int i = 0; i < ramo.size(); i++) {
			for (int j = i + 1; j < ramo.size(); j++) {
				if (ramo.get(i).ehFormulaConjugada(ramo.get(j)))
					return true;
			}
		}

		return false;
	}

	/**
	 * Método responsável por verificar se o ramo está saturado.
	 * @return true caso o ramo esteja saturado e false em caso contrário.
	 */
	private boolean verificarSaturacao() {
		for (int i = 0; i < ramo.size(); i++){
			FormulaMarcada f = ramo.get(i);
			if(f.obterTamanho() != 1 && (f.ehRegraAlfa() || betas.get(i)))
				return false;
		}
		return true;
	}

	/**
	 * Método responsável por definir se devem ser exibidas na saída padrão
	 * informações de debug
	 * @param true caso queira informações de debug ou false em caso contrário.
	 */
	public void definirModoDebug(boolean debug) {
		this.debug = debug;
	}

}
