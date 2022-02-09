#include "Header.h"
#include "validMoves.h"

/*function get arrays of pos to any point at board*/
chessPosArray*** validKnightMoves() {
	
	int i, j;
	chessPos pos;
	chessPosArray*** validMoves = (chessPosArray***)malloc((ROWSIZE) * sizeof(chessPosArray**));
	checkAllocation(validMoves);

	for (i = 0; i < ROWSIZE; i++) {

		validMoves[i] = (chessPosArray**)malloc(COLSIZE*sizeof(chessPos*));
		checkAllocation(validMoves[i]);

		for (j = 0; j < COLSIZE; j++)
		{
			pos[0] = 'A' + i;
			pos[1] = '1' + j;
			validMoves[i][j] = createPosArray(pos);

		}

		
	}
	return validMoves;
}

/*function get pos and return array of legal place to go*/
chessPosArray* createPosArray(chessPos pos) {

	char row, col;
	int places[8][2] = { {-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1} };
	int i, logSize = 0, phSize = 1;
	chessPosArray* posArr = (chessPosArray*)malloc(sizeof(chessPosArray));
	checkAllocation(posArr);

	chessPos* new = (chessPos*)malloc(sizeof(chessPos));
	checkAllocation(new);

	for (i = 0; i < 8; i++)
	{
		row = pos[0] + places[i][0];
		col = pos[1] + places[i][1];

		if (isLegalCol(col) && isLegalRow(row))/*the pos is inside the board*/
		{
			if (logSize == phSize) {
				phSize *= 2;
				new = (chessPos*)realloc(new, phSize * sizeof(chessPos));
				checkAllocation(new);
			}

			new[logSize][0] = row;
			new[logSize][1] = col;
			logSize++;
		}
	}
	if (logSize < phSize) {
		new = (chessPos*)realloc(new, logSize * sizeof(chessPos));
		checkAllocation(new);
	}

	posArr->positions = new;
	posArr->size = logSize;

	return posArr;
}

