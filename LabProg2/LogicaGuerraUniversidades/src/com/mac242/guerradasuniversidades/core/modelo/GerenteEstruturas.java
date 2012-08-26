package com.mac242.guerradasuniversidades.core.modelo;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observable;
import java.util.Timer;
import java.util.TimerTask;

public class GerenteEstruturas extends Observable {
	private List<SalaAula> salas = new ArrayList<SalaAula>();

	private int deltaTaxaPE;
	private int deltaTaxaFO;
	private int deltaTaxaManutencao;
	private int deltaTaxaFuncionarios;
	private int deltaFOMax;
	private int deltaFO;
	private int gastos;
	private Map<Estrutura, Integer> custos;
	private Map<Estrutura, Integer> disp;

	public GerenteEstruturas(FocoAdministracao foco) {
		calcularCustos(foco);
		calcularLimites();
	}

	private void calcularCustos(FocoAdministracao foco) {
		custos = new HashMap<Estrutura, Integer>();
		custos.put(Estrutura.SALA_AULA, 400);
		custos.put(Estrutura.PROFESSOR, 200);
		custos.put(Estrutura.ALUNO, 75);
		custos.put(Estrutura.BANDEJAO, 600);
		custos.put(Estrutura.SETOR_DADOS, 500);
		custos.put(Estrutura.PRACA_CENTRAL, 400);
		custos.put(Estrutura.CENTRO_ESPORTES, 700);
		custos.put(Estrutura.AUMENTO_SALARIAL, 700);

		custos.put(Estrutura.CHURRASCO_DEBATE, 400);
		if (foco == FocoAdministracao.HUMANAS)
			custos.put(Estrutura.CHURRASCO_DEBATE, 275);

		custos.put(Estrutura.FESTA, 400);
		if (foco == FocoAdministracao.BIOMEDICAS)
			custos.put(Estrutura.FESTA, 300);

		custos.put(Estrutura.SOBREMESA_BANDEJAO, 250);
		if (foco == FocoAdministracao.BIOMEDICAS)
			custos.put(Estrutura.SOBREMESA_BANDEJAO, 140);

		custos.put(Estrutura.SEMINARIO, 300);
		if (foco == FocoAdministracao.BIOMEDICAS)
			custos.put(Estrutura.SEMINARIO, 200);
		
		custos.put(Estrutura.GUARDA_UNIVERSITARIA, 1500);
	}

	private void calcularLimites() {
		disp = new HashMap<Estrutura, Integer>();
		disp.put(Estrutura.SALA_AULA, 5);
		disp.put(Estrutura.PROFESSOR, 0);
		disp.put(Estrutura.ALUNO, 0);
		disp.put(Estrutura.BANDEJAO, 1);
		disp.put(Estrutura.SETOR_DADOS, -1);
		disp.put(Estrutura.PRACA_CENTRAL, 1);
		disp.put(Estrutura.CENTRO_ESPORTES, 1);
		disp.put(Estrutura.AUMENTO_SALARIAL, -1);
		disp.put(Estrutura.CHURRASCO_DEBATE, 15);
		disp.put(Estrutura.FESTA, Integer.MAX_VALUE);
		disp.put(Estrutura.SOBREMESA_BANDEJAO, 0);
		disp.put(Estrutura.SEMINARIO, -1);
		disp.put(Estrutura.GUARDA_UNIVERSITARIA, 1);
	}

	/**
	 * Supõe que usuário possui PE >= 500 e pelo menos um espaço vago. Libera
	 * uma nova sala para ser populada com professor e alunos.
	 */
	public void comprarSala() {
		salas.add(new SalaAula());
		deltaTaxaManutencao++;

		int profDisp = disp.get(Estrutura.PROFESSOR);
		int alunoDisp = disp.get(Estrutura.ALUNO);
		disp.put(Estrutura.PROFESSOR, profDisp + 1);
		disp.put(Estrutura.ALUNO, alunoDisp + 10);

		if (disp.get(Estrutura.SETOR_DADOS) == -1)
			disp.put(Estrutura.SETOR_DADOS, 1);
		if (disp.get(Estrutura.AUMENTO_SALARIAL) == -1)
			disp.put(Estrutura.AUMENTO_SALARIAL, 10);
		if (disp.get(Estrutura.SEMINARIO) == -1)
			disp.put(Estrutura.SEMINARIO, Integer.MAX_VALUE);

		comprarEstrutura(Estrutura.SALA_AULA);
	}

	public int obterQtdSalas() {
		return salas.size();
	}

	/**
	 * Supõe que haja uma sala sem professor. Adiciona um professor à primeira
	 * sala sem professor.
	 */
	public void contratarProfessor() {
		int i = 0;
		while (salas.get(i).possuiProfessor())
			i++;
		salas.get(i).alterarProfessor(true);

		comprarEstrutura(Estrutura.PROFESSOR);
	}

	public int obterQtdProfessores() {
		int qtdProfessores = 0;

		for (SalaAula s : salas) {
			if (s.possuiProfessor())
				qtdProfessores++;
		}

		return qtdProfessores;
	}

	/**
	 * Supõe que haja uma sala não cheia (10 alunos) Adiciona um aluno à
	 * primeira sala que atender ao requisito.
	 */
	public void matricularAluno() {
		int i = 0;
		while (salas.get(i).estaCheia())
			i++;
		salas.get(i).adicionarAluno();

		comprarEstrutura(Estrutura.ALUNO);
	}

	public int obterQtdAlunos() {
		int qtdAlunos = 0;

		for (SalaAula s : salas) {
			qtdAlunos += s.obterQtdAlunos();
		}

		return qtdAlunos;
	}

	public void comprarBandejao() {
		deltaTaxaManutencao += 2;
		deltaFOMax += 3;

		disp.put(Estrutura.SOBREMESA_BANDEJAO, Integer.MAX_VALUE);

		comprarEstrutura(Estrutura.BANDEJAO);
	}
	
	public void destruirBandejao() {
		deltaTaxaManutencao -= 2;
		deltaFOMax -= 3;

		disp.put(Estrutura.SOBREMESA_BANDEJAO, 0);

		destruirEstrutura(Estrutura.BANDEJAO);
	}

	public void comprarSetorDados() {
		deltaTaxaManutencao += 3;
		deltaTaxaPE += 10;

		comprarEstrutura(Estrutura.SETOR_DADOS);
	}
	
	public void destruirSetorDados() {
		deltaTaxaManutencao -= 3;
		deltaTaxaPE -= 10;

		destruirEstrutura(Estrutura.SETOR_DADOS);
	}

	public void comprarPracaCentral() {
		deltaTaxaManutencao += 2;
		deltaTaxaFO++;

		comprarEstrutura(Estrutura.PRACA_CENTRAL);
	}
	
	public void destruirPracaCentral() {
		deltaTaxaManutencao -= 2;
		deltaTaxaFO--;

		destruirEstrutura(Estrutura.PRACA_CENTRAL);
	}

	public void comprarCentroEsportes() {
		deltaTaxaManutencao += 2;
		deltaTaxaFO++;

		comprarEstrutura(Estrutura.CENTRO_ESPORTES);
	}
	
	public void destruirCentroEsportes() {
		deltaTaxaManutencao -= 2;
		deltaTaxaFO--;

		destruirEstrutura(Estrutura.CENTRO_ESPORTES);
	}

	public void concederAumentoSalarial() {
		deltaTaxaFuncionarios += 2;
		deltaTaxaPE += 3;

		comprarEstrutura(Estrutura.AUMENTO_SALARIAL);
	}

	public void promoverChurrascoDebate() {
		deltaTaxaPE++; 
		
		comprarEstrutura(Estrutura.CHURRASCO_DEBATE);
	}

	public void promoverFesta() {
		deltaFO += 2;

		comprarEstrutura(Estrutura.FESTA);
	}

	public void servirSobremesaBandejao() {
		deltaFO++;

		comprarEstrutura(Estrutura.SOBREMESA_BANDEJAO);
	}

	public void promoverSeminario() {
		deltaTaxaPE += 7;

		new Timer().schedule(new TimerTask() {
			public void run() {
				deltaTaxaPE -= 7;
				setChanged();
				Notificacao notificacao = new Notificacao()
					.setEstrutura(Estrutura.SEMINARIO)
					.setTipo(TipoNotificacao.ATUALIZACAO);
				notifyObservers(notificacao);
			}
		}, 7000 * GuerraDasUniversidades.obterDuracaoDia());

		comprarEstrutura(Estrutura.SEMINARIO);
	}
	
	public void comprarGuardaUniversitaria(){
		deltaTaxaManutencao += 2;
		
		comprarEstrutura(Estrutura.GUARDA_UNIVERSITARIA);
	}

	public void destruirGuardaUniversitaria() {
		deltaTaxaManutencao -= 2;
		
		Notificacao notificacao = new Notificacao()
			.setEstrutura(Estrutura.GUARDA_UNIVERSITARIA)
			.setTipo(TipoNotificacao.DESTRUICAO);
		setChanged();
		notifyObservers(notificacao);
	}
	
	private void comprarEstrutura(Estrutura e) {
		gastos += custos.get(e);

		int disponibilidade = disp.get(e);
		disp.put(e, disponibilidade - 1);

		setChanged();
		Notificacao notificacao = new Notificacao()
			.setEstrutura(e)
			.setTipo(TipoNotificacao.COMPRA);
		notifyObservers(notificacao);
	}
	
	private void destruirEstrutura(Estrutura e) {
		int disponibilidade = disp.get(e);
		disp.put(e, disponibilidade + 1);
		
		setChanged();
		Notificacao notificacao = new Notificacao()
			.setEstrutura(e)
			.setTipo(TipoNotificacao.DESTRUICAO);
		notifyObservers(notificacao);
	}

	/**
	 * @return a variação da taxa de manutenção desde a última chamada ao
	 *         método.
	 */
	public int obterDeltaTaxaManutencao() {
		int taxa = deltaTaxaManutencao;
		deltaTaxaManutencao = 0;
		return taxa;
	}

	/**
	 * @return a variação da taxa de PE/seg desde a última chamada ao método.
	 */
	public int obterDeltaTaxaPE() {
		int PE = deltaTaxaPE;
		deltaTaxaPE = 0;
		return PE;
	}

	/**
	 * @return Os gastos desde a última chamada ao método.
	 */
	public int obterGastos() {
		int valor = gastos;
		gastos = 0;
		return valor;
	}

	/**
	 * @return a variação da taxa de funcionários desde a última chamada ao
	 *         método.
	 */
	public int obterDeltaTaxaFuncionarios() {
		int funcionarios = deltaTaxaFuncionarios;
		deltaTaxaFuncionarios = 0;
		return funcionarios;
	}

	/**
	 * @return a variação da taxa do foco desde a última chamada ao método.
	 */
	public int obterDeltaTaxaFO() {
		int FO = deltaTaxaFO;
		deltaTaxaFO = 0;
		return FO;
	}

	/**
	 * @return a variação da taxa do foco desde a última chamada ao método.
	 */
	public int obterDeltaFOMax() {
		int FOMax = deltaFOMax;
		deltaFOMax = 0;
		return FOMax;
	}
	
	public int obterDeltaFO() {
		int varFO = deltaFO;
		deltaFO = 0;
		return varFO;
	}

	public void quebrarEstruturaAleatoria() {
		List<Estrutura> possiveis = new ArrayList<Estrutura>();
		possiveis.add(Estrutura.BANDEJAO);
		possiveis.add(Estrutura.SETOR_DADOS);
		possiveis.add(Estrutura.CENTRO_ESPORTES);
		possiveis.add(Estrutura.PRACA_CENTRAL);
		
		Collections.shuffle(possiveis);
		Estrutura candidato = null;
		for(Estrutura e : possiveis) {
			if(disp.get(e) == 0){
				candidato = e;
				break;
			}
		}
		
		if(candidato == null)
			return;
		
		switch (candidato) {
		case BANDEJAO:
			destruirBandejao();
			break;
		case SETOR_DADOS:
			destruirSetorDados();
			break;
		case CENTRO_ESPORTES:
			destruirCentroEsportes();
			break;
		case PRACA_CENTRAL:
			destruirPracaCentral();
			break;
		default:
			break;
		}
	}

	public boolean estruturaDisponivel(Estrutura e, int PE) {
		return disp.get(e) > 0 && PE >= custos.get(e);
	}

	public List<StatusSalaAula> obterInfoSalas() {
		List<StatusSalaAula> lista = new ArrayList<StatusSalaAula>();

		for (SalaAula s : salas) {
			lista.add(new StatusSalaAula(s));
		}

		return lista;
	}
	
	public void esvaziarSala(){
		SalaAula vazia = salas.remove(0);
		vazia.alterarProfessor(false);
		vazia.definirQtdAlunos(0);
		salas.add(vazia);
		
		int dispProf = disp.get(Estrutura.PROFESSOR);
		int dispAluno = disp.get(Estrutura.ALUNO);
		
		disp.put(Estrutura.PROFESSOR, dispProf + 1);
		disp.put(Estrutura.ALUNO, dispAluno + 10);
		
		
		Notificacao notificacao = new Notificacao()
			.setEstrutura(Estrutura.SALA_AULA)
			.setTipo(TipoNotificacao.ATUALIZACAO);
		setChanged();
		notifyObservers(notificacao);
	}

	public boolean possuiGuardaUniversitaria() {
		return disp.get(Estrutura.GUARDA_UNIVERSITARIA) == 0;
	}
	
}
