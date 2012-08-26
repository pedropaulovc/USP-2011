package com.mac242.guerradasuniversidades.java;

import playn.core.PlayN;
import playn.java.JavaPlatform;

import com.mac242.guerradasuniversidades.core.GuerraDasUniversidades;

public class GuerraDasUniversidadesJava {

  public static void main(String[] args) {
    JavaPlatform platform = JavaPlatform.register();
    platform.assetManager().setPathPrefix("src/main/java/com/mac242/guerradasuniversidades/resources");
    platform.setTitle("Guerra das Universidades");
    PlayN.run(new GuerraDasUniversidades());
  }
}
