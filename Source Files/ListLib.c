#include <ListLib.h>

// Lists Functions

void insertCellToEndOfMultipleSourceMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail)
{
	if (isEmptyMultipleSourceMovesList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

void insertDataToEndOfMultipleSourceMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* data)
{
	MultipleSourceMovesListCell* newTail;
	newTail = createNewSingleSourceMovesList(data, NULL);
	insertCellToEndOfMultipleSourceMovesList(lst, newTail);
}

MultipleSourceMovesListCell* createNewSingleSourceMovesList(SingleSourceMovesList* data, MultipleSourceMovesListCell* next)
{
	MultipleSourceMovesListCell* res;
	res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));

	if (!res)
	{
		printf("Memory allocation failure!!!");
		exit(1);
	}

	res->single_source_moves_list = data;
	res->next = next;
	return res;
}

void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst)
{
	lst->head = lst->tail = NULL;
}

bool isEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst)
{
	if (lst->head == NULL)
		return true;
	return false;
}