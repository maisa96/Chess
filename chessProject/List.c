
#include "List.h"
#include "Header.h"

void freeList(chessPosList* list) {

	chessPosCell* saver, * curr;
	curr = list->head;

	while (curr != NULL) {
		saver = curr->next;
		free(curr);
		curr = saver;
	}
}
void insertDataToEndList(chessPosList* lst, chessPos data)
{
	chessPosCell* newTail;
	newTail = createNewListNode(data, NULL);
	insertNodeToEndList(lst, newTail);
}
chessPosCell* createNewListNode(chessPos data, chessPosCell* next)
{
	chessPosCell* res;
	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkAllocation(res);

	res->position[0] = data[0];
	res->position[1] = data[1];
	res->next = next;
	return res;
}
void insertNodeToEndList(chessPosList* lst, chessPosCell* tail)
{
	if (isEmptyList(lst) == true) {
		lst->head = lst->tail = tail;
	}
	else {
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}
void makeEmptyList(chessPosList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}
bool isEmptyList(chessPosList* list) {
	if (list->head == NULL)
		return true;
	else
		return false;
}
void insertDataToHeadList(chessPosList* lst, chessPos data)
{
	chessPosCell* newHead;
	newHead = createNewListNode(data, lst->head);
	insertNodeToHeadList(lst, newHead);
}
void insertNodeToHeadList(chessPosList* lst, chessPosCell* head)
{
	if (isEmptyList(lst) == true)
	{
		lst->head = lst->tail = head;
	}
	else
	{
		lst->head = head;
	}
}

