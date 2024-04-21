#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENSIBILIDADE 30;

void print(char tabela[3][3]){
    printf("\n");
    for(int i = 0; i < 3; i++) {
      printf("  %c  ║  %c  ║  %c ", tabela[i][0], tabela[i][1], tabela[i][2]);
      if(i < 2) printf("\n═════╬═════╬═════\n");
    }
    printf("\n");
}

int check_winner(const char tabela[3][3]){
    if(tabela[0][0] == tabela[1][1] && tabela[1][1] == tabela[2][2] && tabela[0][0] != ' '){
      return 1;
    }
    if(tabela[0][2] == tabela[1][1] && tabela[1][1] == tabela[2][0] && tabela[0][2] != ' '){
      return 1;
    }
    for(int i = 0; i < 3; i++){
      if(tabela[0][i] == tabela[1][i] && tabela[1][i] == tabela[2][i] && tabela[0][i] != ' '){
        return 1;
      }
      if(tabela[i][0] == tabela[i][1] && tabela[i][1] == tabela[i][2] && tabela[i][0] != ' '){
        return 1;
      }
    }
    return 0;
}

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

void movimentacao_mouse(int *lin, int *col, int mov_x, int mov_y, int *sensi_movx, int *sensi_movy, char tabela[3][3]){
    int sensibilidade = SENSIBILIDADE;
    if(mov_x == 1){
      *sensi_movx+= 1;
      if(*col < 2 && *sensi_movx >= sensibilidade) {
        *col += 1;
        *sensi_movx = 0;
      }
    }
    else if (mov_x == 255){
      *sensi_movx-= 1;
      if(*col > 0 && *sensi_movx <= -sensibilidade) {
        *col -= 1;
        *sensi_movx = 0;
      }
    }
    if(mov_y == 1){
      *sensi_movy+= 1;
      if(*lin > 0 && *sensi_movy >= sensibilidade){
        *lin -= 1;
        *sensi_movy = 0;
      }
    }
    else if (mov_y == 255){
      *sensi_movy-= 1;
      if(*lin < 2 && *sensi_movy <= -sensibilidade){
        *lin += 1;
        *sensi_movy = 0;
      }
    }
}

int main(void) {
    FILE *file_ptr;
    const char *mouse_device = "/dev/input/mice"; 
    unsigned char mouse_data[6];
    // Abre o dispositivo do mouse para leitura em modo binário
    file_ptr = fopen(mouse_device, "rb");
    if (file_ptr == NULL ) {
      perror("Erro ao abrir o dispositivo do mouse - botoes");
      return 1;
    }
    char tabela[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char selec;
    int col = 0;
    int lin = 0;
    int cont = 0; 
    int player = 1;
    int quadrante, botao, botao2, mov_x, mov_y;
    int sensi_movx = 0;
    int sensi_movy = 0;
    while(1){
      printf("%d, %d\n", lin, col);
      quadrante = 0;
      if(lin == 0) quadrante = lin + col + 1;
      else if(lin == 1) quadrante = lin+ col + 3;
      else if (lin == 2) quadrante = lin + col + 5;
      print(tabela);
      printf("\nquadrante: %d\n",quadrante);
      printf("player: %d\n",player);
      fread(mouse_data, sizeof(unsigned char), sizeof(mouse_data), file_ptr);
      botao = (int)mouse_data[0];
      mov_x = (int)mouse_data[1];
      mov_y = (int)mouse_data[2];
      botao2 = (int)mouse_data[3];
      // contadores para quadrantes
      if (((botao == 9 && botao2 == 8) || (botao == 8 && botao2 == 9)) && tabela[lin][col] == ' '){
        cont += 1;
          if (player == 1){
            if (tabela[lin][col] == ' '){
              tabela[lin][col] = 'X';
            }
          }
          else{
            if (tabela[lin][col] == ' '){
              tabela[lin][col] = 'O';
            }
          }
      }
      movimentacao_mouse(&lin, &col, mov_x, mov_y, &sensi_movx, &sensi_movy, tabela);
      if(check_winner(tabela)){
        system("clear");
        print(tabela);
        printf("Vitória jogador %d\n", player);
        break;
      }
      if(cont == 9){
        system("clear");
        print(tabela);
        printf("Jogo terminou em empate\n");
        break;
      }
      if(cont % 2 == 0){
        player = 1;
      }
      else player = 2;
      fflush(stdout);
      system("clear");
    }
    fclose(file_ptr);
    return 0;
}
