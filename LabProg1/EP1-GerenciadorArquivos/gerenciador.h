/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP1 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403
 *
 * Neste arquivo estão definidos os protótipos a serem implementados em
 * gerenciador.c referentes às operações de gerenciamento de arquivos
 * além de definições de constantes usadas ao longo do programa.
 */

#ifndef GERENCIADOR_H_
#define GERENCIADOR_H_

#define DT_ALL 255

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>
#include "lista/lista.h"

/**
 * Esta struct quando inicializada representa um diretório aberto,
 * contendo uma única lista duplamente encadeada com cabeça de lista
 * que referencia cada struct dirent do diretório obtida através da função
 * opendir(). Ainda, contém o caminho completo do diretório aberto com uma
 * barra ao final do caminho.
 */
typedef struct {
	tLista *lista;
	char path[PATH_MAX];
} manip;


/**
 * Esta função recebe uma string contendo um caminho absoluto sem a barra final
 * para o diretório a ser aberto e retorna um ponteiro alocado usando malloc para
 * uma struct manip caso o diretório seja válido e o processo
 * tenha permissões para abri-lo. Caso contrário, ou caso não
 * haja memória suficiente ela retornará NULL.
 */
manip* abrirDiretorio(char *dir);

/**
 * Esta função é responsável por desalocar todas as estruturas de dados contidas
 * em manip. Além disso, ela executa o comando free no parâmetro.
 */
void fecharDiretorio(manip *manip);

/**
 * Esta função exibe na saída padrão todos os arquivos presentes no diretório
 * corrente que possuem o campo d_type de seus respectivos dirents iguais a
 * "tipo". Caso tipo seja igual a DT_ALL (Constante igual a 255), a função
 * lista todos os arquivos do diretório.
 */
void listar(manip *manip, unsigned char tipo);

/**
 * Esta função possui o mesmo comportamento de "listar" com a diferença que
 * exibe antes de cada arquivo seu tipo correspondente extraído do campo d_type
 * dos respectivos dirent's.
 */
void listarComTipo(manip *manip, unsigned char tipo);

/**
 * Esta função é responsável por receber um ponteiro inicializado de uma struct
 * manip e os caminhos absolutos anterior e posterior dos arquivos a serem renomeados.
 * Caso a operação tenha sido realizada com sucesso retorna 0, caso contrário retorna
 * -1 e modifica a variável errno.
 */
int renomear(manip *manip, char *nomeAnt, char *nomeDest);

/**
 * Esta função é responsável por receber um ponteiro inicializado de uma struct
 * manip e o caminho absoluto do arquivo ou diretório a ser removido. Caso a
 * operação tenha sido realizada com sucesso retorna 0, caso contrário retorna
 * -1 e modifica a variável errno.
 */
int remover(manip *manip, char *nome);

/**
 * Esta função é responsável por receber um ponteiro inicializado de uma struct
 * manip e o caminho absoluto do arquivo a ser criado. Caso a operação tenha
 * sido realizada com sucesso retorna 0, caso contrário retorna -1 e modifica
 * a variável errno.
 */
int criar(manip *manip, char *nome);

/**
 * Esta função é responsável por receber o caminho absoluto do arquivo cujos
 * conteúdos serão exibidos na saída padrão ao usuário. Caso a operação tenha
 * sido realizada com sucesso retorna 0, caso contrário retorna -1 e modifica
 * a variável errno.
 */
int ver(char *nome);

/**
 * Esta função recebe como parâmetros três strings, base, dest e abs. O primeiro
 * representa um caminho absoluto de um diretório inicial com uma barra ao
 * final da string. Já o segundo representa um caminho absoluto ou relativo ao
 * diretório base. O terceiro deve apontar para uma região de memória com tamanho
 * mínimo de PATH_MAX caracteres (Definido em limits.h) onde será gravado o resultado
 * do cálculo do diretório absoluto.
 *
 * O cálculo funciona da seguinte forma: Caso dest seja um caminho absoluto (Com uma
 * barra ('/') no início) o programa apenas copiará os conteúdos de dest para abs e
 * retornará 1. Caso dest seja um caminho relativo será calculado usando a função
 * realpath o caminho absoluto da concatenação de base com dest. Se realpath retornar
 * sucesso, seu resultado será copiado em abs e a função retornará 1, senão retornará
 * 0 e o conteúdo de abs será indefinido.
 */
int obterDirAbsoluto(char *base, char *dest, char *abs);

/**
 * Esta função recebe um ponteiro inicializado para um manipulador e atualiza a lista
 * de dirent's do diretório representado pelo parâmetro.
 */
void atualizarLista(manip *manipulador);

#endif /* GERENCIADOR_H_ */
