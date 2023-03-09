//
// ECE 209 602
// Zachary Price
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PhoneTower.h"

struct phone{
    char identifier[13];
    int xCoord;
    int yCoord;
    Tower tower;
};

// allocate and return a new Phone with specified ID and location
Phone createPhone(const char *id, int x, int y){
    struct phone* cell;

    cell = malloc(sizeof(Phone));

    if((x < 0) || (y < 0)) return NULL;
    else{
        strcpy(cell->identifier, id);
        cell->xCoord = x;
        cell->yCoord = y;
    }

    return cell;
}

// given a Phone, return a pointer to its ID string
const char * phoneID(Phone p){
    char* ID;

    strcpy(ID, p->identifier);

    return ID;
}

// given a Phone, return its x and y location using the provided pointers
void phoneLocation(Phone p, int *xaddr, int *yaddr){
    return;
}

// given a Phone, return the Tower to which it is currently connected
Tower phoneTower(Phone p){
    Tower cell;

    return cell;
}

// find a Phone by its ID string
Phone findPhone(const char *id){
    Phone phone;

    return phone;
}

// move existing phone to a new location
void movePhone(Phone p, int newx, int newy){
    return;
}