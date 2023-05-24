#include <GameLib.h>

void PlayGame(Board board, Player starting_player)
{
	int pNum = 0;
	bool hasWinner = false;
	SingleSourceMovesList* bestList;
	STATS players_stats[2] = { 0 };

	players_stats[pNum].player = starting_player;

	if (starting_player == FIRST_PLAYER)
		players_stats[pNum + 1].player = SECOND_PLAYER;
	else
		players_stats[pNum + 1].player = FIRST_PLAYER;

	printBoard(board);

	while (!hasWinner)
	{
		bestList = getBestListForPlayer(board, players_stats[pNum].player);
		Turn(board, players_stats[pNum].player);
		addStats(players_stats, pNum, bestList);

		printf("%c's turn:\n", players_stats[pNum].player);
		printf("%c%c->%c%c\n", bestList->head->position->row, bestList->head->position->col,
			bestList->tail->position->row, bestList->tail->position->col);
		printBoard(board);

		if (checkWinner(board, players_stats))
		{
			hasWinner = true;
			break;
		}

		SWITCH_PLAYER(pNum);
	}

	printStats(players_stats, pNum);
}

void addStats(STATS* players_stats, int pNum, SingleSourceMovesList* lst)
{
	int captures = lst->tail->captures;

	players_stats[pNum].total_moves++;
	players_stats[pNum].total_captures += captures;

	if (captures > players_stats[pNum].best_capture)
		players_stats[pNum].best_capture = captures;
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

bool checkWinner(Board board, STATS* players_stats)
{
	int col;
	// Check first and last row, to see if a player has reached to the end
	for (col = 0; col < BOARD_SIZE; col++)
		if (board[FIRST_ROW][col] == SECOND_PLAYER || board[LAST_ROW][col] == FIRST_PLAYER)
			return true;

	// Check players' capture counters, to see if other player's pieces are no more
	if (players_stats[0].best_capture == MAX_CAPTURES || players_stats[1].best_capture == MAX_CAPTURES)
		return true;

	return false;
}

void printStats(STATS* players_stats, int pNum)
{
	int best_capturer_ind;

	printf("%c wins!\n", players_stats[pNum].player);
	printf("%c performed %d moves.\n", players_stats[pNum].player, players_stats[pNum].total_moves);

	if (players_stats[0].best_capture > players_stats[1].best_capture)
		best_capturer_ind = 0;
	else
		best_capturer_ind = 1;

	printf("%c performed the highest number of captures in a single move - %d\n",
		players_stats[best_capturer_ind].player, players_stats[best_capturer_ind].best_capture);
}
