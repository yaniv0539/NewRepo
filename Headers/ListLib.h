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

// Q2

void makeEmptySSMList(SingleSourceMovesList* lst);
bool isEmptyList(SingleSourceMovesList* lst);
SingleSourceMovesListCell* createNewSSMListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertSSMListCellToStartList(SingleSourceMovesList* lst, SingleSourceMovesListCell* cell);
void removeSSMListCellFromStartList(SingleSourceMovesList* list);
void checkListAllocation(SingleSourceMovesList* lst);
void printList(SingleSourceMovesList* lst); // ****TEST****
void freeList(SingleSourceMovesList* lst);

// Q3

void insertCellToEndOfMultipleSourceMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail);
void insertDataToEndOfMultipleSourceMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* data);
MultipleSourceMovesListCell* createNewSingleSourceMovesList(SingleSourceMovesList* data, MultipleSourceMovesListCell* next);
void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst);
bool isEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst);

#endif // !__LIST_LIB