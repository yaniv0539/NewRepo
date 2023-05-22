#include <GameLib.h>

void main()
{
	Board board;
	SingleSourceMovesTree* pTree;
	checkersPos pos = { 'G', '2' };
	SingleSourceMovesList* lst;
	MultipleSourceMovesList* lst2;
	buildBoard(board);

	// Q1
	pTree = FindSingleSourceMoves(board, &pos);

	// Q2
	lst = FindSingleSourceOptimalMove(pTree);

	// Q3
	lst2 = FindAllPossiblePlayerMoves(board, 'B');

	// Q4
	Turn(board, 'B');
}