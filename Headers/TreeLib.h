#ifndef __TREE_LIB_H
#define __TREE_LIB_H

typedef struct SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far;
	struct SingleSourceMovesTreeNode* next_moves[2];
} SingleSourceMovesTreeNode;

typedef struct SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
} SingleSourceMovesTree; 

// Basic Tree prototypes:

// Q1

void makeEmptySingleSourceMovesTree(SingleSourceMovesTree* tr);
SingleSourceMovesTreeNode* createNewSingleSourceMovesTreeNode(Board board, checkersPos* pSrc, 
	unsigned short numOfCaptures, SingleSourceMovesTreeNode* next_moves[]);

// include Board, checkersPos (Game.h ?)

#endif // !__TREE_LIB_H