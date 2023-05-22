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




// Functions I created, Declarations:
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
void FindSingleSourceOptimalMoveHelperT(SingleSourceMovesList* currentPath, SingleSourceMovesList* bestPath, SingleSourceMovesTreeNode* root);
void FindSingleSourceOptimalMoveHelperB(SingleSourceMovesList* currentPath, SingleSourceMovesList* bestPath, SingleSourceMovesTreeNode* root);

Player getPlayerFromPos(Board board, checkersPos* pSrc);
int getRowNum(char rowChar);
int getColNum(char colNum);


//


// Main Q2 function
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	Player p;
	p = getPlayerFromPos(moves_tree->source->board, moves_tree->source->pos);

	SingleSourceMovesList* currentPath, *bestPath; // should malloc? 
	makeEmptySSMList(currentPath);
	makeEmptySSMList(bestPath);

	if (p == 'T')
	{
		FindSingleSourceOptimalMoveHelperT(currentPath, bestPath, moves_tree->source);
	}
	else if(p == 'B')
	{
		FindSingleSourceOptimalMoveHelperB(currentPath, bestPath, moves_tree->source);

	}

	return bestPath;

}

void FindSingleSourceOptimalMoveHelperT(SingleSourceMovesList* currentPath, SingleSourceMovesList* bestPath, SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
		return;

	// Add current node to current path
	SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
	insertSSMListCellToEndList(currentPath, newCell); 

	if (root->next_move[0] == NULL && root->next_move[1] == NULL)
	{
		if (bestPath->head == NULL || root->total_captures_so_far >= bestPath->tail->captures)
		{
			copyList(bestPath, currentPath);
		}
	}
	else
	{
		FindSingleSourceOptimalMoveHelper(currentPath, bestPath, root->next_move[0]);
		FindSingleSourceOptimalMoveHelper(currentPath, bestPath, root->next_move[1]);
	}

	// Remove current node from current path before returning to previous call
	removeSSMListCellFromEndList(currentPath); 
}

void FindSingleSourceOptimalMoveHelperB(SingleSourceMovesList* currentPath, SingleSourceMovesList* bestPath, SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
		return;

	// Add current node to current path
	SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
	insertSSMListCellToEndList(currentPath, newCell);

	if (root->next_move[0] == NULL && root->next_move[1] == NULL)
	{
		if (bestPath->head == NULL || root->total_captures_so_far >= bestPath->tail->captures)
		{
			copyList(bestPath, currentPath);
		}
	}
	else
	{
		FindSingleSourceOptimalMoveHelper(currentPath, bestPath, root->next_move[1]);
		FindSingleSourceOptimalMoveHelper(currentPath, bestPath, root->next_move[0]);
	}

	// Remove current node from current path before returning to previous call
	removeSSMListCellFromEndList(currentPath);
}


// Gets the player name from position.
Player getPlayerFromPos(Board board, checkersPos* pSrc)
{
	int rowNum, colNum;

	rowNum = getRowNum(pSrc->row);
	colNum = getColNum(pSrc->col);

	return board[rowNum][colNum];
}

// Change row from char to int.
int getRowNum(char rowChar)
{
	return rowChar - 'A';
}

// Change column from char to int.
int getColNum(char colNum)
{
	return colNum - '1';
}

//

void makeEmptySSMList(SingleSourceMovesList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

bool isEmptyList(SingleSourceMovesList* lst)
{
	if (lst->head == NULL && lst->tail == NULL)
		return true;
	else
		return false;
}

SingleSourceMovesListCell* createNewSSMListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next)
{
	SingleSourceMovesListCell* newNode;
	newNode = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	checkCellAllocation(newNode);

	newNode->position = position;
	newNode->captures = captures;
	newNode->next = next;

	return newNode;
}

void insertSSMListCellToEndList(SingleSourceMovesList* lst, SingleSourceMovesListCell* cell)
{
	if (isEmptyList(lst) == true)
	{
		lst->head = lst->tail = cell;
	}
	else 
	{
		lst->tail->next = cell;
		lst->tail = cell;
	}
	cell->next = NULL;

}

void copyList(SingleSourceMovesList* dest, SingleSourceMovesList* src)
{
	freeList(dest);

	SingleSourceMovesListCell* current = src->head;
	while (current != NULL)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(current->position, current->captures, NULL);
		insertSSMListCellToEndList(dest, newCell);
		current = current->next;
	}
}

void removeSSMListCellFromEndList(SingleSourceMovesList* list)
{
	// If the list is empty, return
	if (list->head == NULL)
		return;

	// If there is only one node on the list
	if (list->head == list->tail)
	{
		free(list->head);
		list->head = list->tail = NULL;
		return;
	}

	SingleSourceMovesListCell* secondLast = list->head;
	while (secondLast->next != list->tail)
	{
		secondLast = secondLast->next;
	}

	free(list->tail);
	list->tail = secondLast;
	list->tail->next = NULL;
}

void freeList(SingleSourceMovesList* lst)
{
	SingleSourceMovesListCell* current = lst->head;
	while (current != NULL)
	{
		SingleSourceMovesListCell* next = current->next;
		free(current);
		current = next;
	}
	lst->head = NULL;
	lst->tail = NULL;
}

void checkCellAllocation(SingleSourceMovesListCell* cell)
{
	if (cell == NULL) {
		printf("memory allocation failed!");
		exit(1);
	}
}

