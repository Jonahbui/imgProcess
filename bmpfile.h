// bmpfile.h
#ifndef _BMPFILE_H_
#define _BMPFILE_H_

#include "bmpimage.h"

/* Open BMP image given filename
 * Returns pointer to BMP image (success) or NULL (failure)
 */
BMP_Image *BMP_open(const char* filename);

/* Save a BMP image to the given filename
 * Returns 1 (success) or 0 (failure)
 */
int BMP_save(const BMP_Image* image, const char* filename);

// Release the memory of a BMP image structure
void BMP_destroy(BMP_Image* image);
#endif

