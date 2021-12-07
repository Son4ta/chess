#include"Board.h"

Board::Board()
{
	//棋盘所有位置初始化为0
	for (int i = 0; i <= LINE; i++) {
		for (int j = 0; j <= LINE; j++) {
			record[i][j] = 0;
		}
	}
	who = 0;
	who_win = 0;
}

void Board::main_thread()
{
	initgraph(1600, 900);				//窗口初始化
	setbkcolor(RGB(30, 30, 30));		//更新背景颜色
	cleardevice();
	dice();						//调用骰子函数
	Sleep(3000);
	draw_board();
	fight();
	Sleep(1000);
}

void Board::welcome()
{
}

void Board::draw_board()
{
	//绘制棋盘线
	cleardevice();
	//绘制边线
	BeginBatchDraw();
	for (int i = 0; i != BOARD_SIZE; i += 4) {
		line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X + i, BOARD_CORNER_Y);
		line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X, BOARD_CORNER_Y + i);
		line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE - i, BOARD_CORNER_Y + BOARD_SIZE);
		line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE - i);
		Sleep(1);
		FlushBatchDraw();
	}
	EndBatchDraw();
	Sleep(20);
	//绘制格子，闪动效果
	BeginBatchDraw();
	for (int j = 0; j <= 255; j++) {
		setlinecolor(RGB(j, j, j));
		for (int i = 0; i <= LINE; i++) {
			line(BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y, BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y + BOARD_SIZE);
			line(BOARD_CORNER_X, BOARD_CORNER_Y + i * GRID, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + i * GRID);
		}
		FlushBatchDraw();
	}
	for (int j = 255; j >= 0; j--) {
		setlinecolor(RGB(j, j, j));
		for (int i = 0; i <= LINE; i++) {
			line(BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y, BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y + BOARD_SIZE);
			line(BOARD_CORNER_X, BOARD_CORNER_Y + i * GRID, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + i * GRID);
		}
		FlushBatchDraw();
	}
	for (int j = 0; j <= 255; j++) {
		setlinecolor(RGB(j, j, j));
		for (int i = 0; i <= LINE; i++) {
			line(BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y, BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y + BOARD_SIZE);
			line(BOARD_CORNER_X, BOARD_CORNER_Y + i * GRID, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + i * GRID);
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	//绘制两边信息
}

void Board::fight()
{
	ExMessage mouse;		// 定义消息变量
	while (!who_win)		//我超，没人赢，都在演是吧
	{
		mouse = getmessage(EM_MOUSE | EM_KEY);	// 获取一条鼠标或按键消息

		switch (mouse.message)
		{
		case WM_LBUTTONDOWN:
			// 如果点左键
			locate(mouse.x, mouse.y);			//交给judge函数判断落子位置与输赢
			who = (who == 1) ? 2 : 1;			//切换执棋者
			break;

		case WM_KEYDOWN:
			if (mouse.vkcode == VK_ESCAPE)
				break;							// 按 ESC 键退出程序
		}
	}
}

void Board::dice()
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
	outtextxy(190, 350, _T('0' + white));
	settextcolor(RGB(250, 135, 35));	//字体颜色设置
	outtextxy(1250, 350, _T('0' + black));
	who = (black > white) ? 1 : 2;
	RECT r = { 0, 0, 1600, 900 };
	settextstyle(50, 0, _T("黑体"));	//在屏幕中间打印结果
	if (who == 1) {
		settextcolor(RGB(109, 109, 109));
		drawtext(_T("黑方先手！对弈即将开始"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		settextcolor(RGB(240, 240, 240));
		drawtext(_T("白方先手！对弈即将开始"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

bool Board::locate(int x, int y)
{
	int location_x = 0, location_y = 0;			//棋子最后位置
	int correct_x = 0, correct_y = 0;			//对最后位置（lacation）的修正量
	//坐标变换，以棋盘左上角为原点↓y→x
	location_x = (x - BOARD_CORNER_X) / GRID;	//获取鼠标点击位置左上方最近的点来确定格子
	location_y = (y - BOARD_CORNER_Y) / GRID;	//此时用户可能想在格子的任意一角下棋，进一步判断
	//计算点击位置最近的一角，确定修正量
	correct_x = ((x - BOARD_CORNER_X) - (location_x * GRID)) / (GRID / 2);
	correct_y = ((y - BOARD_CORNER_Y) - (location_y * GRID)) / (GRID / 2);
	//修正location
	location_x += correct_x;
	location_y += correct_y;
	//在记录中更新棋盘中的棋子
	record[location_x][location_y] = who;
	//判断输赢
	judge(location_x, location_y);
	//更新棋盘
	renew_board();
	return false;
}

void Board::judge(int location_x, int location_y) {
	//判断输赢
	int count = 0;
	//左右
	for (int i = location_x; record[i][location_y] == who && (i >= 0 && i <= LINE); i++) {
		count++;
	}
	for (int i = location_x; record[i][location_y] == who && (i >= 0 && i <= LINE); i--) {
		count++;
	}
	count -= 1;				//减去自身重复计算
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//重置计数器
	//上下
	for (int i = location_y; record[location_x][i] == who && (i >= 0 && i <= LINE); i++) {
		count++;
	}
	for (int i = location_y; record[location_x][i] == who && (i >= 0 && i <= LINE); i--) {
		count++;
	}
	count -= 1;				//减去自身重复计算
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//重置计数器
	//主对角线
	for (int i = location_x, j = location_y; record[i][j] == who && (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE); i++, j++) {
		count++;
	}
	for (int i = location_x, j = location_y; record[i][j] == who && (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE); i--, j--) {
		count++;
	}
	count -= 1;				//减去自身重复计算
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//重置计数器
	//次对角线
	for (int i = location_x, j = location_y; record[i][j] == who && (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE); i++, j--) {
		count++;
	}
	for (int i = location_x, j = location_y; record[i][j] == who && (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE); i--, j++) {
		count++;
	}
	count -= 1;				//减去自身重复计算
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//重置计数器
}

void Board::renew_board()
{
	for (int i = 0; i <= LINE; i++) {
		for (int j = 0; j <= LINE; j++) {
			if (record[i][j] == 1) {
				setfillcolor(BLACK);
				fillcircle(i * GRID + BOARD_CORNER_X, j * GRID + BOARD_CORNER_Y, RADIUS);
			}
			if (record[i][j] == 2) {
				setfillcolor(WHITE);
				fillcircle(i * GRID + BOARD_CORNER_X, j * GRID + BOARD_CORNER_Y, RADIUS);
			}
		}
	}
}