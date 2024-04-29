#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENSIBILIDADE 25;

#define padrao "\033[0m"
#define vermelho "\033[1;41m"
#define verde "\033[1;42m"
//

void proximo_quadrante(int *lin, int *col){
    if (*col < 2){
      *col += 1;
    }
    else{
      if (*lin < 2){
        *lin += 1;
        *col = 0;
      }
      else{
        *col = 0;
        *lin = 0;
      }    
    }
}

void anterior_quadrante(int *lin, int *col){
    if (*col <= 2 && *col != 0){
      *col -= 1;
    }
    else{
      if (*lin <= 2 && *lin != 0){
        *lin -= 1;
        *col = 2;
      }
      else{
        *col = 2;
        *lin = 2;
      }    
    }
}



int clique_mouse(int botao, int botao2, char tabela[3][3], unsigned char mouse_data[6], int *cont, int player, int lin, int col){
    if ((((botao == 9 || botao2 == 9) && (mouse_data[5] == 0 && mouse_data[4] == 0)) || ((botao == 9 && botao2 == 8) || (botao == 8 && botao2 == 9))) && tabela[lin][col] == ' '){
      *cont += 1;
      if (player == 1){
        tabela[lin][col] = 'X';
        return 1;
      }
      else{
        tabela[lin][col] = 'O';
        return 1;
      }
    }
    return 0;
}


int movimentacao_mouse(int *lin, int *col, int mov_x, int mov_y, int *sensi_movx, int *sensi_movy){
    int sensibilidade = SENSIBILIDADE;
    if(mov_x >= 1 && mov_x <= 60){
      *sensi_movx+= 1;
      if(*col < 2 && (*sensi_movx >= sensibilidade)) {
        *col += 1;
        *sensi_movx = 0;
        *sensi_movy = 0;
        return 1;
      }
    }
    else if (mov_x >= 200){
      *sensi_movx-= 1;
      if(*col > 0 &&( *sensi_movx <= -sensibilidade)) {
        *col -= 1;
        *sensi_movx = 0;
        *sensi_movy = 0;
        return 1;
      }
    }
    if(mov_y >= 1 && mov_y <= 60){
      *sensi_movy+= 1;
      if(*lin > 0 &&( *sensi_movy >= sensibilidade)){
        *lin -= 1;
        *sensi_movy = 0;
        *sensi_movx = 0;
        return 1;
      }
    }
    else if (mov_y >= 200){
      *sensi_movy-= 1;
      if(*lin < 2 &&( *sensi_movy <= -sensibilidade)){
        *lin += 1;
        *sensi_movy = 0;
        *sensi_movx = 0;
        return 1;
      }
    }
    return 0;
}
