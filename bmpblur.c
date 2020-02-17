// bmpblur.c
#include "bmpfunc.h"

// Use to translate the coordinates of an image to an index and return the value at that index
// Takes in a the coordinates of the pixel, the image with the pixel, and pixel color
// Returns according rgb value at index, -1 if index out of bounds
int getPxl(int x, int y, BMP_Image* img, char clr)
{
    int index;
	switch(clr)
    {
        case 'r':
            index = 3*(y*(img -> width)+x) + 2;
            break;
        case 'g':
            index = 3*(y*(img -> width)+x) + 1;
            break;
        case 'b':
            index = 3*(y*(img -> width)+x);
            break;
		default:
			index = -1;
			break;
    }
	
	// If the index is not within the image, return the value to be zero
    if(index >= 0 && index < (img -> data_size))
		return (img -> data[index]);     
	return 0;
}

void BMP_blur(BMP_Image* img)
{
    int height = img -> height;
    int width = img -> width;

    int x, y;

    // Go through the image and calculate the average rgb value for each pixel based of the pixlels around it (3x3)
    for(y = 0; y < height; y++)
   
        for(x = 0; x < width; x++)
        {
            int r1 = getPxl(x-1, y-1, img, 'r');            
            int g1 = getPxl(x-1, y-1, img, 'g');            
            int b1 = getPxl(x-1, y-1, img, 'b');

            int r2 = getPxl(x, y-1, img, 'r');            
            int g2 = getPxl(x, y-1, img, 'g');            
            int b2 = getPxl(x, y-1, img, 'b');

            int r3 = getPxl(x+1, y-1, img, 'r');            
            int g3 = getPxl(x+1, y-1, img, 'g');            
            int b3 = getPxl(x+1, y-1, img, 'b');
			
            int r4 = getPxl(x-1, y, img, 'r');            
            int g4 = getPxl(x-1, y, img, 'g');            
            int b4 = getPxl(x-1, y, img, 'b');

            int r5 = getPxl(x, y, img, 'r');            
            int g5 = getPxl(x, y, img, 'g');            
            int b5 = getPxl(x, y, img, 'b');
			
            int r6 = getPxl(x+1, y, img, 'r');            
            int g6 = getPxl(x+1, y, img, 'g');            
            int b6 = getPxl(x+1, y, img, 'b');
			
            int r7 = getPxl(x-1, y+1, img, 'r');            
            int g7 = getPxl(x-1, y+1, img, 'g');            
            int b7 = getPxl(x-1, y+1, img, 'b');
			
            int r8 = getPxl(x, y+1, img, 'r');            
            int g8 = getPxl(x, y+1, img, 'g');            
            int b8 = getPxl(x, y+1, img, 'b');
			
            int r9 = getPxl(x+1, y+1, img, 'r');            
            int g9 = getPxl(x+1, y+1, img, 'g');            
            int b9 = getPxl(x+1, y+1, img, 'b');
			
			img -> data[3*(y*(img -> width)+x)  ] = (b1 + b2 + b3 + b4 + b5 + b6 +b7 + b8 + b9)/9;
			img -> data[3*(y*(img -> width)+x)+1] = (g1 + g2 + g3 + g4 + g5 + g6 +g7 + g8 + g9)/9;
			img -> data[3*(y*(img -> width)+x)+2] = (r1 + r2 + r3 + r4 + r5 + r6 +r7 + r8 + r9)/9;
        }
    }
}

