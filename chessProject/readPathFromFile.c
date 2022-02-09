#include "Header.h"
#include "readPathFromFile.h"
#include "display.h"
#include "question3.h"
#include "validMoves.h"
#include "findAllBoard.h"


int checkAndDisplayPathFromFile(char* file_name) {

	FILE* fp;
	chessPosList* allBoardPath, list;
	chessPosCell* curr;
	bool isValid;
	pathTree path;
	int valueToReturn, countNode = 0;

	fp = fopen(file_name, "rb");

	/*file does not exist*/
	if (fp == NULL)
		return ERROR;

	/*file is exist - scan the list and close file*/
	list = scanPathFromFile(fp);
	fclose(fp);

	isValid = IsValidPath(list);

	if (isValid) {

		display(&list);

		curr = list.head;

		while (curr != NULL) {
			countNode++;
			curr = curr->next;
		}

		if (countNode == BOARDSIZE)
			valueToReturn = COVER_ALL;
		else
			valueToReturn = NOT_COVER_ALL;
	}

	else {
		valueToReturn = NOTVALID;
	}

	freeList(&list);
	return valueToReturn;
}
chessPosList scanPathFromFile(FILE* fp) {
	chessPosList list;
	chessPos pos;
	short int numOfPos;
	int indexPos = 0, placeInByte = SUMBITSINBYTE, sumPosScaned = 0, rem;
	BYTE byte, mask, maskHelp, * TenMasks = maskArr();

	makeEmptyList(&list);

	fread(&numOfPos, sizeof(short int), 1, fp);
	fread(&byte, sizeof(BYTE), 1, fp);

	while (sumPosScaned < numOfPos) {

		if (indexPos == 2) {
			insertDataToEndList(&list, pos);
			indexPos = ROW;
			sumPosScaned++;
		}

		if (placeInByte > 2) {
			mask = byte & TenMasks[SUMBITSINBYTE - placeInByte];
			placeInByte = placeInByte - 3;

			pos[indexPos] = convertFromMaskToChar(placeInByte, mask, indexPos);
			indexPos++;

			if (placeInByte == 0) {
				placeInByte = SUMBITSINBYTE;
				fread(&byte, sizeof(BYTE), 1, fp);
			}
		}

		else {/*placeInByte<=2 or 1*/
			rem = SUMBITSINPOS - placeInByte;
			byte = byte << (SUMBITSINBYTE - placeInByte);
			byte = byte >> (SUMBITSINBYTE - SUMBITSINPOS);

			mask = byte;

			placeInByte = SUMBITSINBYTE;
			fread(&byte, sizeof(BYTE), 1, fp);

			maskHelp = 0;
			maskHelp = maskHelp | byte;
			maskHelp = maskHelp >> (SUMBITSINBYTE - rem);
			placeInByte = placeInByte - rem;

			mask = mask | maskHelp;

			pos[indexPos] = convertFromMaskToChar(NONE, mask, indexPos);
			indexPos++;
		}
	}

	free(TenMasks);
	return list;
}
BYTE* maskArr() {
	BYTE* maskArr = (BYTE*)malloc(6 * sizeof(BYTE));
	checkAllocation(maskArr);

	maskArr[0] = 7 << 5; //1110 0000
	maskArr[1] = 7 << 4; //0111 0000
	maskArr[2] = 7 << 3; //0011 1000
	maskArr[3] = 7 << 2; //0001 1100
	maskArr[4] = 7 << 1; //0000 1110
	maskArr[5] = 7;      //0000 0111

	return maskArr;
}
char convertFromMaskToChar(int StartBit, BYTE mask, int rowOrCol) {
	char ch = '\0';

	mask = mask >> StartBit;

	switch (rowOrCol)
	{
	case ROW:
		ch = (int)mask + 'A';
		break;
	case COL:
		ch = (int)mask + '1';
		break;
	}

	return ch;
}
bool IsValidPath(chessPosList list) {
	chessPosCell* curr;
	chessPos pos;
	chessPosArray* validPos=NULL;
	int i, size;
	bool isLegal = true, found = false;

	curr = list.head;

	while (curr->next != NULL && isLegal) {
		pos[0] = (curr->position)[0];
		pos[1] = (curr->position)[1];

		validPos = createPosArray(pos);
		size = validPos->size;

		pos[0] = (curr->next->position)[0];
		pos[1] = (curr->next->position)[1];

		/*check if the next position is in the pos array*/
		for (i = 0; i < size; i++) {
			if (((validPos->positions[i])[0] == pos[0]) && ((validPos->positions[i])[1] == pos[1])) {
				found = true;
				break;
			}
		}
		
		if (found != true)
			isLegal = false;

		if (validPos != NULL) {
			free(validPos->positions);
			free(validPos);
		}
		curr = curr->next;
	}
	
	return isLegal;
}

