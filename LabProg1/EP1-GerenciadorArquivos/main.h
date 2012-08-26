/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP1 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403
 *
 * Neste arquivo estão definidos os protótipos a serem implementados em
 * main.c referentes à interface em modo texto do gerenciador de arquivos
 * implementado para este primeiro exercício programa além de inclusões
 * de headers usadas ao longo do programa.
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <dirent.h>
#include <libgen.h>
#include <limits.h>
#include "gerenciador.h"

/**
 * Esta struct contém as principais variáveis da interface do programa, o número
 * de argumentos recebidos no último comando, os argumentos propriamente ditos
 * e o manipulador de arquivos a ser passado à biblioteca para a execução das
 * operações de manipulação de arquivos.
 */
typedef struct {
	int numArgumentos;
	char **argumentos;
	manip *manip;
} interface;

/**
 * Esta função recebe uma string para a linha de comando a ser parseada
 * e um ponteiro para um inteiro que conterá o número de argumentos
 * capturados. Ao final da execução será retornado um vetor de strings
 * alocado usando malloc contendo em cada posição um argumento ou NULL
 * caso o número de argumentos seja igual a 0.
 *
 * A regra de parseamento segue:
 * COMANDO[espaços]*[ARG1][espaços]*,[espaços]*[ARG2]...
 * onde COMANDO é um único caractere dentre os comandos implementados
 * (c, l, d, ?, x ...).
 */
char** parsearArgumentos(char *linha, int *numArgumentos);

/**
 * Esta função exibe na saída padrão uma saudação inicial ao usuário,
 * indicando o início do programa.
 */
void exibirIntroducao();

/**
 * Esta função exibe na saída padrão uma lista contendo as opções disponíves
 * do programa.
 */
void exibirMenu();

/**
 * Esta função é responsável pelo interfaceamento entre a biblioteca do programa
 * e o usuário, informando possíveis erros na execução da operação de troca de
 * diretório.
 */
void trocarDiretorio(interface *iu);

/**
 * Esta função é responsável pelo interfaceamento entre a biblioteca do programa
 * e o usuário, informando possíveis erros na execução da operação de listagem de
 * diretório. A função recebe como parâmetro além de uma struct interface um
 * tipo de arquivo a ser listado dentre os definidos em dirent.h (DT_REG, DT_DIR,
 * ...) ou DT_ALL (Macro definida em gerenciador.h como 255) para listar todos
 * os arquivos do diretório.
 */
void listarDiretorio(interface *iu, unsigned char tipo);

/**
 * Esta função é responsável pelo interfaceamento entre a biblioteca do programa
 * e o usuário, informando possíveis erros na execução da operação de remoção de
 * arquivos.
 */
void removerArquivo(interface *iu);

/**
 * Esta função é responsável pelo interfaceamento entre a biblioteca do programa
 * e o usuário, informando possíveis erros na execução da operação de movimentação
 * de arquivos.
 */
void moverArquivo(interface *iu);

/**
 * Esta função é responsável pelo interfaceamento entre a biblioteca do programa
 * e o usuário, informando possíveis erros na execução da operação de criação de
 * arquivos.
 */
void criarArquivo(interface *iu);

/**
 * Esta função é responsável pelo interfaceamento entre a biblioteca do programa
 * e o usuário, informando possíveis erros na execução da operação de listagem de
 * diretório. Para explicação do parâmetro tipo, vide a função listarDiretorio.
 */
void listarDiretorioComTipos(interface *iu, unsigned char tipo);

/**
 * Esta função é responsável pelo interfaceamento entre a biblioteca do programa
 * e o usuário, informando possíveis erros na execução da operação de visualizar
 * um arquivo.
 */
void verArquivo(interface *iu);

/**
 * Esta função é responsável pelo interfaceamento entre a biblioteca do programa
 * e o usuário, informando possíveis erros na execução da operação de listar o
 * diretório atual.
 */
void verDiretorioAtual(interface *iu);

/**
 * Esta função é responsável por desalocar as estruturas de dados usadas no programa
 * e encerrar a execução do programa com sucesso.
 */
void sairPrograma(interface *iu);

#endif /* MAIN_H_ */
