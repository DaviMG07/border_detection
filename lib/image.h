#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
  uint8_t* data;
  int      width;
  int      height;
  uint8_t  channels;
} Image;

Image* get_gray_image(const char* path);
void   free_image(Image* image);
void save_image(const char* path, Image* image);

#endif
