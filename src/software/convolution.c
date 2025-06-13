#include "../../lib/software/convolution.h"

#include <stdint.h>
#include <stdlib.h>

uint16_t** hadamard(uint8_t** matrix_a, uint8_t** matrix_b, int size) {
  uint16_t** matrix_c = new_matrix(sizeof(uint16_t), size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrix_c[i][j] = (uint16_t)(matrix_a[i][j] * matrix_b[i][j]);
    }
  }
  return matrix_c;
}

uint8_t sum(uint16_t** matrix, int size) {
  uint64_t result = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      result += (uint64_t)matrix[i][j];
    }
  }
  return (result > UINT8_MAX) ? (uint8_t)255 : (uint8_t)result;
}

uint8_t** get_window(uint8_t** matrix, int width, int height, int pixel_x, int pixel_y, int window_size) {

}
