// bmpblur.c
#include "bmpfunc.h"
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct blur_args
{
	BMP_Image* img;
	int rad;
	int row;
}Blur_Args;

// Use to translate the coordinates of an image to an index and return the value at that index
// Takes in the coordinates of the pixel, the image with the pixel, and pixel color
// Returns according rgb value at index, 0 if index out of bounds
uint32_t GetPxl(uint32_t x, uint32_t y, BMP_Image* img, char clr)
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

//Use to blur an image faster by assigning each row to a thread
void* blur_threads(void* arguments)
{
    //Recast the args back into struct to read
	Blur_Args* args = (Blur_Args*)arguments;
	
	int x;
	int y = args -> row;
	int radius = args -> rad;
	uint32_t width = args -> img -> width;
	for(x = 0; x < width; x++)
	{
		//Accumulate rgb values to find the new pixel rgb value later
        int r = 0;
		int g = 0;
		int b = 0;

		int i, j;
		
		// Use these for-loops to calculate the average rgb value within a radius
		for(i = y-radius; i <= y+radius; i++)// y-coordinate of pixel
		{
			for(j = x-radius; j <= x+radius; j++)// x-coordinate of pixel
			{
				if(i >= 0 && j >= 0)
				{
					r+= GetPxl(j, i, (args -> img), 'r');
					g+= GetPxl(j, i, (args -> img), 'g');
					b+= GetPxl(j, i, (args -> img), 'b');
				}
			}
		}
		
		// Determine the total number of pixels used to calculate the new pixel color value
		// This will be used to average out the rgb values for a pixel to get a value within 0-255
		int dimension = (1+radius*2)*(1+radius*2);

		// Sets the new blurred pixel in the image
		args -> img -> data[3*(y*width+x)  ] = b/dimension;
		args -> img -> data[3*(y*width+x)+1] = g/dimension;
		args -> img -> data[3*(y*width+x)+2] = r/dimension;
	}	
	return NULL;
}

void BMP_blur(BMP_Image* img, int radius)
{
    uint32_t height = img -> height;

    int y;
	
	//Use to store arguments to pass onto threads
	Blur_Args args[height];
	
	pthread_t threadArr[height];
	
    // Use to loop through each row of pixels and assign them to threads
    for(y = 0; y < height; y++)
    {
		args[y].img = img;
		args[y].rad = radius;
		args[y].row = y;
		
		if(pthread_create(&threadArr[y], NULL, blur_threads, (void*)&args[y]))
		{
			perror("Error creating thread: ");
			exit(EXIT_FAILURE);
		}
		if(pthread_join(threadArr[y], NULL)) 
		{
			perror("Problem with pthread_join: ");
		}
    }
}

