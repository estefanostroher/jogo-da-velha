#include<stdio.h>
#include<stdlib.h>

/*
    Jogo da velha em C com vetores.
    Criador: Estefano Ströher
*/

void criar_tabela(char *tab){
    short int i;

    for(i = 0; i < 9; i++){
        tab[i] = ' ';
    }
}

void imprimir_tabela(char *tab){
    system("clear");

    printf("\n\tJogo da velha\n\n");
    printf("\t %c | %c | %c\n", tab[0], tab[1], tab[2]);
    printf("\t-----------\n");
    printf("\t %c | %c | %c\n", tab[3], tab[4], tab[5]);
    printf("\t-----------\n");
    printf("\t %c | %c | %c\n", tab[6], tab[7], tab[8]);
}

int completou_diag_princ(char *tab, char j){
    if(tab[0] == j && tab[4] == j && tab[8] == j){
        return 1;
    }

    else{
        return 0;
    }
}

int completou_diag_sec(char *tab, char j){
    if(tab[2] == j && tab[4] == j && tab[6] == j){
        return 1;
    }

    else{
        return 0;
    }
}

int completou_linha(char *tab, char j, int pos1, int pos2, int pos3){
    if(tab[pos1] == j && tab[pos2] == j && tab[pos3] == j){
        return 1;
    }

    else{
        return 0;
    }
}

int completou_linhas(char *tab, char j){
    short int completou = 0;

    completou += completou_linha(tab, j, 0, 1, 2);
    completou += completou_linha(tab, j, 3, 4, 5);
    completou += completou_linha(tab, j, 6, 7, 8);

    return completou;
}

int completou_coluna(char *tab, char j, short int pos1, short int pos2, short int pos3){
    if(tab[pos1] == j && tab[pos2] == j && tab[pos3] == j){
        return 1;
    }

    else{
        return 0;
    }
}

int completou_colunas(char *tab, char j){
    short int completou = 0;

    completou += completou_coluna(tab, j, 0, 3, 6);
    completou += completou_coluna(tab, j, 1, 4, 7);
    completou += completou_coluna(tab, j, 2, 5, 8);

    return completou;
}

int checagem(char *tab, int pos){
    if(pos < 0 || pos > 8 || tab[pos] != ' '){
        return 0;
    }
    
    else{
        return 1;
    }
}

void coordenadas(char *tab, char j){
    short int pos;

    printf("\nDigite uma posicao: ");
    scanf("%hd", &pos);

    while(checagem(tab, pos) == 0){
        printf("Erro! Digite uma posicao: ");
        scanf("%hd", &pos);
    }
    tab[pos] = j;
}

void partida_com_jogador2(char *tab){
    short int jogador = 1, p1 = 0, p2 = 0, jogadas = 0;
    char jogador1 = 'X', jogador2 = 'O';

    do{
        imprimir_tabela(tab);
        if(jogador == 1){
            coordenadas(tab, jogador1);
            p1 += completou_diag_princ(tab, jogador1);
            p1 += completou_diag_sec(tab, jogador1);
            p1 += completou_linhas(tab, jogador1);
            p1 += completou_colunas(tab, jogador1);
            jogador++;
        }

        else{
            coordenadas(tab, jogador2);
            p2 += completou_diag_princ(tab, jogador2);
            p2 += completou_diag_sec(tab, jogador2);
            p2 += completou_linhas(tab, jogador2);
            p2 += completou_colunas(tab, jogador2);
            jogador--;
        }
        jogadas++;
    }
    while(p1 == 0 && p2 == 0 && jogadas < 9);

    imprimir_tabela(tab);

    if(p1 == 1){
        printf("\n\tJogador 1 venceu!\n");
    }

    else if(p2 == 1){
        printf("\n\tJogador 2 venceu!\n");
    }

    else{
        printf("\n\tEmpate!\n");
    }
}

int main(){
    char *tabela = malloc(9 * sizeof(char));
    short int pos = 0, opcao = 1;

    if(tabela != NULL){
        do{
            criar_tabela(tabela);
            partida_com_jogador2(tabela);

            printf("\nContinuar jogando?(Sim - 1/ Nao - 0): ");
            scanf("%hd", &opcao);
        }
        while(opcao != 0);

        free(tabela);
        tabela = NULL;

        return 0;
    }

    else{
        printf("\nNao foi possivel alocar memoria pro jogo.\n");
        return 1;
    }
}