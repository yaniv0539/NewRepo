#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BOARD_SIZE 8

#define FIRST_PLAYER 'T'
#define SECOND_PLAYER 'B'
#define EMPTY_PLACE ' '

#define LEFT 0
#define RIGHT 1

#define SINGLE_MOVE 1
#define DOUBLE_MOVE 2

#define STUCK 0
#define MOVE_WITHOUT_CAPTURE 1
#define MOVE_WITH_CAPTURE 2

#define FIRST_COL 0
#define SECOND_COL 1
#define FIRST_ROW 0
#define SECOND_ROW 1

typedef struct checkersPos {
	char row, col;
} checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far;
	struct SingleSourceMovesTreeNode* next_moves[2];
} SingleSourceMovesTreeNode;

typedef struct SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
} SingleSourceMovesTree;

void buildBoard(Board board);
void makeEmptySingleSourceMovesTree(SingleSourceMovesTree* tr);
Player getPlayerFromPos(Board board, checkersPos* pSrc);
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* pSrc);
SingleSourceMovesTreeNode* FindSingleSourceMovesHelper(Board board, checkersPos* pSrc,
	Player p, unsigned short numOfCaptures, bool isFirstMove);
SingleSourceMovesTreeNode* createNewSingleSourceMovesTreeNode(Board board, checkersPos* pSrc,
	unsigned short numOfCaptures, SingleSourceMovesTreeNode* next_moves[]);
void copyBoard(Board newBoard, Board oldBoard);
int checkDiagonal(Board board, checkersPos* pSrc, Player p, unsigned short numOfCaptures, int dir, bool isFirstMove);
void createNewSrc(checkersPos* res, checkersPos* pSrc, Player p, int dir, int steps);
int getRowNum(char rowChar);
int getColNum(char colNum);

void main()
{
	Board board;
	SingleSourceMovesTree* pTree;
	checkersPos pos = { 'G', '2' };

	buildBoard(board);

	pTree = FindSingleSourceMoves(board, &pos);
}

// Temporary function to build board. 
void buildBoard(Board board)
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			board[i][j] = ' ';

	board[3][0] = FIRST_PLAYER;
	board[1][2] = FIRST_PLAYER;
	board[5][2] = FIRST_PLAYER;
	board[1][4] = FIRST_PLAYER;
	board[3][4] = FIRST_PLAYER;
	board[1][6] = FIRST_PLAYER;
	board[3][6] = FIRST_PLAYER;
	//board[1][6] = FIRST_PLAYER;
	//board[2][1] = FIRST_PLAYER;
	//board[2][3] = FIRST_PLAYER;
	//board[2][5] = FIRST_PLAYER;
	//board[2][7] = FIRST_PLAYER;

	board[6][1] = SECOND_PLAYER;
	//board[5][2] = SECOND_PLAYER;
	//board[5][4] = SECOND_PLAYER;
	//board[5][6] = SECOND_PLAYER;
	//board[6][1] = SECOND_PLAYER;
	//board[6][3] = SECOND_PLAYER;
	//board[6][5] = SECOND_PLAYER;
	//board[6][7] = SECOND_PLAYER;
	//board[7][0] = SECOND_PLAYER;
	//board[7][2] = SECOND_PLAYER;
	//board[7][4] = SECOND_PLAYER;
	//board[7][6] = SECOND_PLAYER;
}

// Makes empty single source moves tree by initialized to NULL
void makeEmptySingleSourceMovesTree(SingleSourceMovesTree* tr)
{
	tr->source = NULL;
}

// Gets the player name from position.
Player getPlayerFromPos(Board board, checkersPos* pSrc)
{
	int rowNum, colNum;

	rowNum = getRowNum(pSrc->row);
	colNum = getColNum(pSrc->col);

	return board[rowNum][colNum];
}

// Creates new single source moves tree. If position not valid returns NULL. Else calls helper function.
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* pSrc)
{
	SingleSourceMovesTree* pTree;
	Player p;

	p = getPlayerFromPos(board, pSrc);

	if (p == EMPTY_PLACE)
		return NULL;

	pTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));

	if (!pTree)
	{
		printf("Memory Allocation Failure!!!");
		exit(1);
	}

	makeEmptySingleSourceMovesTree(pTree);

	pTree->source = FindSingleSourceMovesHelper(board, pSrc, p, 0, true);

	return pTree;
}
//TEST GIT

// Recursive helper function to 'FindSingleSourceMoves'. Creates all the possible routes for single source. 
SingleSourceMovesTreeNode* FindSingleSourceMovesHelper(Board board, checkersPos* pSrc,
	Player p, unsigned short numOfCaptures, bool isFirstMove)
{
	SingleSourceMovesTreeNode* source;
	int rightRoute, leftRoute;
	checkersPos rightSrc, leftSrc;

	rightRoute = checkDiagonal(board, pSrc, p, numOfCaptures, RIGHT, isFirstMove);
	leftRoute = checkDiagonal(board, pSrc, p, numOfCaptures, LEFT, isFirstMove);

	source = createNewSingleSourceMovesTreeNode(board, pSrc, numOfCaptures, NULL);

	if (rightRoute == STUCK && leftRoute == STUCK)
		return source;

	if (rightRoute == MOVE_WITHOUT_CAPTURE)
	{
		createNewSrc(&rightSrc, pSrc, p, RIGHT, MOVE_WITHOUT_CAPTURE);
		source->next_moves[RIGHT] = FindSingleSourceMovesHelper(board, &rightSrc, p, numOfCaptures, false);
	}

	else if (rightRoute == MOVE_WITH_CAPTURE)
	{
		createNewSrc(&rightSrc, pSrc, p, RIGHT, MOVE_WITH_CAPTURE);
		source->next_moves[RIGHT] = FindSingleSourceMovesHelper(board, &rightSrc, p, numOfCaptures + 1, false);
	}

	if (leftRoute == MOVE_WITHOUT_CAPTURE)
	{
		createNewSrc(&leftSrc, pSrc, p, LEFT, MOVE_WITHOUT_CAPTURE);
		source->next_moves[LEFT] = FindSingleSourceMovesHelper(board, &leftSrc, p, numOfCaptures, false);
	}

	else if (leftRoute == MOVE_WITH_CAPTURE)
	{
		createNewSrc(&leftSrc, pSrc, p, LEFT, MOVE_WITH_CAPTURE);
		source->next_moves[LEFT] = FindSingleSourceMovesHelper(board, &leftSrc, p, numOfCaptures + 1, false);
	}

	return source;
}

// Creates new single source move tree node by assimilate inside: The board, his source position,
// number of captures so far and array with his next possible moves.
SingleSourceMovesTreeNode* createNewSingleSourceMovesTreeNode(Board board, checkersPos* pSrc,
	unsigned short numOfCaptures, SingleSourceMovesTreeNode* next_moves[])
{
	SingleSourceMovesTreeNode* newNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));

	if (!newNode)
	{
		printf("Memory Allocation Failure!!!");
		exit(1);
	}

	copyBoard(newNode->board, board);

	newNode->pos = pSrc;
	newNode->total_captures_so_far = numOfCaptures;

	if (next_moves == NULL)
	{
		newNode->next_moves[LEFT] = NULL;
		newNode->next_moves[RIGHT] = NULL;
	}
	else
	{
		newNode->next_moves[LEFT] = next_moves[LEFT];
		newNode->next_moves[RIGHT] = next_moves[RIGHT];
	}

	return newNode;
}

// Copy Board.
void copyBoard(Board newBoard, Board oldBoard)
{
	int i, j;
	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			newBoard[i][j] = oldBoard[i][j];
}

// Checks the all possible routes for specific source on board. 
int checkDiagonal(Board board, checkersPos* pSrc, Player p, unsigned short numOfCaptures, int dir, bool isFirstMove)
{
	int rowNum, colNum;

	rowNum = getRowNum(pSrc->row);
	colNum = getColNum(pSrc->col);

	// Checks if not first move and didn't capture yet.
	if (!numOfCaptures && !isFirstMove)
		return STUCK;

	// Checks if stuck after single move.
	if ((p == FIRST_PLAYER && dir == LEFT && colNum == FIRST_COL) ||
		(p == FIRST_PLAYER && dir == RIGHT && colNum == BOARD_SIZE - 1) ||
		(p == SECOND_PLAYER && dir == LEFT && colNum == BOARD_SIZE - 1) ||
		(p == SECOND_PLAYER && dir == RIGHT && colNum == FIRST_COL))
		return STUCK;

	// Checks if should move without capture.
	else if ((p == FIRST_PLAYER && dir == LEFT && board[rowNum + SINGLE_MOVE][colNum - SINGLE_MOVE] == EMPTY_PLACE && !numOfCaptures) ||
		(p == FIRST_PLAYER && dir == RIGHT && board[rowNum + SINGLE_MOVE][colNum + SINGLE_MOVE] == EMPTY_PLACE && !numOfCaptures) ||
		(p == SECOND_PLAYER && dir == LEFT && board[rowNum - SINGLE_MOVE][colNum + SINGLE_MOVE] == EMPTY_PLACE && !numOfCaptures) ||
		(p == SECOND_PLAYER && dir == RIGHT && board[rowNum - SINGLE_MOVE][colNum - SINGLE_MOVE] == EMPTY_PLACE && !numOfCaptures))
		return MOVE_WITHOUT_CAPTURE;

	// Checks if stuck after double move.
	else if ((p == FIRST_PLAYER && dir == LEFT && colNum == SECOND_COL) ||
		(p == FIRST_PLAYER && dir == RIGHT && colNum == BOARD_SIZE - 2) ||
		(p == SECOND_PLAYER && dir == LEFT && colNum == BOARD_SIZE - 2) ||
		(p == SECOND_PLAYER && dir == RIGHT && colNum == SECOND_COL))
		return STUCK;

	// Checks if should move and capture!
	else if ((p == FIRST_PLAYER && dir == LEFT && board[rowNum + SINGLE_MOVE][colNum - SINGLE_MOVE] == SECOND_PLAYER && board[rowNum + DOUBLE_MOVE][colNum - DOUBLE_MOVE] == ' ') ||
		(p == FIRST_PLAYER && dir == RIGHT && board[rowNum + SINGLE_MOVE][colNum + SINGLE_MOVE] == SECOND_PLAYER && board[rowNum + DOUBLE_MOVE][colNum + DOUBLE_MOVE] == ' ') ||
		(p == SECOND_PLAYER && dir == LEFT && board[rowNum - SINGLE_MOVE][colNum + SINGLE_MOVE] == FIRST_PLAYER && board[rowNum - DOUBLE_MOVE][colNum + DOUBLE_MOVE] == ' ') ||
		(p == SECOND_PLAYER && dir == RIGHT && board[rowNum - SINGLE_MOVE][colNum - SINGLE_MOVE] == FIRST_PLAYER && board[rowNum - DOUBLE_MOVE][colNum - DOUBLE_MOVE] == ' '))
		return MOVE_WITH_CAPTURE;

	return STUCK;
}

// Creates new position by the data that was given - player, his direction and how many steps he wants to move. 
void createNewSrc(checkersPos* res, checkersPos* pSrc, Player p, int dir, int steps)
{
	if (p == FIRST_PLAYER && dir == LEFT)
	{
		res->row = pSrc->row + steps;
		res->col = pSrc->col - steps;
	}

	else if (p == FIRST_PLAYER && dir == RIGHT)
	{
		res->row = pSrc->row + steps;
		res->col = pSrc->col + steps;
	}

	else if (p == SECOND_PLAYER && dir == LEFT)
	{
		res->row = pSrc->row - steps;
		res->col = pSrc->col + steps;
	}

	else if (p == SECOND_PLAYER && dir == RIGHT)
	{
		res->row = pSrc->row - steps;
		res->col = pSrc->col - steps;
	}
}

// Change row from char to int.
int getRowNum(char rowChar)
{
	return rowChar - 'A';
}

// Change column from char to int.
int getColNum(char colNum)
{
	return colNum - '1';
}