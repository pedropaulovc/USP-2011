/**
 * EP1 - Provador Teoremas
 * @author Pedro Paulo Vezzá Campos
 * @author Ana Luísa Losnak
 * @author Daniel Moraes Huguenin
 * 
 * Classe de testes unitários de ProvadorTeoremas.
 */

package testesUnitarios;

import static org.junit.Assert.assertEquals;

import org.junit.Test;

import provadorTeoremas.ProvadorTeoremas;
import provadorTeoremas.Resultado;

public class TestesProvadorTeoremas {

	String[][][] sequentes = { 
/* 0*/		{ { "(p .I. q)", "(p)" }, { "(q)" } },
/* 1*/		{ { "(p .I. q)", "(q)" }, { "(p)" } }, 
/* 2*/		{ { "(p .I. q)", "(.N. p)" }, { "(.N. q)" } },
/* 3*/		{ { "(p .I. q)", "(.N. q)" }, { "(.N. p)" } },
/* 4*/		{ { "(a .O. z)", "(a .I. (b .O. y))", "(z .I. (b .O. y))", "(b .I. (c .O. x))", "(y .I. (c .O. x))"}, { "(c .O. x)" } },
/* 5*/		{ {}, {"(((a .O. b) .I. q) .A. (.N. s))", } },
/* 6*/		{ {}, {"(((.N. q) .I. (.N. p)) .I. (p .I. q))", } },
/* 7*/		{ {}, {"(((.N. p) .I. (.N. q)) .I. (p .I. q))", } },
/* 8*/		{ {}, {"((p .I. q) .I. (p .I. (q .O. r)))", } },
/* 9*/		{ {}, {"((p .I. q) .I. (p .I. (q .A. r)))", } },
/*10*/		{ {}, {"((.N. (p .A. q)) .I. ((.N. p) .A. (.N. q)))", } },
/*11*/		{ {}, {"((.N. (p .O. q)) .I. ((.N. p) .O. (.N. q)))", } },
/*12*/		{ {}, {"((.N. (p .A. q)) .I. ((.N. p) .O. (.N. q)))", } },
/*13*/		{ {}, {"((.N. (p .O. q)) .I. ((.N. p) .A. (.N. q)))", } },
/*14*/		{ {}, {"((p .O. q) .I. ((.N. q) .I. p))", } },
/*15*/		{ {}, {"((p .I. q) .I. (q .I. p))", } },
/*16*/		{ {}, {"((p .I. q) .I. ((.N. q) .I. (.N. p)))", } },
/*17*/		{ {}, {"(p .I. p)", } },
/*18*/		{ {}, {"((p .I. q) .I. ((r .I. p) .I. (r .I. p)))", } },
/*19*/		{ {}, {"((p .I. (q .I. r)) .I. (q .I. (p .I. r)))", } },
/*20*/		{ {}, {"((p .I. (p .I. q)) .I. (p .I. q))", } },
/*21*/		{ {}, {"((p .I. (q .I. r)) .I. ((p .I. q) .I. (p .I. r)))", } },
/*22*/		{ {}, {"(p .I. (q .I. p))", } },
/*23*/		{ {}, {"(((p .I. q) .I. p) .I. p)", } },
/*24*/		{ {}, {"(((.N. p) .A. (.N. q)) .I. (.N. (p .A. q)))", } },
/*25*/		{ {}, {"(((.N. p) .O. (.N. q)) .I. (.N. (p .O. q)))", } },
/*26*/		{ {}, {"(((.N. p) .O. (.N. q)) .I. (.N. (p .A. q)))", } },
/*27*/		{ {}, {"(((.N. p) .A. (.N. q)) .I. (.N. (p .O. q)))", } },
/*28*/		{ {}, {"(p .I. (p .O. q))", } },
/*29*/		{ {}, {"((p .A. q) .I. p)", } },
/*30*/		{ {}, {"((p .A. q) .I. q)", } },
/*31*/		{ {}, {"(((p .I. q) .A. (q .I. r)) .I. (p .I. r))", } },
/*32*/		{ {}, {"(((p .O. q) .A. (.N. p)) .I. q)", } },
/*33*/		{ {}, {"(((p .O. q) .A. (.N. q)) .I. p)", } },
/*34*/		{ {}, {"(((p .O. q) .A. ((.N. p) .O. r)) .I. (q .O. r))", } },
/*35*/		{ {}, {"(((p .O. q) .A. ((.N. q) .O. r)) .I. (p .O. r))", } },
/*36*/		{ {}, {"((p .A. q) .I. (p .A. q))", } },
/*37*/		{ {}, {"(((.N. p) .O. q) .I. (p .I. q))", } },
/*38*/		{ {}, {"((p .I. q) .I. ((.N. p) .O. q))", } },
/*39*/		{ {}, {"((p .I. q) .I. ((.N. q) .I. (.N. p)))", } },
/*40*/		{ {}, {"(((.N. q) .I. (.N. p)) .I. (p .I. q))", } },
/*41*/		{ {}, {"((p .A. p) .I. p)", } },
/*42*/		{ {}, {"(p .I. (p .A. p))", } },
/*43*/		{ {}, {"((p .O. p) .I. p)", } },
/*44*/		{ {}, {"(p .I. (p .O. p))", } },
/*45*/		{ {}, {"((q .A. p) .I. (p .A. q))", } },
/*46*/		{ {}, {"((p .A. q) .I. (q .A. p))", } },
/*47*/		{ {}, {"(((p .O. q) .O. r) .I. (p .O. (q .O. r)))", } },
/*48*/		{ {}, {"((p .O. (q .O. r)) .I. ((p .O. q) .O. r))", } },
/*49*/		{ {}, {"(((p .A. q) .A. r) .I. (p .A. (q .A. r)))", } },
/*50*/		{ {}, {"((p .A. (q .A. r)) .I. ((p .A. q) .A. r))", } },
/*51*/		{ {}, {"((p .O. (q .A. r)) .I. ((p .O. q) .A. (p .O. r)))", } },
/*52*/		{ {}, {"((p .A. (q .O. r)) .I. ((p .A. q) .O. (p .A. r)))", } },
/*53*/		{ {}, {"((p .O. (q .A. r)) .I. ((p .O. q) .A. (p .O. r)))", } },
/*54*/		{ {}, {"(((p .A. q) .O. (p .A. r)) .I. (p .A. (q .O. r)))", } },
/*55*/		{ {}, {"(((p .O. q) .A. (p .O. r)) .I. (p .O. (q .A. r)))", } },
			};

	Resultado[] esperadas = {
/* 0*/		new Resultado(true), 
/* 1*/		new Resultado(false, "F(p),T(q)"),
/* 2*/		new Resultado(false, "T(q),F(p)"), 
/* 3*/		new Resultado(true), 
/* 4*/		new Resultado(true), 
/* 5*/		new Resultado(false, "T(a),F(q)"), 
/* 6*/		new Resultado(true), 
/* 7*/		new Resultado(false, "T(p),F(q)"), 
/* 8*/		new Resultado(true), 
/* 9*/		new Resultado(false, "T(p),T(q),F(r)"), 
/*10*/		new Resultado(false, "F(p),T(q)"), 
/*11*/		new Resultado(true), 
/*12*/		new Resultado(true), 
/*13*/		new Resultado(true), 
/*14*/		new Resultado(true), 
/*15*/		new Resultado(false, "T(q),F(p)"), 
/*16*/		new Resultado(true), 
/*17*/		new Resultado(true), 
/*18*/		new Resultado(true), 
/*19*/		new Resultado(true),
/*20*/		new Resultado(true),
/*21*/		new Resultado(true),
/*22*/		new Resultado(true),
/*23*/		new Resultado(true),
/*24*/		new Resultado(true),
/*25*/		new Resultado(false, "T(p),F(q)"),
/*26*/		new Resultado(true),
/*27*/		new Resultado(true),
/*28*/		new Resultado(true),
/*29*/		new Resultado(true),
/*30*/		new Resultado(true),
/*31*/		new Resultado(true),
/*32*/		new Resultado(true),
/*33*/		new Resultado(true),
/*34*/		new Resultado(true),
/*35*/		new Resultado(true),
/*36*/		new Resultado(true),
/*37*/		new Resultado(true),
/*38*/		new Resultado(true),
/*39*/		new Resultado(true),
/*40*/		new Resultado(true),
/*41*/		new Resultado(true),
/*42*/		new Resultado(true),
/*43*/		new Resultado(true),
/*44*/		new Resultado(true),
/*45*/		new Resultado(true),
/*46*/		new Resultado(true),
/*47*/		new Resultado(true),
/*48*/		new Resultado(true),
/*49*/		new Resultado(true),
/*50*/		new Resultado(true),
/*51*/		new Resultado(true),
/*52*/		new Resultado(true),
/*53*/		new Resultado(true),
/*54*/		new Resultado(true),
/*55*/		new Resultado(true),
			};

	/**
	 * Teste unitário do método provar()
	 */
	@Test
	public void testarProvar(){
		ProvadorTeoremas provador = new ProvadorTeoremas();
		provador.definirModoDebug(true);
		
		for(int i = 0; i < sequentes.length; i++){
			System.out.println(i);
			assertEquals("Erro na iteração " + i, esperadas[i], provador.provar(sequentes[i][0], sequentes[i][1]));
			System.out.println("---------------");
		}
	}
}
