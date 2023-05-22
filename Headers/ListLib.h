#ifndef __LIST_LIB
#define __LIST_LIB

typedef struct _SingleSourceMovesListCell {
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList; 

typedef struct multipleSourceMovesListCell {
	SingleSourceMovesList* single_source_moves_list;
	struct multipleSourceMovesListCell* next;
} MultipleSourceMovesListCell;

typedef struct multipleSourceMovesList {
	MultipleSourceMovesListCell* head;
	MultipleSourceMovesListCell* tail;
} MultipleSourceMovesList;

// Basic List prototypes:
void makeEmptySSMList(SingleSourceMovesList* lst);
bool isEmptyList(SingleSourceMovesList* lst);
SingleSourceMovesListCell* createNewSSMListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertSSMListCellToStartList(SingleSourceMovesList* lst, SingleSourceMovesListCell* cell);
void removeSSMListCellFromStartList(SingleSourceMovesList* list);
void checkCellAllocation(SingleSourceMovesListCell* cell);
void checkListAllocation(SingleSourceMovesList* lst);

void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst);
void insertToEndOfMultipleSourceMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* tail);

void printList(SingleSourceMovesList* lst); // ****TEST****
void freeList(SingleSourceMovesList* lst);

#endif // !__LIST_LIB