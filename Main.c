#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENSIBILIDADE 25;

#define padrao "\033[0m"
#define vermelho "\033[1;41m"
#define verde "\033[1;42m"


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


void print_jogo(char tabela[3][3], unsigned char mouse_data[6], int quadrante, int player, int lin, int col){
    system("clear");
    printf("%d, %d, %d, %d, %d, %d\n", mouse_data[0], mouse_data[1], mouse_data[2], mouse_data[3], mouse_data[4], mouse_data[5]);
    printf("%d, %d\n", lin, col);
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
      printf("Vitória jogador %d\n", player);
      return 1;
    }
    else if(cont == 9){
      system("clear");
      print_tabela(tabela);
      printf("Jogo terminou em empate\n");
      return 1;
    }
    return 0;
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
    int col = 0;
    int lin = 0;
    int cont = 0; 
    int player = 1;
    int quadrante, botao, botao2, mov_x, mov_y;
    int sensi_movx = 0;
    int sensi_movy = 0;
    int v1,v2 = 1;
    int lin1, col1, lin2, col2, lin3, col3;
    while(1){
      calcular_quadrante(&quadrante, lin, col);
      if((v1 || v2) || (cont == 0)){
        print_jogo(tabela, mouse_data, quadrante, player, lin, col);
      }
      fread(mouse_data, sizeof(unsigned char), sizeof(mouse_data), file_ptr);
      botao = (int)mouse_data[0];
      mov_x = (int)mouse_data[1];
      mov_y = (int)mouse_data[2];
      botao2 = (int)mouse_data[3];
      v1 = clique_mouse(botao, botao2, tabela, mouse_data, &cont, player, lin, col);
      v2 = movimentacao_mouse(&lin, &col, mov_x, mov_y, &sensi_movx, &sensi_movy);
      if(finalizar_jogo(cont, tabela, player, &lin1, &col1, &lin2, &col2, &lin3, &col3)){
        break;
      }
      if(cont % 2 == 0){
        player = 1;
      }
      else player = 2;
      fflush(stdout);
    }
    fclose(file_ptr);
    return 0;
}
