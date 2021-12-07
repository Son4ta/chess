#ifndef _BOAED_H_
#define _BOAED_H_

#include <iostream>
#include <graphics.h>
#include <time.h>
#include <conio.h>

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
#define MAXSTAR 2000	// 星星总数
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
	int count;							//总共有多少棋子辣？
	Board();
	void main_thread();					// 主线程
	void welcome();						//开始界面
	void draw_board();					//绘制棋盘
	bool time_judge();					//30秒倒计时
	void fight();						//下棋！
	void dice();						//骰子
	bool locate(int x, int y);			//落子，返回值为是否落子成功，即无重复落子
	void judge(int location_x, int location_y);			//裁判
	void renew_board();
	void win();							//结算动画
};

//class Star {
//public:
//	struct STAR
//	{
//		double	x;
//		int		y;
//		double	step;
//		int		color;
//	};
//
//	STAR star[MAXSTAR];
//
//	// 初始化星星
//	void InitStar(int i)
//	{
//		star[i].x = 0;
//		star[i].y = rand() % 900;
//		star[i].step = (rand() % 5000) / 1000.0 + 1;
//		star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
//		star[i].color = RGB(star[i].color, star[i].color, star[i].color);
//	}
//
//	// 移动星星
//	void MoveStar(int i)
//	{
//		// 擦掉原来的星星
//		putpixel((int)star[i].x, star[i].y, 0);
//
//		// 计算新位置
//		star[i].x += star[i].step;
//		if (star[i].x > 1600)	InitStar(i);
//
//		// 画新星星
//		putpixel((int)star[i].x, star[i].y, star[i].color);
//	}
//
//	// 主函数
//	void star_main()
//	{
//		srand((unsigned)time(NULL));	// 随机种子
//		// 初始化所有星星
//		for (int i = 0; i < MAXSTAR; i++)
//		{
//			InitStar(i);
//			star[i].x = rand() % 1600;
//		}
//
//		// 绘制星空，按任意键退出
//		while (!_kbhit())
//		{
//			for (int i = 0; i < MAXSTAR; i++)
//				MoveStar(i);
//			Sleep(20);
//		}
//	}
//};
#endif // _BOAED_H_