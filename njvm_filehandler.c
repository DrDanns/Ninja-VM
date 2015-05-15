/*
 * File:	njvm_filehandler.c
 * Author:	Stanislav Hannes, 5000458
 * Date:	12.11.2014
 * Describtion:	extends functions for open, read, check and close the file
 */
#include <stdio.h>
#include <stdlib.h>

#include "njvm_filehandler.h"

FILE* openFile(char *path)
{
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        fputs("Error: cannot open code file.\n", stderr);
        exit(EXIT_FAILURE);
    }
    return file;

}

unsigned int* readFile(FILE* file)
{
    unsigned int *buffer;
    int instructionSize=0;
    int sdaSize=0;
    int i;

    buffer = (unsigned int*) malloc (16);
    if (buffer==NULL) {
        fputs("Error: cannot allocate memory for the filecheck.\n", stderr);
        exit(EXIT_FAILURE);
    }

/*check the header*/
    for (i=0; i < 4; i++) {

        fread(buffer, sizeof(int),1,file);

        if (i==0){
            if(*buffer != 1178749518){ /*NJVM in int*/
                fputs("Error: File has not Ninja Binary File Format.\n", stderr);
		        exit(EXIT_FAILURE);
	        }
        }

        else if (i==1){
            if (*buffer != VERSION){
                fputs("Error: File has wrong Version Number.\n", stderr);
		        exit(EXIT_FAILURE);
	        }
	    }    

        else if (i==2)
            instructionSize=*buffer;

        else if (i==3)
            sdaSize=*buffer;

    }

    free(buffer);

    if (sdaSize != 0)  allocateSDA(sdaSize);

    /*allocate space and fill it with the programm*/
    buffer = (unsigned int*) malloc (instructionSize * sizeof(int));
    fread(buffer, sizeof(int),instructionSize,file);
    fclose(file);
    return buffer;


}


