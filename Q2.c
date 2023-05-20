#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 8

typedef struct _checkersPos
{
	char row, col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far; // מספר דילוגים עד כה
	struct _SingleSourceMovesTreeNode* next_move[2]; //יעדי תנועה
    
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;

typedef struct _SingleSoourceMovesListCell {
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;

typedef struct _SingleSoourceMovesList {
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;


// Functions I created, Declarations:
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
int FindSingleSourceOptimalMoveHelper(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* root);

void makeEmptySSMList(SingleSourceMovesList* lst);
SingleSourceMovesListCell* createNewSSMListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertSSMListCellToStartList(SingleSourceMovesList* lst, SingleSourceMovesListCell* cell);
//


// Main Q2 function
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	int sizeOfRoute;
	SingleSourceMovesList* lst;
	makeEmptySSMList(lst);
	sizeOfRoute = FindSingleSourceOptimalMoveHelper(lst, moves_tree->source);

	return lst;

}

int FindSingleSourceOptimalMoveHelper(SingleSourceMovesList* lst, SingleSourceMovesTreeNode* root)
{
	SingleSourceMovesListCell* newCell;
	int captureL = 0, captureR = 0;
	if (root->next_move[0] == NULL && root->next_move[1] == NULL)
	{
		return root->total_captures_so_far;
	}	
	else if (root->next_move[0] != NULL && root->next_move[1] == NULL)
	{
		captureL = FindSingleSourceOptimalMoveHelper(lst, root->next_move[0]);
	}
	else if (root->next_move[0] == NULL && root->next_move[1] != NULL)
	{
		captureR = FindSingleSourceOptimalMoveHelper(lst, root->next_move[1]);
	}
	else if (root->next_move[0] != NULL && root->next_move[1] != NULL)
	{
		captureL = FindSingleSourceOptimalMoveHelper(lst, root->next_move[0]);
		captureR = FindSingleSourceOptimalMoveHelper(lst, root->next_move[1]);
	}

	if (captureL > captureR)
	{
		newCell = createNewSSMListCell(root->next_move[0]->pos, root->next_move[0]->total_captures_so_far, NULL);
		insertSSMListCellToStartList(lst, newCell);
		return captureL + root->total_captures_so_far;
	}
	else if (captureL <= captureR)
	{
		newCell = createNewSSMListCell(root->next_move[1]->pos, root->next_move[1]->total_captures_so_far, NULL);
		insertSSMListCellToStartList(lst, newCell);
		return captureR + root->total_captures_so_far;
	}
}

//


void makeEmptySSMList(SingleSourceMovesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

SingleSourceMovesListCell* createNewSSMListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* newNode;
	newNode = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));

	newNode->position = position;
	newNode->captures = captures;
	newNode->next = next;

	return newNode;
}

void insertSSMListCellToStartList(SingleSourceMovesList* lst, SingleSourceMovesListCell* cell)
{
	if (isEmptyList(lst) == true)
	{
		cell->next = NULL;
		lst->head = lst->tail = cell;
	}
	else
	{
		cell->next = lst->head;
		lst->head = cell;
	}
}