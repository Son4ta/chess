/*******************************************
 * 武汉工程大学20智能科学与技术一班 Son4ta
 * 五子棋 for C++ (Ver:2021年12月9日)
 * https://github.com/Son4ta/chess
 *
 *			Power by Son4ta
 *******************************************/
#ifndef _BOAED_H_
#define _BOAED_H_

#include <iostream>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <stack>

using namespace std;
//#include <conio.h>
//手动调节
constexpr auto WINDOS_X = 1600;										//窗口宽
constexpr auto WINDOS_Y = 900;										//窗口高
constexpr auto BOARD_SIZE = 800;									//棋盘大小
constexpr auto LINE = 16;											//20x20格
constexpr auto TIME = 30;											//30秒
constexpr auto DECORATE = 15;										//装饰线
constexpr auto FIX = 4;												//修正
constexpr auto WARNING = 9;											//警告时间
//AUTO
constexpr auto BOARD_CORNER_X = (WINDOS_X - BOARD_SIZE) / 2;		//棋盘左上角坐标x
constexpr auto BOARD_CORNER_Y = (WINDOS_Y - BOARD_SIZE) / 2;		//棋盘左上角坐标y
constexpr auto GRID = BOARD_SIZE / LINE;							//格子边长
constexpr auto RADIUS = GRID / 2 - 2;								//棋子半径

class Board {
public:
	int record[LINE + 1][LINE + 1];		//棋盘上现有棋子 0无1黑2白 有16格=有17个点可以下
	int who_win;						//1黑赢2白赢
	int who;							//谁在下棋？
	int num;							//时间
	int sum_time;						//总时间
	int account;						//总共有多少棋子辣？
	stack <pair<int, int>> step;		//记录每一步坐标的栈
	Board();

	void main_thread();					// 主线程
	void welcome();						//开始界面
	void display_rule();				//展示规则画面
	void draw_board();					//绘制棋盘
	bool time_judge();					//30秒倒计时
	void fight();						//下棋！
	void dice();						//骰子
	bool locate(int x, int y);			//落子，返回值为是否落子成功，即无重复落子
	void judge(int location_x, int location_y);			//裁判
	void renew_board();
	void win();							//结算动画
	void traceback();					//回溯悔棋
	void review();						//复盘画面
};
#endif // _BOAED_H_