#include"Board.h"

Board::Board()
{
	record[0][0] = { 0 };//��������λ�ó�ʼ��Ϊ0
	black = false;
}

bool Board::dice()
{
	int black, white;

	srand((unsigned)time(NULL));//�������

	black = rand() % 6 + 1;	//����
	white = rand() % 6 + 1;
	return black > white;
}

bool Board::judge(int x, int y)
{
	return false;
}