#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENSIBILIDADE 25;

#define padrao "\033[0m"
#define vermelho "\033[1;41m"
#define verde "\033[1;42m"


void print_menu(){
    system("clear");
    printf("__________________ _______        _________ _______  _______        _________ _______  _______\n");
    printf("\\__   __/\\__   __/(  ____ \\       \\__   __/(  ___  )(  ____ \\       \\__   __/(  ___  )(  ____ \\\n");
    printf("   ) (      ) (   | (    \\/          ) (   | (   ) || (    \\/          ) (   | (   ) || (    \\/\n");
    printf("   | |      | |   | |       _____    | |   | (___) || |       _____    | |   | |   | || (__\n");
    printf("   | |      | |   | |      (_____)   | |   |  ___  || |      (_____)   | |   | |   | ||  __)\n");
    printf("   | |      | |   | |                | |   | (   ) || |                | |   | |   | || (\n");
    printf("   | |   ___) (___| (____/\\          | |   | )   ( || (____/\\          | |   | (___) || (____/\\\n");
    printf("   )_(   \\_______/(_______/          )_(   |/     \\|(_______/          )_(   (_______)(_______/\n");
    printf("\n\n                              [B1] Iniciar jogo        [B2] Sair\n");
}

void print_tabela(char tabela[3][3]){
    printf("\n");
    for(int i = 0; i < 3; i++) {
      printf("  %c  ", tabela[i][0]);
      printf("║");
      printf("  %c  ",tabela[i][1]);
      printf("║");
      printf("  %c ",tabela[i][2]);
      if(i < 2) printf("\n═════╬═════╬═════\n");
    }
    printf("\n");
}

void print_tabela_colorida(char tabela[3][3], int lin, int col){
    printf("\n");
    for(int i = 0; i < 3; i++) {
      if(lin == i && col == 0 && tabela[i][0] == ' ') printf(verde"  %c  "padrao, tabela[i][0]);
      else if(lin == i && col == 0 && tabela[i][0] != ' ') printf(vermelho"  %c  "padrao, tabela[i][0]);
      else printf("  %c  ", tabela[i][0]);
      printf("║");
      if(lin == i && col == 1 && tabela[i][1] == ' ') printf(verde"  %c  "padrao,tabela[i][1]);
      else if(lin == i && col == 1 && tabela[i][1] != ' ') printf(vermelho"  %c  "padrao, tabela[i][1]);
      else printf("  %c  ",tabela[i][1]);
      printf("║");
      if(lin == i && col == 2 && tabela[i][2] == ' ') printf(verde"  %c  "padrao,tabela[i][2]);
      else if(lin == i && col == 2 && tabela[i][2] != ' ') printf(vermelho"  %c  "padrao, tabela[i][2]);
      else printf("  %c  ",tabela[i][2]);
      if(i < 2) printf("\n═════╬═════╬═════\n");
    }
    printf("\n");
}

void print_tabela_resultado(char tabela[3][3], int *lin1, int *col1, int *lin2, int *col2, int *lin3, int *col3){
    printf("\n");
    for(int i = 0; i < 3; i++) {
      if((*lin1 == i && *col1 == 0) || (*lin2 == i && *col2 == 0) || (*lin3 == i && *col3 == 0)) printf(verde"  %c  "padrao, tabela[i][0]);
      else printf("  %c  ", tabela[i][0]);
      printf("║");
      if((*lin1 == i && *col1 == 1) || (*lin2 == i && *col2 == 1) || (*lin3 == i && *col3 == 1)) printf(verde"  %c  "padrao,tabela[i][1]);
      else printf("  %c  ",tabela[i][1]);
      printf("║");
      if((*lin1 == i && *col1 == 2) || (*lin2 == i && *col2 == 2) || (*lin3 == i && *col3 == 2)) printf(verde"  %c  "padrao,tabela[i][2]);
      else printf("  %c  ",tabela[i][2]);
      if(i < 2) printf("\n═════╬═════╬═════\n");
    }
    printf("\n");



}


int check_winner(const char tabela[3][3], int *lin1, int *col1, int *lin2, int *col2, int *lin3, int *col3){
    if(tabela[0][0] == tabela[1][1] && tabela[1][1] == tabela[2][2] && tabela[0][0] != ' '){
      *lin1 = 0;
      *col1 = 0;
      *lin2 = 1;
      *col2 = 1;
      *lin3 = 2;
      *col3 = 2;
      return 1;
    }
    if(tabela[0][2] == tabela[1][1] && tabela[1][1] == tabela[2][0] && tabela[0][2] != ' '){
      *lin1 = 0;
      *col1 = 2;
      *lin2 = 1;
      *col2 = 1;
      *lin3 = 2;
      *col3 = 0;
      return 1;
    }
    for(int i = 0; i < 3; i++){
      if(tabela[0][i] == tabela[1][i] && tabela[1][i] == tabela[2][i] && tabela[0][i] != ' '){
        *lin1 = 0;
        *col1 = i;
        *lin2 = 1;
        *col2 = i;
        *lin3 = 2;
        *col3 = i;
        return 1;
      }
      if(tabela[i][0] == tabela[i][1] && tabela[i][1] == tabela[i][2] && tabela[i][0] != ' '){
        *lin1 = i;
        *col1 = 0;
        *lin2 = i;
        *col2 = 1;
        *lin3 = i;
        *col3 = 2;
        return 1;
      }
    }
    return 0;
}

void print_jogo(char tabela[3][3], unsigned char mouse_data[6], int quadrante, int player, int lin, int col){
    system("clear");
    print_tabela_colorida(tabela, lin, col);
    printf("\nquadrante: %d\n",quadrante);
    printf("player: %d\n",player);
}


void calcular_quadrante(int *quadrante, int lin, int col){
    if(lin == 0) *quadrante = lin + col + 1;
    else if(lin == 1) *quadrante = lin+ col + 3;
    else if (lin == 2) *quadrante = lin + col + 5;
}


int finalizar_jogo(int cont, char tabela[3][3], int player, int *lin1, int *col1, int *lin2, int *col2, int *lin3, int *col3){
    if(check_winner(tabela, lin1, col1, lin2, col2, lin3, col3)){
      system("clear");
      print_tabela_resultado(tabela, lin1, col1, lin2, col2, lin3, col3);
      printf("\nVitória jogador %d\n", player);
      return 1;
    }
    else if(cont == 9){
      system("clear");
      print_tabela(tabela);
      printf("\nJogo terminou em empate\n");
      return 1;
    }
    return 0;
}
