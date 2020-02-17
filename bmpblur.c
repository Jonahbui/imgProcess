// bmpblur.c
#include "bmpfunc.h"
#include <stdint.h>

// Use to translate the coordinates of an image to an index and return the value at that index
// Takes in the coordinates of the pixel, the image with the pixel, and pixel color
// Returns according rgb value at index, 0 if index out of bounds
uint32_t getPxl(uint32_t x, uint32_t y, BMP_Image* img, char clr)
{
    uint32_t index = 3*(y*(img -> width)+x);
    if(index < (img -> data_size))
    { 
        switch(clr)
        {
            case 'r':
                index += 2;
                break;
            case 'g':
                index += 1;
                break;
            case 'b':
                index = index;
                break;
            default:
                index = 0;
                break;
        }
        return (img -> data[index]);
    }
    // If the index is not within the image, return the value to be zero
    return 0;    
}

void BMP_blur(BMP_Image* img, int radius)
{
    uint32_t height = img -> height;
    uint32_t width = img -> width;

    int x, y;

    // Use to loop through every pixel
    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            int r = 0;
            int g = 0;
            int b = 0;

            int i, j;
            
            // Use these for loops to calculate the average rgb value within the radius
            for(i = y-radius; i <= y+radius; i++)// y-coordinate of pixel
            {
                for(j = x-radius; j <= x+radius; j++)// x-coordinate of pixel
                {
                    if(i >= 0 && j >= 0)
                    {
                        r+= getPxl(j, i, img, 'r');
                        g+= getPxl(j, i, img, 'g');
                        b+= getPxl(j, i, img, 'b');
                    }
                }
            }
            
            // Determine the total number of pixels used to calculate the new pixel color value
            // This will be used to average out the rgb values for a pixel to get a value within 0-255
            int dimension = (1+radius*2)*(1+radius*2);

            // Sets the new blurred pixel in the image
            img -> data[3*(y*(img -> width)+x)  ] = b/dimension;
            img -> data[3*(y*(img -> width)+x)+1] = g/dimension;
            img -> data[3*(y*(img -> width)+x)+2] = r/dimension;
        }
    }
}

