package com.mac242.guerradasuniversidades.core.modelo;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class FachadaJogador {
	private Jogador jogador;
	private GerenteEstruturas gerente;
	private GuerraDasUniversidades jogo;

	public FachadaJogador(Jogador jogador, GuerraDasUniversidades jogo) {
		this.jogador = jogador;
		this.jogo = jogo;
		this.gerente = jogador.obterGerenteEstruturas();
	}

	public List<Estrutura> obterEstruturasDisponiveis() {
		List<Estrutura> disponiveis = new ArrayList<Estrutura>();
		
		for(Estrutura e : Estrutura.values()){
			if(gerente.estruturaDisponivel(e, jogador.obterPontosEnsino()))
				disponiveis.add(e);
		}
		
		return disponiveis;
	}

	public int obterPontosEnsino() {
		return jogador.obterPontosEnsino();
	}

	public int obterFoco() {
		return jogador.obterFoco();
	}

	public int obterHP() {
		return jogador.obterHP();
	}

	public List<StatusSalaAula> obterInfoSalas() {
		return gerente.obterInfoSalas();
	}

	public void observarInformes() {

	}

	public int obterTaxaManutencao() {
		return jogador.obterTaxaManutencao();
	}

	public int obterTaxaFuncionarios() {
		return jogador.obterTaxaFuncionarios();
	}
	
	public int obterTaxaFoco() {
		return jogador.obterTaxaFoco();
	}
	
	public int obterTaxaPontosEnsino(){
		return jogador.obterTaxaPontosEnsino();
	}
	
	public void obterInfoOponentes() {

	}

	public boolean comprarEstrutura(Estrutura e){
		if(!gerente.estruturaDisponivel(e, jogador.obterPontosEnsino()))
			return false;
		switch (e) {
		case SALA_AULA:
			gerente.comprarSala();
			break;
		case PROFESSOR:
			gerente.contratarProfessor();
			break;
		case ALUNO:
			gerente.matricularAluno();
			break;
		case BANDEJAO:
			gerente.comprarBandejao();
			break;
		case SETOR_DADOS:
			gerente.comprarSetorDados();
			break;
		case PRACA_CENTRAL:
			gerente.comprarPracaCentral();
			break;
		case CENTRO_ESPORTES:
			gerente.comprarCentroEsportes();
			break;
		case AUMENTO_SALARIAL:
			gerente.concederAumentoSalarial();
			break;
		case CHURRASCO_DEBATE:
			gerente.promoverChurrascoDebate();
			break;
		case FESTA:
			gerente.promoverFesta();
			break;
		case SOBREMESA_BANDEJAO:
			gerente.servirSobremesaBandejao();
			break;
		case SEMINARIO:
			gerente.promoverSeminario();
			break;
		case GUARDA_UNIVERSITARIA:
			gerente.comprarGuardaUniversitaria();
			break;
		default:
			return false;
		}
		
		return true;
	}
	
	public ResultadoAtaque atacar(NomeUniversidade alvo){
		Set<NomeUniversidade> vivos = jogo.obterVivos();
		
		if(jogador.obterFoco() == 0)
			return ResultadoAtaque.FOCO_ZERO;
		if(jogador.calcularPoderAtaque() == 0)
			return ResultadoAtaque.SEM_SALA_COMPLETA;
		if(alvo.equals(jogador))
			return ResultadoAtaque.AUTO_ATAQUE;
		if(!vivos.contains(alvo))
			return ResultadoAtaque.ALVO_MORTO;
		
		jogador.atacar(jogo.obterTipoJogador(alvo));
		
		return ResultadoAtaque.SUCESSO;
	}
	
	public int obterFocoMaximo() {
		return jogador.obterFocoMaximo();
	}
	
	public NomeUniversidade obterNomeUniversidade(){
		return jogador.obterNomeUniversidade();
	}

}
