#include <GameLib.h>

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

// Gets the player name from position.
Player getPlayerFromPos(Board board, checkersPos* pSrc)
{
	int rowNum, colNum;

	rowNum = ROW_CHAR_TO_INT(pSrc->row);
	colNum = COL_CHAR_TO_INT(pSrc->col);

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

// Recursive helper function to 'FindSingleSourceMoves'. Creates all the possible routes for single source. 
SingleSourceMovesTreeNode* FindSingleSourceMovesHelper(Board board, checkersPos* pSrc,
	Player p, unsigned short numOfCaptures, bool isFirstMove)
{
	SingleSourceMovesTreeNode* next_moves[2] = { NULL };
	int rightRoute, leftRoute;
	checkersPos* rightSrc, * leftSrc;
	Board rightBoard, leftBoard;

	rightRoute = checkDiagonal(board, pSrc, p, numOfCaptures, RIGHT, isFirstMove);
	leftRoute = checkDiagonal(board, pSrc, p, numOfCaptures, LEFT, isFirstMove);

	if (rightRoute != STUCK)
	{
		rightSrc = createNewCheckersPos(pSrc->row, pSrc->col, p, RIGHT, rightRoute);
		createNewBoard(rightBoard, board, pSrc, p, RIGHT, rightRoute);
		next_moves[RIGHT] = FindSingleSourceMovesHelper(rightBoard, rightSrc, p, numOfCaptures + ISWITHCAPTURE(rightRoute), false);
	}

	if (leftRoute != STUCK)
	{
		leftSrc = createNewCheckersPos(pSrc->row, pSrc->col, p, LEFT, leftRoute);
		createNewBoard(leftBoard, board, pSrc, p, LEFT, leftRoute);
		next_moves[LEFT] = FindSingleSourceMovesHelper(leftBoard, leftSrc, p, numOfCaptures + ISWITHCAPTURE(leftRoute), false);
	}

	return createNewSingleSourceMovesTreeNode(board, pSrc, numOfCaptures, next_moves);
}

// Creates new board by the data that was given - Old borad, new Board, player, his direction and how many steps he moved.
void createNewBoard(Board res, Board oldBoard, checkersPos* pSrc, Player p, int dir, int steps)
{
	int rowNum, colNum;

	rowNum = ROW_CHAR_TO_INT(pSrc->row);
	colNum = COL_CHAR_TO_INT(pSrc->col);

	memcpy(res, oldBoard, sizeof(char) * BOARD_SIZE * BOARD_SIZE);

	res[rowNum][colNum] = ' ';
	res[rowNum + (ROW_MOVE(p) * steps)][colNum + (COL_MOVE(p, dir) * steps)] = p;
	if (steps == DOUBLE_MOVE)
		res[rowNum + (ROW_MOVE(p))][colNum + (COL_MOVE(p, dir))] = ' ';
}

// Creates new position by the data that was given - row, column, player, his direction and how many steps he wants to move. 
checkersPos* createNewCheckersPos(int row, int col, Player p, int dir, int steps)
{
	checkersPos* res;

	res = (checkersPos*)malloc(sizeof(checkersPos));

	if (!res)
	{
		printf("Memory Allocation Failure!!!");
		exit(1);
	}

	res->row = row + (ROW_MOVE(p) * steps);
	res->col = col + (COL_MOVE(p, dir) * steps);

	return res;
}

// Checks the all possible routes for specific source on board. 
int checkDiagonal(Board board, checkersPos* pSrc, Player p, unsigned short numOfCaptures, int dir, bool isFirstMove)
{
	int rowNum, colNum;

	rowNum = ROW_CHAR_TO_INT(pSrc->row);
	colNum = COL_CHAR_TO_INT(pSrc->col);

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