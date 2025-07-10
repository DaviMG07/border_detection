#include "../lib/includes.h"

// Testa a inversão de cores de uma imagem.
void test_image() {
    Image* image = get_image("media/tilapia.jpg");
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            for (int c = 0; c < 3; c++) {
                image->colors[c]->self[i][j] ^= 255;
            }
        }
    }
    save_image("media/test.jpg", *image, 1);
    free_image(image);
}

// Testa os algoritmos de detecção de borda.
void test_edge_detection_image() {
    Image* image_ptr = get_image("media/tilapia.jpg");
    Image image = *image_ptr;
    
    Image* sobel = sobel_image(image);
    Image* sobel_expanded = sobel_expanded_image(image);
    Image* prewitt = prewitt_image(image);
    Image* roberts = roberts_image(image);
    Image* laplace = laplace_image(image);
    free_image(image_ptr);

    printf("Salvando imagens com filtros de detecção de borda...\n");

    save_image("media/sobel_gray.jpg", *sobel, 0);
    save_image("media/sobel_expanded_gray.jpg", *sobel_expanded, 0);
    save_image("media/prewitt_gray.jpg", *prewitt, 0);
    save_image("media/roberts_gray.jpg", *roberts, 0);
    save_image("media/laplace_gray.jpg", *laplace, 0);

    printf("Imagens salvas com sucesso.\n");

    free_image(sobel);
    free_image(sobel_expanded);
    free_image(prewitt);
    free_image(roberts);
    free_image(laplace);
}

// Função principal que executa os testes.
int main() {
    printf("Executando teste de inversão de imagem...\n");
    test_image();
    printf("Teste de inversão finalizado.\n\n");
    
    printf("Executando testes de detecção de borda...\n");
    test_edge_detection_image();
    printf("Testes de detecção de borda finalizados.\n");
    return 0;
}
