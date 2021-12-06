#include"Board.h"

Board::Board()
{
	record[0][0] = { 0 };//棋盘所有位置初始化为0
	black = false;
}

bool Board::dice()
{
	int black, white;

	srand((unsigned)time(NULL));//随机数种

	black = rand() % 6 + 1;	//骰子
	white = rand() % 6 + 1;
	return black > white;
}

bool Board::judge(int x, int y)
{
	return false;
}