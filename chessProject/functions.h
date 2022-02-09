#ifndef MAIN_FUNCTIONS
#define MAIN_FUNCTIONS

#include "Header.h"

int showMenu();
void scanPossition(char* row, char* col);
void printTypeOfPathToUser(int typeOfPath, chessPosList* list);
char* scanFileNameFromUser();
void didNotEnterAPossition();
void thereIsNotAPath();

#endif // !MAIN_FUNCTIONS
