
/*******************************************************
* Michael Saar
* 315240937
* 01
* Ex6
*******************************************************/

#include "ex6.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"

#define NAME_SIZE 50
#define THREE 3
#define EXIT_OPTION '0'
#define OPTION_ONE '1'
#define OPTION_TWO '2'
#define OPTION_THREE '3'
#define OPTION_FOUR '4'
#define OPTION_FIVE '5'
#define OPTION_SIX '6'
#define OPTION_SEVEN '7'


/***********************************************************************************
* Function name: printMenu
* Input: no input
* Output: no return
* Function Operation: the function prints a main menu
     *** this function is matching to the simplePrintLine functions ***
***********************************************************************************/
void printMenu(){
    printf("Please select an operation:\n\t0. Exit.\n\t1. Create family.\n\t2. Add family member.\n\t3. "
           "Print Family-Tree.\n\t4. Bidud.\n\t5. Superspreader.\n\t6. Vaccine.\n\t7. Print the menu.\n");
}

/***********************************************************************************
* Function name: printPrintersMenu
* Input: no input
* Output: no return
* Function Operation: the function prints a secondary menu
     *** this function is matching to the simplePrintLine functions ***
***********************************************************************************/
static void printPrintersMenu(){
    printf("Please select an operation:\n\t0. Return to the main menu.\n\t1. Print Trin-Ari family.\n"
           "\t2. Print Pre-order.\n\t3. Print Left-order.\n\t4. Print BFS.\n");
}

/***********************************************************************************
* Function name: quarantinePrintLine
* Input: no input
* Output: no return
* Function Operation: the function prints a question
     *** this function is matching to the simplePrintLine functions ***
***********************************************************************************/
static void quarantineQuestionPrint(){
    printf("Enter the ID of the suspected member\n");
}

/***********************************************************************************
* Function name: supersprederQuestionPrint
* Input: no input
* Output: no return
* Function Operation: the function prints a question
     *** this function is matching to the simplePrintLine functions ***
***********************************************************************************/
static void superspreaderQuestionPrint(){
    printf("Enter the ID of the suspected Superspreader\n");
}

/***********************************************************************************
* Function name: quarantinePrintLine
* Input: TrinAri* person
* Output: no return
* Function Operation: the function prints the name and id of person according to the format of quarantine situation
     *** this function is matching to the printLine functions ***
***********************************************************************************/
static void quarantinePrintLine(TrinAri* person){
    //if person == NULL don't print
    if (person == NULL){
        return;
    }
    printf("#StayHome! %s %d\n", person->name, person->id);
}

/***********************************************************************************
* Function name: standardPrint1
* Input: TrinAri* person
* Output: no return
* Function Operation: the function prints the name and id of person according to a standard1 format
     *** this function is matching to the printLine functions ***
***********************************************************************************/
static void standardPrint1(TrinAri* person){
    //if person == NULL don't print
    if (person == NULL){
        return;
    }
    printf("%s %d\n", person->name, person->id);
}

/***********************************************************************************
* Function name: standardPrint2
* Input: TrinAri* person
* Output: no return
* Function Operation: the function prints the name and id of person according to a standard2 format
     *** this function is matching to the printLine functions ***
***********************************************************************************/
static void standardPrint2(TrinAri* person){
    //if person == NULL don't print
    if (person == NULL){
        return;
    }
    printf("%s ID: %d\n", person->name, person->id);
}

/***********************************************************************************
* Function name: destroyPrint
* Input: TrinAri* person
* Output: no return
* Function Operation: the function prints the name and id of person according to a destroyPrint format
     *** this function is matching to the printLine functions ***
***********************************************************************************/
void destroyPrint(TrinAri* person){
    //if person == NULL don't print
    if (person == NULL){
        return;
    }
    printf("%s ID: %d Survived!\n", person->name, person->id);
}

/***********************************************************************************
* Function name: isFamilyExist
* Input: TriTreeFam* family
* Output: no return
* Function Operation: the function checks if a family has been created. If not it prints a message
***********************************************************************************/
static int isFamilyExist(TriTreeFam* family){
    //if family does not exist
    if (family->root == NULL){
        printf("Please create the family first\n");
        return 0;
    }
    return 1;
}

/***********************************************************************************
* Function name: destroyTree
* Input: TrinAri* root, printLine line
* Output: no return
* Function Operation: the function destroys all the sub trees of root
***********************************************************************************/
void destroyTree(TrinAri* root, printLine line){
    //stop condition - if root is null
    if (root == NULL){
        return;
    }
    //destroy the left, middle and right sub-trees
    destroyTree(root->left, line);
    destroyTree(root->middle, line);
    destroyTree(root->right, line);
    //print message
    line(root);
    //free root
    root->parent = NULL;
    free(root->name);
    free(root);
}

/***********************************************************************************
* Function name: allocationFailure
* Input: TrinAri* person, TriTreeFam* family
* Output: no return
* Function Operation: the function checks if ptr == NULL. If so, that means malloc has failed and in that case,
                      the function frees all allocated memory and exits the program
***********************************************************************************/
static void allocationFailure(void* ptr, TriTreeFam* family, printLine line){
    //check if ptr == NULL
    if (ptr == NULL){
        printf("Malloc Failed!");
        destroyTree(family->root, line);
        exit(1);
    }
}

/***********************************************************************************
* Function name: createPerson
* Input: char* name, int id
* Output: TrinAri* (pointer to new created TrinAri person)
* Function Operation: the function creates new TrinAri person and puts name in its name, and id in its id,
                      and initializes its descendants (left, middle and right) to NULL.
                      checks in the function that calls this function if malloc failed.
***********************************************************************************/
static TrinAri* createPerson(char* name, int id){
    //allocate memory to create new person
    TrinAri* newPerson = malloc(sizeof(TrinAri));
    //if malloc failed
    if (newPerson == NULL){
        return NULL;
    }
    //point newPerson->name to name and put id in newPerson->id
    newPerson->name = name;
    newPerson->id = id;
    //initialize all descendants and parent to NULL
    newPerson->left = NULL;
    newPerson->middle = NULL;
    newPerson->right = NULL;
    newPerson->parent = NULL;
    //print message and return newPerson
    printf("Hello %s, ID: %d\n", newPerson->name, newPerson->id);
    return newPerson;
}

/***********************************************************************************
* Function name: getInput
* Input: int* id, char* name
* Output: no return
* Function Operation: the function asks and gets input from the user and puts it in id and name
***********************************************************************************/
static void getInput(int* id, char* name){
    //get name input
    printf("enter name\n");
    scanf(" %[^\n]", name);
    //get id input
    printf("enter ID\n");
    scanf("%d", id);
}

/***********************************************************************************
* Function name: createFamily
* Input: TriTreeFam* family (pointer to TriTreeFam)
* Output: no return
* Function Operation: the function gets input from the user to get family's root name and id.
                      the function creates new TrinAri person and point root to it
***********************************************************************************/
static void createFamily(TriTreeFam* family){
    //if the family already exists
    if (family->root != NULL){
        printf("The family has already been created\n");
        return;
    }
    // create new string for person's name and int id for person's id
    char* name = malloc(NAME_SIZE * sizeof(char));
    //check if malloc failed
    allocationFailure(name, family, destroyPrint);
    int id;
    //get inputs for id and name
    getInput(&id, name);
    //create root person
    family->root = createPerson(name, id);
    //check if malloc failed
    allocationFailure(family->root, family, destroyPrint);
}

/***********************************************************************************
* Function name: findPerson
* Input: TrinAri* root, int id
* Output: TrinAri* (pointer to new created TrinAri person) if found the TrinAri person with id, else returns NULL
* Function Operation: the function runs recursively through all the descendants of root and compares their IDs
                      if it finds the TrinAri matching id, it returns a pointer to it. if hasn't found, it returns NULL
***********************************************************************************/
static TrinAri* findPerson(TrinAri* root, int id){
    //stop conditions: if root->id == id or if reached to NULL, return root
    if (root == NULL){
        return root;
    }
    if (root->id == id){
        return root;
    }
    //if personToFind is in the left tree of root, return it
    TrinAri* personToFind = findPerson(root->left, id);
    if (personToFind != NULL){
        return personToFind;
    }
    //if personToFind is in the middle tree of root, return it
    personToFind = findPerson(root->middle, id);
    if (personToFind != NULL){
        return personToFind;
    }
    //return the value of right: if the person is there, a pointer will be returned, else, null will be returned
    return findPerson(root->right, id);
}

/***********************************************************************************
* Function name: makeAppointment
* Input: TrinAri* person, TrinAri* descendant
* Output: no return
* Function Operation: the function adds an appointment between person and descendant, which means it checks which
                      of left, middle and right are NULL (in that order) and points them to descendant and the
                      descendant to its parent
***********************************************************************************/
static void makeAppointment(TrinAri* person, TrinAri* descendant){
    //if there is no left child, add descendant to person->left
    if (person->left == NULL){
        person->left = descendant;
        descendant->parent = person;
        return;
    }
    //if there is no middle child, add descendant to person->middle
    if (person->middle == NULL){
        person->middle = descendant;
        descendant->parent = person;
        return;
    }
    //if there is no right child, add descendant to person->right
    if (person->right == NULL){
        person->right = descendant;
        descendant->parent = person;
        return;
    }
}

/***********************************************************************************
* Function name: newPerson
* Input: TrinAri* root
* Output: pointer to new created TrinAri person
* Function Operation: the function asks for input of name and id and checks if there's already a TrinAri person with
                      that id. If so, the function asks for another input, until getting a valid id
                      if the id is valid, the function creates a new TrinAri person with id and name got from the user,
                      and returns a pointer to it
***********************************************************************************/
static TrinAri* newPerson (TrinAri* root){
    //create new string for name, int for id, and new TrinAri person to check if exists in family
    char* name = malloc(NAME_SIZE * sizeof(char));
    //if malloc failed
    if (name == NULL){
        return NULL;
    }
    int idToAdd;
    TrinAri* isExist;
    //while user inputs existing TrinAri person's id, ask for another name and id
    do{
        //get name and id from the user
        getInput(&idToAdd, name);
        //check if the id exists in tree
        isExist = findPerson(root, idToAdd);
        //print message
        if (isExist != NULL){
            printf("ID %d belongs to %s\n", idToAdd, isExist->name);
        }
    } while (isExist != NULL);
    //point personToAdd to new TrinAri person with name and idToAdd got from user
    TrinAri* personToAdd = createPerson(name, idToAdd);
    return personToAdd;
}

/***********************************************************************************
* Function name: addAppointment
* Input: TriTreeFam* family
* Output: no return
* Function Operation: the function asks for input of the id of the TrinAri person the user wants to add an appointment
                      with.
                      the function checks if that person exist's in family, and if it does, if there are available
                      appointments to be made with it. If so, the function asks for input of name and id, creates a new
                      TrinAri person, and makes an appointment between the first TrinAri person to new person
***********************************************************************************/
static void addAppointment(TriTreeFam* family){
    //check if family exists
    if (!isFamilyExist(family)){
        return;
    }
    //get id input from user
    int id;
    printf("Enter the ID of the person who wants to make an appointment?\n");
    scanf("%d", &id);
    //check if person exists in family. If not - print message and return
    TrinAri* person = findPerson(family->root, id);
    if (person == NULL){
        printf("There is no ID %d\n", id);
        return;
    }
    //if there's no room for new appointments for person
    if (person->left != NULL && person->middle != NULL && person->right != NULL){
        printf("%s ID: %d can't meet more than 3 members!\n", person->name, person->id);
        return;
    }
    //get a new person (personToAdd) to be appointed with person
    TrinAri* personToAdd = newPerson(family->root);
    //if malloc failed in newPerson function
    allocationFailure(personToAdd, family, destroyPrint);
    //add personToAdd to tree
    makeAppointment(person, personToAdd);
}

/***********************************************************************************
* Function name: printTree
* Input: printTreeKind operation, printLine line, TriTreeFam* family
* Output: no return
* Function Operation: the function operates a printTreeKind function on family root
***********************************************************************************/
static void printTree(printTreeKind operation, printLine line, TriTreeFam* family){
    //operate and check if operation failed (if malloc failed)
    if (!operation(family->root, line)){
        //if malloc has failed in operation, go through exit procedure
        allocationFailure(NULL, family, destroyPrint);
    }
}

/***********************************************************************************
* Function name: printPreOrder
* Input: TrinAri* root
* Output: returns 1, since it cannot be unsuccessful
* Function Operation: the function prints all the descendants of root and root itself pre-order:
                      root, left child, middle child, right child
     *** this function is matching to the printTreeKind functions ***
***********************************************************************************/
static int printPreOrder(TrinAri* root, printLine line){
    //stop condition: if root is NULL
    if (root == NULL){
        return 1;
    }
    //recursively print root, left, middle and right
    line(root);
    printPreOrder(root->left, line);
    printPreOrder(root->middle, line);
    printPreOrder(root->right, line);
    return 1;
}

/***********************************************************************************
* Function name: printLeftOrder
* Input: TrinAri root
* Output: returns 1, since it cannot be unsuccessful
* Function Operation: the function prints all the descendants of root and root itself left-order:
                      left child, root, middle child, right child
     *** this function is matching to the printTreeKind functions ***
***********************************************************************************/
static int printLeftOrder(TrinAri* root, printLine line){
    //stop condition: if root is NULL
    if (root == NULL){
        return 1;
    }
    //recursively print  left, root, middle and right
    printLeftOrder(root->left, line);
    line(root);
    printLeftOrder(root->middle, line);
    printLeftOrder(root->right, line);
    return 1;
}

/***********************************************************************************
* Function name: printBFS
* Input: TrinAri* root, printLine line (kind of printing to apply)
* Output: returns 1 if malloc of Queue does not fail, else, returns 0
* Function Operation: the function prints all the TrinAri people in BFS order, starting at a given root.
    * Algorithm:
    * create a pointer current to TrinAri
    * create a queue
    * point the front of queue to root
    * while queue is not empty:
        * print the front
        * add children of front to rear of queue (order: left, middle, right)
        * delete front
        * current is now front
    * destroy queue
     *** this function is matching to the printTreeKind functions ***
***********************************************************************************/
static int printBFS(TrinAri* root, printLine line){
    //if there is no root
    if (root == NULL){
        return 1;
    }
    //create new TrinAri pointer and point it to root
    TrinAri* current = root;
    //create new queue and check if creation was successful, if not, operate failure procedure
    Queue* q = createQueue();
    if (!enQueue(q, root)){
        return 0;
    }
    //while queue is not empty
    while (!isEmpty(q)){
        //point current to the front of queue and print it
        current = q->front->key;
        line(current);
        //if current->left exists
        if (current->left != NULL){
            //add to rear and check if failed
            if(!enQueue(q,current->left)){
                return 0;
            }
        }
        //if current->middle exists
        if (current->middle != NULL){
            //add to rear and check if failed
            if (!enQueue(q,current->middle)){
                return 0;
            }
        }
        //if current->right exists
        if (current->right != NULL){
            //add to rear and check if failed
            if(!enQueue(q,current->right)){
                return 0;
            }
        }
        //delete front of queue
        deQueue(q);
    }
    destroyQueue(q);
    return 1;
}

/***********************************************************************************
* Function name: smallQuarantinePrint
* Input: TrinAri* person
* Output: returns 1, since it cannot be unsuccessful
* Function Operation: the function prints the parent of person (if exists) and its descendants
     *** this function is matching to the printTreeKind functions ***
***********************************************************************************/
static int smallQuarantinePrint(TrinAri* person, printLine line){
    //if parent exist, print it
    line(person->parent);
    //print suspect
    line(person);
    //if parent->left exist, print it
    line(person->left);
    //if parent->middle exist, print it
    line(person->middle);
    //if parent->right exist, print it
    line(person->right);
    return 1;
}

/***********************************************************************************
* Function name: superSpreader
* Input: TrinAri* suspect
* Output: returns 1 if BFS printing was successful, else, 0
* Function Operation: the function prints the parent of person (if exists) and all of its descendants in BFS method
     *** this function is matching to the printTreeKind functions ***
***********************************************************************************/
static int superSpreader(TrinAri* suspect, printLine line){
    //print message for suspect's parent
    line(suspect->parent);
    //print message for all descendants of suspect in BFS method
    return (printBFS(suspect, line));
}

/***********************************************************************************
* Function name: quarantine
* Input: TriTreeFam* family, printTreeKind quarantinePrint, simplePrintLine line1, printLine line2
* Output: no return
* Function Operation: the function get an ID of a suspect and prints a quarantine message according to quarantinePrint
                      for example - printing the parent, the suspect, and its three descendants. Or printing all the
                      descendants of the suspect in BFS
***********************************************************************************/
static void quarantine(TriTreeFam* family, printTreeKind quarantinePrint, simplePrintLine line1, printLine line2){
    //get id from user
    if (!isFamilyExist(family)){
        return;
    }
    //print message and get input
    line1();
    int id;
    scanf("%d", &id);
    //find the suspect
    TrinAri* suspect = findPerson(family->root, id);
    //if id inserted doesn't match any TrinAri person, return
    if (suspect == NULL){
        printf("ID %d does not exist\n", id);
        return;
    }
    //print the quarantine and check if BFS print was successful
    if (!quarantinePrint(suspect, line2)){
        allocationFailure(NULL, family, destroyPrint);
    }
}

/***********************************************************************************
* Function name: vaccine
* Input: TriTreeFam* family
* Output: no return
* Function Operation: the function gets an ID of a person who got vaccinated and frees it and all it descendants
***********************************************************************************/
static void vaccine(TriTreeFam* family){
    //check if family exists
    if (!isFamilyExist(family)){
        return;
    }
    //get the id of the person who got vaccinated
    printf("Who got vaccinated (ID)?\n");
    int id;
    scanf("%d", &id);
    //find the person and check if it exists
    TrinAri* survivor = findPerson(family->root, id);
    if (survivor == NULL){
        printf("There is no ID %d\n", id);
        return;
    }
    //if the vaccinated person is the head of the family, destroy the whole tree and initialize family root to NULL
    if (survivor->parent == NULL){
        destroyTree(survivor, destroyPrint);
        //reset the TriTreeFam family root
        family->root = NULL;
        return;
    }
    //find which descendant of parent is survivor and change it to null before destroying all of survivor's sub - tree
    if (survivor->parent->left == survivor){
        survivor->parent->left = NULL;
    }
    if (survivor->parent->middle == survivor){
        survivor->parent->middle = NULL;
    }
    if (survivor->parent->right == survivor){
        survivor->parent->right = NULL;
    }
    //destroy sub-tree of survivor
    destroyTree(survivor, destroyPrint);
}

/***********************************************************************************
* Function name: printersMenuValCheck
* Input: char choice
* Output: 0 if choice is nivalid, 1 if valid
* Function Operation: the function gets a char and checks if it's equal to '0' to '4' and if so the input is valid
        *** this function matching the menuValidityCheck functions ***
***********************************************************************************/
static int printersMenuValCheck(char choice){
    //check if choice == i. (i starts at '0' ends at '4'
    for (char i = EXIT_OPTION; i <= OPTION_FOUR; i++) {
        if (choice == i){
            return 0;
        }
    }
    //the input is valid
    return 1;
}

/***********************************************************************************
* Function name: mainMenuValCheck
* Input: char choice
* Output: 0 if choice is nivalid, 1 if valid
* Function Operation: the function gets a char and checks if it's equal to '0' to '4' and if so the input is valid
        *** this function matching the menuValidityCheck functions ***
***********************************************************************************/
int mainMenuValCheck(char choice){
    //if choice != '0' the input is valid
    if (choice != EXIT_OPTION){
            return 1;
        }
    //if choice == '0' return 0
    return 0;
}

/***********************************************************************************
* Function name: menu
* Input: TriTreeFam* family, menuCases cases, menuValidityCheck validityCheck, simplePrintLine menuLine
* Output: no return
* Function Operation: the function asks for input from the user, checks if it's valid and runs switch-case operation
                      according to cases function
        *** this is a generic menu function ***
***********************************************************************************/
void menu(TriTreeFam* family, menuCases cases, menuValidityCheck validityCheck, simplePrintLine menuLine){
    //print message
    menuLine();
    char choice;
    //while input is valid to still operate the menu
    do {
        //get input and run cases
        scanf(" %c", &choice);
        cases(family, choice);
    }while (validityCheck(choice));
}

/***********************************************************************************
* Function name: printersMenuCases
* Input: TriTreeFam* family, char choice
* Output: no return
* Function Operation: the function runs other functions according to choice
        *** this function matching the menuCases functions ***
***********************************************************************************/
static void printersMenuCases(TriTreeFam* family, char choice){
    switch (choice) {
        case EXIT_OPTION:
            return;
        case OPTION_ONE:
            print2DUtil(family->root, THREE);
            return;
        case OPTION_TWO:
            printTree(printPreOrder,standardPrint2, family);
            return;
        case OPTION_THREE:
            printTree(printLeftOrder, standardPrint2, family);
            return;
        case OPTION_FOUR:
            printTree(printBFS, standardPrint1, family);
            return;
        //if choice is not a valid option
        default:
            printf("Error: unrecognized operation.\n");
            printPrintersMenu();
    }
}

/***********************************************************************************
* Function name: mainMenuCases
* Input: TriTreeFam* family, char choice
* Output: no return
* Function Operation: the function runs other functions according to choice
        *** this function matching the menuCases functions ***
***********************************************************************************/
void mainMenuCases(TriTreeFam* family, char choice){
    int isDefaultPrint = 1;
    switch (choice) {
        case EXIT_OPTION:
            return;
        case OPTION_ONE:
            createFamily(family);
            break;
        case OPTION_TWO:
            addAppointment(family);
            break;
        case OPTION_THREE:
            menu(family, printersMenuCases, printersMenuValCheck, printPrintersMenu);
            isDefaultPrint = 0;
            printMenu();
            break;
        case OPTION_FOUR:
            quarantine(family, smallQuarantinePrint, quarantineQuestionPrint ,quarantinePrintLine);
            break;
        case OPTION_FIVE:
            quarantine(family, superSpreader, superspreaderQuestionPrint ,quarantinePrintLine);
            break;
        case OPTION_SIX:
            vaccine(family);
            break;
        case OPTION_SEVEN:
            printMenu();
            isDefaultPrint = 0;
            break;
        default:
            printf("Error: unrecognized operation.\n");
            break;
    }
    if (isDefaultPrint){
        printf("Select the next operation (insert 7 for the entire menu):\n");
    }
}