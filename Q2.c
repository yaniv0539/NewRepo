#include <GameLib.h>


SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	Player p;
	p = getPlayerFromPos(moves_tree->source->board, moves_tree->source->pos);

	SingleSourceMovesList* bestPath;
	bestPath = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkListAllocation(bestPath);
	makeEmptySSMList(bestPath);

	if (p == 'T')
	{
		bestPath = FindSingleSourceOptimalMoveHelperT(moves_tree->source);
	}
	else if (p == 'B')
	{
		bestPath = FindSingleSourceOptimalMoveHelperB(moves_tree->source);
	}

	//removeSSMListCellFromStartList(bestPath);

	return bestPath;

}

SingleSourceMovesList* FindSingleSourceOptimalMoveHelperT(SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
	{
		SingleSourceMovesList* lst = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
		checkListAllocation(lst);
		makeEmptySSMList(lst);
		return lst;
	}

	SingleSourceMovesList* lstL, * lstR;
	lstL = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkListAllocation(lstL);
	lstR = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkListAllocation(lstR);
	makeEmptySSMList(lstL);
	makeEmptySSMList(lstR);

	lstL = FindSingleSourceOptimalMoveHelperT(root->next_moves[0]);
	lstR = FindSingleSourceOptimalMoveHelperT(root->next_moves[1]);

	if (lstL->head == NULL || lstR->head == NULL)
	{
		if (lstR->head == NULL)
		{
			SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
			insertSSMListCellToStartList(lstL, newCell);
			freeList(lstR);
			return lstL;
		}
		else if (lstL->head == NULL)
		{
			SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
			insertSSMListCellToStartList(lstR, newCell);
			freeList(lstL);
			return lstR;
		}
	}
	else if (lstL->tail->captures <= lstR->tail->captures)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
		insertSSMListCellToStartList(lstR, newCell);
		freeList(lstL);
		return lstR;
	}
	else if (lstL->tail->captures > lstR->tail->captures)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
		insertSSMListCellToStartList(lstL, newCell);
		freeList(lstR);
		return lstL;
	}

	return NULL;
}

SingleSourceMovesList* FindSingleSourceOptimalMoveHelperB(SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
	{
		SingleSourceMovesList* lst = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
		checkListAllocation(lst);
		makeEmptySSMList(lst);
		return lst;
	}

	SingleSourceMovesList* lstL, * lstR;
	lstL = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkListAllocation(lstL);
	lstR = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkListAllocation(lstR);
	makeEmptySSMList(lstL);
	makeEmptySSMList(lstR);

	lstL = FindSingleSourceOptimalMoveHelperB(root->next_moves[0]);
	lstR = FindSingleSourceOptimalMoveHelperB(root->next_moves[1]);

	if (lstL->head == NULL || lstR->head == NULL)
	{
		if (lstL->head == NULL)
		{
			SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
			insertSSMListCellToStartList(lstR, newCell);
			freeList(lstL);
			return lstR;
		}
		else if (lstR->head == NULL)
		{
			SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
			insertSSMListCellToStartList(lstL, newCell);
			freeList(lstR);
			return lstL;
		}
	}
	else if (lstL->tail->captures <= lstR->tail->captures)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
		insertSSMListCellToStartList(lstR, newCell);
		freeList(lstL);
		return lstR;
	}
	else if (lstL->tail->captures > lstR->tail->captures)
	{
		SingleSourceMovesListCell* newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
		insertSSMListCellToStartList(lstL, newCell);
		freeList(lstR);
		return lstL;
	}

	return NULL;
}

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

	if (!newNode)
	{
		printf("Memory Allocation Failure!!!");
		exit(1);
	}

	newNode->position = (checkersPos*)malloc(sizeof(checkersPos));

	if (!newNode->position) {
		printf("Memory Allocation Failure!!!");
		exit(1);
	}
	newNode->position->row = position->row;
	newNode->position->col = position->col;
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

//void removeSSMListCellFromStartList(SingleSourceMovesList* list)
//{
//	// If the list is empty, return
//	if (list->head == NULL)
//		return;
//
//	// If there is only one node on the list
//	if (list->head == list->tail)
//	{
//		free(list->head);
//		list->head = list->tail = NULL;
//		return;
//	}
//
//	SingleSourceMovesListCell* temp = list->head;
//	list->head = list->head->next;
//
//	free(temp);
//
//}

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

void checkListAllocation(SingleSourceMovesList* lst)
{
	if (lst == NULL) {
		printf("memory allocation failed!");
		exit(1);
	}
}

//  ****TEST****
void printList(SingleSourceMovesList* lst)
{
	SingleSourceMovesListCell* curr;
	curr = lst->head;
	while (curr != NULL)
	{
		printf("(%c, %c) -> ", curr->position->row, curr->position->col);
		curr = curr->next;
	}
}
