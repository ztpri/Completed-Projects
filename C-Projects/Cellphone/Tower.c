//
// ECE 209 602
// Zachary Price
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PhoneTower.h"

struct tower{
    char identifier[13];
    Phone phone;
    int xCoord;
    int yCoord;
};

// allocate a return a new Tower with the specified ID and location
Tower createTower(const char *id, int x, int y){
    Tower tow;

    tow = malloc(sizeof(Tower));

    if((x < 0) || (y < 0)) return NULL;
    else{
        strcpy(tow->identifier, id);
        tow->xCoord = x;
        tow->yCoord = y;
    }

    return tow;
}

// given a Tower, return a pointer to its ID string
const char * towerID(Tower t){
    char* ID = t->identifier;
    return ID;
}

// given a Tower, return its location using the pointers provided
void towerLocation(Tower t, int *xaddr, int *yaddr){
    *xaddr = t->xCoord;
    *yaddr = t->yCoord;

    return;
}

// create a connection between two Towers
// t2 will be added to t1's neighbor list
// t1 will be added to t2's neighbor list
void addConnection(Tower t1, Tower t2){
    return;
}

// given a Tower, return a list of Towers connected to that Tower
// list will not be altered or deallocated by caller
TowerNode towerNeighbors(Tower t){
    TowerNode tow;

    return tow;
}

// inform Tower t that Phone p is now connected
void addPhone(Tower t, Phone p){
    return;
}
// inform Tower t that Phone o is no longer connected
void removePhone(Tower t, Phone p){
    return;
}

// given a Tower, return a list of Phones connected to that Tower
// list will not be altered or deallocated by caller
PhoneNode towerPhones(Tower t){
    PhoneNode p;

    return p;
}


// return the null Tower, allocate if necessary
Tower nullTower(){
    Tower tow;

    return tow;
}

// return the Tower with matching ID (or NULL if not found)
Tower findTower(const char *id){
    Tower tow;

    return tow;
}

// return a list of all towers, in alphabetical order
// list will not be altered or deallocated by caller
TowerNode allTowers(){
    TowerNode tow;

    return tow;
}

// routes a call between two phones, start to end
// returns a list of Towers required to connect the call, in routing order
// list may be altered or deallocated by caller
TowerNode routeCall(Phone start, Phone end){
    TowerNode tow;

    return tow;
}