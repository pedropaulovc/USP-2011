/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP3 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: DANIEL HUGUENIN - 5118403 E PEDRO PAULO - 7538743
 *
 * Neste arquivo estão implementados os protótipos definidos em
 * navegacao.h referentes às operações de interfaceamento do gerenciador
 * de arquivos com o usuário.
 */

#include "navegacao.h"

/**
 * Variável representante da coordenada atual na matriz de ladrilhos
 * do arquivo apontado pela mira.
 */
static coordenada coordArquivo = { 0, 0 };
/**
 * Variável responsável por armazenar a posição atual da câmera.
 */
static ponto posCam = { 0., 0., ALT };
/**
 * Variável exibirAviso é responsável por definir se um aviso deve ser exibido
 * no próximo redesenho da tela (Valor 1) ou não (Valor 0). Variável
 * lado armazena o tamanho do lado da matriz de ladrilhos.
 */
static int exibirAviso = 0, leitura = 0, lado;
/**
 * Variável apontadora do aviso a ser apresentado ao usuário caso exibirAviso
 * tenha valor 1.
 */
static char *aviso = "";

static void (*callback)(void);

/**
 * Definições dos códigos ASCII de teclas mapeadas a operações no programa. Teclas
 * de letras representam a versão minúscula.
 */
#define TECLA_ENTER 0xD
#define TECLA_INTERROG 0x3F
#define TECLA_ESC 0x1B
#define TECLA_DEL 0x7F
#define TECLA_A 0x61
#define TECLA_C 0x63
#define TECLA_D 0x64
#define TECLA_N 0x6E
#define TECLA_Q 0x71
#define TECLA_R 0x72
#define TECLA_X 0x78
#define TECLA_BACKSPACE 0x08

void desenharTela() {
	int i, j;
	/* Limpa cores e profundidade */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Matriz de projeção */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.2, 1.2, -1.2, 1.2, -2, 2);

	/* Matriz de modelagem */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Posicionamento da câmera */
	gluLookAt(posCam.x, posCam.y, posCam.z, posCam.x, posCam.y, 0, 0., 1., 0.);

	tElemento *t = manipulador->lista->cabeca->sucessor;

	/* Ladrilhos */
	lado = ceil(sqrt(NUM_ARQUIVOS));
	coordenada c;
	for (i = 0; i < lado && (t->info); i++) {
		c.i = i;
		for (j = 0; (j < lado) && (t->info); j++) {
			c.j = j;
			desenharLadrilho(c, t->info);
			t = t->sucessor;
		}
	}
	desenharNave();
	/* para garantir animação suave */
	glutSwapBuffers();

	/* atualiza a imagem */
	glFlush();
}

void desenharNave() {

	/* A câmera está fixa dentro da nave, precisamos desenhar a "moldura" */
	/* Versão supostamente mais limpa */
	GLdouble projection[16]; /* matriz da câmera */
	/* Sistema de coordenadas da câmera */
	glGetDoublev(GL_PROJECTION_MATRIX, projection);

	/* Deslocando para a câmera */
	glPushMatrix();
	glLoadMatrixd(projection);

	/* draw the texture to the screen, on a white box from (0,0) to (1, 1). Other shapes may be used. */
	glColor3f(1.0, 1.0, 1.0);

	/* you need to put a glTexCoord and glVertex call , one after the other, for each point */
	glBegin(GL_QUADS);
	glTexCoord2f(-1, 0);
	glVertex3f(-1.5, -1.5, 2);
	glTexCoord2f(-1, -1);
	glVertex3f(-1.5, 1.5, 2);
	glTexCoord2f(0, -1);
	glVertex3f(1.5, 1.5, 2);
	glTexCoord2f(0, 0);
	glVertex3f(1.5, -1.5, 2);
	glEnd();

	//glDeleteTextures(1, &image);

	ponto p = { -0.9, 1.25, 0 };
	desenharQuadrado("Novo ", p, 1);
	p.x = -.81;
	p.y = -1.25;
	p.z = 0;
	desenharQuadrado("Renomear", p, 1);
	p.x = .82;
	p.y = 1.25;
	p.z = 0;
	desenharQuadrado("Deletar", p, 1);
	p.x = .78;
	p.y = -1.25;
	p.z = 0;
	desenharQuadrado("Atualizar", p, 1);
	p.x = 0;
	p.y = -1.25;
	p.z = 0;
	desenharQuadrado("Abrir", p, 1);

	if (exibirAviso) {
		p.x = 0.4;
		p.y = 0.8;
		p.z = 0;
		desenharQuadrado(aviso, p, 1);
		if (!leitura) {
			exibirAviso = 0;
			glutTimerFunc(1000, limparAviso, 0);
		}

	}
	if (leitura) {

		desenharCaixadeEntrada(buffer);

	}

	desenharMoldura();
	desenharMira();

	glDisable(GL_DEPTH_TEST);
	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	/* Retorna à posição original */
	glPopMatrix();
}

void desenharMoldura() {

	glBegin(GL_LINE_STRIP);

	glColor3f(0, 0, 0);

	glVertex3f(+1.8 * LADO, +1.8 * LADO, ALT);
	glVertex3f(+1.8 * LADO, -1.8 * LADO, ALT);
	glVertex3f(-1.8 * LADO, -1.8 * LADO, ALT);
	glVertex3f(-1.8 * LADO, +1.8 * LADO, ALT);
	glVertex3f(+1.8 * LADO, +1.8 * LADO, ALT);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(+1.8 * LADO, +1.8 * LADO, ALT);
	glVertex3f(+5, +5, 0.);

	glVertex3f(-1.8 * LADO, +1.8 * LADO, ALT);
	glVertex3f(-5, +5, 0);

	glVertex3f(-1.8 * LADO, -1.8 * LADO, ALT);
	glVertex3f(-5, -5, 0);

	glVertex3f(+1.8 * LADO, -1.8 * LADO, ALT);
	glVertex3f(+5, -5, 0.);

	glEnd();

	glBegin(GL_QUADS);

	{
		/* Lado direito */
		glColor4f(0.23, .45, 0.45, 0.4);
		glVertex3f(+5, -5, 0.);
		glVertex3f(+5, +5, 0.);
		glVertex3f(+1.8 * LADO, +1.8 * LADO, ALT);
		glVertex3f(+1.8 * LADO, -1.8 * LADO, ALT);

		/* Lado esquerdo */
		glVertex3f(-5, -5, 0);
		glVertex3f(-5, +5, 0);
		glVertex3f(-1.8 * LADO, +1.8 * LADO, ALT);
		glVertex3f(-1.8 * LADO, -1.8 * LADO, ALT);

		/* Lado superior */
		glColor4f(0.21, .40, 0.40, 0.4);
		glVertex3f(-5, +5, 0);
		glVertex3f(+5, +5, 0);
		glVertex3f(+1.8 * LADO, +1.8 * LADO, ALT);
		glVertex3f(-1.8 * LADO, +1.8 * LADO, ALT);

		/* Lado inferior */
		glVertex3f(-5, -5, 0);
		glVertex3f(+5, -5, 0);
		glVertex3f(+1.8 * LADO, -1.8 * LADO, ALT);
		glVertex3f(-1.8 * LADO, -1.8 * LADO, ALT);
	}
	glEnd();
}

void desenharMira() {
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		glColor3f(1., 0., 0.);
		glVertex3f(-.25, 0, 1);
		glVertex3f(.25, 0, 1);
		glVertex3f(0, .25, 1);
		glVertex3f(0, -.25, 1);
	}
	glEnd();
}

void desenharLadrilho(coordenada coord, struct dirent *arquivo) {
	cor cor = { 0.4, 0.60, 0.4 };
	glPushMatrix();
	glTranslated(1.7 * LADO * coord.j, -1.2 * LADO * coord.i, 0.);

	switch (arquivo->d_type) {
	case DT_DIR:
		desenharDiretorio();
		break;
	case DT_REG:
		cor.r = 0.90;
		cor.g = 0.90;
		cor.b = 0.90;
		desenharArquivo(cor);
		break;
	case DT_BLK:
		cor.r = 0.85;
		cor.g = 0.36;
		cor.b = 0.26;
		desenharArquivo(cor);
		break;
	case DT_CHR:
		cor.r = 0.31;
		cor.g = 0.80;
		cor.b = 0.77;
		desenharArquivo(cor);
		break;
	case DT_FIFO:
		cor.r = 0.78;
		cor.g = 0.96;
		cor.b = 0.39;
		desenharArquivo(cor);
		break;
	case DT_LNK:
		cor.r = 1.;
		cor.g = 0.42;
		cor.b = 0.42;
		desenharArquivo(cor);
		break;
	case DT_SOCK:
		cor.r = 0.82;
		cor.g = 0.95;
		cor.b = 0.65;
		desenharArquivo(cor);
		break;
	case DT_UNKNOWN:
		cor.r = 0.4;
		cor.g = 0.60;
		cor.b = 0.4;
		desenharArquivo(cor);
		break;
	case DT_WHT:
		cor.r = 1.;
		cor.g = 0.77;
		cor.b = 0.55;
		desenharArquivo(cor);
		break;
	default:
		desenharArquivo(cor);
		break;
	}

	desenharNome(arquivo->d_name);
	glPopMatrix();
}

void desenharDiretorio() {
	glBegin(GL_QUADS);
	{
		/* Corpo */
		glColor3f(0.95, 0.77, 0.35);
		glVertex3f(-LADO / 1.3 + .05, -LADO / 2. + .05, 0.01);
		glVertex3f(+LADO / 1.3 - 0.05, -LADO / 2. + .05, 0.01);
		glVertex3f(+LADO / 1.3 - 0.05, +LADO / 2.5 - .03, 0.01);
		glVertex3f(-LADO / 1.3 + .05, +LADO / 2.5 - .03, 0.01);

		/* Aba */
		glColor3f(0.75, 0.57, 0.15);
		glVertex3f(0, +LADO / 2.5 - .03, 0.01);
		glVertex3f(-LADO / 1.3 + .05, +LADO / 2.5 - .03, 0.01);
		glVertex3f(-LADO / 1.3 + .05, .25, 0.01);
		glVertex3f(-.1, .25, 0.01);
	}
	glEnd();

	/* Contorno */
	glBegin(GL_LINE_STRIP);
	{
		glColor3f(0., 0., 0.);
		glVertex3f(-LADO / 1.3 + .05, +LADO / 2.5 - .03, 0.02);
		glVertex3f(-LADO / 1.3 + .05, -LADO / 2. + .05, 0.02);
		glVertex3f(+LADO / 1.3 - 0.05, -LADO / 2. + .05, 0.02);

		glVertex3f(+LADO / 1.3 - 0.05, +LADO / 2.5 - .03, 0.02);
		glVertex3f(0, +LADO / 2.5 - .03, 0.02);
		glVertex3f(-LADO / 1.3 + .05, +LADO / 2.5 - .03, 0.02);

		glVertex3f(-LADO / 1.3 + .05, .25, 0.02);
		glVertex3f(-.1, .25, 0.02);
		glVertex3f(0, +LADO / 2.5 - .03, 0.02);
	}
	glEnd();
}

void desenharArquivo(cor c) {
	glColor3f(c.r, c.g, c.b);
	/* Corpo */
	glBegin(GL_POLYGON);
	{
		glVertex3f(-LADO / 1.3 + .05, -LADO / 2. + .05, 0.01);
		glVertex3f(+LADO / 1.3 - 0.05, -LADO / 2. + .05, 0.01);
		glVertex3f(+LADO / 1.3 - 0.05, +LADO / 2. - .05, 0.01);
		glVertex3f(-LADO / 1.3 + .1, +LADO / 2. - .05, 0.01);
		glVertex3f(-LADO / 1.3 + .05, +LADO / 2. - .1, 0.01);
	}
	glEnd();

	/* Dobra */
	glLineWidth(0.1);
	glBegin(GL_LINE_STRIP);
	{
		glColor3f(0., 0., 0.);
		glVertex3f(-LADO / 1.3 + .05, +LADO / 2. - .1, 0.02);
		glVertex3f(-LADO / 1.3 + .1, +LADO / 2. - .1, 0.02);
		glVertex3f(-LADO / 1.3 + .1, +LADO / 2. - .05, 0.02);
	}
	glEnd();

	/* Contorno */
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	{

		glColor3f(0., 0., 0.);
		glVertex3f(-LADO / 1.3 + .05, -LADO / 2. + .05, 0.02);
		glVertex3f(+LADO / 1.3 - 0.05, -LADO / 2. + .05, 0.02);
		glVertex3f(+LADO / 1.3 - 0.05, +LADO / 2. - .05, 0.02);
		glVertex3f(-LADO / 1.3 + .1, +LADO / 2. - .05, 0.02);
		glVertex3f(-LADO / 1.3 + .05, +LADO / 2. - .1, 0.02);
		glVertex3f(-LADO / 1.3 + .05, -LADO / 2. + .05, 0.02);
	}
	glEnd();
}

void desenharNome(char *nome) {
	char nomeCurto[16];
	strncpy(nomeCurto, nome, 16);

	if (strlen(nome) > 16) {
		nomeCurto[12] = nomeCurto[13] = nomeCurto[14] = '.';
		nomeCurto[15] = '\0';
	}

	ponto p = { -LADO / 1.3 + .1, .1, 0.2 };
	imprimir(nomeCurto, p, MONOSPACE_8);
}

void desenharQuadrado(char *text, ponto p, GLdouble largura) {

	int len = strlen(text);

	glBegin(GL_LINE_STRIP);{
		glColor3f(0, 0, 0);
		glVertex3f(p.x - 0.2 * len / 6, p.y + 0.1 * largura, p.z);
		glVertex3f(p.x + 0.2 * len / 6, p.y + 0.1 * largura, p.z);
		glVertex3f(p.x + 0.2 * len / 6, p.y - 0.1 * largura, p.z);
		glVertex3f(p.x - 0.2 * len / 6, p.y - 0.1 * largura, p.z);
		glVertex3f(p.x - 0.2 * len / 6, p.y + 0.1 * largura, p.z);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(p.x - 0.2 * len / 6, p.y + 0.1 * largura, p.z);
		glVertex3f(p.x + 0.2 * len / 6, p.y + 0.1 * largura, p.z);
		glVertex3f(p.x + 0.2 * len / 6, p.y - 0.1 * largura, p.z);
		glVertex3f(p.x - 0.2 * len / 6, p.y - 0.1 * largura, p.z);
	}
	glEnd();

	ponto q = { p.x - len * 0.025, p.y - 0.03, p.z - 0.05 };
	imprimir(text, q, MONOSPACE_9);
}

void desenharCaixadeEntrada(char *text) {

	ponto q;

	q.x = -1;
	q.y = -1;
	q.z = -0.1;

	glBegin(GL_QUADS);
	{
		glColor3f(0.8, 0.8, 0.8);
		glVertex3f(-1.05, -1.05, 0);
		glVertex3f(1.05, -1.05, 0);
		glVertex3f(1.05, -0.9, 0);
		glVertex3f(-1.05, -0.9, 0);
	}
	glEnd();

	imprimir(text, q, MONOSPACE_9);
}

void imprimir(char *s, ponto p, fonte fonte) {
	void *funcao_fonte = GLUT_BITMAP_9_BY_15;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos3f(p.x, p.y, p.z);

	switch (fonte) {
	case MONOSPACE_8:
		funcao_fonte = GLUT_BITMAP_8_BY_13;
		break;
	case HELVETICA_10:
		funcao_fonte = GLUT_BITMAP_HELVETICA_10;
		break;
	default:
		break;
	}

	while (*s)
		glutBitmapCharacter(funcao_fonte, *s++);
}

void limparAviso(int a) {
	glutPostRedisplay();
}

void tratarTeclado(unsigned char k, int x, int y) {

	if (leitura) {
		int i = 0;
		if (k == TECLA_ENTER) {
			leitura = 0;
			callback();
			glutPostRedisplay();
			return;
		}
		if (k == TECLA_BACKSPACE) {
			while (buffer[i] != '\0')
				i++;
			if (i != 0)
				buffer[i - 1] = '\0';
			glutPostRedisplay();
			return;
		}
		while (buffer[i] != '\0')
			i++;
		if (i < 39) {
			buffer[i] = k;
			buffer[i + 1] = '\0';
		}
		glutPostRedisplay();

		return;
	}

	switch (k) {
	case TECLA_ENTER:
		abrirArquivo();
		break;

	case TECLA_C:
	case TECLA_N:
		criarArquivo();
		break;

	case TECLA_R:
		renomearArquivo();
		break;

	case TECLA_A:
		atualizarTela(TRUE);
		break;

	case TECLA_D:
	case TECLA_DEL:
		deletarArquivo();
		break;

	case TECLA_ESC:
	case TECLA_Q:
	case TECLA_X:
		exit(0);
		break;

	case TECLA_INTERROG:
		exibirMenu();
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void tratarTecladoEspecial(int k, int x, int y) {
	switch (k) {
	case GLUT_KEY_RIGHT:
		if ((coordArquivo.i == NUM_ARQUIVOS / lado && coordArquivo.j + 1
				== NUM_ARQUIVOS % lado) || coordArquivo.j + 1 == lado) {
			return;
		}

		animarMovimento(1020, HORIZONTAL);
		coordArquivo.j++;
		break;

	case GLUT_KEY_F5:
		atualizarTela(TRUE);
		break;

	case GLUT_KEY_LEFT:
		if (coordArquivo.j == 0) {
			return;
		}

		animarMovimento(-1020, HORIZONTAL);
		coordArquivo.j--;
		break;

	case GLUT_KEY_UP:
		if (coordArquivo.i == 0) {
			return;
		}
		animarMovimento(720, VERTICAL);
		coordArquivo.i--;
		break;

	case GLUT_KEY_DOWN:
		if ((coordArquivo.i == (NUM_ARQUIVOS / lado) - 1 && coordArquivo.j + 1
				> NUM_ARQUIVOS % lado) || coordArquivo.i == NUM_ARQUIVOS / lado) {
			return;
		}

		animarMovimento(-720, VERTICAL);
		coordArquivo.i++;
		break;
	default:
		break;
	}
}

void tratarMouse(int b, int s, int x, int y) {
	/* Botão direito atualiza a tela*/
	if (b == GLUT_RIGHT_BUTTON) {
		atualizarTela(TRUE);
		return;
	}

	/* Botão esquerdo move a câmera para um ladrilho vizinho ou executa
	 * uma função */
	if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN) {
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX, winY, winZ;

		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetIntegerv(GL_VIEWPORT, viewport);

		winX = (float) x;
		winY = (float) viewport[3] - (float) y;
		glReadPixels(x, (int) winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

		ponto p = { winX, winY, winZ };
		acao clique = mapearTela(p);

		switch (clique) {
		case DIAGDIRSUP:
			if (coordArquivo.i != 0 && coordArquivo.j != lado - 1) {
				tratarTecladoEspecial(GLUT_KEY_UP, 0, 0);
				tratarTecladoEspecial(GLUT_KEY_RIGHT, 0, 0);
			}
			break;

		case DIAGESQSUP:
			if (coordArquivo.i != 0 && coordArquivo.j != 0) {
				tratarTecladoEspecial(GLUT_KEY_UP, 0, 0);
				tratarTecladoEspecial(GLUT_KEY_LEFT, 0, 0);
			}
			break;

		case DIAGESQINF:
			if (!((coordArquivo.i == (NUM_ARQUIVOS / lado) - 1
					&& coordArquivo.j > NUM_ARQUIVOS % lado) || coordArquivo.i
					== NUM_ARQUIVOS / lado || coordArquivo.j == 0)) {
				tratarTecladoEspecial(GLUT_KEY_LEFT, 0, 0);
				tratarTecladoEspecial(GLUT_KEY_DOWN, 0, 0);
			}
			break;

		case DIAGDIRINF:
			if (!((coordArquivo.i == (NUM_ARQUIVOS / lado) - 1
					&& coordArquivo.j + 2 > NUM_ARQUIVOS % lado)
					|| coordArquivo.i == NUM_ARQUIVOS / lado) && coordArquivo.j
					!= lado - 1) {
				tratarTecladoEspecial(GLUT_KEY_RIGHT, 0, 0);
				tratarTecladoEspecial(GLUT_KEY_DOWN, 0, 0);
			}
			break;

		case CIMA:
			tratarTecladoEspecial(GLUT_KEY_UP, 0, 0);
			break;

		case BAIXO:
			tratarTecladoEspecial(GLUT_KEY_DOWN, 0, 0);
			break;

		case DIREITA:
			tratarTecladoEspecial(GLUT_KEY_RIGHT, 0, 0);
			break;

		case ESQUERDA:
			tratarTecladoEspecial(GLUT_KEY_LEFT, 0, 0);
			break;

		case DELETAR:
			deletarArquivo();
			break;

		case ATUALIZAR:
			atualizarTela(TRUE);
			break;

		case RENOMEAR:
			renomearArquivo();
			break;

		case ABRIR:
			abrirArquivo();
			break;

		case NOVO:
			criarArquivo();
			break;

		default:
			break;
		}

		posCam.z = ALT;
		glutPostRedisplay();

		return;
	}
}

acao mapearTela(ponto p) {
	p.x -= 250;
	p.y -= 250;
	if (abs(p.x) < 187 && abs(p.y) < 185) {
		/* Região de visualização dos ladrilhos */

		if (p.x > 116 && abs(p.y) < 60) {
			return DIREITA;
		}
		if (p.x < -116 && abs(p.y) < 60) {
			return ESQUERDA;
		}
		if (p.y < -86 && abs(p.x) < 95) {
			return BAIXO;
		}
		if (p.y > 86 && abs(p.x) < 95) {
			return CIMA;
		}
		if (p.x > 116 && p.y > 87) {
			return DIAGDIRSUP;
		}
		if (p.x < -116 && p.y > 87) {
			return DIAGESQSUP;
		}
		if (p.x < -116 && p.y < -87) {
			return DIAGESQINF;

		}
		if (p.x > 116 && p.y < -87) {
			return DIAGDIRINF;
		}

	} else {
		if (p.y > 200 && p.y < 232) {
			/* Parte de cima do painel */
			if (p.x > -188 && p.x < -128) {
				return NOVO;
			}
			if (p.x > 100 && p.x < 183) {
				return DELETAR;
			}
		} else {
			/* Parte de baip.xo do painel */
			if (p.y > -235 && p.y < -200) {
				if (p.x > -186 && p.x < -96) {
					return RENOMEAR;
				}

				if (p.x > -30 && p.x < 30) {
					return ABRIR;

				}
				if (p.x > 80 && p.x < 187) {
					return ATUALIZAR;
				}
			}

		}
	}

	return INVALIDO;
}

void animarMovimento(GLint distancia, tipoAnim tipo) {
	int i;
	void *animacao;

	if (tipo == HORIZONTAL)
		animacao = animarHorizontal;
	else
		animacao = animarVertical;

	for (i = 0; i < 100; i++)
		glutTimerFunc(i * 2, animacao, distancia);
}

void animarHorizontal(GLint distancia) {
	GLfloat distanciaCam = distancia;

	posCam.x = posCam.x + distanciaCam / 100000;
	glutPostRedisplay();
}

void animarVertical(GLint distancia) {
	GLfloat distanciaCam = distancia;

	posCam.y = posCam.y + distanciaCam / 100000;
	glutPostRedisplay();
}

void atualizarTela(int avisar) {
	atualizarLista(manipulador);

	if (POSICAO_ATUAL >= NUM_ARQUIVOS) {
		coordArquivo.i = coordArquivo.j = 0;
		posCam.x = posCam.y = 0;
	}

	if (avisar) {
		exibirAviso = 1;
		aviso = "Atualizada!";
	}

	glutPostRedisplay();
}

void exibirMenu() {
	puts("Todas as operações são realizadas no arquivo na mira da nave.");
	puts("d ou DEL - Deletar o arquivo");
	puts("ENTER - Abrir o diretorio");
	puts("r - Renomeia o arquivo");
	puts("c ou n - Cria um arquivo (se nao existe)");
	puts("F5 ou a - Atualiza a lista de arquivos");
	puts("? - Exibe este menu");
	puts("q ou ESC - Fecha o gerenciador de arquivos");
}

void abrirArquivo() {
	char destino[PATH_MAX];

	exibirAviso = 1;
	if (ARQUIVO_ATUAL->d_type != DT_DIR) {
		aviso = "Nao e diretorio";
		return;
	}

	if (!obterDirAbsoluto(manipulador->path, ARQUIVO_ATUAL->d_name, destino)) {
		aviso = "Erro";
		return;
	}

	manip *tmp = abrirDiretorio(destino);
	if (!tmp) {
		aviso = "Erro";
		return;
	}

	aviso = "Abriu Diretorio";

	fecharDiretorio(manipulador);
	manipulador = tmp;

	coordArquivo.i = coordArquivo.j = 0;
	posCam.x = posCam.y = 0;
}

void criarArquivo() {
	char destino[PATH_MAX];

	if ((buffer[0] == '\0') && (leitura == 0)) {
		leitura = 1;
		callback = &criarArquivo;
		exibirAviso = 1;
		aviso = "Nome do arquivo:";
		desenharTela();
	}
	if ((buffer[0] != '\0') && (leitura == 0)) {
		exibirAviso = 1;
		gerarCaminhoDir(manipulador->path, buffer, destino);

		aviso = "Arquivo Criado";
		if (criar(manipulador, destino) == -1)
			aviso = "Erro!";
		buffer[0] = '\0';
	}
}

void renomearArquivo() {
	char destino[PATH_MAX];
	char fonte[PATH_MAX];

	if ((buffer[0] == '\0') && (leitura == 0)) {
		leitura = 1;
		callback = &renomearArquivo;
		exibirAviso = 1;
		aviso = "Nome do arquivo:";
		desenharTela();
	}

	if ((buffer[0] != '\0') && (leitura == 0)) {

		gerarCaminhoDir(manipulador->path, buffer, destino);
		exibirAviso = 1;
		aviso = "Arquivo Renomeado";

		if (!obterDirAbsoluto(manipulador->path, ARQUIVO_ATUAL->d_name, fonte))
			aviso = "Erro";
		if (renomear(manipulador, fonte, destino) == -1)
			aviso = "Erro";
		buffer[0] = '\0';

		if (POSICAO_ATUAL == NUM_ARQUIVOS) {
			if (coordArquivo.j == 0)
				tratarTecladoEspecial(GLUT_KEY_UP, 0, 0);
			else
				tratarTecladoEspecial(GLUT_KEY_LEFT, 0, 0);
		}

	}
}

void deletarArquivo() {
	char destino[PATH_MAX];

	exibirAviso = 1;

	aviso = "Arquivo Removido";
	if (!obterDirAbsoluto(manipulador->path, ARQUIVO_ATUAL->d_name, destino))
		aviso = "Erro";
	else if (remover(manipulador, destino) == -1)
		aviso = "Erro";

	if (POSICAO_ATUAL == NUM_ARQUIVOS) {
		if (coordArquivo.j == 0)
			tratarTecladoEspecial(GLUT_KEY_UP, 0, 0);
		else
			tratarTecladoEspecial(GLUT_KEY_LEFT, 0, 0);
	}
}
