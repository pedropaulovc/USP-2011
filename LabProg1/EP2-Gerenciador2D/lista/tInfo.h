/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP2 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403
 *
 * Neste arquivo estão definidos os protótipos a serem implementados em
 * tInfo.h referentes às operações de remoção e comparação de
 * structs do tipo tInfo.
 */

#include <string.h>
#include <stdlib.h>
#include <dirent.h>

/**
 * Este tipo é a definição do que cada elemento da lista vai referenciar
 * como dado.
 */
typedef struct dirent tInfo;

/**
 * Esta função realiza a operação de remoção conveniente de remoção da
 * memória da estrutura referenciada pelo parâmetro passado.
 */
void destroiInfo(tInfo *info);

/**
 * Esta função compara duas estruturas tInfo e retorna 1 se i1 for maior
 * que i2 e 0 em caso contrário.
 */
int maior(tInfo *i1, tInfo *i2);
