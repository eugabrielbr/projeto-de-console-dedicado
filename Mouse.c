#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENSIBILIDADE 25; // Define a sensibilidade do mouse

#define padrao "\033[0m" // Define as cores para impressão na tela
#define vermelho "\033[1;41m"
#define verde "\033[1;42m"

// Função para mover para o próximo quadrante do tabuleiro
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

// Função para mover para o quadrante anterior do tabuleiro
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

// Função para lidar com o clique do mouse
int clique_mouse(int botao, int botao2, char tabela[3][3], unsigned char mouse_data[6], int *cont, int player, int lin, int col){
    // Verifica se o botão esquerdo do mouse foi clicado
    if ((((botao == 9 || botao2 == 9) && (mouse_data[5] == 0 && mouse_data[4] == 0)) || ((botao == 9 && botao2 == 8) || (botao == 8 && botao2 == 9))) && tabela[lin][col] == ' '){
      *cont += 1; // Incrementa o contador de movimentos
      // Verifica o jogador atual e insere seu marcador (X ou O) na posição selecionada
      if (player == 1){
        tabela[lin][col] = 'X';
        return 1; // Retorna 1 indicando que o clique foi bem-sucedido
      }
      else{
        tabela[lin][col] = 'O';
        return 1; 
      }
    }
    return 0; // Retorna 0 indicando que o clique não foi bem-sucedido
}

// Função para lidar com o movimento do mouse
int movimentacao_mouse(int *lin, int *col, int mov_x, int mov_y, int *sensi_movx, int *sensi_movy){
    int sensibilidade = SENSIBILIDADE; // Define a sensibilidade do movimento do mouse
    // Verifica o movimento horizontal do mouse
    if(mov_x >= 1 && mov_x <= 60){
      *sensi_movx+= 1; // Incrementa o contador de movimento horizontal
      // Verifica se é possível mover para a direita e se a sensibilidade de movimento horizontal é suficiente
      if(*col < 2 && (*sensi_movx >= sensibilidade)) {
        *col += 1; // Move para a direita
        *sensi_movx = 0; // Reinicia o contador de movimento horizontal
        *sensi_movy = 0; // Reinicia o contador de movimento vertical
        return 1; // Retorna 1 indicando que o movimento foi bem-sucedido
      }
    }
    // Verifica o movimento horizontal do mouse
    else if (mov_x >= 200){
      *sensi_movx-= 1; // Decrementa o contador de movimento horizontal
      // Verifica se é possível mover para a esquerda e se a sensibilidade de movimento horizontal é suficiente
      if(*col > 0 &&( *sensi_movx <= -sensibilidade)) {
        *col -= 1; // Move para a esquerda
        *sensi_movx = 0; // Reinicia o contador de movimento horizontal
        *sensi_movy = 0; // Reinicia o contador de movimento vertical
        return 1; // Retorna 1 indicando que o movimento foi bem-sucedido
      }
    }
    // Verifica o movimento vertical do mouse
    if(mov_y >= 1 && mov_y <= 60){
      *sensi_movy+= 1; // Incrementa o contador de movimento vertical
      // Verifica se é possível mover para cima e se a sensibilidade de movimento vertical é suficiente
      if(*lin > 0 &&( *sensi_movy >= sensibilidade)){
        *lin -= 1; // Move para cima
        *sensi_movy = 0; // Reinicia o contador de movimento vertical
        *sensi_movx = 0; // Reinicia o contador de movimento horizontal
        return 1; // Retorna 1 indicando que o movimento foi bem-sucedido
      }
    }
    // Verifica o movimento vertical do mouse
    else if (mov_y >= 200){
      *sensi_movy-= 1; // Decrementa o contador de movimento vertical
      // Verifica se é possível mover para baixo e se a sensibilidade de movimento vertical é suficiente
      if(*lin < 2 &&( *sensi_movy <= -sensibilidade)){
        *lin += 1; // Move para baixo
        *sensi_movy = 0; // Reinicia o contador de movimento vertical
        *sensi_movx = 0; // Reinicia o contador de movimento horizontal
        return 1; // Retorna 1 indicando que o movimento foi bem-sucedido
      }
    }
    return 0; // Retorna 0 indicando que o movimento não foi bem-sucedido
}
