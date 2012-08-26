package com.mac242.guerradasuniversidades.core.modelo;
import java.util.ArrayList;
import java.util.List;
import java.util.Observable;
import java.util.Observer;
import java.util.Random;

public class JogadorMaquina extends Observable implements Observer, TipoJogador {
	private Jogador jogador;
	private FachadaJogador fachada;
	private Random rand;
	
	private final static String[] nomes = { "Alair", "Alan", "Goldman",
			"Ana Cristina", "Fujita", "Mandel", "Carlinhos", "Hitoshi",
			"Humes", "Cris", "Batista", "Ernesto", "Kon", "Flávio", "Reverbel",
			"JEF", "Coelho", "Kunio", "Leliane", "Leônidas", "Marcílio",
			"Marcel", "Finger", "MQZ", "Gerosa", "Gubi", "Maria Ângela",
			"Nami", "Nelson", "Nina", "Feofiloff", "Silva e Silva", "Renata",
			"Hirata", "Marcondes", "Ronaldo", "Routo", "Siang", "Setzer",
			"Yoshi", "Yoshiko" };
	
	public JogadorMaquina(ConstrutorJogador construtor, GuerraDasUniversidades jogo) {
		jogador = construtor.construir(jogo);
		jogador.addObserver(this);
		fachada = new FachadaJogador(jogador, jogo);
		rand = new Random();
	}

	public static List<JogadorMaquina> construirOponentes(NomeUniversidade jogador, 
			GuerraDasUniversidades jogo) {
		ConstrutorJogador construtor = new ConstrutorJogador();
		Random rand = new Random();
		List<JogadorMaquina> oponentes = new ArrayList<JogadorMaquina>();
		
		for (NomeUniversidade n : NomeUniversidade.values()) {
			if (n.equals(jogador))
				continue;
			FocoAdministracao[] focos = FocoAdministracao.values();
			construtor
				.definirFoco(focos[rand.nextInt(focos.length)])
				.definirNome(nomes[rand.nextInt(nomes.length)])
				.definirUniversidade(n);
			oponentes.add(new JogadorMaquina(construtor, jogo));
		}

		return oponentes;
	}

	@Override
	public void atualizarPE() {
		jogador.atualizarPE();
	}

	@Override
	public void atualizarTaxas() {
		jogador.atualizarTaxas();
	}

	@Override
	public int obterPontosEnsino() {
		return jogador.obterPontosEnsino();
	}

	@Override
	public int obterFoco() {
		return jogador.obterFoco();
	}

	@Override
	public int obterHP() {
		return jogador.obterHP();
	}

	@Override
	public int obterTaxaManutencao() {
		return jogador.obterTaxaFoco();
	}

	@Override
	public int obterTaxaFuncionarios() {
		return jogador.obterTaxaFuncionarios();
	}

	@Override
	public int obterTaxaFoco() {
		return jogador.obterTaxaFoco();
	}

	@Override
	public GerenteEstruturas obterGerenteEstruturas() {
		return jogador.obterGerenteEstruturas();
	}

	@Override
	public int obterTaxaPontosEnsino() {
		return jogador.obterTaxaPontosEnsino();
	}

	@Override
	public int obterFocoMaximo() {
		return jogador.obterFocoMaximo();
	}

	@Override
	public String obterNome() {
		return jogador.obterNome();
	}

	/**
	 * Implementação da IA das máquinas
	 */
	@Override
	public void realizarJogada() {
		if(Math.random() < 0.9)
			return;

		fachada.comprarEstrutura(Estrutura.GUARDA_UNIVERSITARIA);
//		Estrutura[] estruturas = Estrutura.values();
//		fachada.comprarEstrutura(estruturas[rand.nextInt(estruturas.length)]);
	}

	@Override
	public StatusJogador obterStatus() {
		return jogador.obterStatus();
	}

	@Override
	public NomeUniversidade obterNomeUniversidade() {
		return jogador.obterNomeUniversidade();
	}

	@Override
	public void update(Observable o, Object arg) {
		setChanged();
		notifyObservers(arg);
	}

	@Override
	public int calcularPoderAtaque() {
		return jogador.calcularPoderAtaque();
	}

	@Override
	public void atacar(TipoJogador alvo) {
		jogador.atacar(alvo);
	}

	@Override
	public void receberAtaque(int poder) {
		jogador.receberAtaque(poder);
	}

}
