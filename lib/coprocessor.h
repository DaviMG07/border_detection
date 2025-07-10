#ifndef COPROCESSOR_H
#define COPROCESSOR_H

#include "matrix.h"
#include "structs.h"

#define LW_BRIDGE_BASE 0xFF200000
#define LW_BRIDGE_SPAN 0x00005000
#define DATA_IN_BASE  0x0
#define DATA_OUT_BASE 0x10

// Armazena um valor em uma posição específica da memória do coprocessador.
void store(int id, int row, int col, int value, Mpu* mpu);
// Carrega um valor de uma posição específica da memória do coprocessador.
int load(int row, int col, Mpu* mpu);
// Executa a convolução no coprocessador.
void conv(Mpu* mpu);

// Preenche uma matriz 5x5 com um valor específico.
void filler(int matrix[5][5], int value);

// Inicializa a estrutura Mpu para comunicação com o coprocessador.
Mpu* init_mpu();

// Libera os recursos alocados para a estrutura Mpu.
void cleanup_mpu(Mpu* mpu);

// Envia uma matriz para o coprocessador.
void send_matrix(int id, Matrix matrix, Mpu* mpu);

// Obtém um valor de uma posição específica da memória do coprocessador.
int get_value(int col, int row, Mpu* mpu);

#endif
