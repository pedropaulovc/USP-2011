package com.mac242.guerradasuniversidades.core.modelo;
import java.util.List;
import java.util.Observable;
import java.util.Observer;
import java.util.Scanner;

public class InterfaceUsuario implements Observer {
	Scanner scanner = new Scanner(System.in);
	String nome;
	FocoAdministracao foco;
	GuerraDasUniversidades jogo;
	NomeUniversidade universidade;
	private FachadaJogador jogador;

	public InterfaceUsuario() {
		iniciarJogoDefault();
		menuPrincipal();
	}

	private void iniciarJogoDefault() {
		ConstrutorJogador construtor = new ConstrutorJogador()
				.definirFoco(FocoAdministracao.BIOMEDICAS)
				.definirNome("Lorem")
				.definirUniversidade(NomeUniversidade.USP);
		jogo = new GuerraDasUniversidades();
		jogo.iniciar(construtor);
		jogador = jogo.obterJogador();
		jogo.addObserver(this);
	}

	@SuppressWarnings("unused")
	private void iniciarJogo() {
		System.out.print("Digite seu nome: ");
		nome = scanner.nextLine();

		System.out.println("Escolha seu foco [1-4]:");
		System.out.println("1 - Biomédicas");
		System.out.println("2 - Exatas");
		System.out.println("3 - Humanas");
		System.out.println("4 - Esportes");
		switch (scanner.nextInt()) {
		case 1:
			foco = FocoAdministracao.BIOMEDICAS;
			break;
		case 2:
			foco = FocoAdministracao.EXATAS;
			break;
		case 3:
			foco = FocoAdministracao.HUMANAS;
			break;
		case 4:
			foco = FocoAdministracao.ESPORTES;
			break;
		default:
			foco = null;
			break;
		}

		System.out.println("Escolha sua universidade [1-3]:");
		System.out.println("1 - USP");
		System.out.println("2 - UNICAMP");
		System.out.println("3 - UFSC");

		switch (scanner.nextInt()) {
		case 1:
			universidade = NomeUniversidade.USP;
			break;
		case 2:
			universidade = NomeUniversidade.UNICAMP;
			break;
		case 3:
			universidade = NomeUniversidade.UFSC;
			break;
		default:
			universidade = null;
			break;
		}

		System.out.println("Perfil escolhido: ");
		System.out.println("\tNome: " + nome);
		System.out.println("\tFoco: " + foco);
		System.out.println("\tUniversidade: " + universidade);

		ConstrutorJogador construtor = new ConstrutorJogador()
				.definirFoco(foco)
				.definirNome(nome)
				.definirUniversidade(universidade);
		jogo = new GuerraDasUniversidades();
		jogo.iniciar(construtor);
		jogador = jogo.obterJogador();
	}

	private void menuPrincipal() {
		while (true) {
			exibirMenu();
			
			String linha = "";
			while (linha.length() == 0)
				linha = scanner.nextLine();

			switch (linha.charAt(0)) {
			case 's':
				exibirStatus();
				break;
			case 'd':
				exibirEstruturasDisponiveis();
				break;
			case 'c':
				comprarEstrutura();
				break;
			case 'a':
				exibirSituacaoSalasAula();
				break;
			case 't':
				atacarOponente();
				break;
			case 'X':
				comprarExercito();
				break;
			default:
				break;
			}
		}
	}
		
	private void comprarExercito() {
		jogador.comprarEstrutura(Estrutura.SALA_AULA);
		jogador.comprarEstrutura(Estrutura.PROFESSOR);
		for(int i = 0; i < 10; i++)
			jogador.comprarEstrutura(Estrutura.ALUNO);
	}

	private void atacarOponente() {
		System.out.println("Escolha o alvo: ");
		NomeUniversidade[] nomes = NomeUniversidade.values();
		
		int i = 0;
		for(NomeUniversidade n : nomes){
			if(!n.equals(jogador.obterNomeUniversidade()))
				System.out.println(i + " - " + n);
			i++;
		}
		
		int opcao = scanner.nextInt();
		System.out.println(jogador.atacar(nomes[opcao]));
	}

	private void exibirStatus(){
		System.out.println("Escolha uma opção abaixo:");
		int i = 0;
		NomeUniversidade[] nomes = NomeUniversidade.values();
		
		for(NomeUniversidade n : nomes){
			System.out.println(i++ + " - " + n);
		}
		System.out.println(i + " - Todos os jogadores");

		int opcao = scanner.nextInt();
		
		if(opcao < 0 || opcao > nomes.length){
			System.out.println("Opção inválida");
		} else if (opcao == nomes.length){
			for(NomeUniversidade n : nomes){
				exibirStatus(n);
			}
		} else {
			exibirStatus(nomes[opcao]);
		}
	}
	
	private void exibirStatus(NomeUniversidade nome) {
		StatusJogador status = jogo.obterStatus(nome);
		
		System.out.println("Nome (Uni):       " + status.nome + " (" + nome + ")");
		System.out.println("Dia:              " + jogo.obterDia());
		System.out.println("HP:               " + status.HP + "/10");
		System.out.println("PE:               " + status.PE);
		System.out.println("FO:               " + status.FO);
		System.out.println("FO Máximo:        " + status.maxFO);
		System.out.println("PE/seg:           "	+ status.taxaPE);
		System.out.println("FO/dia:           " + status.taxaFO);
		System.out.println("Manutenção/dia:   " + status.taxaManutencao);
		System.out.println("Funcionários/dia: "	+ status.taxaFuncionarios);
		System.out.println();
	}

	private void exibirEstruturasDisponiveis() {
		List<Estrutura> disponiveis = jogador.obterEstruturasDisponiveis();

		System.out.println("Estruturas disponíveis: ");
		for (Estrutura e : disponiveis)
			System.out.println(e);
	}

	private void comprarEstrutura() {
		System.out.println("Escolha uma das opções abaixo: ");
		int i = 0;
		for (Estrutura e : Estrutura.values()) {
			System.out.println(i + " - " + e);
			i++;
		}
		
		int estrutura = scanner.nextInt();
		if(estrutura < 0 || estrutura >= Estrutura.values().length){
			System.out.println("Opção inválida");
			return;
		}
		
		if (jogador.comprarEstrutura(Estrutura.values()[estrutura]))
			System.out.println("Compra feita com SUCESSO.");
		else
			System.out.println("Compra FALHOU.");
	}

	private void exibirSituacaoSalasAula() {
		System.out.println("Possui prof? | Num alunos");
		for (StatusSalaAula s : jogador.obterInfoSalas()) {
			System.out
					.println(s.possuiProfessor() + " | " + s.obterQtdAlunos());
		}
	}

	private void exibirMenu() {
		System.out.println("Escolha uma das opções: ");
		System.out.println("s - Ver status atual");
		System.out.println("d - Ver estruturas disponíveis");
		System.out.println("c - Comprar uma estrutura");
		System.out.println("a - Ver situação das salas de aula");
		System.out.println("o - Exibir status dos oponentes");
		System.out.println("t - Atacar oponente");
		System.out.println("X - Comprar exército");
		System.out.println();
	}

	@Override
	public void update(Observable o, Object arg) {
		Notificacao notificacao = (Notificacao) arg;
		if(arg == null)
			return;
		if(TipoNotificacao.ATUALIZACAO.equals(notificacao.getTipo()))
			System.out.print("*");
		System.out.println("=== " + arg + " ===");
	}

}
