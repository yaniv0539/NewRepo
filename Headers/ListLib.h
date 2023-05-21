typedef struct _SingleSourceMovesListCell {
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList; 

// Basic List prototypes:
void makeEmptySSMList(SingleSourceMovesList* lst);
bool isEmptyList(SingleSourceMovesList* lst);
SingleSourceMovesListCell* createNewSSMListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);
void insertSSMListCellToStartList(SingleSourceMovesList* lst, SingleSourceMovesListCell* cell);
void copyList(SingleSourceMovesList* dest, SingleSourceMovesList* src); // DELETE
void removeSSMListCellFromEndList(SingleSourceMovesList* list); // DELETE
void freeList(SingleSourceMovesList* lst);
void checkCellAllocation(SingleSourceMovesListCell* cell);
void checkListAllocation(SingleSourceMovesList* lst);
