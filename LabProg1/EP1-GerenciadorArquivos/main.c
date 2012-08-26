/**
 * MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1
 * EP1 - GERENCIADOR DE ARQUIVOS
 * ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403
 *
 * Neste arquivo estão implementadas as funções definidas em
 * main.h referentes à interface em modo texto do gerenciador de arquivos.
 */

#include "main.h"

int main(int argc, char **argv) {
	interface iu;
	char linha[MAX_INPUT], comando;
	iu.manip = abrirDiretorio(getenv("PWD"));

	exibirIntroducao();

	do {
		printf("%s> ", iu.manip->path);
		scanf("%[^\n]", linha);
		getchar();
		iu.argumentos = parsearArgumentos(linha, &(iu.numArgumentos));
		comando = linha[0];

		if (linha[1] != ' ' && linha[1] != '\0') {
			fprintf(stderr, "Comando inválido\n");
			continue;
		}

		switch (comando) {
		case 'c':
			trocarDiretorio(&iu);
			break;
		case 'l':
			listarDiretorio(&iu, DT_ALL);
			break;
		case 'r':
			removerArquivo(&iu);
			break;
		case 'm':
			moverArquivo(&iu);
			break;
		case 'n':
			criarArquivo(&iu);
			break;
		case 'd':
			listarDiretorio(&iu, DT_DIR);
			break;
		case 't':
			listarDiretorioComTipos(&iu, DT_ALL);
			break;
		case 'v':
			verArquivo(&iu);
			break;
		case 'p':
			verDiretorioAtual(&iu);
			break;
		case '?':
			exibirMenu();
			break;
		case 'x':
			sairPrograma(&iu);
			break;
		default:
			fprintf(stderr, "Comando inválido\n");
			break;
		}
	} while (1);

	return (EXIT_SUCCESS);
}

void exibirIntroducao() {
	puts("MAC0211 - LABORATÓRIO DE PROGRAMAÇÃO 1");
	puts("ALUNOS: PEDRO PAULO - 7538743 E DANIEL HUGUENIN - 5118403");
	puts("EP1 - GERENCIADOR DE ARQUIVOS");
	puts("Para ver as funções disponíveis digite '?<Enter>'");
}

void exibirMenu() {
	puts("Parâmetros indicados com []'s são opcionais");
	puts(
			"Cada comando deve ser separado de seus argumentos por pelo menos 1 espaço.\n");
	puts("c DIR - Troca o diretório corrente para DIR");
	puts("l [DIR] - Lista o diretório DIR ou o diretório corrente");
	puts("r ARQ - Remove o arquivo ARQ");
	puts("m FON, DES - Renomeia o arquivo FON para DES");
	puts("n ARQ - Cria o arquivo ARQ, se não existe");
	puts("d [DIR] - Lista apenas os diretórios de DIR ou o diretório corrente");
	puts(
			"t [DIR] - Lista diretório DIR ou o corrente mostrando os tipos de cada arquivo");
	puts("v ARQ - Exibe os conteúdos do arquivo ARQ");
	puts("p - Exibe o diretório corrente");
	puts("? - Exibe este menu");
	puts("x - Sai do programa\n");
}

char** parsearArgumentos(char *linha, int *numArgumentos) {
	*numArgumentos = 0;
	int i, j, atual;
	i = j = atual = 0;
	char **argumentos;

	while (linha[i] != '\0') {
		if (linha[i] == ',')
			(*numArgumentos)++;
		i++;
	}

	(*numArgumentos)++;

	argumentos = (char**) malloc(sizeof(char*) * (*numArgumentos));

	i = 1;
	do {
		while (linha[i] == ' ')
			i++;

		if (linha[i] == '\0' && *numArgumentos == 1) {
			free(argumentos);
			*numArgumentos = 0;
			return NULL;
		}

		argumentos[atual] = linha + i;
		atual++;

		while (linha[i] != '\0' && linha[i] != ',')
			i++;

		j = i - 1;
		while (linha[j] == ' ')
			j--;
		linha[j + 1] = '\0';

		i++;
	} while (atual != *numArgumentos);

	return argumentos;
}

void trocarDiretorio(interface *iu) {
	char dir[PATH_MAX];
	manip *novoManip = NULL;

	if (iu->numArgumentos < 1) {
		fprintf(stderr, "c: Falta argumento\n");
		return;
	}

	if (obterDirAbsoluto(iu->manip->path, iu->argumentos[0], dir))
		novoManip = abrirDiretorio(dir);

	if (novoManip == NULL) {
		perror("Diretório inválido");
		return;
	}

	fecharDiretorio(iu->manip);
	iu->manip = novoManip;
}

void listarDiretorio(interface *iu, unsigned char tipo) {
	manip *aListar = iu->manip;
	char dir[PATH_MAX];

	if (iu->numArgumentos > 0) {
		if (obterDirAbsoluto(iu->manip->path, iu->argumentos[0], dir))
			aListar = abrirDiretorio(dir);
		else
			aListar = NULL;
	}

	if (aListar == NULL) {
		perror("Diretório inválido");
		return;
	}

	listar(aListar, tipo);

	if (iu->numArgumentos > 0)
		fecharDiretorio(aListar);
}

void removerArquivo(interface *iu) {
	char arquivo[PATH_MAX];

	if (iu->numArgumentos == 0) {
		fprintf(stderr, "r: Falta argumento\n");
		return;
	}

	if (!obterDirAbsoluto(iu->manip->path, iu->argumentos[0], arquivo)) {
		perror("r: Não foi possível remover o arquivo");
		return;
	}

	if (remover(iu->manip, arquivo) == -1)
		perror("r: I'm sorry, Dave. I'm afraid I can't do that");
}

void moverArquivo(interface *iu) {
	char fonte[PATH_MAX], destino[PATH_MAX];

	if (iu->numArgumentos < 2) {
		fprintf(stderr, "m: Faltam argumentos\n");
		return;
	}

	if (!obterDirAbsoluto(iu->manip->path, iu->argumentos[0], fonte)) {
		perror("m: Não foi possível renomear o arquivo");
		return;
	}

	/* Como o arquivo de destino não existe previamente não podemos usar
	 a função obterDirAbsoluto() */
	if (iu->argumentos[1][0] == '/')
		/* Usuário quer mover p/ dir absoluto */
		strcpy(destino, iu->argumentos[1]);

	/* Usuário quer mover p/ dir relativo */
	strcpy(destino, iu->manip->path);
	strcat(destino, iu->argumentos[1]);

	if (renomear(iu->manip, fonte, destino) == -1)
		perror("m: Não foi possível renomear o arquivo");
}

void criarArquivo(interface *iu) {
	char arquivo[PATH_MAX];

	if (iu->numArgumentos < 1) {
		fprintf(stderr, "n: Falta argumento\n");
		return;
	}

	/* Como o arquivo de destino não existe previamente não podemos usar
	 a função obterDirAbsoluto() */
	if (iu->argumentos[0][0] == '/')
		/* Usuário quer mover p/ dir absoluto */
		strcpy(arquivo, iu->argumentos[0]);

	/* Usuário quer mover p/ dir relativo */
	strcpy(arquivo, iu->manip->path);
	strcat(arquivo, iu->argumentos[0]);

	if (criar(iu->manip, arquivo) == -1)
		perror("n: Não foi possível criar o arquivo");
}

void listarDiretorioComTipos(interface *iu, unsigned char tipo) {
	manip *aListar = iu->manip;
	char dir[PATH_MAX];

	if (iu->numArgumentos > 0) {
		if (obterDirAbsoluto(iu->manip->path, iu->argumentos[0], dir))
			aListar = abrirDiretorio(dir);
		else
			aListar = NULL;

		aListar = abrirDiretorio(dir);
	}

	if (aListar == NULL) {
		perror("Diretório inválido");
		return;
	}

	listarComTipo(aListar, tipo);

	if (iu->numArgumentos > 0)
		fecharDiretorio(aListar);
}

void verArquivo(interface *iu){
	char arquivo[PATH_MAX];

	if (iu->numArgumentos < 1) {
		fprintf(stderr, "v: Falta argumento\n");
		return;
	}

	if (!obterDirAbsoluto(iu->manip->path, iu->argumentos[0], arquivo)) {
		perror("v: Não foi possível visualizar o arquivo");
		return;
	}

	if(ver(arquivo) == -1)
		perror("v: Não foi possível visualizar o arquivo");
}

void verDiretorioAtual(interface *iu) {
	puts(iu->manip->path);
}

void sairPrograma(interface *iu) {
	fecharDiretorio(iu->manip);
	exit(EXIT_SUCCESS);
}
