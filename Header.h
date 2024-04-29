#ifndef HASH_H
#define HASH_H

void print_tabela(char tabela[3][3]);
void print_tabela_colorida(char tabela[3][3], int lin, int col);
void print_tabela_resultado(char tabela[3][3], int *lin1, int *col1, int *lin2, int *col2, int *lin3, int *col3);
int check_winner(const char tabela[3][3], int *lin1, int *col1, int *lin2, int *col2, int *lin3, int *col3);
void proximo_quadrante(int *lin, int *col);
void anterior_quadrante(int *lin, int *col);
int clique_mouse(int botao, int botao2, char tabela[3][3], unsigned char mouse_data[6], int *cont, int player, int lin, int col);
int movimentacao_mouse(int *lin, int *col, int mov_x, int mov_y, int *sensi_movx, int *sensi_movy);
void print_jogo(char tabela[3][3], unsigned char mouse_data[6], int quadrante, int player, int lin, int col);
void calcular_quadrante(int *quadrante, int lin, int col);
int finalizar_jogo(int cont, char tabela[3][3], int player, int *lin1, int *col1, int *lin2, int *col2, int *lin3, int *col3);


#endif 