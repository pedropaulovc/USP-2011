package com.mac242.guerradasuniversidades.core.modelo;
public class SalaAula {
	private boolean temProfessor;
	private int qtdAlunos;
	private static final int capacidade = 10;

	public boolean possuiProfessor() {
		return temProfessor;
	}

	public void alterarProfessor(boolean temProfessor) {
		this.temProfessor = temProfessor;
	}

	public int obterQtdAlunos() {
		return qtdAlunos;
	}

	public void adicionarAluno() {
		qtdAlunos++;
	}
	
	public boolean estaCheia(){
		return qtdAlunos == capacidade;
	}
	
	public static int obterCapacidade(){
		return capacidade;
	}

	public void definirQtdAlunos(int i) {
		this.qtdAlunos = 0;
	}
}
