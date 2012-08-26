package com.mac242.guerradasuniversidades.core.modelo;

public interface TipoJogador {

		public void atualizarPE();

		public void atualizarTaxas();

		public int obterPontosEnsino();
		
		public int obterFoco();

		public int obterHP();

		public int obterTaxaManutencao();
		
		public int obterTaxaFuncionarios();
		
		public int obterTaxaFoco();

		public GerenteEstruturas obterGerenteEstruturas();

		public int obterTaxaPontosEnsino();

		public int obterFocoMaximo();
		
		public String obterNome();

		public void realizarJogada();
		
		public StatusJogador obterStatus();
		
		public NomeUniversidade obterNomeUniversidade();
		
		public int calcularPoderAtaque();
		
		public void atacar(TipoJogador alvo);
		
		public void receberAtaque(int poder);

}
