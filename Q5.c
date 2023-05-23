#include <GameLib.h>

void PlayGame(Board board, Player starting_player)
{
	bool hasWinner = false;
	Player currPlayer;
	SingleSourceMovesList* bestList;

	currPlayer = starting_player;
	STATS stats = { EMPTY_PLACE , 0 , 0 , EMPTY_PLACE, 0 };
	printBoard(board);

	while (!hasWinner)
	{
		bestList = getBestListForPlayer(board, currPlayer);
		Turn(board, currPlayer);
		addStats(&stats, currPlayer, bestList);

		printf("%c's turn:\n", currPlayer);
		printf("%c%c->%c%c\n", bestList->head->position->row, bestList->head->position->col,
			bestList->tail->position->row, bestList->tail->position->col);  //C8->D7
		printBoard(board);

		if (checkWinner(board, stats))
		{
			hasWinner = true;
			stats.winner = currPlayer;
		}
		SWITCH_PLAYER(currPlayer);
	}

	printStats(stats);
}

void addStats(STATS* stats, Player currPlayer, SingleSourceMovesList* lst)
{
	int captures;
	captures = lst->tail->captures;

	// Add to total captures
	if (currPlayer == FIRST_PLAYER)
		stats->total_captures_first += captures;
	else
		stats->total_captures_second += captures;

	// Check best captures in one move
	if (captures > stats->best_capture)
	{
		stats->best_capture = captures;
		stats->best_capture_player = currPlayer;
	}
}

void printBoard(Board board)
{
	int i, j;
	int inRow = 0, indCol = 0;
	for (i = 0; i < BOARD_PRINT_SIZE; i++)
	{
		if (i % 2 == 0)
			printf("+-+-+-+-+-+-+-+-+-+");
		else if (i == 1)
			printf("+ |1|2|3|4|5|6|7|8|");
		else
		{
			indCol = 0;
			for (j = 0; j < BOARD_PRINT_SIZE; j++)
			{
				if (j % 2 == 0)
					printf("|");
				else if (j == 1)
					printf("%c", 'A' + inRow);
				else
				{
					if (board[inRow][indCol] == FIRST_PLAYER || board[inRow][indCol] == SECOND_PLAYER)
						printf("%c", board[inRow][indCol]);
					else
						printf(" ");
					indCol++;
				}
			}
			inRow++;
		}
		printf("\n");
	}
	printf("\n");
}

bool checkWinner(Board board, STATS stats)
{
	int col;
	// Check first and last row, to see if a player has reached to the end
	for (col = 0; col < BOARD_SIZE; col++)
	{
		if (board[FIRST_ROW][col] == SECOND_PLAYER || board[BOARD_SIZE - 1][col] == FIRST_PLAYER)
			return true;
	}

	// Check players' capture counters, to see if other player's pieces are no more
	if (stats.total_captures_first == MAX_CAPTURES || stats.total_captures_second == MAX_CAPTURES)
		return true;

	return false;
}

void printStats(STATS stats)
{
	printf("%c wins!\n", stats.winner);

	if (stats.winner == FIRST_PLAYER)
		printf("%c performed %d moves.\n", stats.winner, stats.total_captures_first);
	else
		printf("%c performed %d moves.\n", stats.winner, stats.total_captures_second);

	printf("%c performed the highest number of captures in a single move - %d\n", stats.best_capture_player, stats.best_capture);
}