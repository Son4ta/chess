#include"Board.h"

Board::Board()
{
	record[0][0] = { 0 };//棋盘所有位置初始化为0
	black = false;
}

void Board::main_thread()
{
	initgraph(1600, 900);				//窗口初始化
	setbkcolor(RGB(30, 30, 30));		//更新背景颜色
	cleardevice();
	black = dice();						//调用骰子函数
	RECT r = { 0, 0, 1600, 900 };
	settextstyle(50, 0, _T("黑体"));	//在屏幕中间打印结果
	if (black) {
		settextcolor(RGB(109, 109, 109));
		drawtext(_T("黑方先手！对弈即将开始"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		settextcolor(RGB(240, 240, 240));
		drawtext(_T("白方先手！对弈即将开始"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	Sleep(3000);
}

void Board::welcome()
{
}

void Board::draw_board()
{
	for (int i = BOARD_CORNER_X, j = BOARD_CORNER_Y;)
}

bool Board::dice()
{
	int black, white;
	srand((unsigned)time(NULL));		//随机数种
	settextstyle(100, 0, _T("黑体"));	//字体设置
	settextcolor(RGB(240, 240, 240));	//字体颜色设置
	outtextxy(160, 165, _T("白棋"));	//打印白棋和黑棋
	settextcolor(RGB(109, 109, 109));	//字体颜色设置
	outtextxy(1220, 165, _T("黑棋"));
	settextstyle(300, 0, _T("黑体"));	//字体设置
	settextcolor(WHITE);				//字体颜色设置
	BeginBatchDraw();					//开始批量绘图让画面不闪动
	//骰子
	for (int i = 70; i < 100; i++) {
		black = rand() % 6 + 1;
		white = rand() % 6 + 1;
		while (black == white) {		//防止出现相等的尴尬局面
			black = rand() % 6 + 1;
			white = rand() % 6 + 1;
		}
		outtextxy(190, 350, _T('0' + black));
		outtextxy(1250, 350, _T('0' + white));
		Sleep(i);						//让数字跳动越来越慢
		FlushBatchDraw();
	}
	//HRGN rgn = CreateRectRgn(0, 390, 1600, 900);
	// 将该矩形区域设置为裁剪区
	//setcliprgn(rgn);
	//clearcliprgn();
	//DeleteObject(rgn);
	EndBatchDraw();
	settextcolor(RGB(8, 118, 202));		//字体颜色设置
	outtextxy(190, 350, _T('0' + black));
	settextcolor(RGB(250, 135, 35));	//字体颜色设置
	outtextxy(1250, 350, _T('0' + white));
	return black > white;				//返回先手
}

bool Board::judge(int x, int y)
{
	return false;
}