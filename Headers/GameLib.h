#ifndef __GAME_LIB_H
#define __GAME_LIB_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <TreeLib.h>
#include <ListLib.h>

#define BOARD_SIZE 8

#define FIRST_PLAYER 'T'
#define SECOND_PLAYER 'B'
#define EMPTY_PLACE ' '

#define LEFT 0
#define RIGHT 1
#define UP -1
#define DOWN 1

#define SINGLE_MOVE 1
#define DOUBLE_MOVE 2

#define STUCK 0
#define MOVE_WITHOUT_CAPTURE 1
#define MOVE_WITH_CAPTURE 2

#define FIRST_COL 0
#define SECOND_COL 1
#define FIRST_ROW 0
#define SECOND_ROW 1

#define ISWITHCAPTURE(toCapture) (((toCapture) == (MOVE_WITH_CAPTURE)) ? 1 : 0)
#define COL_MOVE(p, dir) ( (p) == FIRST_PLAYER ) ? ( ( (dir) == RIGHT ) ? (RIGHT) : (LEFT - 1) ) :\
												   ( ( (dir) == RIGHT ) ? (LEFT - 1) : (RIGHT) )
#define ROW_MOVE(p) ((p) == FIRST_PLAYER) ? DOWN : UP
#define ROW_CHAR_TO_NUM(row) ((row) - 'A')
#define COL_CHAR_TO_NUM(col) ((col) - '1')

typedef struct _checkersPos
{
	char row, col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

// Game Multifunctional Prototypes:
void buildBoard(Board board);
void copyBoard(Board newBoard, Board oldBoard); // ???

Player getPlayerFromPos(Board board, checkersPos* pSrc);
int getRowNum(char rowChar); // Delete because of Macro??
int getColNum(char colNum); // Delete because of Macro??

// Q1
Player getPlayerFromPos(Board board, checkersPos* pSrc);
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* pSrc);
SingleSourceMovesTreeNode* FindSingleSourceMovesHelper(Board board, checkersPos* pSrc,
	Player p, unsigned short numOfCaptures, bool isFirstMove);
SingleSourceMovesTreeNode* createNewSingleSourceMovesTreeNode(Board board, checkersPos* pSrc,
	unsigned short numOfCaptures, SingleSourceMovesTreeNode* next_moves[]);
void createNewBoard(Board res, Board oldBoard, checkersPos* pSrc, Player p, int dir, int steps);
int checkDiagonal(Board board, checkersPos* pSrc, Player p, unsigned short numOfCaptures, int dir, bool isFirstMove);
void createNewSrc(checkersPos* res, checkersPos* pSrc, Player p, int dir, int steps);

//Q2
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
SingleSourceMovesList* FindSingleSourceOptimalMoveHelperT(SingleSourceMovesTreeNode* root);
SingleSourceMovesList* FindSingleSourceOptimalMoveHelperB(SingleSourceMovesTreeNode* root);

#endif // !__GAME_LIB_H