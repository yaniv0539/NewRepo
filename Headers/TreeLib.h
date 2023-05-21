typedef struct SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far;
	struct SingleSourceMovesTreeNode* next_moves[2];
} SingleSourceMovesTreeNode;

typedef struct SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
} SingleSourceMovesTree; 

// Basic tree prototypes:
void makeEmptySingleSourceMovesTree(SingleSourceMovesTree* tr);

SingleSourceMovesTreeNode* createNewSingleSourceMovesTreeNode(Board board, checkersPos* pSrc, 
	unsigned short numOfCaptures, SingleSourceMovesTreeNode* next_moves[]);
//

// include Board, checkersPos (Game.h ?)

