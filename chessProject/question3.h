#ifndef BUILD_TREE
#define BUILD_TREE

#include "Header.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
void findAllHelper(treeNode* root, bool fathers[][COLSIZE], chessPosArray*** positionArr);
treeNode* createNewTreeNode(int row, int col);

#endif // !BUILD_TREE

