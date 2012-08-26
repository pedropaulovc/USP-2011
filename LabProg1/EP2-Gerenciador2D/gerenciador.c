/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP3 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403
 *
 * Neste arquivo estão implementados os protótipos definidos em
 * gerenciador.h referentes às operações de gerenciamento de arquivos.
 */

#include "gerenciador.h"

manip* abrirDiretorio(char *dir) {
	struct dirent *ep, *epCopia;

	if (dir == NULL) /*Argumento inválido */
		return NULL;

	manip *manipulador = (manip*) malloc(sizeof(manip));
	if (manipulador == NULL) /* Sem memória */
		return NULL;

	manipulador->lista = criaLista();
	if (manipulador->lista == NULL) { /* Sem memória */
		free(manipulador);
		return NULL;
	}

	DIR *dp = opendir(dir);
	if (dp == NULL) { /* Diretório inválido */
		destroiLista(manipulador->lista);
		free(manipulador);
		return NULL;
	}

	strcpy(manipulador->path, dir);
	if (dir[1] != '\0') /*Não estamos no diretório raiz*/
		strcat(manipulador->path, "/");

	while ((ep = readdir(dp)) != NULL) {
		epCopia = (struct dirent*) malloc(sizeof(struct dirent));
		memcpy(epCopia, ep, sizeof(struct dirent));
		adicionarOrdem(manipulador->lista, epCopia);
	}

	closedir(dp);
	return manipulador;
}

void fecharDiretorio(manip *manip) {
	if (manip == NULL)
		return;

	destroiLista(manip->lista);
	free(manip);
}

void listar(manip *manip, unsigned char tipo) {
	tElemento *dp = manip->lista->cabeca->sucessor;

	while (dp != manip->lista->cabeca) {
		if (dp->info->d_type == tipo || tipo == DT_ALL)
			puts(dp->info->d_name);
		dp = dp->sucessor;
	}
}

void listarComTipo(manip *manip, unsigned char tipo) {
	char *nomeTipo = "";
	tElemento *dp = manip->lista->cabeca->sucessor;

	while (dp != manip->lista->cabeca) {
		if (dp->info->d_type == tipo || tipo == DT_ALL) {
			switch (dp->info->d_type) {
			case DT_BLK:
				nomeTipo = "orient block";
				break;
			case DT_CHR:
				nomeTipo = "orient char ";
				break;
			case DT_DIR:
				nomeTipo = "diretório   ";
				break;
			case DT_FIFO:
				nomeTipo = "fifo        ";
				break;
			case DT_LNK:
				nomeTipo = "link        ";
				break;
			case DT_REG:
				nomeTipo = "regular     ";
				break;
			case DT_SOCK:
				nomeTipo = "socket      ";
				break;
			case DT_UNKNOWN:
				nomeTipo = "desconhecido";
				break;
			case DT_WHT:
				nomeTipo = "whiteout    ";
				break;
			default:
				nomeTipo = "desconhecido";
				break;
			}
		}
		printf("%s - %s\n", nomeTipo, dp->info->d_name);
		dp = dp->sucessor;
	}
}

int renomear(manip *manip, char *nomeAnt, char *nomeDest) {
	int resultado = rename(nomeAnt, nomeDest);

	if (resultado == 0)
		atualizarLista(manip);

	return resultado;
}

int remover(manip *manip, char *nome) {
	int resultado;

	resultado = unlink(nome);
	if (resultado == -1 && errno == EISDIR)
		resultado = rmdir(nome);

	if (resultado == 0)
		atualizarLista(manip);

	return resultado;
}

int criar(manip *manip, char *nome) {
	int resultado = -1;

	FILE *file = fopen(nome, "a");

	if (file != NULL) {
		fclose(file);
		resultado = 0;
	}

	if (resultado == 0)
		atualizarLista(manip);

	return resultado;
}

int ver(char *arquivo) {
	FILE *fp;
	char *linha = NULL;
	size_t tamBuffer = 0;
	ssize_t qtdLido;

	fp = fopen(arquivo, "r");
	if (fp == NULL)
		return -1;

	while ((qtdLido = getline(&linha, &tamBuffer, fp)) != -1)
		puts(linha);

	if (linha)
		free(linha);
	return 0;
}

int obterDirAbsoluto(char *base, char *dest, char *abs) {
	char *tmp;

	gerarCaminhoDir(base, dest, abs);
	tmp = realpath(abs, NULL);
	if (tmp == NULL)
		return FALSE;
	strcpy(abs, tmp);
	free(tmp);
	return TRUE;
}

int gerarCaminhoDir(char *base, char *dest, char *abs){
	if(dest[0] == '/'){
		/* Usuário quer ir p/ dir absoluto */
		strcpy(abs, dest);
		return TRUE;
	}

	strcpy(abs, base);
	strcat(abs, dest);
	return TRUE;
}

void atualizarLista(manip *manipulador) {
	manip *tmp;

	tmp = abrirDiretorio(manipulador->path);
	destroiLista(manipulador->lista);
	manipulador->lista = tmp->lista;
	free(tmp);
}
