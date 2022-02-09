#include "display.h"

void display(chessPosList* lst)
{
	int place = 1;
	chessPosCell* cur = lst->head;
	int placeMat[ROWSIZE][COLSIZE];
	int i, j, row, col;

	delRepeat(lst);

	/*Reset matrix*/
	for (i = 0; i < ROWSIZE; i++)
		for (j = 0; j < COLSIZE; j++)
			placeMat[i][j] = EMPTY;

	while (cur != NULL)
	{
		row = (int)(cur->position[0] - 'A');
		col = (int)(cur->position[1] - '1');
		placeMat[row][col] = place;
		place++;
		cur = cur->next;
	}

	for (i = 0; i <= COLSIZE; i++)
	{
		if (i == 0)
			printf("     ");
		else
			printf(" | %2d |", i);
	}
	printf("\n\n");
	
	for (i = 0; i < ROWSIZE; i++)
	{
		printRow((char)(i + 'A'), placeMat[i]);
	}	
}
void delRepeat(chessPosList* lst)
{
	chessPosCell* cur = lst->head, * tmp = lst->head;
	bool countMat[ROWSIZE][COLSIZE];
	int i, j, row, col;

	/*Reset counter matrix*/
	for (i = 0; i < ROWSIZE; i++)
		for (j = 0; j < COLSIZE; j++)
			countMat[i][j] = false;

	while (cur != NULL)
	{
		row = (int)(cur->position[0] - 'A');
		col = (int)(cur->position[1] - '1');
		/*First time in list*/
		if (countMat[row][col] == false)
		{
			countMat[row][col] = true;
		}
		/*Exist in list*/
		else
		{
			if (lst->tail == cur)
			{
				lst->tail = tmp;
			}

			tmp->next = cur->next;
			free(cur);
			cur = tmp;
		}
		tmp = cur;
		cur = cur->next;
	}
}
void printRow(char rowSymbol, int rowArr[])
{
	int i;
	printf("| %c |", rowSymbol);
	for (i = 0; i < ROWSIZE; i++)
	{
		if (rowArr[i] == 0)
			printf("| |");
		else
			printf(" | %2d |", rowArr[i]);
	}
	printf("\n\n");
}
