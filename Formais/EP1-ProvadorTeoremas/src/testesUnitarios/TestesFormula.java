/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Classe de testes unitários de Formula.
 */

package testesUnitarios;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;

import java.util.ArrayList;
import java.util.List;

import org.junit.Test;

import provadorTeoremas.Formula;

public class TestesFormula {

	String[] entradas = { 
			"((p .A. q) .O. ((.N. r) .X. s))",
			"((p.A.q).O.((.N.r).X.s))",
			"(p .I. q)",
			"(p .A. q)",
			"(p .O. q)",
			"(.N. p)",
			"(p)", 
			"(((a .O. b) .I. q) .A. (.N. s))",
			"(((.N. q) .I. (.N. p)) .I. (p .I. q))",
			"(((.N. p) .I. (.N. q)) .I. (p .I. q))",
			"((p .I. q) .I. (p .I. (q .O. r)))",
			"((p .I. q) .I. (p .I. (q .A. r)))",
			"((.N. (p .A. q)) .I. ((.N. p) .A. (.N. q)))",
			"((.N. (p .O. q)) .I. ((.N. p) .O. (.N. q)))",
			"((p .O. q) .I. ((.N. q) .I. p))",
			"((p .I. q) .I. (q .I. p))",
			"((p .I. q) .I. ((.N. q) .I. (.N. p)))",
			"(p .I. p)",
			"((p .I. q) .I. ((r .I. p) .I. (r .I. p)))",
			"((p .I. (q .I. r)) .I. (q .I. (p .I. r)))",
			"((p .I. (p .I. q)) .I. (p .I. q))",
			"((p .I. (q .I. r)) .I. ((p .I. q) .I. (p .I. r)))",
			"(p .I. (q .I. p))",
			"(((p .I. q) .I. p) .I. p)", 
			};

	String[][] preordem = { 
			{ ".O.", ".A.", "p", "q", ".X.", ".N.", "r", "s" },
			{ ".O.", ".A.", "p", "q", ".X.", ".N.", "r", "s" },
			{ ".I.", "p", "q" },
			{ ".A.", "p", "q" },
			{ ".O.", "p", "q" },
			{ ".N.", "p"},
			{ "p" }, 
			{ ".A.", ".I.", ".O.", "a", "b", "q", ".N.", "s" },
			{ ".I.", ".I.", ".N.", "q", ".N.", "p", ".I.", "p", "q" },
			{ ".I.", ".I.", ".N.", "p", ".N.", "q", ".I.", "p", "q" },
			{ ".I.", ".I.", "p", "q", ".I.", "p", ".O.", "q", "r" },
			{ ".I.", ".I.", "p", "q", ".I.", "p", ".A.", "q", "r" },
			{ ".I.", ".N.", ".A.", "p", "q", ".A.", ".N.", "p", ".N.", "q" },
			{ ".I.", ".N.", ".O.", "p", "q", ".O.", ".N.", "p", ".N.", "q" },
			{ ".I.", ".O.", "p", "q", ".I.", ".N.", "q", "p" },
			{ ".I.", ".I.", "p", "q", ".I.", "q", "p" },
			{ ".I.", ".I.", "p", "q", ".I.", ".N.", "q", ".N.", "p" },
			{ ".I.", "p", "p" },
			{ ".I.", ".I.", "p", "q", ".I.", ".I.", "r", "p", ".I.", "r", "p" },
			{ ".I.", ".I.", "p", ".I.", "q", "r", ".I.", "q", ".I.", "p", "r" },
			{ ".I.", ".I.", "p", ".I.", "p", "q", ".I.", "p", "q" },
			{ ".I.", ".I.", "p", ".I.", "q", "r", ".I.", ".I.", "p", "q", ".I.", "p", "r" },
			{ ".I.", "p", ".I.", "q", "p" },
			{ ".I.", ".I.", ".I.", "p", "q", "p", "p" } };

	String[][] inordem = { 
			{ "p", ".A.", "q", ".O.", "r", ".N.", ".X.", "s" },
			{ "p", ".A.", "q", ".O.", "r", ".N.", ".X.", "s" },
			{ "p", ".I.", "q" },
			{ "p", ".A.", "q" },
			{ "p", ".O.", "q" },
			{ "p", ".N." },
			{ "p" },
			{ "a", ".O.", "b", ".I.", "q", ".A.", "s", ".N." },
			{ "q", ".N.", ".I.", "p", ".N.", ".I.", "p", ".I.", "q" }, 
			{ "p", ".N.", ".I.", "q", ".N.", ".I.", "p", ".I.", "q" }, 
			{ "p", ".I.", "q", ".I.", "p", ".I.", "q", ".O.", "r" }, 
			{ "p", ".I.", "q", ".I.", "p", ".I.", "q", ".A.", "r" },
			{ "p", ".A.", "q", ".N.", ".I.", "p", ".N.", ".A.", "q", ".N." }, 
			{ "p", ".O.", "q", ".N.", ".I.", "p", ".N.", ".O.", "q", ".N." }, 
			{ "p", ".O.", "q", ".I.", "q", ".N.", ".I.", "p" }, 
			{ "p", ".I.", "q", ".I.", "q", ".I.", "p" }, 
			{ "p", ".I.", "q", ".I.", "q", ".N.", ".I.", "p", ".N." }, 
			{ "p", ".I.", "p" }, 
			{ "p", ".I.", "q", ".I.", "r", ".I.", "p", ".I.", "r", ".I.", "p" }, 
			{ "p", ".I.", "q", ".I.", "r", ".I.", "q", ".I.", "p", ".I.", "r" }, 
			{ "p", ".I.", "p", ".I.", "q", ".I.", "p", ".I.", "q" }, 
			{ "p", ".I.", "q", ".I.", "r", ".I.", "p", ".I.", "q", ".I.", "p", ".I.", "r" }, 
			{ "p", ".I.", "q", ".I.", "p" }, 
			{ "p", ".I.", "q", ".I.", "p", ".I.", "p" } };

	int[] tamanhos = { 8, 8, 3, 3, 3, 2, 1, 8, 9, 9, 9, 9, 10, 10, 8, 7, 9, 3, 11, 11, 9, 13, 5, 7 };

	/**
	 * Teste unitário do método parsearFormula()
	 */
	@Test
	public void testarParsearFormula() {
		List<String> resultado = new ArrayList<String>();

		for (int i = 0; i < entradas.length; i++) {
			Formula f = Formula.parsearFormula(entradas[i]);
			f.preordem(resultado);
			assertArrayEquals(preordem[i], resultado.toArray());

			resultado.clear();

			f.inordem(resultado);
			assertArrayEquals(inordem[i], resultado.toArray());

			resultado.clear();
		}
	}

	/**
	 * Teste unitário do método obterTamanho()
	 */
	@Test
	public void testarObterTamanho() {
		for (int i = 0; i < entradas.length; i++) {
			Formula f = Formula.parsearFormula(entradas[i]);
			assertEquals(tamanhos[i], f.obterTamanho());
		}
	}

}
