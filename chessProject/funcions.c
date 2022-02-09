
#include "Header.h"
#include <stdlib.h>
#include "validMoves.h"
#include "display.h"
#include "functions.h"

/*menu*/

int showMenu() {

	char choice, ch;
	bool finish = false;

	while (!finish) {

		printf("1. Enter a knight's starting position\n");
		printf("2. Create all possible knight paths\n");
		printf("3. Find a knight path covering all board\n");
		printf("4. Save knight path covering all board to file\n");
		printf("5. Load and display path from file\n");
		printf("6. Exit\n\n");

		scanf(" %c%c", &choice, &ch);

		if (ISLEGALCHOICECOL(choice)) {
			if (ch == '\n')
				finish = true;

			else {
				while (ch != '\n') {
					scanf("%c", &ch);
				}
				printf("invalid choice ! please enter again\n");
			}
		}
		else {
			while (ch != '\n') {
				scanf("%c", &ch);
			}
			printf("invalid choice ! please enter again\n");
		}
	}

	return choice;
}
bool checkValid() {

}
void scanPossition(char *row, char *col) {
	
	char posCol, posRow, ch;
	bool valid = false;

	printf("Please enter a possition: a row and then a col!\n");

	while (!valid)
	{
		scanf(" %c %c%c", &posRow, &posCol, &ch);

		if (isLegalRow (posRow)) {
			if (isLegalCol(posCol))
				if (ch == '\n')
					valid = true;
		}

		if (!valid) {
			while (ch != '\n') {
				scanf("%c", &ch);
			}
			printf("Invalid input!! Please enter the possition again\n\n");
		}
	}

	*row = posRow;
	*col = posCol;

	return;
}
char* scanFileNameFromUser() {

	char* Name;
	int logSize = 0, phySize = 1;
	char ch;

	Name = (char*)malloc(sizeof(char));
	checkAllocation(Name);

	scanf(" %c", &ch);

	while (ch != '\n') {

		if (phySize == logSize) {
			phySize *= 2;

			Name = (char*)realloc(Name, sizeof(char) * phySize);
			checkAllocation(Name);
		}

		Name[logSize] = ch;
		logSize++;

		scanf("%c", &ch);
	}

	if (logSize == phySize) {
		Name = (char*)realloc(Name, sizeof(char) * (logSize + 1));
		checkAllocation(Name);

		logSize++;
		phySize++;

		Name[logSize - 1] = '\0';
	}

	else /*if there is enough place insert '\0'*/
	{
		Name[logSize] = '\0';

		/*if there are more place than char*/
		if (logSize != phySize) {
			Name = (char*)realloc(Name, sizeof(char) * (logSize + 1));
			checkAllocation(Name);
		}
	}

	return Name;
}
void printTypeOfPathToUser(int typeOfPath, chessPosList* list) {
	switch (typeOfPath)
	{
	case 3:
		printf("The path does not cover all board\n");
		break;
	case 2:
		printf("The path covers all board\n");
		break;
	case 1:
		printf("The path is not valid!!\n");
		break;
	case -1:
		printf("The file is not exist!!\n");
		break;
	}
}
void didNotEnterAPossition() {
	printf("Position has not been entered!\n\n");
}
void thereIsNotAPath() {
	printf("There is no path that cover all board!\n");
}
void freeTree(treeNode* root) {

	treeNodeListCell* curr = root->next_possible_positions, * saver;
	if (root == NULL)
		return;

	while (curr != NULL) {
		saver = curr->next;
		freeTree(curr->node);
		free(curr);
		curr = saver;
	}

	free(root);
	return;
}
bool isLegalCol(char col) {
	if (col >= MIN_COL && col <= MAX_COL)
		return true;
	else
		return false;
}
bool isLegalRow(char row) {
	if (row >= MIN_ROW && row <= MAX_ROW)
		return true;
	else
		return false;
}

