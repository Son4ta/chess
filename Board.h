#ifndef _BOAED_H_
#define _BOAED_H_

#include <iostream>
#include <graphics.h>
#include <time.h>
#include <string>
#include <sstream>
using namespace std;
//#include <conio.h>
//�ֶ�����
constexpr auto WINDOS_X = 1600;										//���ڿ�
constexpr auto WINDOS_Y = 900;										//���ڸ�
constexpr auto BOARD_SIZE = 800;									//���̴�С
constexpr auto LINE = 16;											//20x20��
constexpr auto TIME = 30;											//30��
constexpr auto DECORATE = 15;										//װ����
constexpr auto FIX = 4;												//����
//AUTO
constexpr auto BOARD_CORNER_X = (WINDOS_X - BOARD_SIZE) / 2;		//�������Ͻ�����x
constexpr auto BOARD_CORNER_Y = (WINDOS_Y - BOARD_SIZE) / 2;		//�������Ͻ�����y
constexpr auto GRID = BOARD_SIZE / LINE;							//���ӱ߳�
constexpr auto RADIUS = GRID / 2 - 2;								//���Ӱ뾶

class Board {
public:
	int record[LINE + 1][LINE + 1];		//�������������� 0��1��2�� ��16��=��17���������
	int who_win;						//1��Ӯ2��Ӯ
	int who;							//˭�����壿
	int num;							//ʱ��
	int sum_time;						//��ʱ��
	Board();
	void main_thread();					// ���߳�
	void welcome();						//��ʼ����
	void draw_board();					//��������
	bool time_judge();					//30�뵹��ʱ
	void fight();						//���壡
	void dice();						//����
	bool locate(int x, int y);			//���ӣ�����ֵΪ�Ƿ����ӳɹ��������ظ�����
	void judge(int location_x, int location_y);			//����
	void renew_board();
	void win();							//���㶯��
};

#endif // _BOAED_H_