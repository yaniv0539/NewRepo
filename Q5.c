#include <GameLib.h>

#define BOARD_PRINT_SIZE 19

#define DECIDE_PLAYER(player1, player2) ((player1) == (FIRST_PLAYER)) ? (player2 = SECOND_PLAYER) : (player2 = FIRST_PLAYER)

typedef struct Stats {
	Player winner;
	int total_captures_first;
	int total_captures_second;
	Player best_capture_player;
	int best_capture;
}STATS;

//Q4
void Turn(Board board, Player player);
//

void PlayGame(Board board, Player starting_player);
void printBoard(Board board);
bool checkWinner(Board board);
void printStats(STATS stats);

//
void PlayGame(Board board, Player starting_player)
{
	bool winner = false;

	Player player1, player2, currPlayer;
	currPlayer = player1 = starting_player;
	DECIDE_PLAYER(player1, player2);
	
	STATS stats = { ' ' , 0 , 0 , ' ', 0 };

	printBoard(board);
	while (winner != true)
	{
		Turn(board, currPlayer);
		printf("%c's turn:\n", currPlayer);
		//printf("%c%c->%c%c", lst->head->pos->...)  C8->D7
		printBoard(board);
		if (checkWinner(board))
		{
			winner = true;
			stats.winner = currPlayer;
		}
		DECIDE_PLAYER(currPlayer, currPlayer);
		
	}

	printStats(stats);
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

bool checkWinner(Board board)
{
	// Check first and last row, to see if a player has reached to the end

	// Check players' capture counters, to see if other player's pieces are no more
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
void Turn(Board board, Player player) {

}
//