package com.mac242.guerradasuniversidades.html;

import playn.core.PlayN;
import playn.html.HtmlGame;
import playn.html.HtmlPlatform;

import com.mac242.guerradasuniversidades.core.GuerraDasUniversidades;

public class GuerraDasUniversidadesHtml extends HtmlGame {

  @Override
  public void start() {
    HtmlPlatform platform = HtmlPlatform.register();
    platform.assetManager().setPathPrefix("guerradasuniversidades/");
    PlayN.run(new GuerraDasUniversidades());
  }
}
