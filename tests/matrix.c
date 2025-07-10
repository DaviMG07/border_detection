#include "../lib/includes.h"

// Testa a criação de uma nova matriz.
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

// Testa a criação e impressão de uma matriz.
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

// Testa a multiplicação de Hadamard.
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

// Testa a soma dos elementos de uma matriz.
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

// Testa a extração de uma janela de uma matriz.
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
            window = get_window(*matrix, j, i); 
            print_matrix(*window);
            free_matrix(window);
        }
    }
    free_matrix(matrix);
}

// Testa a operação de convolução.
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
    free_matrix(convolved);
}


// Testa a detecção de borda genérica.
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

// Testa o operador de Sobel.
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

// Testa o operador de Sobel expandido.
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

// Testa o operador de Prewitt.
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

// Testa o operador de Roberts Cross.
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

// Testa o operador de Laplace.
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

// Testa a convolução com uma máscara de Sobel 5x5.
void test_convolution_with_padded_sobel_mask() {
    printf("\n--- Testing Convolution with 5x5 Padded Sobel Mask ---\n");

    int matrix_size = 5; 
    Matrix* matrix = new_matrix(matrix_size, matrix_size);
    for (int i = 0; i < matrix->height; i++) {
        for (int j = 0; j < matrix; j++) {
            matrix->self[i][j] = rand() % 256; 
        }
    }

    int sobel_padded_ref[5][5] = {
        {0, 0, 0, 0, 0},
        {0, -1, 0, 1, 0},
        {0, -2, 0, 2, 0},
        {0, -1, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };
    
    Matrix* kernel = copy_reference(sobel_padded_ref);

    printf("Random Matrix (%dx%d):\n", matrix->height, matrix->width);
    print_matrix(*matrix);
    printf("Padded Sobel Gx Kernel (5x5):\n");
    print_matrix(*kernel);

    Matrix* result = convolution(*matrix, *kernel);
    printf("Convolution Result:\n");
    print_matrix(*result);

    free_matrix(matrix);
    free_matrix(kernel);
    free_matrix(result);
}


// Função principal que executa os testes.
int main() {
    srand(time(NULL));

    printf("Running tests...\n");
    
    printf("Test new_matrix result: %d\n", test_new_matrix());
    test_matrix();
    test_hadamard();
    test_sum();
    test_convolution();
    test_generic_edge_detection();
    
    test_sobel();
    test_sobel_expanded();
    test_prewitt();
    test_roberts();
    test_laplace();

    Matrix* matrix;
    Matrix* kernel;
    
    int ref[5][5] = {
    {1, 0, 2, 0, 3},
    {4, 0, 5, 0, 6},
    {7, 0, 8, 0, 9},
    {10, 0, 11, 0, 12},
    {13, 0, 14, 0, 15}
    };
    int ref1[5][5] = {
    {0, 1, 0, 2, 0},
    {0, 3, 0, 4, 0},
    {0, 5, 0, 6, 0},
    {0, 7, 0, 8, 0},
    {0, 9, 0, 10, 0}
    };

    kernel = copy_reference(ref);
    matrix = copy_reference(ref1);
    Matrix* result = convolution(*matrix, *kernel);
    print_matrix(*matrix);
    print_matrix(*kernel);
    print_matrix(*result);

    free_matrix(matrix);
    free_matrix(kernel);
    free_matrix(result);

    test_convolution_with_padded_sobel_mask();

    printf("\nAll tests finished.\n");
    return 0;
}
