#include "display.h"
#include "Header.h"
#include "validMoves.h"
#include "question3.h"
#include "readPathFromFile.h"
#include "functions.h"
#include "findAllBoard.h"
#include "writeToFile.h"

void main() {
	char choice;
	int typeOfPath;
	chessPos userPosChoice;
	pathTree tree;
	bool longPathUse = false, didEnterAPos = false, keepPlaying = true, treeWasBuilt = false;
	char* fileName = NULL;
	chessPosList* longPath = NULL;

	tree.root = NULL;

	while (keepPlaying) {

		choice = showMenu();

		switch (choice)
		{
		case '1':
			scanPossition(&userPosChoice[0], &userPosChoice[1]);
			didEnterAPos = true;
			break;
		case '2':
			if (!didEnterAPos)
				didNotEnterAPossition();
			else {
				tree = findAllPossibleKnightPaths(&userPosChoice);
				treeWasBuilt = true;
			}
			break;
		case '3':

			if (!didEnterAPos)
				didNotEnterAPossition();

			else
			{
				if (!treeWasBuilt) {
					tree = findAllPossibleKnightPaths(&userPosChoice);
					treeWasBuilt = true;
				}
				longPath = findKnightPathCoveringAllBoard(&tree);
				longPathUse = true;
			}

			break;
		case '4':
			if (!didEnterAPos)
				didNotEnterAPossition();

			else
			{
				if (!longPathUse)
				{
					if (!treeWasBuilt) {
						tree = findAllPossibleKnightPaths(&userPosChoice);
						treeWasBuilt = true;
					}

					longPath = findKnightPathCoveringAllBoard(&tree);
					longPathUse = true;
				}

				if (longPath == NULL)
				thereIsNotAPath();

				else {
					printf("Please enter file name: \n");

					fileName = scanFileNameFromUser();
					saveListToBinFile(fileName, longPath);

					free(fileName);
					fileName = NULL;
				}
			}
			break;
		case '5':
			
			printf("Please enter file name that you want to read from: \n");

			fileName = scanFileNameFromUser();
			typeOfPath = checkAndDisplayPathFromFile(fileName);

			printTypeOfPathToUser(typeOfPath, longPath);
			break;
		case '6':
			keepPlaying = false;
			break;
		}
	}

	if (fileName != NULL)
		free(fileName);

	if (longPath != NULL)
		freeList(longPath);

	if (tree.root != NULL)
		freeTree(tree.root);

	printf("Thank you!!\n");

}



