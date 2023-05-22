#include <TreeLib.h>

// Q1

// Makes empty single source moves tree by initialized to NULL
void makeEmptySingleSourceMovesTree(SingleSourceMovesTree* tr)
{
	tr->source = NULL;
}

// Creates new single source move tree node by assimilate inside: The board, his source position,
// number of captures so far and array with his next possible moves.
SingleSourceMovesTreeNode* createNewSingleSourceMovesTreeNode(Board board, checkersPos* pSrc,
	unsigned short numOfCaptures, SingleSourceMovesTreeNode* next_moves[])
{
	SingleSourceMovesTreeNode* newNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));

	if (!newNode)
	{
		printf("Memory Allocation Failure!!!");
		exit(1);
	}

	memcpy(newNode->board, board, sizeof(char) * BOARD_SIZE * BOARD_SIZE);
	newNode->pos = pSrc;
	newNode->total_captures_so_far = numOfCaptures;
	newNode->next_moves[LEFT] = next_moves[LEFT];
	newNode->next_moves[RIGHT] = next_moves[RIGHT];

	return newNode;
}