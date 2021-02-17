
/*******************************************************
* Michael Saar
* 315240937
* 01
* Ex6
*******************************************************/

#include <stdio.h>
#include "ex6.h"
#include "Utils.h"

int main() {
    //create new family and initialize it
    TriTreeFam family;
    family.root = NULL;
    //run the main menu
    menu(&family, mainMenuCases,mainMenuValCheck, printMenu);
    destroyTree(family.root, destroyPrint);
    return 0;
}
