/**
 * Aluno: Pedro Paulo Vezzá Campos - 7538743
 * EP1: Backtracking e pilhas - 2011
 * Sobre o arquivo: Aqui é implementada a função main do programa além dos
 * algoritmos relevantes à solução do problema proposto.
 */

#include "main.h"

/**
 * Função main do programa, é responsável por conter em um laço
 * que delega as tarefas de inicialização do programa, leitura
 * de entrada, busca e apresentação da solução e encerramento.
 */
int main() {
	jogo oJogo;
	estado *inicial;
	movimento *resp;

	do{
		inicializaJogo(&oJogo);
		inicial = leJogoEntrada(&oJogo);
		if(inicial == NULL)
			return 0;
		resp = buscaSolucao(oJogo, inicial);
		exibeSolucao(oJogo, resp);
		encerraJogo(oJogo);
	} while (TRUE);
}

/**
 * Função responsável por alocar e inicializar a pilha a ser utilizada
 * no backtracking além de outros campos relevantes do jogo.
 */
void inicializaJogo(jogo *oJogo){
	oJogo->candidatos = (pilha*) malloc(sizeof(pilha));
	inicializarPilha(oJogo->candidatos);
	oJogo->maxMov = 0;
}

/**
 * Função responsável por ler o tabuleiro de entrada segundo
 * o formato definido na especificação do EP. Em caso de entrada
 * malformatada o programa encerra imediatamente. Se a entrada é
 * válida retorna um ponteiro para o estado inicial do jogo
 * (Tabuleiro intacto) senão retorna NULL.
 */
estado* leJogoEntrada(jogo *oJogo){
	int i, j, k, conteudo;
	estado *inicial = alocaEstado(0);

	if(scanf("%d %d", &(oJogo->l), &(oJogo->c)) != 2 ||
			oJogo->l <= 0 || oJogo->c <= 0)
		return NULL;

	oJogo->obj = alocaMatriz(oJogo->l, oJogo->c);
	inicial->tabuleiro = alocaMatriz(oJogo->l, oJogo->c);

	for (k = 0; k < oJogo->l * oJogo->c; k++) {
		if(scanf("%d %d %d", &i, &j, &conteudo) != 3)
			return NULL;
		inicial->tabuleiro[i][j] = conteudo;
		oJogo->obj[i][j] = conteudo == 0 ? 0 : -conteudo;
		oJogo->maxMov += conteudo;
	}
	
	return inicial;
}

/**
 * Função responsável por implementar o algoritmo de backtracking propriamente dito
 * de maneira iterativa para varrer o espaço de estados. Se encontrar uma
 * resposta válida retorna um vetor com maxMov posições contendo os passos a serem
 * seguidos, senão retorna NULL.
 */
movimento* buscaSolucao(jogo oJogo, estado *inicial){
	estado *atual = inicial;

	do {
		if(!empilhaCandidatos(oJogo, atual)) {
			if(matrizesIguais(oJogo.obj, atual->tabuleiro, oJogo.l, oJogo.c))
				return atual->passos;
			if(pilhaVazia(oJogo.candidatos))
				return NULL;
		}

		desalocaEstado(atual, oJogo.l);
		atual = desempilha(oJogo.candidatos);
	} while(TRUE);
}

/**
 * Função responsável por analisar o tabuleiro referenciado em "atual" para
 * gerar e empilhar todos os novos estados possíveis no momento. Caso pelo
 * menos um novo estado tenha sido empilhado, retorna TRUE, senão, FALSE.
 */
int empilhaCandidatos(jogo oJogo, estado *atual){
	int i, j, k, empilhou = FALSE;
	char direcoes[] = {'N', 'S', 'L', 'O'};
	movimento mov;
	estado *novo;

	if(atual->numMov == oJogo.maxMov)
		return FALSE;

	for(i = 0; i < oJogo.l; i++){
		for(j = 0; j < oJogo.c; j++){
			if(atual->tabuleiro[i][j] != PINO)
				continue;

			for(k = 0; k < 4; k++){
				mov = geraMovimento(i, j, direcoes[k]);
				if(movimentoValido(oJogo, atual, mov)){
					novo = executaMovimento(oJogo, atual, mov);
					empilha(oJogo.candidatos, novo);
					empilhou = TRUE;
				}
			}
		}
	}

	return empilhou;
}

/**
 * Função responsável por calcular e retornar um novo movimento dadas as
 * coordenadas e uma direção.
 */
movimento geraMovimento(int x, int y, char direcao){
	movimento mov;

	mov.x = x; mov.y = y; mov.direcao = direcao;
	mov.destX = 0; mov.destY = 0;
	switch (direcao){
        case 'N':
            mov.destX = mov.x - 2; mov.destY = mov.y;
            break;
        case 'S':
        	mov.destX = mov.x + 2; mov.destY = mov.y;
            break;
        case 'L':
        	mov.destX = mov.x; mov.destY = mov.y + 2;
            break;
        case 'O':
        	mov.destX = mov.x; mov.destY = mov.y - 2;
            break;
    }

	return mov;
}

/**
 * Função responsável por analisar um movimento dentro de um tabuleiro e
 * retornar se ele é válido, ou seja se o movimento ocorre dentro do tabuleiro,
 * com a origem o meio sendo pinos e o destino é um buraco).
 */
int movimentoValido(jogo oJogo, estado *atual, movimento mov){
    return mov.x < oJogo.l && mov.x >= 0 &&
			mov.y < oJogo.c && mov.y >= 0 &&
			mov.destX < oJogo.l && mov.destX >= 0 &&
			mov.destY < oJogo.c && mov.destY >= 0 &&
			atual->tabuleiro[mov.x][mov.y] == PINO &&
			atual->tabuleiro[(mov.x + mov.destX)/2][(mov.y + mov.destY)/2] == PINO &&
			atual->tabuleiro[mov.destX][mov.destY] == BURACO;
}

/**
 * Função responsável por dado um estado de um tabuleiro ("atual") e um
 * movimento retornar um novo estado idêntico ao anterior exceto pela
 * movimentação das peças informada via parâmetro em "mov".
 */
estado* executaMovimento(jogo oJogo, estado *atual, movimento mov){
	estado *novo = clonaEstado(atual, oJogo.l, oJogo.c);
	novo->passos[novo->numMov - 1] = mov;
	novo->tabuleiro[mov.x][mov.y] = BURACO;
	novo->tabuleiro[(mov.x + mov.destX)/2][(mov.y + mov.destY)/2] = BURACO;
	novo->tabuleiro[mov.destX][mov.destY] = PINO;
	return novo;
}

/**
 * Função responsável por imprimir o retorno de buscaSolucao. Se não foi
 * encontrada resposta exibe "NAO EXISTE SOLUCAO" senão imprime n-m linhas
 * com a resposta obtida pelo programa, com a primeira linha sendo o primeiro
 * movimento e assim por diante.
 */
void exibeSolucao(jogo oJogo, movimento *resp){
	int i;

	if (resp == NULL){
		puts("NAO EXISTE SOLUCAO");
		return;
	}

	for(i = 0; i < oJogo.maxMov; i++)
		printf("%d %d %c\n", resp[i].x, resp[i].y, resp[i].direcao);
}

/**
 * Função responsável por desalocar todas estruturas de dados remanecentes do
 * cálculo da resposta ao jogo dado.
 */
void encerraJogo(jogo oJogo){
	while(!pilhaVazia(oJogo.candidatos))
		desalocaEstado(desempilha(oJogo.candidatos), oJogo.l);
	desalocaMatriz(oJogo.obj, oJogo.l);
	free(oJogo.candidatos);
}
