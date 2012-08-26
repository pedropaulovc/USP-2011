package com.mac242.guerradasuniversidades.core;

import static playn.core.PlayN.graphics;
import static playn.core.PlayN.keyboard;
import playn.core.Game;
import playn.core.Keyboard;

public class GuerraDasUniversidades implements Game {
	
	private TipoTela atual;
	private Menu menu;
	private Opcoes opcoes;
	private Recordes recordes;
	private KonamiCode kc;
	private Iniciar iniciar;
	private Universidades universidades;
	private TelaPrincipal telaprincipal;
		
	public GuerraDasUniversidades(){
		menu = new Menu(this);
		opcoes = new Opcoes(this);
		recordes = new Recordes(this);
		kc = new KonamiCode(this);
		iniciar = new Iniciar(this);
		universidades = new Universidades(this);
		telaprincipal = new TelaPrincipal(this);
	}
	
	@Override
	public void init() {
		graphics().setSize(711, 531);
		tratarTeclado();
		exibirTela(menu);
	}

	private void tratarTeclado() {
		keyboard().setListener(new Keyboard.Adapter() {
			public void onKeyDown(Keyboard.Event event) {
				int key = event.keyCode();
				if (key == Keyboard.KEY_ESC) {
					exibirTela(menu);
				} else if(kc.pressionarTecla(key)) {
					exibirTela(kc);
				}
			}
		});
	}

	public void exibirTela(TipoTela tela){
		if(atual != null){
			atual.shutdown();
		}
		atual = tela;
		atual.init();
	}
	
	@Override
	public void update(float delta) {
		atual.update(delta);
	}

	@Override
	public void paint(float alpha) {
		atual.paint(alpha);
	}

	@Override
	public int updateRate() {
		return 100;
	}

	public Menu obterMenu(){
		return menu;
	}
	
	public Opcoes obterOpcoes(){
		return opcoes;
	}
	
	public Recordes obterRecordes(){
		return recordes;
	}
	
	public Iniciar obterIniciar(){
		return iniciar;
	}
	
	public Universidades obterUniversidades(){
		return universidades;
	}

	
	public TelaPrincipal obterTelaprincipal(){
		return telaprincipal;
	}
	
}
