#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void movimentacao_mouse(int *lin, int *col, int mov_x, int mov_y){
    if(mov_x == 1){
      if(*col < 2) *col ++;
    }
    else if (mov_x == 255){
      if(*col > 0) *col --;
    }

    if(mov_y == 1){
      if(*lin > 0) *lin --;
    }
    else if (mov_y == 255){
      if(*lin < 2) *lin ++;
    }
}

int main(void) {
    FILE *file_ptr;
    const char *mouse_device = "/dev/input/mice"; 
    unsigned char mouse_data[3];
    // Abre o dispositivo do mouse para leitura em modo binário
    file_ptr = fopen(mouse_device, "rb");
    if (file_ptr == NULL ) {
        perror("Erro ao abrir o dispositivo do mouse - botoes");
        return 1;
    }
    printf("Lendo eventos do mouse...\n");
    char tabela[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char selec;
    int col = 0;
    int lin = 0;
    int cont = 0; 
    int player = 1;
    int quadrante;
    int botao;
    int mov_x;
    int mov_y;
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
      //selec = getchar(); //tirar quando mudar para mouse, por enq ta tendo input
    
      // contadores para quadrantes
      if (mov_x == 255){ //mudar '\n' para 'r' qd for para mouse
        proximo_quadrante(&lin, &col);
        if (tabela[lin][col] != ' ') {
          while(tabela[lin][col] != ' ')
            proximo_quadrante(&lin, &col);
        }
      }
      else if (mov_x = 1){ //mudar '\n' para 'r' qd for para mouse
        anterior_quadrante(&lin, &col);
        if (tabela[lin][col] != ' ') {
          while(tabela[lin][col] != ' ')
            anterior_quadrante(&lin, &col);
        }
      }
      if (botao == 9){
        cont += 1;
        while(tabela[lin][col] != ' '){
            proximo_quadrante(&lin, &col);
        }
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
