#include <GameLib.h>

void Turn(Board board, Player player)
{
	SingleSourceMovesList* player_best_move;
	SingleSourceMovesTree* player_best_move_tree;

	player_best_move = getBestListForPlayer(board, player);

	if (player_best_move != NULL)
	{
		player_best_move_tree = FindSingleSourceMoves(board, player_best_move->head->position);
		updateBoard(board, player_best_move_tree->source, player_best_move->tail->position);
	}
}

SingleSourceMovesList* getBestListForPlayer(Board board, Player player)
{
	int max_captures, curr_source_best_captures;

	MultipleSourceMovesList* player_best_moves_list;
	MultipleSourceMovesListCell* source_best_move, * player_best_move;
	player_best_moves_list = FindAllPossiblePlayerMoves(board, player);

	max_captures = NO_MOVES_AT_ALL;
	source_best_move = player_best_moves_list->head;
	player_best_move = NULL;

	while (source_best_move != NULL)
	{
		curr_source_best_captures = source_best_move->single_source_moves_list->tail->captures;
		if (isCurrSourceTheBest(player, source_best_move, player_best_move, max_captures, curr_source_best_captures))
		{
			max_captures = curr_source_best_captures;
			player_best_move = source_best_move;
		}
		source_best_move = source_best_move->next;
	}

	if (player_best_move == NULL)
		return NULL;
	return player_best_move->single_source_moves_list;
}

bool isCurrSourceTheBest(Player player, MultipleSourceMovesListCell* source_best_move,
	MultipleSourceMovesListCell* player_best_move, int max_captures, int curr_source_best_captures)
{
	char source_col, source_row, player_col, player_row;

	if (!hasValidMove(source_best_move) || curr_source_best_captures < max_captures)
		return false;

	else if (player_best_move == NULL || curr_source_best_captures > max_captures)
		return true;

	source_col = source_best_move->single_source_moves_list->head->position->col;
	source_row = source_best_move->single_source_moves_list->head->position->row;

	player_col = player_best_move->single_source_moves_list->head->position->col;
	player_row = player_best_move->single_source_moves_list->head->position->row;

	if (player == FIRST_PLAYER && ((source_row > player_row) || (source_row == player_row && source_col > player_col)))
		return true;
	else if (player == SECOND_PLAYER && ((source_row < player_row) || (source_row == player_row && source_col < player_col)))
		return true;
	return false;
}

bool hasValidMove(MultipleSourceMovesListCell* source_best_move)
{
	if (source_best_move->single_source_moves_list->head == source_best_move->single_source_moves_list->tail)
		return false;
	return true;
}

void updateBoard(Board board, SingleSourceMovesTreeNode* source, checkersPos* pSrc)
{
	if (source == NULL)
		return;

	updateBoard(board, source->next_moves[LEFT], pSrc);
	updateBoard(board, source->next_moves[RIGHT], pSrc);

	if (source->pos->col == pSrc->col && source->pos->row == pSrc->row)
		memcpy(board, source->board, sizeof(char) * BOARD_SIZE * BOARD_SIZE);
}