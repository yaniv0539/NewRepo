#include <ListLib.h>

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

	newNode->position = malloc(sizeof(checkersPos));
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

void removeSSMListCellFromStartList(SingleSourceMovesList* list)
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

	SingleSourceMovesListCell* temp = list->head;
	list->head = list->head->next;

	free(temp);

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

void insertToEndOfMultipleSourceMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* tail)
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

void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst)
{
	lst->head = lst->tail = NULL;
}