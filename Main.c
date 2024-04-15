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

void proximo_quadrante(int *col, int *lin){
      if (*lin < 2){
        *lin += 1;
      }
      else{
          if (*col < 2){
            *col += 1;
            *lin = 0;
          }
          else{
            *col = 0;
            *lin = 0;
          }    
      }
}

int main(void) {
    char tabela[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char selec;
    int col = 0;
    int lin = 0;
    int cont = 0; 
    int player = 1;        
    int quadrante;
    while(1){
      printf("%d, %d\n", col, lin);
      quadrante = 0;
      if(col == 0) quadrante = lin + col + 1;
      else if(col == 1) quadrante = lin+ col + 3;
      else if (col == 2) quadrante = lin + col + 5;
      print(tabela);
      printf("\nquadrante: %d\n",quadrante);
      printf("player: %d\n",player);
      selec = getchar(); //tirar quando mudar para mouse, por enq ta tendo input
    
      // contadores para quadrantes
      if (selec == '\n'){ //mudar '\n' para 'r' qd for para mouse
        proximo_quadrante(&col, &lin);
        if (tabela[col][lin] != ' ') {
          while(tabela[col][lin] != ' ')
            proximo_quadrante(&col, &lin);
        }
      }
      else if (selec == 'l'){
        cont += 1;
          if (player == 1){
              if (tabela[col][lin] == ' '){
                  tabela[col][lin] = 'X';
              }

          }
          else{
              if (tabela[col][lin] == ' '){
                  tabela[col][lin] = 'O';
              }
          }
      }
      if(check_winner(tabela)){
        system("clear");
        print(tabela);
        printf("Vitória jogador %d\n", player);
        break;
      }
      else if(cont == 9){
        system("clear");
        print(tabela);
        printf("Jogo terminou em empate\n");
        break;
      }
      if(cont % 2 == 0){
        player = 1;
      }
      else player = 2;
      system("clear");
    }

    return 0;
}
