package com.mac242.guerradasuniversidades.core.modelo;

public class ConstrutorJogador {
	private String nome;
	private FocoAdministracao foco;
	private NomeUniversidade universidade;

	public ConstrutorJogador definirNome(String nome){
		this.nome = nome;
		return this;
	}
	
	public ConstrutorJogador definirFoco(FocoAdministracao foco){
		this.foco = foco;
		return this;
	}
	
	public ConstrutorJogador definirUniversidade(NomeUniversidade universidade){
		this.universidade = universidade;
		return this;
	}
	
	public String obterNome() {
		return nome;
	}

	public FocoAdministracao obterFoco() {
		return foco;
	}

	public NomeUniversidade obterUniversidade() {
		return universidade;
	}

	public Jogador construir(GuerraDasUniversidades jogo) {
		return new Jogador(this, jogo);
	}

}
