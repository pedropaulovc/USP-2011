/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP3 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: DANIEL HUGUENIN - 5118403 E PEDRO PAULO - 7538743
 *
 * Neste arquivo estão definidos os protótipos a serem implementados em
 * navegacao.c referentes às operações de interfaceamento gráfico do
 * gerenciador de arquivos com o usuário além de definições de constantes
 * usadas ao longo do programa.
 */

#include <string.h>
#include <stdio.h>
#include <GL/glut.h> /* Uso do Glut */
#include <stdlib.h>
#include <math.h>
#include "gerenciador.h"
#include "lista/lista.h"
#include "background.c" /* Imagem do backgound */


/**
 * Variável que identifica a textura do background
 */
GLuint image;

/**
 * Definição do tamanho do ladrilho e altura padrão da câmera
 */
#define LADO  .6
/**
 * Definição da altura da câmera
 */
#define ALT 1
/**
 * Definição da posição atual na lista de arquivos do diretório do ladrilho
 * apontado pela mira.
 */
#define POSICAO_ATUAL coordArquivo.i * lado + coordArquivo.j
/**
 * Definição do ponteiro para o arquivo na lista de arquivos referenciado pela
 * mira.
 */
#define ARQUIVO_ATUAL obterPosicao(manipulador->lista, POSICAO_ATUAL)
/**
 * Definição do número de arquivos no diretório.
 */
#define NUM_ARQUIVOS manipulador->lista->numElementos

/**
 * Enumeração de fontes utilizáveis pela função imprimir.
 */
typedef enum {
	MONOSPACE_8, HELVETICA_10, MONOSPACE_9
} fonte;

/**
 * Enumeração das ações realizáveis através de um clique na tela, mapeado
 * pela função mapear.
 */
typedef enum {
	NOVO,
	DELETAR,
	RENOMEAR,
	DIREITA,
	CIMA,
	ESQUERDA,
	BAIXO,
	DIAGDIRSUP,
	DIAGESQSUP,
	DIAGESQINF,
	DIAGDIRINF,
	INVALIDO,
	ATUALIZAR,
	ABRIR
} acao;

/**
 * Enumeração das possibilidades de animação ao trocar de ladrilhos.
 */
typedef enum {
	HORIZONTAL, VERTICAL
} tipoAnim;

/**
 * Definição do tipo abstrato de dados ponto, contendo três coordenadas.
 */
typedef struct {
	GLfloat x, y, z;
} ponto;

/**
 * Definição do tipo abstrato de dados cor, contendo três componentes.
 */
typedef struct {
	GLfloat r, g, b;
} cor;

/**
 * Definição do tipo abstrato de dados coordenada, contendo dois índices.
 */
typedef struct {
	GLint i, j;
} coordenada;

/**
 * Variável apontadora do diretório aberto atualmente pelo programa.
 */
manip *manipulador;

/* Variável buffer da entrada do usuário */
char buffer[40];


/**
 * Esta função é responsável por exibir na tela um campo para o usuário fornecer
 * parâmetros de texto. Exibe o texto digitado até o momento passado através da
 * variável text.
 */
void desenharCaixadeEntrada(char *text);

/**
 * Função responsável por redesenhar toda a tela, composta pela moldura, mira,
 * ladrilhos, botões e opcionalmente um aviso caso a variável exibirAviso esteja
 * com valor 1.
 */
void desenharTela();

/**
 * Subfunção de desenho da nave, imprime a moldura, mira, botões e opcionalmente o
 * aviso.
 */
void desenharNave();
/**
 * Subfunção de desenho da moldura, uma "caixa" vazada por onde a câmera avista os
 * ladrilhos.
 */
void desenharMoldura();
/**
 * Subfunção de desenho da mira, uma cruz no centro da tela.
 */
void desenharMira();

/**
 * Função responsável por receber uma coordenada e desenhar o ladrilho
 * que representará o arquivo "arquivo" e seu rótulo. Decide o formato e a cor
 * do ladrilho em função de seu campo d_type.
 */
void desenharLadrilho(coordenada c, struct dirent *arquivo);
/**
 * Subfunção de desenho de diretório apontado , um polígono representando uma
 * pasta com um nome rotulado.
 */
void desenharDiretorio();
/**
 * Subfunção de desenho de arquivo, recebe como parâmetro a cor a ser
 * utilizada.
 */
void desenharArquivo(cor c);
/**
 * Subfunção de desenho de nome de arquivos e diretórios. Caso o nome
 * seja maior que o representável na figura adiciona reticências no final.
 */
void desenharNome(char *nome);
/**
 * Função de desenho de um quadrado com texto apontado por text, posicionado
 * no ponto p, e com largura (no eixo y) de "largura".
 */
void desenharQuadrado(char *text, ponto p, GLdouble largura);

/**
 * Função de impressão de texto na tela. Recebe como parâmetro o texto
 * a ser impresso na variável s, o ponto inicial de impressão em p e a
 * fonte a ser utilizada em "fonte".
 */
void imprimir(char *s, ponto p, fonte fonte);
/**
 * Função responsável por limpar um aviso previamente impresso, redesenhando
 * a tela.
 */
void limparAviso(int a);

/**
 * Função responsável por tratar eventos de pressionamento de teclas normais
 * de teclado e delegar a tarefa a ser realizada à função responsável. Recebe
 * como parâmetro a tecla em k, e as coordenadas do ponto onde foi pressionada
 * a tecla em x e y.
 */
void tratarTeclado(unsigned char k, int x, int y);
/**
 * Função responsável por tratar eventos de pressionamento de teclas especiais
 * de teclado e delegar a tarefa a ser realizada à função responsável. Recebe
 * como parâmetro a tecla em k, e as coordenadas do ponto onde foi pressionada
 * a tecla em x e y.
 */
void tratarTecladoEspecial(int k, int x, int y);
/**
 * Função responsável por tratar eventos de cliques de mouse, recebendo como
 * parâmetros o botão clicado em botao, o estado do clique em "estado" e as
 * coordenadas do clique em x e y. Delega a tarefa a ser realizada à função
 * responsável.
 */
void tratarMouse(int botao, int estado, int x, int y);

/**
 * Função responsável por receber um clique no ponto p da tela e retornar a
 * ação a ser realizada pela função de tratamento de mouse.
 */
acao mapearTela(ponto p);

/**
 * Função responsável por receber a distância a ser animada em "distancia" e
 * o tipo de animação em "tipo" e delegar a tarefa à função competente de animação.
 */
void animarMovimento(GLint distancia, tipoAnim tipo);
/**
 * Função responsável por animar um movimento horizontal ao movimentar a câmera
 * a distância "distancia" passada por parâmetro e redesenhar a tela.
 */
void animarHorizontal(GLint distancia);
/**
 * Função responsável por animar um movimento vertical ao movimentar a câmera
 * a distância "distancia" passada por parâmetro e redesenhar a tela.
 */
void animarVertical(GLint distancia);

/**
 * Função responsável por invocar o redesenho da tela, informando o usuário
 * da operação caso a variável "avisar" esteja definida com valor verdadeiro.
 * Movimenta a mira para a posição (0,0) caso o ladrilho anteriormente apontado
 * pela mira não exista mais.
 */
void atualizarTela(int avisar);

/**
 * Esta função exibe na saída padrão uma lista contendo as opções disponíves
 * do programa.
 */
void exibirMenu();
/**
 * Esta função é responsável por abrir o arquivo apontado pela mira no programa.
 * Caso o arquivo seja um diretório acessível, o abre e exibe seus conteúdos. Caso
 * contrário exibe "Erro" ao usuário.
 */
void abrirArquivo();
/**
 * Esta função é responsável por criar um novo arquivo recebendo da entrada padrão
 * um caminho absoluto ou relativo do arquivo a ser criado. Informa o usuário do
 * sucesso ou fracasso da operação.
 */
void criarArquivo();
/**
 * Esta função é responsável por renomear o arquivo apontado pela mira recebendo
 * da entrada padrão um caminho absoluto ou relativo do novo nome do arquivo
 * a ser renomeado. Informa o usuário do sucesso ou fracasso da operação.
 */
void renomearArquivo();
/**
 * Esta função é responsável por deletar o arquivo apontado pela mira. Informa o
 * usuário do sucesso ou fracasso da operação.
 */
void deletarArquivo();

