#include <stdio.h>
#include <stdlib.h>

int main() {
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

    while (1) {
        // Lê 3 bytes de dados do mouse
        fread(mouse_data, sizeof(unsigned char), sizeof(mouse_data), file_ptr);

        
        int botao = (int)mouse_data[0];
        int mov_x = (int)mouse_data[1];
        int mov_y= (int)mouse_data[2];
        
        if (botao == 9){
            printf("botao esquerdo\n");
        }
        else if (botao == 10){
            printf("botao direito\n");
        }
        
    
        if(mov_x == 1){
            printf("movendo direita\n");
        }
        else if (mov_x == 255){
            printf("movendo esquerda\n");
        }

    

        if(mov_y == 1){
            printf("movendo cima\n");
        }
        else if (mov_y == 255){
            printf("movendo baixo\n");
        }
        

        fflush(stdout);
    }

   
    fclose(file_ptr);
  

    return 0;
}