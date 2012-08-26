package com.mac242.guerradasuniversidades.core.modelo;
public class StatusSalaAula {
	private SalaAula sala;
	
	public StatusSalaAula(SalaAula sala){
		this.sala = sala;
	}
	
	public boolean possuiProfessor() {
		return sala.possuiProfessor();
	}

	public int obterQtdAlunos() {
		return sala.obterQtdAlunos();
	}

	
	public boolean estaCheia(){
		return sala.obterQtdAlunos() == SalaAula.obterCapacidade();
	}
	
	public static int obterCapacidade(){
		return SalaAula.obterCapacidade();
	}
}
