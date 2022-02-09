#ifndef MAIN
#define MAIN 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROWSIZE 5
#define COLSIZE 5
#define BOARDSIZE 25
#define ROW 0
#define COL 1
#define SUMBITSINPOS 3
#define SUMBITSINBYTE 8
#define ERROR -1
#define NOTVALID 1
#define MIN_COL '1'
#define MIN_ROW 'A'
#define MAX_COL '5'
#define MAX_ROW 'E'
#define COVER_ALL 2
#define NOT_COVER_ALL 3


#define ISLEGALCHOICECOL(x) ((x)=='1' || (x)=='2' || (x)=='3' || (x)=='4' || (x)=='5' || (x)=='6' ) ? true : false

typedef struct _treeNode treeNode;
typedef struct _treeNodeListCell treeNodeListCell;
typedef unsigned char BYTE; 
typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;
typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;
typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;
typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions;
} treeNode;
typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;
typedef struct _pathTree {
	treeNode* root;
} pathTree;


void checkAllocation(void* pointer);
void checkOpenFile(void* pointer);
void freePosArr(chessPosArray*** arr);
void freeTree(treeNode* root);
int showMenu();
void scanPossition(char* row, char* col);
char* scanFileNameFromUser();
void printTypeOfPathToUser(int typeOfPath, chessPosList* list);
void didNotEnterAPossition();
bool isLegalCol(char col);
bool isLegalRow(char row);

#endif // ! MAIN

