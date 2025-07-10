#include "../lib/includes.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"

// Aloca uma nova imagem.
Image* new_image(int width, int height) {
    Image* image = malloc(sizeof(Image));
    image->colors = malloc(sizeof(Channel*) * 3);
    for (int i = 0; i < 3; i++) {
        image->colors[i] = new_matrix(width, height);
    }
    image->gray = new_matrix(width, height);
    image->width = width;
    image->height = height;
    return image;
}

// Carrega uma imagem de um arquivo.
Image* get_image(const char* path) {
    int x, y, channels;
    unsigned char* gray = stbi_load(path, &x, &y, &channels, 1);
    unsigned char* colors = stbi_load(path, &x, &y, &channels, 3);
    Image* image = new_image(x, y);
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            unsigned char* pixel_offset = colors + (i * x + j) * channels;
            image->colors[0]->self[i][j] = (int)pixel_offset[0];
            image->colors[1]->self[i][j] = (int)pixel_offset[1];
            image->colors[2]->self[i][j] = (int)pixel_offset[2];
            image->gray->self[i][j] = (int)gray[(i * x + j)];
        }
    }
    stbi_image_free(gray);
    stbi_image_free(colors);
    return image;
}

// Libera a memória alocada para uma imagem.
void free_image(Image* image) {
    if (image == NULL) return;

    if (image->gray != NULL) {
        free_matrix(image->gray);
    }

    if (image->colors != NULL) {
        for (int i = 0; i < 3; i++) {
            if (image->colors[i] != NULL) {
                free_matrix(image->colors[i]);
            }
        }
        free(image->colors);
    }
    free(image);
}

// Salva uma imagem em um arquivo.
void save_image(const char* path, Image image, int channel) {
    unsigned char* colors = malloc(sizeof(unsigned char) * image.width * image.height * 3);
    unsigned char* gray = malloc(sizeof(unsigned char) * image.width * image.height);

    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            int index = i * image.width + j;
            unsigned char* pixel_offset = colors + index * 3;
            gray[index] = image.gray->self[i][j];
            for (int c = 0; c < 3; c++) {
                pixel_offset[c] = image.colors[c]->self[i][j];
            }
        }
    }

    if (!channel) {
        stbi_write_jpg(path, image.width, image.height, 1, gray, 100);
    } else {
        stbi_write_jpg(path, image.width, image.height, 3, colors, 100);
    }

    free(colors);
    free(gray);
}

// Aplica uma detecção de borda genérica em uma imagem.
static Image* edge_detection_generic_image(Image image, Channel* (*callback)(Channel)) {
    Channel* gray = callback(*(image.gray));
    Image* result = new_image(image.width, image.height);

    free_matrix(result->gray);

    result->gray = gray;
    return result;
}

// Aplica o operador Sobel em uma imagem.
Image* sobel_image(Image image) {
    return edge_detection_generic_image(image, sobel);
}

// Aplica o operador Sobel expandido em uma imagem.
Image* sobel_expanded_image(Image image) {
    return edge_detection_generic_image(image, sobel_expanded);
}

// Aplica o operador Prewitt em uma imagem.
Image* prewitt_image(Image image) {
    return edge_detection_generic_image(image, prewitt);
}

// Aplica o operador Roberts em uma imagem.
Image* roberts_image(Image image) {
    return edge_detection_generic_image(image, roberts);
}

// Aplica o operador de Laplace em uma imagem.
Image* laplace_image(Image image) {
    return edge_detection_generic_image(image, laplace);
}
