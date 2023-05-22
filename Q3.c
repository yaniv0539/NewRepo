#include <GameLib.h>

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
	int i, j, rowNum, colNum;
	SingleSourceMovesTree* source_moves_tree;
	SingleSourceMovesList* source_optimal_move;
	MultipleSourceMovesList* res;
	checkersPos src = {0};

	res = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));

	if (!res)
	{
		printf("Memory Allocation Failure!!!");
		exit(1);
	}

	makeEmptyMultipleSourceMovesList(&res);

	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == player)
			{
				src.row = COL_INT_TO_CHAR(i);
				src.col = COL_INT_TO_CHAR(j);
				source_moves_tree = FindSingleSourceMoves(board, &src);
				source_optimal_move = FindSingleSourceOptimalMove(source_moves_tree);
				insertToEndOfMultipleSourceMovesList(res, source_optimal_move);
			}
	
	return res;
}