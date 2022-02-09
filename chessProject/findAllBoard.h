
#ifndef COVERALL
#define COVERALL

#include "Header.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
int coverAllHelper(treeNode* root, chessPosList* lst);

#endif // !COVERALL
