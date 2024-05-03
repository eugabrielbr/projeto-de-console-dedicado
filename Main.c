#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <intelfpgaup/KEY.h>
#include "Header.h"

#define SENSIBILIDADE 25;

#define padrao "\033[0m"
#define vermelho "\033[1;41m"
#define verde "\033[1;42m"


int reset(void){
  
  int data;
  
  if(KEY_open() != 1){
    printf("Erro ao abrir!\n");
  }
  
  else{
    
    while(1){
      
      KEY_read(&data);
      
      if(data == 8) {
        
        KEY_close();
        return 1;
      }
      
      if(data == 4){
        
        KEY_close();
        return 2;
      }

    }
  }
  return 0;
}

int main(void) {

  int game = 1;
  int first = 1;
  int iniciar;

  do{
    
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
    int primeiro_print = 1;
    print_menu();
    iniciar = reset();
    if(iniciar == 2) game = 0;
    while(iniciar == 1){
      
      calcular_quadrante(&quadrante, lin, col);
      
      if((v1 || v2) || (primeiro_print == 1)){
        print_jogo(tabela, mouse_data, quadrante, player, lin, col);
	primeiro_print = 0;
      }
      
      fread(mouse_data, sizeof(unsigned char), sizeof(mouse_data), file_ptr);
      
      botao = (int)mouse_data[0];
      mov_x = (int)mouse_data[1];
      mov_y = (int)mouse_data[2];
      botao2 = (int)mouse_data[3];
      v1 = clique_mouse(botao, botao2, tabela, mouse_data, &cont, player, lin, col);
      v2 = movimentacao_mouse(&lin, &col, mov_x, mov_y, &sensi_movx, &sensi_movy);

      if(finalizar_jogo(cont, tabela, player, &lin1, &col1, &lin2, &col2, &lin3, &col3)){
	printf("\nPressione [B1] para voltar ao menu do jogo ou [B2] para finalizar.\n"); 
        int v = reset();
        first = 0;
        if(v == 1) break;
        if(v == 2){
          game = 0;
          break;
        }
      }
      
      if(cont % 2 == 0){
        player = 1;
      }
      else player = 2;

      fflush(stdout);
    }
    fclose(file_ptr);
  
  }while(game);

  KEY_close();
  printf("\nFinalizou o jogo.\n\n");
  return 0;
}
