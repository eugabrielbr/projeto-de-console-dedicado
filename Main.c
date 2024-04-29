#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

#define SENSIBILIDADE 25;

#define padrao "\033[0m"
#define vermelho "\033[1;41m"
#define verde "\033[1;42m"

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
