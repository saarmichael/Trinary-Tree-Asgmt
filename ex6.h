
/*******************************************************
* Michael Saar
* 315240937
* 01
* Ex6
*******************************************************/

#ifndef _EX6_H_
#define _EX6_H_

struct TrinAri {
	int id;
	char * name;
	struct TrinAri *left;
	struct TrinAri *middle;
	struct TrinAri *right;
	struct TrinAri *parent;
};

struct TriTreeFam {
    struct TrinAri *root;
};

typedef struct TrinAri TrinAri;
typedef struct TriTreeFam TriTreeFam;

typedef void (*simplePrintLine)();
typedef void (*printLine)(TrinAri*);
typedef int(*printTreeKind)(TrinAri*, printLine);
typedef void (*menuCases)(TriTreeFam*, char);
typedef int (*menuValidityCheck)(char);

int mainMenuValCheck(char choice);
void menu(TriTreeFam* family, menuCases cases, menuValidityCheck validityCheck, simplePrintLine menuLine);
void mainMenuCases(TriTreeFam* family, char choice);
void printMenu();
void destroyTree(TrinAri* root, printLine line);
void destroyPrint(TrinAri* person);

#endif