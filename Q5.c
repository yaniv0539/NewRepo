#include <GameLib.h>

#define BOARD_PRINT_SIZE 19
#define MAX_CAPTURES 12
#define FIRST_ROW 0 // Exists already in GameLib
#define LAST_ROW 7

#define DECIDE_PLAYER(player1, player2) ((player1) == (FIRST_PLAYER)) ? (player2 = SECOND_PLAYER) : (player2 = FIRST_PLAYER)

typedef struct Stats {
	Player winner;
	int total_captures_first;
	int total_captures_second;
	Player best_capture_player;
	int best_capture;
}STATS;

//Q4
//void Turn(Board board, Player player);
//

void PlayGame(Board board, Player starting_player);
void printBoard(Board board);
bool checkWinner(Board board, STATS stats);
void addStats(STATS* stats, Player currPlayer, SingleSourceMovesList* lst);
void printStats(STATS stats);

SingleSourceMovesList* getBestListForPlayer(Board board, Player currPlayer);


//
void PlayGame(Board board, Player starting_player)
{
	bool winner = false;

	Player currPlayer;
	currPlayer = starting_player;
	
	STATS stats = { ' ' , 0 , 0 , ' ', 0 };

	SingleSourceMovesList* bestList;

	printBoard(board);
	while (winner != true)
	{
		bestList = getBestListForPlayer(board, currPlayer);
		Turn(board, currPlayer);
		addStats(&stats, currPlayer, bestList);

		printf("%c's turn:\n", currPlayer);
		printf("%c%c->%c%c", bestList->head->position->row, bestList->head->position->col,
			bestList->tail->position->row, bestList->tail->position->col);  //C8->D7
		printBoard(board);

		if (checkWinner(board, stats))
		{
			winner = true;
			stats.winner = currPlayer;
		}
		DECIDE_PLAYER(currPlayer, currPlayer);
	}

	printStats(stats);
}

SingleSourceMovesList* getBestListForPlayer(Board board, Player currPlayer)
{
	int max_captures, curr_source_best_captures;

	MultipleSourceMovesList* player_best_moves_list;
	MultipleSourceMovesListCell* source_best_move, * player_best_move;
	player_best_moves_list = FindAllPossiblePlayerMoves(board, currPlayer);

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
	return player_best_move->single_source_moves_list;
}

void addStats(STATS* stats, Player currPlayer, SingleSourceMovesList* lst)
{
	int captures;
	captures = lst->tail->captures;

	// Add to total captures
	if (currPlayer == FIRST_PLAYER)
	{
		stats->total_captures_first += captures;
	}
	else
	{
		stats->total_captures_second += captures;
	}

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
		{
			printf("+-+-+-+-+-+-+-+-+-+");
		}
		else if (i == 1)
		{
			printf("+ |1|2|3|4|5|6|7|8|");
		}
		else
		{
			indCol = 0;
			for (j = 0; j < BOARD_PRINT_SIZE; j++)
			{
				if (j % 2 == 0)
				{
					printf("|");
				}
				else if (j == 1)
				{
					printf("%c", 'A' + inRow);
				}
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
}

bool checkWinner(Board board, STATS stats)
{
	int col;
	// Check first and last row, to see if a player has reached to the end
	for (col = 0; col < BOARD_SIZE; col++)
	{
		if (board[FIRST_ROW][col] == SECOND_PLAYER || board[LAST_ROW][col] == FIRST_PLAYER)
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
//
//