#ifndef _BOAED_H_
#define _BOAED_H_

#include <iostream>
#include <graphics.h>
#include <time.h>
#include <string>
//#include <conio.h>
//�ֶ�����
constexpr auto WINDOS_X = 1600;										//���ڿ�
constexpr auto WINDOS_Y = 900;										//���ڸ�
constexpr auto BOARD_SIZE = 800;									//���̴�С
constexpr auto LINE = 16;											//20x20��
constexpr auto TIME = 30;											//30��
//AUTO
constexpr auto BOARD_CORNER_X = (WINDOS_X - BOARD_SIZE) / 2;		//�������Ͻ�����x
constexpr auto BOARD_CORNER_Y = (WINDOS_Y - BOARD_SIZE) / 2;		//�������Ͻ�����y
constexpr auto GRID = BOARD_SIZE / LINE;							//���ӱ߳�
constexpr auto RADIUS = GRID / 2 - 2;								//���Ӱ뾶

class Board {
public:
	int record[LINE][LINE];			//�������������� 0��1��2��
	bool black;						//����˳��
	Board();
	void main_thread();             //���߳�
	void welcome();					//��ʼ����
	void draw_board();				//��������
	void draw_time();				//30�뵹��ʱ
	void fight();					//���壡
	bool dice();					//����
	bool judge(int x, int y);		//����
};

#endif // _BOAED_H_