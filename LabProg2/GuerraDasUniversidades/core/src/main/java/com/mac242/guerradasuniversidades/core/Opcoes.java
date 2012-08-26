package com.mac242.guerradasuniversidades.core;

import static playn.core.PlayN.graphics;
import static playn.core.PlayN.pointer;
import playn.core.Color;
import playn.core.Font;
import playn.core.GroupLayer;
import react.UnitSlot;
import tripleplay.ui.AxisLayout;
import tripleplay.ui.Background;
import tripleplay.ui.Button;
import tripleplay.ui.Group;
import tripleplay.ui.Interface;
import tripleplay.ui.Label;
import tripleplay.ui.Root;
import tripleplay.ui.Style;
import tripleplay.ui.Styles;
import tripleplay.ui.Stylesheet;

enum Dificuldade{FACIL, MEDIO, DIFICIL};


public class Opcoes extends TipoTela {
	
	private Interface iface;
	private Dificuldade dificuldade = Dificuldade.MEDIO;
	private boolean musica = true;
	private boolean efeitos = true;
	private Button dificuldadeatual, musicaatual, efeitoatual;
	
	private Styles selecionado,naoselecionado;
	
	
	
	public Dificuldade getDificuldade() {
		return dificuldade;
	}

	public void setDificuldade(Dificuldade dificuldade) {
		this.dificuldade = dificuldade;
	}

	public boolean isMusica() {
		return musica;
	}

	public void setMusica(boolean musica) {
		this.musica = musica;
	}

	public boolean isEfeitos() {
		return efeitos;
	}

	public void setEfeitos(boolean efeitos) {
		this.efeitos = efeitos;
	}

	public Opcoes(GuerraDasUniversidades jogo){
		super(jogo);
		naoselecionado = Styles.none().
				add(Style.BACKGROUND.is(Background.solid(0xFFCCCCCC, 5))).
				add(Style.FONT.is(graphics().createFont("Helvetica", Font.Style.PLAIN, 18))).
				addSelected(Style.BACKGROUND.is(Background.solid(0xFFBBBBBB, 6, 4, 4, 6)));
		selecionado = Styles.none().
				add(Style.BACKGROUND.is(Background.solid(0xFFDDCCCC, 5))).
				add(Style.FONT.is(graphics().createFont("Helvetica", Font.Style.PLAIN, 18))).
				addSelected(Style.BACKGROUND.is(Background.solid(0xFFBBBBBB, 6, 4, 4, 6)));
	}
	
	@Override
	public void init() {
		iniciarBase();
		desenharFundo(Color.rgb(255, 255, 255));
		desenharMenu();
	}

	private void desenharMenu() {
		GroupLayer layerMenu = graphics().createGroupLayer();
		base.add(layerMenu);
		
		iface = new Interface(null);
		pointer().setListener(iface.plistener);
		
		Styles labelStyles = Styles.none().
			add(Style.FONT.is(graphics().createFont("Helvetica", Font.Style.BOLD, 20)));
		Stylesheet rootSheet = Stylesheet.builder().
			add(Button.class, naoselecionado).
			add(Label.class, labelStyles).
			create();

		Root root = iface.createRoot(AxisLayout.vertical().gap(80), rootSheet);
		root.setSize(graphics().width(), graphics().height());
		layerMenu.add(root.layer);

		Group dificuldade = new Group(AxisLayout.horizontal().offStretch());
		Group musica = new Group(AxisLayout.horizontal().offStretch());
		Group efeitos = new Group(AxisLayout.horizontal().offStretch());
		Group info = new Group(AxisLayout.horizontal().offStretch());
		root.add(dificuldade, musica, efeitos, info);

		dificuldade.add(new Label("Dificuldade: "));
		
		final Button facil = new Button().setText("Fácil");
		facil.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				dificuldadeatual.setStyles(naoselecionado);
				facil.addStyles(selecionado);
				dificuldadeatual = facil;
				
			}
		});

			
		final Button medio = new Button().setText("Médio");
		medio.addStyles(selecionado);
		dificuldadeatual = medio;
		
		medio.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				dificuldadeatual.setStyles(naoselecionado);
				medio.addStyles(selecionado);
				dificuldadeatual = medio;
				
			}
		});
				
		final Button dificil = new Button().setText("Difícil");
		dificil.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				dificuldadeatual.setStyles(naoselecionado);
				dificil.addStyles(selecionado);
				dificuldadeatual = dificil;
				
			}
		});

		dificuldade.add(facil, medio, dificil);
		
		musica.add(new Label("Música: "));
		final Button ligada = new Button().setText("Ligada");
		ligada.addStyles(selecionado);
		musicaatual = ligada;
		ligada.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				musicaatual.setStyles(naoselecionado);
				ligada.addStyles(selecionado);
				musicaatual = ligada;
				
			}
		});
		final Button desligada = new Button().setText("Desligada");
		desligada.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				musicaatual.setStyles(naoselecionado);
				desligada.addStyles(selecionado);
				musicaatual = desligada;
				
			}
		});		
		musica.add(ligada, desligada);
		
		efeitos.add(new Label("Efeitos: "));
		final Button ligados = new Button().setText("Ligados");
		efeitoatual = ligados;
		
		ligados.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				efeitoatual.setStyles(naoselecionado);
				ligados.addStyles(selecionado);
				efeitoatual = ligados;
				
			}
		});
		
		ligados.addStyles(selecionado);
		final Button desligados = new Button().setText("Desligados");
		desligados.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				efeitoatual.setStyles(naoselecionado);
				desligados.addStyles(selecionado);
				efeitoatual = desligados;
				
			}
		});
		efeitos.add(ligados, desligados);
		Button creditos = new Button().setText("Créditos");
		Button voltar = new Button().setText("Voltar");
		voltar.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				jogo.exibirTela(jogo.obterMenu());
				
			}
		});
		info.add(voltar, creditos);
		
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
	
	public String toString(){
		return "Opções";
	}

}
