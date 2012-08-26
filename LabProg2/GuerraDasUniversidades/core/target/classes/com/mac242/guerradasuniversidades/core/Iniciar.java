package com.mac242.guerradasuniversidades.core;

import static playn.core.PlayN.graphics;
import static playn.core.PlayN.pointer;

import playn.core.Color;
import playn.core.Font;
import playn.core.GroupLayer;
import pythagoras.f.Rectangle;
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

public class Iniciar extends TipoTela{

	private Interface iface;

	public String toString(){
		return "Iniciar";
	}
	
	public Iniciar(GuerraDasUniversidades jogo) {
		super(jogo);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void init() {
		iniciarBase();
		desenharFundo(Color.rgb(255, 255, 255));
		desenhamenu();
		// TODO Auto-generated method stub
		
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
	
	public void desenhamenu(){
		GroupLayer layerMenu = graphics().createGroupLayer();
		base.add(layerMenu);
		
		iface = new Interface(null);
		pointer().setListener(iface.plistener);
		
		Styles labelpadrao = Styles.none().
				add(Style.FONT.is(graphics().createFont("Helvetica", Font.Style.BOLD, 20)));
		
		Styles botaopadrao = Styles.none().
				add(Style.BACKGROUND.is(Background.solid(0xFFCCCCCC, 5))).
				add(Style.FONT.is(graphics().createFont("Helvetica", Font.Style.PLAIN, 18))).
				addSelected(Style.BACKGROUND.is(Background.solid(0xFFBBBBBB, 6, 4, 4, 6)));;
		
		Styles titulopadrao = Styles.none().
				add(Style.FONT.is(graphics().createFont("Helvetica", Font.Style.BOLD, 32)));
			
		Stylesheet rootSheet = Stylesheet.builder().
				add(Button.class, botaopadrao).
				add(Label.class, labelpadrao).
				create();
		
		Root root = iface.createRoot(AxisLayout.vertical().gap(15), rootSheet);
		root.setSize(graphics().width(), graphics().height());
		layerMenu.add(root.layer);
			
			
		Label titulo = new Label("Escolha seu personagem:");
		
		titulo.setStyles(titulopadrao);
		
		Label nomereitor = new Label("Nome do Reitor: _______________________");
		Button esportes = new Button().setText("Esportes");
		Label infoesportes = new Label("Upgrades de Velocidade e Força mais baratos");
		Button humanas = new Button().setText("Humanas");
		Label infohumanas = new Label("Upgrades de Poder de Ensino mais baratos");
		Button exatas = new Button().setText("Exatas");
		Label infoexatas = new Label("Upgrades de Estratégia e Foco mais baratos");
		Button biomedicas = new Button().setText("Biomedicas");
/*		Rectangle retangulo = new Rectangle(20,20,120,120);
		
		biomedicas.bounds(retangulo);*/
		
		esportes.clicked().connect(new UnitSlot() {
			@Override
			public void onEmit() {
				jogo.exibirTela(jogo.obterUniversidades());

			}
		});
		
		humanas.clicked().connect(new UnitSlot() {

			@Override
			public void onEmit() {
				jogo.exibirTela(jogo.obterUniversidades());

			}
		});
		
		exatas.clicked().connect(new UnitSlot() {

			@Override
			public void onEmit() {
				jogo.exibirTela(jogo.obterUniversidades());

			}
		});
		
		biomedicas.clicked().connect(new UnitSlot() {

			@Override
			public void onEmit() {
				jogo.exibirTela(jogo.obterUniversidades());

			}
		});		
		
		Label infobiomedicas = new Label("Upgrades de Pontos de Vida e Foco mais baratos");
	
		Button voltar = new Button().setText("Voltar");
		voltar.clicked().connect(new UnitSlot() {
			
			@Override
			public void onEmit() {
				jogo.exibirTela(jogo.obterMenu());
				
			}
		});
		
		root.add(titulo, nomereitor, esportes, infoesportes, humanas, infohumanas, exatas, infoexatas, biomedicas, infobiomedicas, voltar);
		
	}
}
