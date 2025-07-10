#include "../lib/includes.h"

// Cria e aloca uma nova matriz.
Matrix* new_matrix(int width, int height) {
  Matrix* matrix = malloc(sizeof(Matrix));
  if (matrix == NULL) return NULL;
  matrix->self = malloc(sizeof(int*) * height);
  if (matrix->self == NULL) {
    free(matrix);
    matrix = NULL;
    return NULL;
  }
  for (int i = 0; i < height; i++) {
    matrix->self[i] = malloc(sizeof(int) * width);
    if (matrix->self[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(matrix->self[j]);
      }
      free(matrix->self);
      free(matrix);
      return NULL;
    }
  }
  matrix->width  = width;
  matrix->height = height;
  return matrix;
}

// Libera a memória de uma matriz.
void free_matrix(Matrix* matrix) {
  if (matrix == NULL) return;
  if (matrix->self == NULL) return;
  for (int i = 0; i < matrix->height; i++) {
    if (matrix->self[i] == NULL) continue;
    free(matrix->self[i]);
    matrix->self[i] = NULL;
  }
  free(matrix->self);
  matrix->self = NULL;
  free(matrix);
  matrix = NULL;
}

// Imprime a matriz no console.
void print_matrix(Matrix matrix) {
  printf("printing matrix...\n");
  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
      printf("%d ", matrix.self[i][j]);
    }
    printf("\n");
  }
  printf("done.\n");
}

// Realiza o produto de Hadamard (multiplicação elemento a elemento).
Matrix* hadamard(Matrix a, Matrix b) {
  Matrix* result = new_matrix(a.width, a.height);
  for (int i = 0; i < a.height; i++) {
    for (int j = 0; j < a.width; j++) {
      result->self[i][j] = a.self[i][j] * b.self[i][j];
    }
  }
  return result;
}

// Copia um array 2D estático para uma estrutura Matrix.
Matrix* copy_reference(int ref[5][5]) {
  Matrix* matrix = new_matrix(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      matrix->self[i][j] = ref[i][j];
    }
  }
  return matrix;
}

// Soma todos os elementos de uma matriz.
int sum(Matrix matrix) {
  int result = 0;
  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
      result += matrix.self[i][j];
    }
  }
  return result;
}

// Extrai uma janela 5x5 da matriz com tratamento de bordas.
Matrix* get_window(Matrix matrix, int x, int y) {
  Matrix* window = new_matrix(5, 5);
  int index_x[5];
  int index_y[5];

  for (int i = 0; i < 5; i++) {
    index_x[i] = x + i - 2;
    index_x[i] = index_x[i] >= matrix.width ? matrix.width - 1 : index_x[i] < 0 ? 0 : index_x[i];
    index_y[i] = y + i - 2;
    index_y[i] = index_y[i] >= matrix.height ? matrix.height - 1 : index_y[i] < 0 ? 0 : index_y[i];
  }

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
        window->self[j][i] = matrix.self[index_y[j]][index_x[i]];
    }
  }
  return window;
}


// Realiza a operação de convolução.
#ifndef COPROCESSOR

Matrix* convolution(Matrix matrix, Matrix mask) {
  printf("using hps\n");
  int result;
  Matrix* window;
  Matrix* temp;
  Matrix* convolved = new_matrix(matrix.width, matrix.height);
  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
        window = get_window(matrix, j, i);
        temp   = hadamard(*window, mask);
        result = sum(*temp);
        convolved->self[i][j] = result;
        free_matrix(window);
        free_matrix(temp);
    }
  }
  return convolved;
}

#else

Matrix* convolution(Matrix matrix, Matrix mask) {
  Mpu* mpu = init_mpu();
  printf("using fpga\n");
  int result;
  Matrix* window;
  Matrix* temp;
  Matrix* convolved = new_matrix(matrix.width, matrix.height);
  printf("yep, I could send\n");
  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
      window = get_window(matrix, j, i);
      send_matrix(0, *window, mpu);
      send_matrix(1, mask, mpu);
      conv(mpu);
      result = get_value(0, 0, mpu);
      if (get_value(0, 1, mpu)) {
         result = 0;~((-1) ^ result);
      }
      *(mpu->data_in) = 7;
      convolved->self[i][j] = result;
      free_matrix(window);
    }
  }
  cleanup_mpu(mpu);
  return convolved;
}
#endif


// Transpõe uma matriz.
Matrix* transpose(Matrix matrix) {
  Matrix* result = new_matrix(matrix.height, matrix.width);
  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
      result->self[j][i] = matrix.self[i][j];
    }
  }
  return result;
}

// Detecção de bordas genérica usando gradiente.
Matrix* generic_edge_detection(Matrix matrix, Matrix mask) {
  Matrix* t_mask     = transpose(mask);
  Matrix* horizontal = convolution(matrix, mask);
  Matrix* vertical   = convolution(matrix, *t_mask);
  Matrix* edge       = new_matrix(matrix.width, matrix.height);
  int     magnitude;

  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
      magnitude = (int)sqrt(pow((double)horizontal->self[i][j], 2.0) + pow((double)vertical->self[i][j], 2.0));
      edge->self[i][j] = magnitude > 255 ? 255 : magnitude < 0 ? 0 : magnitude;
    }
  }
  free_matrix(t_mask);
  free_matrix(horizontal);
  free_matrix(vertical);
  return edge;
}

// Aplica o operador de Sobel.
Matrix* sobel(Matrix matrix) {
  Matrix* mask;
  Matrix* result;
  int ref[5][5] = {
    {0, 0, 0, 0, 0},
    {0, -1, 0, 1, 0},
    {0, -2, 0, 2, 0},
    {0, -1, 0, 1, 0},
    {0, 0, 0, 0, 0}
  };
  mask   = copy_reference(ref);
  result = generic_edge_detection(matrix, *mask);
  free_matrix(mask);
  return result;
}

// Aplica o operador de Sobel expandido.
Matrix* sobel_expanded(Matrix matrix) {
  Matrix* mask;
  Matrix* result;
  int ref[5][5] = {
    {-1, -2, 0, 2, 1},
    {-2, -3, 0, 3, 2},
    {-3, -5, 0, 5, 3},
    {-2, -3, 0, 3, 2},
    {-1, -2, 0, 2, 1}
  };
  mask   = copy_reference(ref);
  result = generic_edge_detection(matrix, *mask);
  free_matrix(mask);
  return result;
}

// Aplica o operador de Prewitt.
Matrix* prewitt(Matrix matrix) {
  Matrix* mask;
  Matrix* result;
  int ref[5][5] = {
    {0, 0, 0, 0, 0},
    {0, -1, 0, 1, 0},
    {0, -1, 0, 1, 0},
    {0, -1, 0, 1, 0},
    {0, 0, 0, 0, 0}
  };
  mask   = copy_reference(ref);
  result = generic_edge_detection(matrix, *mask);
  free_matrix(mask);
  return result;
}

// Aplica o operador de Roberts Cross.
Matrix* roberts(Matrix matrix) {
  int result;
  int roberts_gx[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, -1, 0},
    {0, 0, 0, 0, 0}
  };
  int roberts_gy[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 0, -1, 0, 0},
    {0, 0, 0, 0, 0}
  };
  Matrix* mask_gx = copy_reference(roberts_gx);
  Matrix* mask_gy = copy_reference(roberts_gy);
  Matrix* gx      = convolution(matrix, *mask_gx);
  Matrix* gy      = convolution(matrix, *mask_gy);
  Matrix* edge    = new_matrix(matrix.width, matrix.height);

  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
      result = (int)sqrt(pow((double)gx->self[i][j], 2.0) + pow((double)gy->self[i][j], 2.0));
      edge->self[i][j] = result > 255 ? 255 : result;
    }
  }
  free_matrix(mask_gy);
  free_matrix(mask_gx);
  free_matrix(gx);
  free_matrix(gy);
  return edge;
}

// Aplica o operador de Laplace.
Matrix* laplace(Matrix matrix) {
  Matrix* mask;
  Matrix* result;
  int ref[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 1, -8, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
  };
  mask   = copy_reference(ref);
  result = convolution(matrix, *mask);
  for (int i = 0; i < matrix.height; i++) {
    for (int j = 0; j < matrix.width; j++) {
      result->self[i][j] = result->self[i][j] > 255 ? 255 :
                           result->self[i][j] < 0   ? 0   : 
                           result->self[i][j];
    }
  }
  free_matrix(mask);
  return result;
}
