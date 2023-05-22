#include <GameLib.h>

void Turn(Board board, Player player)
{
	MultipleSourceMovesList* player_best_moves_list;
	MultipleSourceMovesListCell* source_best_move, * player_best_move;
	SingleSourceMovesTree* player_best_move_tree;
	int max_captures, curr_source_best_captures;

	max_captures = NO_MOVES_AT_ALL;
	player_best_moves_list = FindAllPossiblePlayerMoves(board, player);

	source_best_move = player_best_move = player_best_moves_list->head;

	while (source_best_move != NULL)
	{
		curr_source_best_captures = source_best_move->single_source_moves_list->tail->captures;
		if (curr_source_best_captures > max_captures ||
			(curr_source_best_captures == max_captures && isReallyCurrSourceTheBest(player, source_best_move, player_best_move)))
		{
			max_captures = curr_source_best_captures;
			player_best_move = source_best_move;
		}
		source_best_move = source_best_move->next;
	}

	if (max_captures != NO_MOVES_AT_ALL)
	{
		player_best_move_tree = FindSingleSourceMoves(board, player_best_move->single_source_moves_list->head->position);
		updateBoard(board, player_best_move_tree->source, player_best_move->single_source_moves_list->tail->position);
	}
}

bool isReallyCurrSourceTheBest(Player player, MultipleSourceMovesListCell* source_best_move, MultipleSourceMovesListCell* player_best_move)
{
	char source_col, source_row, player_col, player_row;

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

void updateBoard(Board board, SingleSourceMovesTreeNode* source, checkersPos* pSrc)
{
	if (source == NULL)
		return;

	updateBoard(board, source->next_moves[LEFT], pSrc);
	updateBoard(board, source->next_moves[RIGHT], pSrc);

	if (source->pos->col == pSrc->col && source->pos->row == pSrc->row)
		memcpy(board, source->board, sizeof(char) * BOARD_SIZE * BOARD_SIZE);
}