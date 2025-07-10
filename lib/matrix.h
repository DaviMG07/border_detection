#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include "structs.h"

#include "coprocessor.h"

// Aloca uma nova matriz.
Matrix* new_matrix(int width, int height);
// Libera a memória alocada para uma matriz.
void free_matrix(Matrix* matrix);

// Imprime uma matriz no console.
void print_matrix(Matrix matrix);
// Copia uma matriz de referência.
Matrix* copy_reference(int ref[5][5]);

// Realiza a multiplicação de Hadamard entre duas matrizes.
Matrix* hadamard(Matrix a, Matrix b);
// Soma todos os elementos de uma matriz.
int sum(Matrix matrix);
// Transpõe uma matriz.
Matrix* transpose(Matrix matrix);

// Obtém uma janela de uma matriz.
Matrix* get_window(Matrix matrix, int x, int y);
// Realiza a convolução entre uma matriz e uma máscara.
Matrix* convolution(Matrix matrix, Matrix mask);

// Aplica uma detecção de borda genérica em uma matriz.
Matrix* generic_edge_detection(Matrix matrix, Matrix mask);
// Aplica o operador Sobel em uma matriz.
Matrix* sobel(Matrix matrix);
// Aplica o operador Sobel expandido em uma matriz.
Matrix* sobel_expanded(Matrix matrix);
// Aplica o operador Prewitt em uma matriz.
Matrix* prewitt(Matrix matrix);
// Aplica o operador Roberts em uma matriz.
Matrix* roberts(Matrix matrix);
// Aplica o operador de Laplace em uma matriz.
Matrix* laplace(Matrix matrix);

#endif 
