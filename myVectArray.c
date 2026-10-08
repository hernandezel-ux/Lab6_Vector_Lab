/***************
* filename: myVectTop.c
* author: emanuel Hernandez
* date: 10/1/2026
* desc: vector calculator
* comp: gcc miniMat.c myVectArray.c myVectTop.c -o miniMat
****************/
    //this is an edit
    #include <stdio.h>
    #include "miniMat.h"

    struct Vector vectArray[10];


    void printVectors(void) {
        for (int i = 0; i < 10; i++) {
            if (vectArray[i].name[0] != '\0') { // Check if the vector is initialized
                printf("%s = %g %g %g\n", vectArray[i].name, vectArray[i].x, vectArray[i].y, vectArray[i].z);
            }
        }
    }

    void clearVectors(void) {
        for (int i = 0; i < 10; i++) {
            vectArray[i].name[0] = '\0'; // Reset the name to indicate the vector is cleared
            vectArray[i].x = 0.0f;
            vectArray[i].y = 0.0f;
            vectArray[i].z = 0.0f;
        }
        printf("All vectors cleared.\n");
    }
