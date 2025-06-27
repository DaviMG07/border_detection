#include <stdio.h>
#include "../lib/matrix.h"

int test_new_matrix() {
  Matrix* matrix = new_matrix(5, 5);
  if (matrix == NULL) return 0;
  if (matrix->self == NULL) return 1;
  for (int i = 0; i < matrix->height; i++) {
    if (matrix->self[i] == NULL)  return 2;
  }
  matrix->self[0][0] = -1;
  if (matrix->self[0][0] != -1) return 3;
  free_matrix(matrix);
  return 4;
}

void test_matrix() {
  Matrix* matrix = new_matrix(7, 2);
  for (int i = 0; i < matrix->height; i++) {
    for (int j = 0; j < matrix->width; j++) {
      matrix->self[i][j] = i*matrix->width + j;
    }
  }
  print_matrix(*matrix);
  free_matrix(matrix);
}

void test_hadamard() {
  int a[5][5];
  int b[5][5];
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      a[i][j] = i*5 + j;
      b[j][i] = i*5 + j;
    }
  }
  Matrix* ma = copy_reference(a);
  Matrix* mb = copy_reference(b);
  Matrix* c = hadamard(*ma, *mb);
  print_matrix(*ma);
  print_matrix(*mb);
  print_matrix(*c);

  free_matrix(ma);
  free_matrix(mb);
  free_matrix(c);
}

void test_sum() {
  Matrix* matrix = new_matrix(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      matrix->self[i][j] = i*5 + j;
    }
  }
  print_matrix(*matrix);
  printf("sum: %d\n", sum(*matrix));
  free_matrix(matrix);
}

void test_get_window() {
  Matrix* matrix = new_matrix(5, 5);
  Matrix* window;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      matrix->self[i][j] = i*5 + j;
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      // get_window espera (matriz, x, y), então é (matriz, j, i)
      window = get_window(*matrix, j, i); 
      print_matrix(*window);
      free_matrix(window); // Liberar a janela a cada iteração
    }
  }
  free_matrix(matrix);
}

void test_convolution() {
    printf("\n--- Testing Convolution ---\n");
    Matrix* matrix = new_matrix(5, 5);
    Matrix* mask   = new_matrix(5, 5);
    Matrix* convolved;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int x = i * 5 + j;
            matrix->self[i][j] = x;
            mask->self[i][j] = j * (x % 2 ? 1 : -1);
        }
    }
    printf("Original Matrix for Convolution:\n");
    print_matrix(*matrix);
    printf("Mask for Convolution:\n");
    print_matrix(*mask);
    
    convolved = convolution(*matrix, *mask);
    printf("Convolved Matrix:\n");
    print_matrix(*convolved);
    
    free_matrix(matrix);
    free_matrix(mask);
    free_matrix(convolved); // Liberar a matriz resultante
}


void test_generic_edge_detection() {
    Matrix* matrix = new_matrix(5, 5);
    Matrix* mask;
    Matrix* result;
    int ref[5][5] = {
        {0, 0, 0, 0, 0},
        {0, -1, -1, -1, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix->self[i][j] = i*5 + j;
        }
    }
    mask = copy_reference(ref);
    result = generic_edge_detection(*matrix, *mask);
    
    printf("\n--- Testing Generic Edge Detection ---\n");
    printf("Original Matrix:\n");
    print_matrix(*matrix);
    printf("Mask:\n");
    print_matrix(*mask);
    printf("Result:\n");
    print_matrix(*result);
    
    free_matrix(matrix);
    free_matrix(mask);
    free_matrix(result);
}

void test_sobel() {
    printf("\n--- Testing Sobel Operator ---\n");
    Matrix* matrix = new_matrix(7, 7);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matrix->self[i][j] = (i > 1 && i < 5 && j > 1 && j < 5) ? 200 : 20;
        }
    }
    printf("Original Matrix:\n");
    print_matrix(*matrix);

    Matrix* result = sobel(*matrix);
    printf("Sobel Result:\n");
    print_matrix(*result);

    free_matrix(matrix);
    free_matrix(result);
}

void test_sobel_expanded() {
    printf("\n--- Testing Sobel Expanded Operator ---\n");
    Matrix* matrix = new_matrix(7, 7);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matrix->self[i][j] = (i > 1 && i < 5 && j > 1 && j < 5) ? 200 : 20;
        }
    }
    printf("Original Matrix:\n");
    print_matrix(*matrix);

    Matrix* result = sobel_expanded(*matrix);
    printf("Sobel Expanded Result:\n");
    print_matrix(*result);

    free_matrix(matrix);
    free_matrix(result);
}

void test_prewitt() {
    printf("\n--- Testing Prewitt Operator ---\n");
    Matrix* matrix = new_matrix(7, 7);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matrix->self[i][j] = j > 3 ? 220 : 30;
        }
    }
    printf("Original Matrix:\n");
    print_matrix(*matrix);

    Matrix* result = prewitt(*matrix);
    printf("Prewitt Result:\n");
    print_matrix(*result);

    free_matrix(matrix);
    free_matrix(result);
}

void test_roberts() {
    printf("\n--- Testing Roberts Cross Operator ---\n");
    Matrix* matrix = new_matrix(7, 7);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matrix->self[i][j] = (i > j) ? 200 : 20;
        }
    }
    printf("Original Matrix:\n");
    print_matrix(*matrix);

    Matrix* result = roberts(*matrix);
    printf("Roberts Result:\n");
    print_matrix(*result);

    free_matrix(matrix);
    free_matrix(result);
}

void test_laplace() {
    printf("\n--- Testing Laplace Operator ---\n");
    Matrix* matrix = new_matrix(7, 7);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matrix->self[i][j] = (i > 1 && i < 5 && j > 1 && j < 5) ? 200 : 20;
        }
    }
    printf("Original Matrix:\n");
    print_matrix(*matrix);

    Matrix* result = laplace(*matrix);
    printf("Laplace Result:\n");
    print_matrix(*result);

    free_matrix(matrix);
    free_matrix(result);
}

int main() {
    printf("Running tests...\n");
    
    printf("Test new_matrix result: %d\n", test_new_matrix());
    test_matrix();
    test_hadamard();
    test_sum();
    // test_get_window(); // Esta função imprime muitas matrizes, pode ser comentada para clareza
    test_convolution();
    test_generic_edge_detection();
    
    // Chamando as novas funções de teste
    test_sobel();
    test_sobel_expanded();
    test_prewitt();
    test_roberts();
    test_laplace();

    printf("\nAll tests finished.\n");
    return 0;
}
