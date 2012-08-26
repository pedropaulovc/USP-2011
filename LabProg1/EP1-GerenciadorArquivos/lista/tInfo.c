/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP1 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403
 *
 * Neste arquivo estão implementados os protótipos definidos em
 * tInfo.h referentes às operações de remoção e comparação de
 * structs do tipo tInfo.
 */

#include "tInfo.h"

void destroiInfo(tInfo *info) {
	free(info);
}

int maior(tInfo *i1, tInfo *i2) {
	if (i1->d_type == i2->d_type)
		return (strcmp(i1->d_name, i2->d_name) > 0);
	return (i1->d_type > i2->d_type);
}
