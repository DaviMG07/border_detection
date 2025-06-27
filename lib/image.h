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

/**
 * @brief Aloca uma nova estrutura de imagem.
 * @param width A largura da imagem.
 * @param height A altura da imagem.
 * @return Um ponteiro para a nova Image.
 */
Image* new_image(int width, int height);

/**
 * @brief Carrega uma imagem de um arquivo.
 * @param path O caminho para o arquivo de imagem.
 * @return Um ponteiro para a Image carregada.
 */
Image* get_image(const char* path);

/**
 * @brief Libera a memória alocada para uma imagem.
 * @param image O ponteiro para a imagem a ser liberada.
 */
void free_image(Image* image);

/**
 * @brief Salva uma imagem em um arquivo JPG.
 * @param path O caminho do arquivo para salvar a imagem.
 * @param image A imagem a ser salva.
 * @param channel Se 0, salva em escala de cinza; se 1, salva colorida.
 */
void save_image(const char* path, Image image, int channel);

/**
 * @brief Aplica o operador Sobel em uma imagem.
 * @param image A imagem de entrada.
 * @return Uma nova imagem com o filtro Sobel aplicado.
 */
Image* sobel_image(Image image);

/**
 * @brief Aplica o operador Sobel expandido em uma imagem.
 * @param image A imagem de entrada.
 * @return Uma nova imagem com o filtro Sobel expandido aplicado.
 */
Image* sobel_expanded_image(Image image);

/**
 * @brief Aplica o operador Prewitt em uma imagem.
 * @param image A imagem de entrada.
 * @return Uma nova imagem com o filtro Prewitt aplicado.
 */
Image* prewitt_image(Image image);

/**
 * @brief Aplica o operador Roberts em uma imagem.
 * @param image A imagem de entrada.
 * @return Uma nova imagem com o filtro Roberts aplicado.
 */
Image* roberts_image(Image image);

/**
 * @brief Aplica o operador de Laplace em uma imagem.
 * @param image A imagem de entrada.
 * @return Uma nova imagem com o filtro de Laplace aplicado.
 */
Image* laplace_image(Image image);

#endif // IMAGE_H
