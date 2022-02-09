#include "validMoves.h"
#include "Header.h"
#include "question3.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	int row, col;
	pathTree tr;
	bool fathers[ROWSIZE][COLSIZE];
	chessPosArray*** positionArr;

	/*build arr with valid moves for any position*/
	positionArr = validKnightMoves();

	/*reset fathers arr*/
	for (int i = 0; i < ROWSIZE; i++)
		for (int j = 0; j < COLSIZE; j++)
			fathers[i][j] = false;

	row = startingPosition[0][0] - 'A';
	col = startingPosition[0][1] - '1';
	
	fathers[row][col] = true; /*start pos is father of everyone*/

	tr.root = (treeNode*)malloc(sizeof(treeNode));
	checkAllocation(tr.root);

	/*make first root*/
	tr.root->position[0] = startingPosition[0][0];
	tr.root->position[1] = startingPosition[0][1];
	tr.root->next_possible_positions = NULL;

	/*build tree*/
	findAllHelper(tr.root, fathers, positionArr);

	freePosArr(positionArr);

	return tr;	
}
void findAllHelper(treeNode* root, bool fathers[][COLSIZE], chessPosArray*** positionArr)
{
	int rootRow, rootCol, row, col;
	unsigned int size, i;
	treeNodeListCell* cur = NULL, *prev = NULL;
	bool firstChild = true;

	rootRow = root->position[0] - 'A';
	rootCol = root->position[1] - '1';

	size = positionArr[rootRow][rootCol]->size;

	for (i = 0; i < size; i++)
	{
		row = (positionArr[rootRow][rootCol]->positions[i][0]) - 'A';
		col = (positionArr[rootRow][rootCol]->positions[i][1]) - '1';

		if (fathers[row][col] == false)/*not his father*/
		{
			cur = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
			checkAllocation(cur);

			cur->node = createNewTreeNode(row, col);
			cur->next = NULL;

			fathers[row][col] = true;
			
			findAllHelper(cur->node, fathers, positionArr);

			fathers[row][col] = false;

			if (firstChild)
			{
				firstChild = false;
				root->next_possible_positions = cur;
			}
			else
			{
				prev->next = cur;
			}

			prev = cur;
			cur = cur->next;
		}
	}
}
void freePosArr(chessPosArray*** arr) {
	int i, j;

	for (i = 0; i < ROWSIZE; i++) {
		for (j = 0; j < COLSIZE; j++)
		{
			free(arr[i][j]->positions);
			free(arr[i][j]);
		}
		free(arr[i]);
	}
	free(arr);
}
treeNode* createNewTreeNode(int row, int col) {
	
	treeNode *new = (treeNode*)malloc(sizeof(treeNode));
	checkAllocation(new);

	new->position[0] = row + 'A';
	new->position[1] = col + '1';
	new->next_possible_positions = NULL;
	
	return new;
}
