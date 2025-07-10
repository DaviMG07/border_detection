#ifndef IMAGE_H
#define IMAGE_H

#include "../lib/matrix.h"

// Define um canal de cor como uma Matrix
typedef Matrix Channel;

// Estrutura para representar uma imagem com canais de cor e escala de cinza
typedef struct {
    Channel** colors; // Matrizes para os canais R, G, B
    Channel* gray;   // Matriz para a escala de cinza
    int       width;  // Largura da imagem
    int       height; // Altura da imagem
} Image;

// Aloca uma nova estrutura de imagem.
Image* new_image(int width, int height);

// Carrega uma imagem de um arquivo.
Image* get_image(const char* path);

// Libera a memória alocada para uma imagem.
void free_image(Image* image);

// Salva uma imagem em um arquivo JPG.
void save_image(const char* path, Image image, int channel);

// Aplica o operador Sobel em uma imagem.
Image* sobel_image(Image image);

// Aplica o operador Sobel expandido em uma imagem.
Image* sobel_expanded_image(Image image);

// Aplica o operador Prewitt em uma imagem.
Image* prewitt_image(Image image);

// Aplica o operador Roberts em uma imagem.
Image* roberts_image(Image image);

// Aplica o operador de Laplace em uma imagem.
Image* laplace_image(Image image);

#endif // IMAGE_H
