#ifndef _READFROMFILE
#define _READFROMFILE
#include "Header.h"
#include "List.h"

#define NONE 0

int checkAndDisplayPathFromFile(char* file_name);
chessPosList scanPathFromFile(FILE* fp);
BYTE* maskArr();
char convertFromMaskToChar(int StartBit, BYTE mask, int rowOrCol);
bool IsValidPath(chessPosList list);


#endif // !_READfROMfILE
