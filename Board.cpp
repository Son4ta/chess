#include"Board.h"
//TODO:复盘结束条件
//TODO:规则显示
Board::Board()
{
	//棋盘所有位置初始化为0
	for (int i = 0; i <= LINE; i++) {
		for (int j = 0; j <= LINE; j++) {
			record[i][j] = 0;
		}
	}
	who = 1;
	who_win = 0;
	num = 0;
	sum_time = 0;
	account = 0;
}

void Board::main_thread()
{
	initgraph(1600, 900);				//窗口初始化
	setbkcolor(RGB(40, 40, 40));		//更新背景颜色
	welcome();
	cleardevice();
	dice();								//调用骰子函数
	Sleep(3000);
	display_rule();
	Sleep(5000);
	draw_board();
	fight();
	Sleep(1000);
	win();
	Sleep(4000);
	review();
}

void Board::welcome()
{
	while (!_kbhit()) {
		for (int i = 0; i <= 40; i += 1) {
			setbkcolor(RGB(i, i, i));		//更新背景颜色
			RECT r = { 0, WINDOS_Y / 4 , WINDOS_X, (WINDOS_Y / 4) * 3 };
			settextstyle(120, 0, _T("黑体"));	//字体设置
			settextcolor(RGB(255, 255, 255));	//字体颜色设置
			drawtext(_T("Five in a Row"), &r, DT_CENTER | DT_VCENTER);

			r = { 0, WINDOS_Y / 4 + 200, WINDOS_X, (WINDOS_Y / 4) * 3 + 200 };
			settextstyle(40, 0, _T("黑体"));	//字体设置
			drawtext(_T("按空格键来投掷骰子开始游戏"), &r, DT_CENTER | DT_VCENTER);
			//cleardevice();

			r = { 0, WINDOS_Y / 4 + 600, WINDOS_X, (WINDOS_Y / 4) * 3 + 600 };
			settextstyle(40, 0, _T("黑体"));	//字体设置
			drawtext(_T("Power by Son4ta"), &r, DT_CENTER | DT_VCENTER);
			//cleardevice();
			Sleep(1);
		}
		for (int i = 40; i >= 0; i -= 1) {
			setbkcolor(RGB(i, i, i));		//更新背景颜色
			RECT r = { 0, WINDOS_Y / 4, WINDOS_X, (WINDOS_Y / 4) * 3 };
			settextstyle(120, 0, _T("黑体"));	//字体设置
			settextcolor(RGB(255, 255, 255));	//字体颜色设置
			drawtext(_T("Five in a Row"), &r, DT_CENTER | DT_VCENTER);

			r = { 0, WINDOS_Y / 4 + 200, WINDOS_X, (WINDOS_Y / 4) * 3 + 200 };
			settextstyle(40, 0, _T("黑体"));	//字体设置
			drawtext(_T("按空格键来投掷骰子开始游戏"), &r, DT_CENTER | DT_VCENTER);
			//cleardevice();

			r = { 0, WINDOS_Y / 4 + 600, WINDOS_X, (WINDOS_Y / 4) * 3 + 600 };
			settextstyle(40, 0, _T("黑体"));	//字体设置
			drawtext(_T("Power by Son4ta"), &r, DT_CENTER | DT_VCENTER);
			//cleardevice();
			Sleep(1);
		}
	}
	for (int i = 0; i <= 40; i += 1) {
		setbkcolor(RGB(i, i, i));		//更新背景颜色
		cleardevice();
		Sleep(1);
	}
}

void Board::display_rule()
{
	wchar_t t[10];							//数字转字符串
	_itow_s(TIME, t, 10, 10);
	t[2] = 'S'; t[3] = '\0';
	wstring str(t);

	cleardevice();
	settextstyle(50, 0, _T("黑体"));	//字体设置
	settextcolor(RGB(255, 255, 255));	//字体颜色设置
	RECT r = { 0, BOARD_CORNER_Y, WINDOS_X, BOARD_CORNER_Y + 100 };
	drawtext(_T("1.五枚棋子连成一线或一方时间耗尽则游戏结束"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, BOARD_CORNER_Y + 200, WINDOS_X, BOARD_CORNER_Y + 300 };
	drawtext(_T("2.在游戏过程中按 Z 键悔棋，按 ESC 直接结束游戏"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, BOARD_CORNER_Y + 400, WINDOS_X, BOARD_CORNER_Y + 500 };
	drawtext(_T("3.本局游戏对弈每步最大用时为"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, BOARD_CORNER_Y + 500, WINDOS_X, BOARD_CORNER_Y + 600 };
	drawtext(t, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Board::draw_board()
{
	//绘制棋盘线
	cleardevice();
	for (int i = 40; i <= 150; i += 1) {
		setbkcolor(RGB(i, i, i));		//更新背景颜色
		Sleep(1);
		cleardevice();
	}
	BeginBatchDraw();
	for (int i = 0; i != BOARD_SIZE; i += 10) {
		setlinecolor(RGB(255, 255, 255));
		setlinestyle(PS_SOLID, 3);
		//绘制边线
		line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X + i, BOARD_CORNER_Y);
		line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X, BOARD_CORNER_Y + i);
		line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE - i, BOARD_CORNER_Y + BOARD_SIZE);
		line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE - i);
		//绘制装饰线
		line(BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y - DECORATE, BOARD_CORNER_X + i + DECORATE + FIX, BOARD_CORNER_Y - DECORATE);
		line(BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y - DECORATE, BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y + i + DECORATE + FIX);
		line(BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE, BOARD_CORNER_X + BOARD_SIZE - i - DECORATE - FIX, BOARD_CORNER_Y + BOARD_SIZE + DECORATE);
		line(BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE, BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE - i - DECORATE - FIX);
		Sleep(1);
		FlushBatchDraw();
	}
	EndBatchDraw();
	setlinestyle(PS_SOLID, 1);
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

bool Board::time_judge()
{
	if (num == -1) {						//超时！对方胜
		who_win = (who == 1) ? 2 : 1;
		return false;
	}

	wchar_t c[10];							//数字转字符串
	_itow_s(num, c, 10, 10);
	wstring str(c);

	if (who == 2) {
		RECT r = { 50, 50, 350, 150 };
		settextstyle(50, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(255, 255, 255));	//字体颜色设置
		drawtext(_T("等待白方执棋"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		r = { 50, 150, 350, 250 };
		settextstyle(70, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(255, 255, 255));	//字体颜色设置
		if (num <= WARNING) {
			settextstyle(125, 0, _T("黑体"));
			settextcolor(RGB(254, 63, 66));
		}
		drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		RECT r = { 1250, 50, 1550, 150 };
		settextstyle(50, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(0, 0, 0));	//字体颜色设置
		drawtext(_T("等待黑方执棋"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		r = { 1250, 150, 1550, 250 };
		settextstyle(70, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(0, 0, 0));	//字体颜色设置
		if (num <= WARNING) {
			settextstyle(125, 0, _T("黑体"));
			settextcolor(RGB(254, 63, 66));
		}
		drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	settextstyle(50, 0, _T("黑体"));
	return true;
}

void Board::fight()
{
	ExMessage mouse;								// 定义消息变量
	clock_t start = clock(), end = clock();			//计时用
	num = TIME - ((end - start) / 1000);			//初始化计时器避免一开始就闪红字
	cleardevice(); renew_board();
	flushmessage();									//刷新缓冲区防止还没开始就有棋子
	while (!who_win && time_judge() && account != LINE * LINE)//我超，没人赢，都在演是吧
	{
		end = clock();								//计时器
		peekmessage(&mouse, EM_MOUSE | EM_KEY);		// 获取一条鼠标或按键消息
		num = TIME - ((end - start) / 1000);		//计时器
		switch (mouse.message)
		{
		case WM_LBUTTONDOWN:
			// 如果点左键
			if (locate(mouse.x, mouse.y)) {			//交给judge函数判断落子位置与输赢
				who = (who == 1) ? 2 : 1;			//切换执棋者
				sum_time += (end - start);			//计时
				start = clock();					//重置计时器
				end = clock();
				num = TIME - ((end - start) / 1000);//初始化计时器
				flushmessage();						//刷新缓冲区
			}
			break;

		case WM_KEYDOWN:
			//如果有键被按下
			//if (mouse.ctrl) {
			if (mouse.vkcode == 90) {
				if (account != 0) {
					traceback();						//按 Z 键撤回一步
					who = (who == 1) ? 2 : 1;			//切换执棋者
					start = clock();					//重置计时器
					end = clock();
					num = TIME - ((end - start) / 1000);//初始化计时器
					flushmessage();						//刷新缓冲区
					mouse.vkcode = -1;
				}
			}
			if (mouse.vkcode == VK_ESCAPE)				// 按 ESC 键退出程序
				return;
			break;
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
	//已有棋子就退出
	if (record[location_x][location_y] != 0) {
		return false;
	}
	//x坐标非法
	if ((location_x > LINE) || (location_x < 0)) {
		return false;
	}
	//y坐标非法
	if ((location_y > LINE) || (location_y < 0)) {
		return false;
	}
	//在记录中更新棋盘中的棋子
	record[location_x][location_y] = who;
	//记录下此步棋（入栈）
	step.push(pair<int, int>(location_x, location_y));
	//判断输赢
	judge(location_x, location_y);
	//记录棋子个数
	account++;
	//更新棋盘
	cleardevice();
	renew_board();
	return true;
}

void Board::judge(int location_x, int location_y) {
	//判断输赢
	int count = 0;
	//左右
	for (int i = location_x; (i >= 0 && i <= LINE) && record[i][location_y] == who; i++) {
		count++;
	}
	for (int i = location_x; (i >= 0 && i <= LINE) && record[i][location_y] == who; i--) {
		count++;
	}
	count -= 1;				//减去自身重复计算
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//重置计数器
	//上下
	for (int i = location_y; (i >= 0 && i <= LINE) && record[location_x][i] == who; i++) {
		count++;
	}
	for (int i = location_y; (i >= 0 && i <= LINE) && record[location_x][i] == who; i--) {
		count++;
	}
	count -= 1;				//减去自身重复计算
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//重置计数器
	//主对角线
	for (int i = location_x, j = location_y; (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE) && record[i][j] == who; i++, j++) {
		count++;
	}
	for (int i = location_x, j = location_y; (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE) && record[i][j] == who; i--, j--) {
		count++;
	}
	count -= 1;				//减去自身重复计算
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//重置计数器
	//次对角线
	for (int i = location_x, j = location_y; (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE) && record[i][j] == who; i++, j--) {
		count++;
	}
	for (int i = location_x, j = location_y; (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE) && record[i][j] == who; i--, j++) {
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
	BeginBatchDraw();
	setlinestyle(PS_SOLID, 3);
	//重写绘制所有线
	line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y);
	line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X, BOARD_CORNER_Y + BOARD_SIZE);
	line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE - BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE);
	line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE - BOARD_SIZE);
	line(BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y - DECORATE, BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y - DECORATE);
	line(BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y - DECORATE, BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE);
	line(BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE, BOARD_CORNER_X + BOARD_SIZE - BOARD_SIZE - DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE);
	line(BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE, BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE - BOARD_SIZE - DECORATE);
	setlinestyle(PS_SOLID, 1);
	//绘制格子
	for (int i = 0; i <= LINE; i++) {
		line(BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y, BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y + BOARD_SIZE);
		line(BOARD_CORNER_X, BOARD_CORNER_Y + i * GRID, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + i * GRID);
	}
	//重写绘制格子
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
	//标出最后一步的棋子
	if (account != 0) {
		int x = BOARD_CORNER_X + step.top().first * GRID, y = BOARD_CORNER_Y + step.top().second * GRID;
		setlinestyle(PS_SOLID, 3);
		setlinecolor(RGB(254, 63, 66));
		POINT pts1[] = { {x + RADIUS, y + RADIUS / 3}, {x + RADIUS, y + RADIUS}, {x + RADIUS / 3, y + RADIUS} };
		polyline(pts1, 3);
		POINT pts2[] = { {x - RADIUS, y + RADIUS / 3}, {x - RADIUS, y + RADIUS}, {x - RADIUS / 3, y + RADIUS} };
		polyline(pts2, 3);
		POINT pts3[] = { {x + RADIUS, y - RADIUS / 3}, {x + RADIUS, y - RADIUS}, {x + RADIUS / 3, y - RADIUS} };
		polyline(pts3, 3);
		POINT pts4[] = { {x - RADIUS, y - RADIUS / 3}, {x - RADIUS, y - RADIUS}, {x - RADIUS / 3, y - RADIUS} };
		polyline(pts4, 3);
		setlinecolor(WHITE);
		setlinestyle(PS_SOLID, 1);
	}
	EndBatchDraw();
}

void Board::win()
{
	BeginBatchDraw();
	if (who_win == 2) {
		for (int i = 150; i <= 220; i += 1) {
			renew_board();
			setbkcolor(RGB(i, i, i));		//更新背景颜色
			Sleep(5);
			cleardevice();
		}
		for (int i = 220; i >= 150; i -= 4) {
			setlinecolor(RGB(i, i, i));
			setfillcolor(RGB(i, i, i));
			fillrectangle(0, WINDOS_Y / 4, WINDOS_X, (WINDOS_Y / 4) * 3);
			Sleep(1);
		}
		RECT r = { 0, WINDOS_Y / 4, WINDOS_X, (WINDOS_Y / 4) * 3 };
		settextstyle(100, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(255, 255, 255));	//字体颜色设置
		drawtext(_T("白方棋手胜利"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	if (who_win == 1) {
		for (int i = 150; i >= 50; i -= 1) {
			renew_board();
			setbkcolor(RGB(i, i, i));		//更新背景颜色
			Sleep(1);
			cleardevice();
		}
		for (int i = 50; i <= 150; i += 4) {
			setlinecolor(RGB(i, i, i));
			setfillcolor(RGB(i, i, i));
			fillrectangle(0, WINDOS_Y / 4, WINDOS_X, (WINDOS_Y / 4) * 3);
			Sleep(1);
		}
		RECT r = { 0, WINDOS_Y / 4, WINDOS_X, (WINDOS_Y / 4) * 3 };
		settextstyle(100, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(0, 0, 0));	//字体颜色设置
		drawtext(_T("黑方棋手胜利"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	if (who_win == 0) {
		for (int i = 150; i >= 50; i -= 1) {
			renew_board();
			setbkcolor(RGB(i, i, i));		//更新背景颜色
			Sleep(1);
			cleardevice();
		}
		for (int i = 50; i <= 150; i += 4) {
			setlinecolor(RGB(i, i, i));
			setfillcolor(RGB(i, i, i));
			fillrectangle(0, WINDOS_Y / 4, WINDOS_X, (WINDOS_Y / 4) * 3);
			Sleep(1);
		}
		RECT r = { 0, WINDOS_Y / 4, WINDOS_X, (WINDOS_Y / 4) * 3 };
		settextstyle(100, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(0, 0, 0));	//字体颜色设置
		drawtext(_T("平局！胜负未分"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	EndBatchDraw();
}

void Board::traceback()
{
	//撤回最后一步
	record[step.top().first][step.top().second] = 0;
	//弹栈，删掉最后一步实现悔棋
	step.pop();
	//棋子减一
	account--;
	//刷新
	cleardevice();
	renew_board();
	//防止有人一直按着Z键
	Sleep(300);
}

void Board::review()
{
	RECT r = { 0, 0, 0, 0 };
	int x = 0, y = 0;
	//防止renew_board再画红框框
	int i = account;
	sum_time /= 1000;			//换算成秒
	account = 0;				//置0棋子数
	//重绘棋盘
	draw_board();
	renew_board();
	//给所有步标上顺序
	for (; i != 0 && !step.empty(); i--) {
		//记录坐标后弹栈
		x = BOARD_CORNER_X + step.top().first * GRID;
		y = BOARD_CORNER_Y + step.top().second * GRID;
		step.pop();
		//数字转字符串
		wchar_t c[10];
		_itow_s(i, c, 10, 10);
		wstring str(c);
		//字体设置
		settextstyle(45, 0, _T("黑体"));
		setbkmode(TRANSPARENT);
		settextcolor(RGB(254, 63, 66));//字体颜色设置
		r = { x + RADIUS, y + RADIUS,x - RADIUS, y - RADIUS };
		//如果大于100个棋子就打印成蓝色
		if (i >= 100) {
			settextstyle(30, 0, _T("黑体"));
			settextcolor(RGB(8, 118, 202));
			r = { x + 2 * RADIUS, y + 2 * RADIUS,x - 2 * RADIUS, y - 2 * RADIUS };
		}
		drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	//打印两边的字
	{
		r = { 1250, 50, 1550, 150 };
		settextstyle(50, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(0, 0, 0));	//字体颜色设置
		drawtext(_T("对弈复盘"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		r = { 50, 50, 350, 150 };
		settextstyle(50, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(255, 255, 255));	//字体颜色设置
		drawtext(_T("对弈总用时"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		r = { 0, 150, 550, 250 };
		settextstyle(70, 0, _T("黑体"));	//字体设置
		settextcolor(RGB(255, 255, 255));	//字体颜色设置
		wchar_t c[10];
		_itow_s(sum_time, c, 10, 10);
		wstring str(c);
		drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	system("pause");
}