#define  STB_IMAGE_IMPLEMENTATION
#define  STB_IMAGE_WRITE_IMPLEMENTATION
#include "../lib/image.h"
#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"

#ifdef COPROCESSOR
#include "../lib/hardware/convolution.h"
#else 
#include "../lib/software/convolution.h"
#endif

#include <stdint.h>
#include <stdio.h>

Image* get_gray_image(const char* path) {
  Image* img = malloc(sizeof(Image));
  img->data = stbi_load(path, &(img->width), &(img->height), &(img->channels), 1);
  return img;
}

static void** new_matrix(size_t size, int x, int y) {
  void** mtx = malloc(size * x);
  for (int i = 0; i < x; i++) {
    mtx[i] = malloc(size * y);
  }
  return mtx
}

uint8_t** img_to_mtx(Image img) {
  uint8_t** matrix = new_matrix(sizeof(uint8_t), img.height, img.width);
  for (int i = 0; i < img.height; i++) {
    for (int j = 0; j < img.width; j++) {
      matrix[i][j] = img.data[(i * img.height) + j];
    }
  }
  return matrix;
}

void free_image(Image* img) {
  if (!img) return;
  if (!(img->data)) return;
  free(img->data);
  img->data = NULL;
  free(img);
  img = NULL;
}

void save_image(Image img, const char* path) {
  stbi_write_jpg(path, img.width, img.height, img.channels, img.data, 100);
}

