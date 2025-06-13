#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
  uint8_t* data;
  int      width;
  int      height;
  uint8_t  channels;
} Image;

Image* get_gray_image(const char* path);
uint8_t** img_to_mtx(Image img);
void   free_image(Image* image);
void   save_image(const char* path, Image* image);

// filters:
Image* img_sobel(Image* original);
Image* img_sobel_expanded(Image* original);
Image* img_prewitt(Image* original);
Image* img_roberts(Image* original);
Image* img_laplace(Image* original);

#endif
