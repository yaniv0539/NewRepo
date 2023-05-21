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

typedef struct _SingleSourceMovesListCell {
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;


// Functions I created, Declarations:
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
SingleSourceMovesList FindSingleSourceOptimalMoveHelperT(SingleSourceMovesTreeNode* root);
SingleSourceMovesList FindSingleSourceOptimalMoveHelperB(SingleSourceMovesTreeNode* root);


Player getPlayerFromPos(Board board, checkersPos* pSrc);
int getRowNum(char rowChar);
int getColNum(char colNum);

void makeEmptySSMList(SingleSourceMovesList* lst);
bool isEmptyList(SingleSourceMovesList* lst);
SingleSourceMovesListCell* createNewSSMListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertSSMListCellToEndList(SingleSourceMovesList* lst, SingleSourceMovesListCell* cell);
void copyList(SingleSourceMovesList* dest, SingleSourceMovesList* src);
void removeSSMListCellFromEndList(SingleSourceMovesList* list);
void freeList(SingleSourceMovesList* lst);
void checkCellAllocation(SingleSourceMovesListCell* cell);
void checkListAllocation(SingleSourceMovesList* lst);
//


// Main Q2 function
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	Player p;
	p = getPlayerFromPos(moves_tree->source->board, moves_tree->source->pos);

	SingleSourceMovesList* bestPath; // should malloc? 
	bestPath = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkListAllocation(bestPath);
	makeEmptySSMList(bestPath);

	if (p == 'T')
	{
		*bestPath = FindSingleSourceOptimalMoveHelperT(moves_tree->source);
	}
	else if(p == 'B')
	{
		*bestPath = FindSingleSourceOptimalMoveHelperB(moves_tree->source);
	}

	return bestPath;

}


SingleSourceMovesList FindSingleSourceOptimalMoveHelperT(SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
	{
		return NULL;
	}

	SingleSourceMovesList lstL, lstR;
	makeEmptySSMList(lstL);
	makeEmptySSMList(lstR);

	lstL = FindSingleSourceOptimalMoveHelperT(root->next_move[0]);
	lstR = FindSingleSourceOptimalMoveHelperT(root->next_move[1]);

	if (lstL == NULL || lstR == NULL)
	{
		if (lstL == NULL)
		{
			SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
			insertSSMListCellToEndList(currentPath, newCell); // change to START
			freeList(&lstL);
			return lstR;
		}
		else if (lstR == NULL)
		{
			SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
			insertSSMListCellToEndList(currentPath, newCell); // change to START
			freeList(&lstR);
			return lstL;
		}
	}
	else if (lstL.tail->captures <= lstR.tail->captures)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
		insertSSMListCellToEndList(currentPath, newCell); // change to START
		freeList(&lstL);
		return lstR;
	}
	else if (lstL.tail->captures > lstR.tail->captures)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
		insertSSMListCellToEndList(currentPath, newCell); // change to START
		freeList(&lstR);
		return lstL;
	}
		
}

SingleSourceMovesList FindSingleSourceOptimalMoveHelperB(SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
	{
		return NULL;
	}

	SingleSourceMovesList lstL, lstR;
	makeEmptySSMList(lstL);
	makeEmptySSMList(lstR);

	lstL = FindSingleSourceOptimalMoveHelperT(root->next_move[1]);
	lstR = FindSingleSourceOptimalMoveHelperT(root->next_move[0]);

	if (lstL == NULL || lstR == NULL)
	{
		if (lstL == NULL)
		{
			SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
			insertSSMListCellToEndList(currentPath, newCell); // change to START
			freeList(&lstL);
			return lstR;
		}
		if (lstR == NULL)
		{
			SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
			insertSSMListCellToEndList(currentPath, newCell); // change to START
			freeList(&lstR);
			return lstL;
		}
	}
	else if (lstL.tail->captures <= lstR.tail->captures)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
		insertSSMListCellToEndList(currentPath, newCell); // change to START
		freeList(&lstL);
		return lstR;
	}
	else if (lstL.tail->captures > lstR.tail->captures)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
		insertSSMListCellToEndList(currentPath, newCell); // change to START
		freeList(&lstR);
		return lstL;
	}

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

void checkListAllocation(SingleSourceMovesList* lst)
{
	if (lst == NULL) {
		printf("memory allocation failed!");
		exit(1);
	}
}

