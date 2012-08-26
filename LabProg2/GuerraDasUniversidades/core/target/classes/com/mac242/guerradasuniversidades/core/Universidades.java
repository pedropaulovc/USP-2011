package com.mac242.guerradasuniversidades.core;

import static playn.core.PlayN.assetManager;
import static playn.core.PlayN.log;
import static playn.core.PlayN.graphics;
import static playn.core.PlayN.pointer;
import playn.core.CanvasLayer;
import playn.core.Color;
import playn.core.Font;
import playn.core.Image;
import playn.core.ImageLayer;
import playn.core.ResourceCallback;
import playn.core.Font.Style;
import playn.core.GroupLayer;
import playn.core.TextFormat;
import playn.core.TextLayout;
import react.UnitSlot;
import tripleplay.ui.AxisLayout;
import tripleplay.ui.Background;
import tripleplay.ui.Button;
import tripleplay.ui.Interface;
import tripleplay.ui.Label;
import tripleplay.ui.Root;
import tripleplay.ui.Styles;
import tripleplay.ui.Stylesheet;

enum NomesUniversidades {USP, UFSC, UNICAMP};

public class Universidades extends TipoTela {

	private Interface iface;
	private NomesUniversidades escolhida;

	public String toString() {
		return "Universidades";
	}

	public Universidades(GuerraDasUniversidades jogo) {
		super(jogo);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void init() {
		iniciarBase();
		desenharFundo(Color.rgb(255, 255, 255));
		desenharMapa();
	}

	@Override
	public void update(float delta) {
		if (iface != null) {
			iface.update(delta);
		}
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

	private void desenharMenu() {
		GroupLayer layerMenu = graphics().createGroupLayer();
		base.add(layerMenu);

		iface = new Interface(null);
		pointer().setListener(iface.plistener);
		Styles naoselecionado = Styles
				.none()
				.add(tripleplay.ui.Style.BACKGROUND.is(Background.solid(
						0xFFCCCCCC, 5)))
				.add(tripleplay.ui.Style.FONT.is(graphics().createFont(
						"Helvetica", Font.Style.PLAIN, 18)))
				.addSelected(
						tripleplay.ui.Style.BACKGROUND.is(Background.solid(
								0xFFBBBBBB, 6, 4, 4, 6)));

		Stylesheet rootSheet = Stylesheet.builder()
				.add(Button.class, naoselecionado).create();

		Root root = iface.createRoot(AxisLayout.vertical().gap(10), rootSheet);
		root.setSize(graphics().width(), graphics().height());
		layerMenu.add(root.layer);

		Button botaousp = new Button().setText("USP");
		botaousp.clicked().connect(new UnitSlot() {

			@Override
			public void onEmit() {
				escolhida = NomesUniversidades.USP;
				jogo.exibirTela(jogo.obterTelaprincipal());
			}
		});

		Button botaoufsc = new Button().setText("UFSC");
		botaoufsc.clicked().connect(new UnitSlot() {

			@Override
			public void onEmit() {
				escolhida = NomesUniversidades.UFSC;
				jogo.exibirTela(jogo.obterTelaprincipal());
			}
		});

		Button botaounicamp = new Button().setText("UNICAMP");
		botaounicamp.clicked().connect(new UnitSlot() {

			@Override
			public void onEmit() {
				escolhida = NomesUniversidades.UNICAMP;
				jogo.exibirTela(jogo.obterTelaprincipal());
			}
		});

		Font font = graphics().createFont("Helvetica", Style.BOLD, 40f);
		TextFormat format = new TextFormat().withFont(font);
		TextLayout layout = graphics().layoutText("Escolha sua Universidade:",
				format);
		int width = (int) Math.ceil(layout.width());
		int height = (int) Math.ceil(layout.height());
		CanvasLayer layer = graphics().createCanvasLayer(width, height);
		layer.canvas().drawText(layout, 0, 0);
		layer.setTranslation(graphics().width() / 2 - width / 2, 20);
		base.add(layer);

		root.add(botaousp, botaoufsc, botaounicamp);
	}

	private void desenharMapa() {
		final Image mapa = assetManager().getImage("images/mapa.jpg");
		mapa.addCallback(new ResourceCallback<Image>() {
			@Override
			public void error(Throwable err) {
				 log().error("Erro carregando imagem", err);
			}
			
			@Override
			public void done(Image resource) {
				ImageLayer layerMapa = graphics().createImageLayer(mapa);
				layerMapa.transform().translate(
						graphics().width() / 2 - mapa.width() / 2, 100);
				base.add(layerMapa);
				desenharMenu();
			}
		});
	}

	/**
	 * @return the escolhida
	 */
	public NomesUniversidades getEscolhida() {
		return escolhida;
	}

}
