#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <stdint.h>

uint16_t** hadamard(uint8_t** matrix_a, uint8_t** matrix_b, int size);
uint8_t    sum(uint16_t** matrix, int size);
uint8_t**  get_window(uint8_t** matrix, int width, int height, int pixel_x, int pixel_y, int window size);
uint8_t**  convolution(uint8_t** source, int width, int height, uint8_t** mask, int mask_size);

#endif
