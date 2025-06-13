#include <stdio.h>
#include "../lib/image.h"

int main() {
  const char* path = "media/tilapia.jpeg";
  Image* img       = get_gray_image(path);
  for (int i = 0; i < img->width * img->height; i += 3) {
    img->data[i] = 255;
  }
  save_image("media/tilapia_result.jpg");
  free_image(img);
  return 0;
}
