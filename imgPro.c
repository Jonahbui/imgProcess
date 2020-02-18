#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "bmpfunc.h"
#include "bmpfile.h"

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KCYN "\x1B[36m"

int main(int argc, char** argv)
{
    printf("\n|******************************************|\n");
    printf("\n|==============| IMG PROCESS |=============|\n");
    printf("\n|******************************************|\n");
    //Use for menu input
    int userinput = -1;

    BMP_Image* image;
    if(argc < 2)    // If there is no image name, exit the program
    {
        printf("Not enough arguements. Expecting argv[1] to be filename at minimum. Exiting...\n");
        return 0;
    }
    else if(argc == 2) // If the only input is image name, just open the image
    {
        image = BMP_open(argv[1]);
    }
    else if(argc == 3)
    {
        //Image in another directory processing
    }
    
    // If the image could not be opened, exit the program
    if(image == NULL)
    {
        printf("File could not be found or opened...\n");
        return 0;
    }
    // Get user input
    printf("\nChoose modification: \n");
    printf("1. Keep only one color\n");
    printf("2. Invert colors\n");
    printf("3. Blur image\n");
    printf("4. Convert to black & white\n");
    printf("> ");
    scanf("%d", &userinput);
    
    //Use to check processing time
    clock_t begin = clock();

    // Apply selected image processing
    switch(userinput)
    {
        case 1: 
            printf("\nPick color: \n");
            printf("0. blue \n1. green \n2. red \n");
            printf("> ");
            int input1 = -1;
            scanf("%d", &input1);
            begin = clock();
            BMP_color(image, input1);
            break;
        case 2:
            begin = clock();
            BMP_invert(image);
            break;
        case 3:
            printf("\nBlur radius (positive ints): \n");
            printf("> ");
            int input_alt = 3;
            scanf("%d", &input_alt);
            begin = clock();
            BMP_blur(image, input_alt);
            break;
        case 4:
            BMP_black_white(image);
            break;
        default:
            break;
    }
    
    //Calculate the time spent processing the image to display to user
    clock_t end = clock();
    double seconds = (double)(end - begin)/CLOCKS_PER_SEC;
    int minutes = ((int)seconds)/60;
    seconds-= minutes*60;

    //Give the user to save or override image
    printf("\nProcess time: %dmn %0.3fs\nSave as new file? [y/n]:\n", minutes, seconds);
    
    // Use to get rid of trailing white space
    char saveoption = getchar();
    while(isalpha(saveoption) == 0)
    {
        saveoption = getchar();
    }

    int result;    // Use to check if the image was successfully saved or not. Inform the user if not
    char modifiedName[400]; // Use to store new name of file
    if(saveoption == 'y')
    {
        // Store the result in a new bmp file
        char* token = strtok(argv[1], "/.");    //Get the filename without extension
        char* label = "_modified.bmp";          //Use to add to end of new file name
        strcpy(modifiedName, token);
        strcat(modifiedName, label);
        result = BMP_save(image, modifiedName);
    }
    else
    {
        result = BMP_save(image, argv[1]);      //Save the image to the original file
    }
    
    //Check if file was succesfully saved
    if(result != 1)
    {
        printf("\nFailed to save file...\n");
    }
    else
    {
        printf("%s", KGRN);
        if(saveoption == 'y')
            printf("\nFile saved as %s\n\n", modifiedName);
        else
            printf("\nFile saved as %s\n\n", argv[1]);
    }
    printf("%s", KNRM);
    return 0;
}
