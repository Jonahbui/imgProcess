// bmpfunc.h
#ifndef _BMPFUNC_H_
#define _BMPFUNC_H_

#include "bmpimage.h"
/* Keep only one color,
 * clr = 2, keep red
 * clr = 1, keep green
 * clr = 0, keep blue
*/

void BMP_color(BMP_Image* image, int clr);

//Invert all of the image data in a BMP image
// (value = 255 - value)
void BMP_invert(BMP_Image* image);

// Calculate vertical edges using the given threshold value
void BMP_edge(BMP_Image* image, int thrshd);

// Convert an RGB image to a gray-level image
void BMP_gray(BMP_Image* image);

// Calculate the histogram of each color
void BMP_histogram(BMP_Image *image);

// Make a checkerboard
void BMP_checker(BMP_Image *image);

// Mix the colors
void BMP_mix(BMP_Image* image);

// Equalize by making the darkest to and brightest to 255
void BMP_equalize(BMP_Image* image);

// Blur an image (by average)
void BMP_blur(BMP_Image* image, int radius);

//Turns an image into black or white only
void BMP_black_white(BMP_Image* image);
#endif
