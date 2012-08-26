package com.mac242.guerradasuniversidades.core.modelo;
public class Notificacao {
	private String nome;
	private NomeUniversidade universidade;
	private TipoNotificacao tipo;
	private Estrutura estrutura;

	public String getNome() {
		return nome;
	}

	public Notificacao setNome(String nome) {
		this.nome = nome;
		return this;
	}

	public NomeUniversidade getUniversidade() {
		return universidade;
	}

	public Notificacao setUniversidade(NomeUniversidade universidade) {
		this.universidade = universidade;
		return this;
	}

	public TipoNotificacao getTipo() {
		return tipo;
	}

	public Notificacao setTipo(TipoNotificacao tipo) {
		this.tipo = tipo;
		return this;
	}

	public Estrutura getEstrutura() {
		return estrutura;
	}

	public Notificacao setEstrutura(Estrutura estrutura) {
		this.estrutura = estrutura;
		return this;
	}
	
	public String toString(){
		return nome + "(" + universidade + ") " + tipo + " " + estrutura;
	}

}
