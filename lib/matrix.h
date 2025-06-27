#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

// Estrutura da Matriz
typedef struct {
  int** self;
  int width;
  int height;
} Matrix;

// --- Protótipos das Funções ---

// Alocação e Desalocação
Matrix* new_matrix(int width, int height);
void free_matrix(Matrix* matrix);

// Utilitários
void print_matrix(Matrix matrix);
Matrix* copy_reference(int ref[5][5]);

// Operações Matemáticas
Matrix* hadamard(Matrix a, Matrix b);
int sum(Matrix matrix);
Matrix* transpose(Matrix matrix);

// Processamento de Imagem
Matrix* get_window(Matrix matrix, int x, int y);
Matrix* convolution(Matrix matrix, Matrix mask);

// Detecção de Bordas
Matrix* generic_edge_detection(Matrix matrix, Matrix mask);
Matrix* sobel(Matrix matrix);
Matrix* sobel_expanded(Matrix matrix);
Matrix* prewitt(Matrix matrix);
Matrix* roberts(Matrix matrix);
Matrix* laplace(Matrix matrix);

#endif // MATRIX_H
