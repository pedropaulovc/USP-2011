package com.mac242.guerradasuniversidades.core;

import static playn.core.PlayN.assetManager;
import static playn.core.PlayN.graphics;
import static playn.core.PlayN.pointer;
import playn.core.Color;
import playn.core.Font;
import playn.core.GroupLayer;
import playn.core.Image;
import playn.core.ImageLayer;
import react.UnitSlot;
import tripleplay.ui.AxisLayout;
import tripleplay.ui.Background;
import tripleplay.ui.Button;
import tripleplay.ui.Group;
import tripleplay.ui.Interface;
import tripleplay.ui.Root;
import tripleplay.ui.Style;
import tripleplay.ui.Styles;
import tripleplay.ui.Stylesheet;

public class Menu extends TipoTela {
	private Interface iface;
	
	public Menu(GuerraDasUniversidades jogo) {
		super(jogo);
	}
	
	@Override
	public void init() {
		iniciarBase();
		desenharFundo(Color.rgb(255, 255, 255));
		desenharLogo();
		desenharMenu();
	}

	private void desenharMenu() {
		GroupLayer layerMenu = graphics().createGroupLayer();
		layerMenu.transform().translateX(10);
		base.add(layerMenu);
		
		iface = new Interface(null);
		pointer().setListener(iface.plistener);
		
		Styles buttonStyles = Styles.none().
			add(Style.BACKGROUND.is(Background.solid(0xFFCCCCCC, 5))).
			add(Style.FONT.is(graphics().createFont("Helvetica", Font.Style.PLAIN, 18))).
			addSelected(Style.BACKGROUND.is(Background.solid(0xFFBBBBBB, 6, 4, 4, 6)));
		Stylesheet rootSheet = Stylesheet.builder().
			add(Button.class, buttonStyles).
			create();

		Root root = iface.createRoot(AxisLayout.vertical().offStretch(), rootSheet);
		root.setSize(250, graphics().height());
		layerMenu.add(root.layer);

		Group buttons = new Group(AxisLayout.vertical().offStretch());
		root.add(buttons);

		for (final TipoTela tela : new TipoTela[] { jogo.obterIniciar(), jogo.obterOpcoes(),
				jogo.obterRecordes() }) {
			Button button = new Button().setText(tela.toString());
			buttons.add(button);
			button.clicked().connect(new UnitSlot() {
				public void onEmit() {
					jogo.exibirTela(tela);
				}
			});
		}
		
		Button sair = new Button().setText("Sair");
		buttons.add(sair);
		sair.clicked().connect(new UnitSlot() {
			public void onEmit() {
				//System.exit(0);
			}
		});
	}

	private void desenharLogo() {
		Image logo = assetManager().getImage("images/logo.jpg");
		ImageLayer layerLogo = graphics().createImageLayer(logo);
		layerLogo.transform().translate(270, 50);
		base.add(layerLogo);
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
		return "Menu";
	}
}
