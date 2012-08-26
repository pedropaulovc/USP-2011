package com.mac242.guerradasuniversidades.core;

import playn.core.Color;

public class Recordes extends TipoTela {

	public Recordes(GuerraDasUniversidades jogo){
		super(jogo);
	}
	
	@Override
	public void init() {
		iniciarBase();
		desenharFundo(Color.rgb(255, 255, 0));
	}

	@Override
	public void paint(float alpha) {
		// TODO Auto-generated method stub

	}

	@Override
	public void update(float delta) {
		// TODO Auto-generated method stub

	}

	@Override
	public void shutdown() {
		destruirBase();
	}

	public String toString(){
		return "Recordes";
	}
}
