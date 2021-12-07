#ifndef _BOAED_H_
#define _BOAED_H_

#include <iostream>
#include <graphics.h>
#include <time.h>
#include <string>
//#include <conio.h>
//手动调节
constexpr auto WINDOS_X = 1600;										//窗口宽
constexpr auto WINDOS_Y = 900;										//窗口高
constexpr auto BOARD_SIZE = 800;									//棋盘大小
constexpr auto LINE = 16;											//20x20格
constexpr auto TIME = 30;											//30秒
//AUTO
constexpr auto BOARD_CORNER_X = (WINDOS_X - BOARD_SIZE) / 2;		//棋盘左上角坐标x
constexpr auto BOARD_CORNER_Y = (WINDOS_Y - BOARD_SIZE) / 2;		//棋盘左上角坐标y
constexpr auto GRID = BOARD_SIZE / LINE;							//格子边长
constexpr auto RADIUS = GRID / 2 - 2;								//棋子半径

class Board {
public:
	int record[LINE][LINE];			//棋盘上现有棋子 0无1黑2白
	bool black;						//下棋顺序
	Board();
	void main_thread();             //主线程
	void welcome();					//开始界面
	void draw_board();				//绘制棋盘
	void draw_time();				//30秒倒计时
	void fight();					//下棋！
	bool dice();					//骰子
	bool judge(int x, int y);		//裁判
};

#endif // _BOAED_H_