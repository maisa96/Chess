#include "Header.h"
#include "List.h"
#include "findAllBoard.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	int pathLen;
	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkAllocation(lst);

	makeEmptyList(lst);

	/*recursive function find long path*/
	pathLen = coverAllHelper(path_tree->root, lst);

	if (pathLen == BOARDSIZE)
		return lst;
	else
	{
		freeList(lst);
		return NULL;
	}
}
int coverAllHelper(treeNode* root, chessPosList* lst)
{
	treeNodeListCell* cur = NULL;
	int depth, maxPathLen = 0;
	chessPosList* maxLst;

	maxLst = (chessPosList*)malloc(sizeof(chessPosList));
	checkAllocation(maxLst);

	makeEmptyList(maxLst);

	if (root == NULL)
		return 0;
	else
	{
		cur = root->next_possible_positions;

		while (cur != NULL)
		{
			depth = coverAllHelper(cur->node, lst);

			/*find the longest path the returned*/
			if (depth > maxPathLen)
			{
				maxPathLen = depth;

				if (!isEmptyList(maxLst));
				freeList(maxLst);

				maxLst->head = lst->head;
				maxLst->tail = lst->tail;
			}
			else
				freeList(lst);

			makeEmptyList(lst);
			cur = cur->next;
		}

		insertDataToHeadList(maxLst, root->position);
		lst->head = maxLst->head;
		lst->tail = maxLst->tail;
		
		makeEmptyList(maxLst);
		free(maxLst);
		
		return maxPathLen + 1;
	}
}
