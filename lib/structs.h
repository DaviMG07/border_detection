#ifndef STRUCTS_H
#define STRUCTS_H

// Estrutura para comunicação com o coprocessador.
typedef struct {
    int fd;
    void* lw_virtual_base;
    volatile int* data_in;
    volatile int* data_out;
} Mpu;

// Estrutura para representar uma matriz.
typedef struct {
    int** self;
    int width;
    int height;
} Matrix;

#endif
