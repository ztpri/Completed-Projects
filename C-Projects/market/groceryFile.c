//
//
// name: Zachary Price
// section: 602

#include <stdio.h>
#include <stdbool.h>
#include "groceryFile.h"

bool readFile(const char *filename, FileInfo *var){
    FILE *file;
    bool state;
    char line[100];
    int debug;

    // ~~~~~~~~~~ remember to change files when done debugging!!!!!!!!!!!!!!!!!!!!!!!!!

    if((int) (file = fopen(filename, "r")) != EOF){     // if file is found
        state = 1;      // set file state to exist

        fgets(line, 100, file);     // read and move past first line before loop

        (*var).purchases = 0;

        while(fgets(line, 100, file) != NULL){
            (*var).purchases += 1;      // increase purchase count at each line
        }
    }
    else state = 0;     // if file is not found

    debug = (*var).purchases;

    debug = debug;

    return state;
}