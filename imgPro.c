#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "bmpfunc.h"
#include "bmpfile.h"

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KCYN "\x1B[36m"

int main(int argc, char** argv)
{
    printf("%s", KYEL);
    printf("\n/////*****IMG PROCESS******/////\n");
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
    scanf("%d", &userinput);
    
    // Apply selected image processing
    switch(userinput)
    {
        case 1: 
            printf("\nPick color: \n");
            printf("0. blue \n1. green \n2. red \n");
            int input1 = -1;
            scanf("%d", &input1);
            BMP_color(image, input1);
            break;
        case 2:
            BMP_invert(image);
            break;
    }
    
    //Give the user to save or override image
    printf("\nSave as new file? [y/n]:\n");
    char saveoption = getchar();
    while(isalpha(saveoption) == 0) //Use to get rid of trailing whitespace
    {
        saveoption = getchar();
    }
    int result;
    char modifiedName[400];
    if(saveoption == 'y')
    {
        // Store the result in a new bmp file
        char* token = strtok(argv[1], "/.");
        char* label = "_modified.bmp";
        strcpy(modifiedName, token);
        strcat(modifiedName, label);
        result = BMP_save(image, modifiedName);
    }
    else
    {
        result = BMP_save(image, argv[1]);
    }
    
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
    return 0;
}
