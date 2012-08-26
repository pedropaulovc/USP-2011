/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Classe de testes unitários de FormulaMarcada.
 */


package testesUnitarios;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import org.junit.Test;

import provadorTeoremas.FormulaMarcada;

public class TestesFormulaMarcada {

	String[] entradas = { 
		"(p .A. q)",
		"(p .O. q)",
		"(p .I. q)",
	};
	
	FormulaMarcada[] subformula1MarcaTrue = { 
		new FormulaMarcada(true, "(p)"),
		new FormulaMarcada(true, "(p)"),
		new FormulaMarcada(false, "(p)"),
	}; 
		
	FormulaMarcada[] subformula1EsperadaMarcaFalse = { 
		new FormulaMarcada(false, "(p)"),
		new FormulaMarcada(false, "(p)"),
		new FormulaMarcada(true, "(p)"),
	};
	
	FormulaMarcada[] subformula2MarcaTrue = { 
		new FormulaMarcada(true, "(q)"),
		new FormulaMarcada(true, "(q)"),
		new FormulaMarcada(true, "(q)"),
	}; 
			
	FormulaMarcada[] subformula2EsperadaMarcaFalse = { 
		new FormulaMarcada(false, "(q)"),
		new FormulaMarcada(false, "(q)"),
		new FormulaMarcada(false, "(q)"),
	};
		
	
	//Assumindo que as marcas são sempre true.
	boolean[] ehAlfa = {true, false, false};
	
	/**
	 * Teste unitário do método ehRegraAlfa()
	 */
	@Test
	public void testarEhRegraAlfa() {
		FormulaMarcada f;
		
		for(int i = 0; i < entradas.length; i++){
			f = new FormulaMarcada(true, entradas[i]);
			assertEquals(ehAlfa[i], f.ehRegraAlfa());
			
			f = new FormulaMarcada(false, entradas[i]);
			assertEquals(!ehAlfa[i], f.ehRegraAlfa());
		}
		
		//Computacionalmente é mais interessante considerar negação como alfa
		assertEquals(true, new FormulaMarcada(true, "(.N. p)").ehRegraAlfa());
		assertEquals(true, new FormulaMarcada(false, "(.N. p)").ehRegraAlfa());
	}

	/**
	 * Teste unitário do método ehRegraBeta()
	 */
	@Test
	public void testarEhRegraBeta() {
		FormulaMarcada f;
		
		for(int i = 0; i < entradas.length; i++){
			f = new FormulaMarcada(true, entradas[i]);
			assertEquals(!ehAlfa[i], f.ehRegraBeta());
			
			f = new FormulaMarcada(false, entradas[i]);
			assertEquals(ehAlfa[i], f.ehRegraBeta());
		}
		
		//Computacionalmente é mais interessante considerar negação como alfa
		assertEquals(false, new FormulaMarcada(true, "(.N. p)").ehRegraBeta());
		assertEquals(false, new FormulaMarcada(false, "(.N. p)").ehRegraBeta());
	}

	
	/**
	 * Teste unitário do método obterPrimeiraSubformula()
	 */
	@Test
	public void testarObterPrimeiraSubformula(){
		FormulaMarcada formula;
		for(int i = 0; i < entradas.length; i++){
			formula = new FormulaMarcada(true, entradas[i]);
			assertEquals(subformula1MarcaTrue[i], formula.obterPrimeiraSubformula());
			
			formula = new FormulaMarcada(false, entradas[i]);
			assertEquals(subformula1EsperadaMarcaFalse[i], formula.obterPrimeiraSubformula());
		}
		
		formula = new FormulaMarcada(true, "(.N. p)");
		assertEquals(new FormulaMarcada(false, "(p)"), formula.obterPrimeiraSubformula());
		formula = new FormulaMarcada(false, "(.N. p)");
		assertEquals(new FormulaMarcada(true, "(p)"), formula.obterPrimeiraSubformula());
	}
	
	/**
	 * Teste unitário do método obterSegundaSubformula()
	 */
	@Test
	public void testarObterSegundaSubformula(){
		FormulaMarcada formula;
		for(int i = 0; i < entradas.length; i++){
			formula = new FormulaMarcada(true, entradas[i]);
			assertEquals(subformula2MarcaTrue[i], formula.obterSegundaSubformula());
			
			formula = new FormulaMarcada(false, entradas[i]);
			assertEquals(subformula2EsperadaMarcaFalse[i], formula.obterSegundaSubformula());
		}
		
		formula = new FormulaMarcada(true, "(.N. p)");
		assertNull(formula.obterSegundaSubformula());
		formula = new FormulaMarcada(false, "(.N. p)");
		assertNull(formula.obterSegundaSubformula());
	}
}
