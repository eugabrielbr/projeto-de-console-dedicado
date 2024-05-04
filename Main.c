#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <intelfpgaup/KEY.h> // Inclui a biblioteca necessária para a interação com a chave no dispositivo Intel FPGA
#include "Header.h" // Inclui o arquivo de cabeçalho personalizado "Header.h"

#define SENSIBILIDADE 25; // Define a sensibilidade do mouse

#define padrao "\033[0m" // Define as cores para impressão na tela
#define vermelho "\033[1;41m"
#define verde "\033[1;42m"


// Função para resetar o jogo
int reset(void){
  
  int data;
  
  // Abre a chave no dispositivo Intel FPGA
  if(KEY_open() != 1){
    printf("Erro ao abrir!\n");
  }
  
  else{
    
    while(1){
      
      // Lê o estado da chave
      KEY_read(&data);
      
      // Verifica se a chave foi pressionada para a direita
      if(data == 8) {
        
        // Fecha a chave
        KEY_close();
        return 1; // Retorna 1 indicando que o jogo deve ser reiniciado
      }
      
      // Verifica se a chave foi pressionada para a esquerda
      if(data == 4){
        
        // Fecha a chave
        KEY_close();
        return 2; // Retorna 2 indicando que o jogo deve ser encerrado
      }

    }
  }
  return 0; // Retorna 0 indicando que nenhum comando foi dado
}


int main(void) {

  int game = 1; // Variável para controlar se o jogo está em execução
  int first = 1; // Variável para indicar se é o primeiro jogo
  int iniciar; // Variável para armazenar o resultado da função de reinicialização

  do{
    
    FILE *file_ptr;
    const char *mouse_device = "/dev/input/mice"; // Caminho para o dispositivo do mouse
    unsigned char mouse_data[6]; // Array para armazenar os dados do mouse
    // Abre o dispositivo do mouse para leitura em modo binário
    file_ptr = fopen(mouse_device, "rb");

    if (file_ptr == NULL ) {
      perror("Erro ao abrir o dispositivo do mouse - botoes");
      return 1; // Retorna 1 indicando um erro
    }

    char tabela[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}}; // Tabuleiro do jogo
    int col = 0; // Índice da coluna atual
    int lin = 0; // Índice da linha atual
    int cont = 0; // Contador de movimentos no jogo
    int player = 1; // Jogador atual
    int quadrante, botao, botao2, mov_x, mov_y; // Variáveis para armazenar informações do mouse
    int sensi_movx = 0; // Sensibilidade do movimento horizontal do mouse
    int sensi_movy = 0; // Sensibilidade do movimento vertical do mouse
    int v1,v2 = 1; // Variáveis de controle para movimento do mouse
    int lin1, col1, lin2, col2, lin3, col3; // Variáveis para armazenar a posição do vencedor
    int primeiro_print = 1; // Variável para controlar o primeiro print do jogo
    print_menu(); // Imprime o menu inicial
    iniciar = reset(); // Executa a função de reinicialização do jogo
    if(iniciar == 2) game = 0; // Se o jogo for encerrado, altera o estado da variável de controle
    while(iniciar == 1){
      
      calcular_quadrante(&quadrante, lin, col); // Calcula o quadrante atual do tabuleiro
      
      // Verifica se é necessário imprimir o jogo
      if((v1 || v2) || (primeiro_print == 1)){
        print_jogo(tabela, mouse_data, quadrante, player, lin, col); // Imprime o jogo atualizado
	primeiro_print = 0; // Altera o estado da variável para indicar que o primeiro print já foi feito
      }
      
      fread(mouse_data, sizeof(unsigned char), sizeof(mouse_data), file_ptr); // Lê os dados do mouse
      
      botao = (int)mouse_data[0]; // Obtém o estado do botão do mouse
      mov_x = (int)mouse_data[1]; // Obtém o movimento horizontal do mouse
      mov_y = (int)mouse_data[2]; // Obtém o movimento vertical do mouse
      botao2 = (int)mouse_data[3]; // Obtém o estado do segundo botão do mouse
      v1 = clique_mouse(botao, botao2, tabela, mouse_data, &cont, player, lin, col); // Verifica o clique do mouse
      v2 = movimentacao_mouse(&lin, &col, mov_x, mov_y, &sensi_movx, &sensi_movy); // Verifica o movimento do mouse

      // Verifica se o jogo terminou
      if(finalizar_jogo(cont, tabela, player, &lin1, &col1, &lin2, &col2, &lin3, &col3)){
	printf("\nPressione [B1] para voltar ao menu do jogo ou [B2] para finalizar.\n"); 
        int v = reset(); // Executa a função de reinicialização
        first = 0; // Altera o estado da variável para indicar que não é mais o primeiro jogo
        if(v == 1) break; // Se o jogo for reiniciado, sai do loop
        if(v == 2){
          game = 0; // Se o jogo for encerrado, altera o estado da variável de controle
          break;
        }
      }
      
      // Alterna o jogador
      if(cont % 2 == 0){
        player = 1;
      }
      else player = 2;

      fflush(stdout); // Limpa o buffer de saída
    }
    fclose(file_ptr); // Fecha o arquivo de dispositivo do mouse
  
  }while(game); // Executa o loop principal enquanto o jogo estiver em execução

  KEY_close(); // Fecha a chave do dispositivo Intel FPGA
  printf("\nFinalizou o jogo.\n\n"); // Imprime a mensagem de encerramento do jogo
  return 0; // Retorna 0 indicando a conclusão bem-sucedida do programa
}
