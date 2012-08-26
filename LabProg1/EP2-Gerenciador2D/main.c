/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP3 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: DANIEL HUGUENIN - 5118403 E PEDRO PAULO - 7538743
 *
 * Neste arquivo está definida a função main do gerenciador de arquivos gráfico
 * implementao utilizando a biblioteca OpenGL/GLUT.
 */

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "gerenciador.h"
#include "navegacao.h"

int main(int ac, char *av[]) {

	buffer[0] = '\0'; /* Limpando o buffer */

	manipulador = abrirDiretorio(getenv("PWD"));

	if (!manipulador) {
		puts("Não foi possível abrir o diretório corrente");
		return 1;
	}


	/* Inicialização */
	glutInit(&ac, av);

	/* Buffers duplos, RGB, profundidade */
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);

	/* Tamanho da janela */
	glutInitWindowSize(500, 500);

	/* Criação da janela */
	glutCreateWindow("Projeto MAC0211-11: Daniel Huguenin e Pedro Paulo");

	/* Configurações de desenho */
	glEnable(GL_DEPTH_TEST); /* teste de profundidade, para 3D */
	glClearColor(1, 1, 1, 1); /* cor de fundo */

	/* Habilitando a textura para o background */
	glEnable(GL_TEXTURE_2D);

	/* Habilitando a transparência do painel "de vidro" da nave. */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(desenharTela); /* Registro da função de desenho */
	glutKeyboardFunc(tratarTeclado); /* idem, teclas normais teclado */
	glutSpecialFunc(tratarTecladoEspecial); /* idem, teclas especiais teclado */
	glutMouseFunc(tratarMouse); /* idem, mouse */

	/* Associando uma referência para o background. */
	glGenTextures(1, &image);

	/* Carregando a imagem contida em background.c na memória. */
	gluBuild2DMipmaps(GL_TEXTURE_2D, gimp_image.bytes_per_pixel,
			gimp_image.width, gimp_image.height, GL_RGBA, GL_UNSIGNED_BYTE,
			gimp_image.pixel_data);

	glutMainLoop(); /* Começa!!!! */
	return 0;
}
