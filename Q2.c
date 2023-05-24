#include <GameLib.h>

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	Player p;
	p = getPlayerFromPos(moves_tree->source->board, moves_tree->source->pos);
	return FindSingleSourceOptimalMoveHelper(moves_tree->source, p);
}

SingleSourceMovesList* FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* root, Player p)
{
	SingleSourceMovesList* res, * left_list, * right_list;
	SingleSourceMovesListCell* newCell;

	res = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	checkListAllocation(res);
	makeEmptySSMList(res);

	if (root == NULL)
		return res;

	left_list = FindSingleSourceOptimalMoveHelper(root->next_moves[LEFT], p);
	right_list = FindSingleSourceOptimalMoveHelper(root->next_moves[RIGHT], p);

	if (isRightListBetter(right_list, left_list, p))
	{
		res = right_list;
		free(left_list);
	}
	else
	{
		res = left_list;
		free(right_list);
	}

	newCell = createNewSSMListCell(root->pos, root->total_captures_so_far, NULL);
	insertSSMListCellToStartList(res, newCell);
	return res;
}

bool isRightListBetter(SingleSourceMovesList* right_list, SingleSourceMovesList* left_list, Player p)
{
	int right_captures, left_captures;

	if (left_list->tail == NULL)
		return true;

	if (right_list->tail == NULL)
		return false;

	right_captures = right_list->tail->captures;
	left_captures = left_list->tail->captures;

	if (right_captures == left_captures)
		return p == FIRST_PLAYER;
	return right_captures > left_captures;
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
