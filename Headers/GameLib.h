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

typedef struct _checkersPos
{
	char row, col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

// Game Prototypes:
void buildBoard(Board board);
void copyBoard(Board newBoard, Board oldBoard);

Player getPlayerFromPos(Board board, checkersPos* pSrc);
int getRowNum(char rowChar);
int getColNum(char colNum);