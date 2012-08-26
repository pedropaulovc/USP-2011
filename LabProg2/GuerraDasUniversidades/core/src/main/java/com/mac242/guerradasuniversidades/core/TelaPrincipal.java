package com.mac242.guerradasuniversidades.core;

import static playn.core.PlayN.assetManager;
import static playn.core.PlayN.graphics;
import static playn.core.PlayN.pointer;

import java.util.HashMap;
import java.util.Map;

import playn.core.Canvas;
import playn.core.CanvasLayer;
import playn.core.Color;
import playn.core.Font;
import playn.core.GroupLayer;
import playn.core.Image;
import playn.core.ImageLayer;
import playn.core.SurfaceLayer;
import playn.core.TextFormat;
import playn.core.TextLayout;
import playn.core.Font.Style;
import react.UnitSlot;
import tripleplay.ui.AxisLayout;
import tripleplay.ui.Button;
import tripleplay.ui.Group;
import tripleplay.ui.Interface;
import tripleplay.ui.Root;
import tripleplay.ui.Styles;

enum Estrutura {
	B1(136, 142, "blocoEnsino"), B2(302, 342, "blocoEnsino"), 
	B3(469, 141, "blocoEnsino"), B4(98, 301, "blocoEnsino"), B5(515, 300, "blocoEnsino"),
	BANDEJAO(453, 223, "bandejao"), SETOR_DADOS(435, 322, "setorDados"), 
	PRACA_CENTRAL(303, 251, "pracaCentral"), 
	CENTRO_ESPORTES(148, 224, "centroEsportes"), GUARDA(224, 330, "guarda");
	
	private int x;
	private int y;
	private Image imagem;
	
	Estrutura(int x, int y, String nome){
		this.x = x;
		this.y = y;
		imagem = assetManager().getImage("images/" + nome + ".jpg");
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	/**
	 * @return the imagem
	 */
	public Image getImagem() {
		return imagem;
	}
	
};

public class TelaPrincipal extends TipoTela {

	private Interface iface;
	private int contaUpdates = 0;
	private int dia = 1;
	private String avisoAtual;
	private Canvas canvasDia;
	private Canvas canvasAvisos;
	private int PE = 1000;
	private int FO = 0;
	private int taxaPE = 15;
	private int taxaManutencao = 0;
	private int taxaFuncionarios = 0;
	private int maxPE = 9000;
	private Canvas canvasFO;
	private int segundos = 0;
	private String[] avisosExemplo = {
			"Funcionários entraram em greve (Foco zerado)",
			"Unicamp atacou você (-1 HP)", " ", "-- Avisos exemplo --",
			"USP atacou UFSC (-1 HP)", };
	private Canvas canvasTaxas;
	private Canvas canvasCampus;
	private Map<Estrutura, Boolean> estruturas;
	
	
	public TelaPrincipal(GuerraDasUniversidades jogo) {
		super(jogo);
		
		estruturas = new HashMap<Estrutura, Boolean>();
		for(Estrutura e : Estrutura.values()){
			estruturas.put(e, false);
		}
	}

	public String toString() {
		return "Tela Principal";
	}

	@Override
	public void init() {
		iniciarBase();
		desenharFundo(Color.rgb(255, 255, 255));
		desenhaEsqueleto();

		GroupLayer layerMenu = graphics().createGroupLayer();
		base.add(layerMenu);

		iface = new Interface(null);
		pointer().setListener(iface.plistener);

		desenhaBarraSuperior();
		desenharLogo();

		CanvasLayer layerDia = graphics().createCanvasLayer(71, 25);
		layerDia.setTranslation(505, 498);
		base.add(layerDia);
		canvasDia = layerDia.canvas();
		desenharDia();

		desenharHP();

		CanvasLayer layerAvisos = graphics().createCanvasLayer(500, 39);
		layerAvisos.setTranslation(32, 396);
		base.add(layerAvisos);
		canvasAvisos = layerAvisos.canvas();

		CanvasLayer layerFO = graphics().createCanvasLayer(150, 15);
		layerFO.setTranslation(534, 473);
		base.add(layerFO);
		canvasFO = layerFO.canvas();

		CanvasLayer layerTaxas = graphics().createCanvasLayer(140, 51);
		layerTaxas.setTranslation(570, 395);
		base.add(layerTaxas);
		canvasTaxas = layerTaxas.canvas();
		desenharTaxas();

		CanvasLayer layerCampus = graphics().createCanvasLayer(671, 290);
		layerCampus.setTranslation(20, 154);
		base.add(layerCampus);
		canvasCampus = layerCampus.canvas();
	}

	private void desenharCampus() {
		canvasCampus.clear();
		for(Estrutura e : estruturas.keySet()){
			if(estruturas.get(e)){
				canvasCampus.drawImage(e.getImagem(), e.getX(), e.getY());
			}
		}
	}

	private void desenharTaxas() {
		String texto = "Manutenção: " + taxaManutencao + "/dia\nFuncionários: "
				+ taxaFuncionarios + "/dia\nPE: " + taxaPE + "/seg";
		Font font = graphics().createFont("Helvetica",
				playn.core.Font.Style.BOLD, 10f);
		TextFormat format = new TextFormat().withFont(font);
		TextLayout layout = graphics().layoutText(texto, format);
		canvasTaxas.clear();
		canvasTaxas.drawText(layout, 0, 0);
	}

	private void desenharFO() {
		canvasFO.clear();
		canvasFO.setFillColor(Color.rgb(255, 255, 0));
		canvasFO.fillRect(10 * (segundos % 16), 0, canvasFO.width() - 10
				* (segundos % 16), canvasFO.height());
	}

	private void desenharHP() {
		Font font = graphics().createFont("Helvetica",
				playn.core.Font.Style.BOLD, 15f);
		TextFormat format = new TextFormat().withFont(font);
		TextLayout layout = graphics().layoutText("HP 10/10", format);
		int width = (int) Math.ceil(layout.width());
		int height = (int) Math.ceil(layout.height());
		CanvasLayer layer = graphics().createCanvasLayer(width, height);
		layer.canvas().drawText(layout, 0, 0);
		layer.setTranslation(612, 498);
		base.add(layer);
	}

	private void desenharAviso(String aviso) {
		if (aviso.length() == 0)
			aviso = " ";
		Font font = graphics().createFont("Helvetica",
				playn.core.Font.Style.BOLD, 11f);
		TextFormat format = new TextFormat().withFont(font).withTextColor(
				Color.rgb(255, 255, 255));
		TextLayout layout = graphics().layoutText(aviso, format);
		canvasAvisos.clear();
		canvasAvisos.drawText(layout, 0, 0);
	}

	private void desenharDia() {
		Font font = graphics().createFont("Helvetica",
				playn.core.Font.Style.BOLD, 15f);
		TextFormat format = new TextFormat().withFont(font);
		TextLayout layout = graphics().layoutText("Dia: " + dia, format);
		canvasDia.clear();
		canvasDia.drawText(layout, 0, 0);
	}

	private void desenharLogo() {
		NomesUniversidades escolhida = jogo.obterUniversidades().getEscolhida();
		String nome = escolhida.toString().toLowerCase();
		Image logo = assetManager().getImage("images/" + nome + ".jpg");
		ImageLayer layerLogo = graphics().createImageLayer(logo);
		layerLogo.setTranslation(14, 15);
		base.add(layerLogo);

		Font font = graphics().createFont("Helvetica",
				playn.core.Font.Style.BOLD, 15f);
		TextFormat format = new TextFormat().withFont(font);
		TextLayout layout = graphics().layoutText(nome.toUpperCase(), format);
		int width = (int) Math.ceil(layout.width());
		int height = (int) Math.ceil(layout.height());
		CanvasLayer layer = graphics().createCanvasLayer(width, height);
		layer.canvas().drawText(layout, 0, 0);
		layer.setTranslation(64 - width / 2, 117);
		base.add(layer);

	}

	private void desenhaBarraSuperior() {
		GroupLayer layerBotoes = graphics().createGroupLayer();
		//layerBotoes.setTranslation(56, -190);
		layerBotoes.setOrigin(100, 100);
		base.add(layerBotoes);

		Button esquerda = new Button();
		esquerda.setIcon(assetManager().getImage("images/setaEsquerda.png"));

		Button direita = new Button();
		direita.setIcon(assetManager().getImage("images/setaDireita.png"));

		Styles estiloLegenda = Styles.none().add(
				tripleplay.ui.Style.FONT.is(graphics().createFont("Helvetica",
						Font.Style.BOLD, 10)));
		
		Button itemBlocoEnsino = new Button();
		itemBlocoEnsino.setIcon(assetManager().getImage(
				"images/blocoEnsino.jpg"));
		Button textoBlocoEnsino = new Button()
				.setText("Bloco Ensino\n$400 / Salas +1");
		textoBlocoEnsino.setStyles(estiloLegenda);
		
		UnitSlot tratadorBlocoEnsino = new UnitSlot() {
			@Override
			public void onEmit() {
				for(int i = 0; i < 4; i++){
					if(!estruturas.get(Estrutura.values()[i])){
						estruturas.put(Estrutura.values()[i], true);
						return;
					}
				}
			}
		};
		itemBlocoEnsino.clicked().connect(tratadorBlocoEnsino);
		textoBlocoEnsino.clicked().connect(tratadorBlocoEnsino);
		
		Group blocoEnsino = new Group(AxisLayout.vertical());
		blocoEnsino.add(itemBlocoEnsino, textoBlocoEnsino);

		
		Button itemSetorDados = new Button();
		itemSetorDados
				.setIcon(assetManager().getImage("images/setorDados.jpg"));
		Button textoSetorDados = new Button()
				.setText("Setor Dados\n$500 / PE +4/seg");
		textoSetorDados.setStyles(estiloLegenda);
		Group setorDados = new Group(AxisLayout.vertical());
		setorDados.add(itemSetorDados, textoSetorDados);

		Button itemBandejao = new Button();
		itemBandejao.setIcon(assetManager().getImage("images/bandejao.jpg"));
		Button textoBandejao = new Button()
				.setText("Bandejão\n$600 / FO MAX +3");
		textoBandejao.setStyles(estiloLegenda);
		Group bandejao = new Group(AxisLayout.vertical());
		bandejao.add(itemBandejao, textoBandejao);

		Button itemProfessor = new Button();
		itemProfessor.setIcon(assetManager().getImage("images/professor.jpg"));
		Button textoProfessor = new Button().setText("Professor\n$600");
		textoProfessor.setStyles(estiloLegenda);
		Group professor = new Group(AxisLayout.vertical());
		professor.add(itemProfessor, textoProfessor);

		Group botoes = new Group(AxisLayout.horizontal().gap(-2));
		botoes.add(esquerda, blocoEnsino, setorDados, bandejao, professor,
				direita);

		Root root = iface.createRoot(AxisLayout.horizontal().gap(-2));
		root.setSize(graphics().width(), graphics().height());
		layerBotoes.add(root.layer);
		root.add(botoes);
	}

	@Override
	public void update(float delta) {
		if (iface != null) {
			iface.update(delta);
		}

		contaUpdates++;

		if (contaUpdates == 10) {
			contaUpdates = 0;
			segundos++;

			if (segundos % 240 == 0) {
				dia++;
				desenharDia();
			}

			if (segundos % 3 == 0) {
				desenharAviso(avisosExemplo[segundos % avisosExemplo.length]);
			}

		}

		desenharFO();
		desenharCampus();
	}

	@Override
	public void paint(float alpha) {
		if (iface != null) {
			iface.paint(alpha);
		}
	}

	@Override
	public void shutdown() {
		if (iface != null) {
			pointer().setListener(null);
			iface = null;
		}

		destruirBase();
	}

	public void desenhaEsqueleto() {
		Image fundo = assetManager().getImage("images/fundomain.png");
		ImageLayer layerFundo = graphics().createImageLayer(fundo);
		base.add(layerFundo);
	}
}
