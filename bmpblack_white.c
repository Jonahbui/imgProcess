#include "bmpfunc.h"

void BMP_black_white(BMP_Image* img)
{
    int i;
    for(i = 0; i < (img -> data_size); i+=3)
    {
        int avg_rgb = ((img -> data[i]) + (img -> data[i+1]) + (img -> data[i+2]))/3;
        if(avg_rgb > 127)
        {
            img -> data[i] = 255;
            img -> data[i+1] = 255;
            img -> data[i+2] = 255;
        }
        else
        {
            img -> data[i] = 0;
            img -> data[i+1] = 0;
            img -> data[i+2] = 0;
        }
    }
}
