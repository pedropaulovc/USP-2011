package com.mac242.guerradasuniversidades.core.modelo;
import java.util.List;
import java.util.Observable;
import java.util.Observer;

public class Jogador extends Observable implements Observer, TipoJogador {
	private String nome;
	private FocoAdministracao foco;
	private NomeUniversidade universidade;
	private GerenteEstruturas gerente;

	private int PE = 1000;
	private int FO = 0;
	private int HP = 10;
	private static final int maxPE = 9000;
	private int maxFO = 10;

	private int taxaPE = 15;
	private int taxaFO = 0;
	private int taxaManutencao = 0;
	private int taxaFuncionarios = 0;

	public Jogador(ConstrutorJogador construtor, GuerraDasUniversidades jogo) {
		this.nome = construtor.obterNome();
		this.foco = construtor.obterFoco();
		this.universidade = construtor.obterUniversidade();
		this.gerente = new GerenteEstruturas(foco);
		this.gerente.addObserver(this);
	}

	public void atualizarPE() {
		PE = Math.min(PE + taxaPE, maxPE);
	}

	public void atualizarTaxas() {
		PE = PE - taxaFuncionarios - taxaManutencao;
		FO = Math.min(FO + taxaFO, maxFO);

		if (PE <= 0){
			gerarPossivelProblema();
			PE = 0;
		}
	}

	@Override
	public void update(Observable o, Object arg) {
		taxaPE += gerente.obterDeltaTaxaPE();
		taxaFuncionarios += gerente.obterDeltaTaxaFuncionarios();
		taxaManutencao += gerente.obterDeltaTaxaManutencao();
		taxaFO += gerente.obterDeltaTaxaFO();
		maxFO += gerente.obterDeltaFOMax();
		PE -= gerente.obterGastos();
		FO += gerente.obterDeltaFO();
		
		setChanged();
		Notificacao notificacao = (Notificacao) arg;
		notificacao
			.setNome(nome)
			.setUniversidade(universidade);
		
		notifyObservers(notificacao);
	}

	/**
	 * Nesse cenário, existe uma probabilidade de 10% de chance de funcionarios
	 * entrarem em greve (o que zera o foco dos alunos) ou uma estrutura
	 * aleatória quebrar, e 90% de nada acontecer.
	 */
	private void gerarPossivelProblema() {
		double rand = Math.random();
		Notificacao notificacao = new Notificacao()
			.setNome(nome)
			.setTipo(TipoNotificacao.GREVE)
			.setUniversidade(universidade);
			
		if(rand > 0.1)
			return;
		
		if (rand <= 0.04){
			FO = 0;
			setChanged();
			notifyObservers(notificacao);
		} else if (rand <= 0.08)
			gerente.quebrarEstruturaAleatoria();
		else {
			FO = 0;
			setChanged();
			notifyObservers(notificacao);
			gerente.quebrarEstruturaAleatoria();
		}
	}
	
	public int obterPontosEnsino() {
		return PE;
	}
	
	public int obterFoco() {
		return FO;
	}

	public int obterHP() {
		return HP;
	}

	public int obterTaxaManutencao() {
		return taxaManutencao;
	}
	
	public int obterTaxaFuncionarios() {
		return taxaFuncionarios;
	}
	
	public int obterTaxaFoco() {
		return taxaFO;
	}

	public GerenteEstruturas obterGerenteEstruturas(){
		return gerente;
	}

	public int obterTaxaPontosEnsino() {
		return taxaPE;
	}

	public int obterFocoMaximo() {
		return maxFO;
	}
	
	public String obterNome(){
		return nome;
	}

	@Override
	public void realizarJogada() {
		//Não faz nada.
	}

	@Override
	public StatusJogador obterStatus() {
		StatusJogador status = new StatusJogador();
		status.FO = FO;
		status.maxFO = maxFO;
		status.HP = HP;
		status.nome = nome;
		status.PE = PE;
		status.taxaFO = taxaFO;
		status.taxaFuncionarios = taxaFuncionarios;
		status.taxaManutencao = taxaManutencao;
		status.taxaPE = taxaPE;
		
		return status;
	}

	@Override
	public NomeUniversidade obterNomeUniversidade() {
		return universidade;
	}
	
	public int calcularPoderAtaque(){
		List<StatusSalaAula> salas = gerente.obterInfoSalas();
		if(salas.size() > 0){
			StatusSalaAula exercito = salas.get(0);
			if(exercito.possuiProfessor() && exercito.estaCheia())
				return FO;
		}
		return 0;
	}
	
	public void atacar(TipoJogador alvo){
		alvo.receberAtaque(calcularPoderAtaque());
		FO /= 2;
		gerente.esvaziarSala();
	}

	@Override
	public void receberAtaque(int poder) {
		if(FO - poder >= 0){
			FO -= poder;
			return;
		}
		
		if(gerente.possuiGuardaUniversitaria()){
			gerente.destruirGuardaUniversitaria();
			return;
		}
		
		HP--;
		FO = 0;
		Notificacao notificacao = new Notificacao()
			.setNome(nome)
			.setUniversidade(universidade)
			.setTipo(TipoNotificacao.PERDA_HP);
		setChanged();
		notifyObservers(notificacao);
		
		if(HP == 0){
			notificacao = new Notificacao()
				.setNome(nome)
				.setUniversidade(universidade)
				.setTipo(TipoNotificacao.MORTE);
			setChanged();
			notifyObservers(notificacao);
		}
	}
}
