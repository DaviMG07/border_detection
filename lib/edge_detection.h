#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H

#include <stdint.h>

uint8_t** sobel(uint8_t** image, int width, int height);
uint8_t** sobel_expanded(uint8_t** image, int width, int height);
uint8_t** prewitt(uint8_t** image, int width, int height);
uint8_t** roberts(uint8_t** image, int width, int height);
uint8_t** laplace(uint8_t** image, intwidth, int height);

#endif
