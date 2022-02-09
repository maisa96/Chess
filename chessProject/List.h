#ifndef LIST_FUNCTIONS
#define LIST_FUNCTIONS

#include "Header.h"

void insertDataToEndList(chessPosList* lst, chessPos data);
chessPosCell* createNewListNode(chessPos data, chessPosCell* next);
void insertNodeToEndList(chessPosList* lst, chessPosCell* tail);
bool isEmptyList(chessPosList* list);
void makeEmptyList(chessPosList* lst);
void freeList(chessPosList* list);
void insertNodeToHeadList(chessPosList* lst, chessPosCell* head);
void insertDataToHeadList(chessPosList* lst, chessPos data);


#endif // !LIST_FUNCTIONS
