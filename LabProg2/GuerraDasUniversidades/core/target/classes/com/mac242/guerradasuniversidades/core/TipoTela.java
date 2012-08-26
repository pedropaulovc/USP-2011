package com.mac242.guerradasuniversidades.core;

import static playn.core.PlayN.graphics;
import playn.core.GroupLayer;
import playn.core.SurfaceLayer;

public abstract class TipoTela {

	protected GuerraDasUniversidades jogo;
	protected GroupLayer base;

	public TipoTela(GuerraDasUniversidades jogo) {
		this.jogo = jogo;
	}

	protected void iniciarBase() {
		base = graphics().createGroupLayer();
		graphics().rootLayer().add(base);
	}
	
	protected void destruirBase(){
		base.destroy();
		base = null;
	}

	protected void desenharFundo(int cor) {
		SurfaceLayer bg = graphics().createSurfaceLayer(graphics().width(),	graphics().height());
		bg.surface().setFillColor(cor);
		bg.surface().fillRect(0, 0, bg.surface().width(), bg.surface().height());
		base.add(bg);
	}
	
	public abstract void init();

	public abstract void paint(float alpha);

	public abstract void update(float delta);

	public abstract void shutdown();
}