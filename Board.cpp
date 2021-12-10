#include"Board.h"
//TODO:���̽�������
//TODO:������ʾ
Board::Board()
{
	//��������λ�ó�ʼ��Ϊ0
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
	initgraph(1600, 900);				//���ڳ�ʼ��
	setbkcolor(RGB(40, 40, 40));		//���±�����ɫ
	welcome();
	cleardevice();
	dice();								//�������Ӻ���
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
			setbkcolor(RGB(i, i, i));		//���±�����ɫ
			RECT r = { 0, WINDOS_Y / 4 , WINDOS_X, (WINDOS_Y / 4) * 3 };
			settextstyle(120, 0, _T("����"));	//��������
			settextcolor(RGB(255, 255, 255));	//������ɫ����
			drawtext(_T("Five in a Row"), &r, DT_CENTER | DT_VCENTER);

			r = { 0, WINDOS_Y / 4 + 200, WINDOS_X, (WINDOS_Y / 4) * 3 + 200 };
			settextstyle(40, 0, _T("����"));	//��������
			drawtext(_T("���ո����Ͷ�����ӿ�ʼ��Ϸ"), &r, DT_CENTER | DT_VCENTER);
			//cleardevice();

			r = { 0, WINDOS_Y / 4 + 600, WINDOS_X, (WINDOS_Y / 4) * 3 + 600 };
			settextstyle(40, 0, _T("����"));	//��������
			drawtext(_T("Power by Son4ta"), &r, DT_CENTER | DT_VCENTER);
			//cleardevice();
			Sleep(1);
		}
		for (int i = 40; i >= 0; i -= 1) {
			setbkcolor(RGB(i, i, i));		//���±�����ɫ
			RECT r = { 0, WINDOS_Y / 4, WINDOS_X, (WINDOS_Y / 4) * 3 };
			settextstyle(120, 0, _T("����"));	//��������
			settextcolor(RGB(255, 255, 255));	//������ɫ����
			drawtext(_T("Five in a Row"), &r, DT_CENTER | DT_VCENTER);

			r = { 0, WINDOS_Y / 4 + 200, WINDOS_X, (WINDOS_Y / 4) * 3 + 200 };
			settextstyle(40, 0, _T("����"));	//��������
			drawtext(_T("���ո����Ͷ�����ӿ�ʼ��Ϸ"), &r, DT_CENTER | DT_VCENTER);
			//cleardevice();

			r = { 0, WINDOS_Y / 4 + 600, WINDOS_X, (WINDOS_Y / 4) * 3 + 600 };
			settextstyle(40, 0, _T("����"));	//��������
			drawtext(_T("Power by Son4ta"), &r, DT_CENTER | DT_VCENTER);
			//cleardevice();
			Sleep(1);
		}
	}
	for (int i = 0; i <= 40; i += 1) {
		setbkcolor(RGB(i, i, i));		//���±�����ɫ
		cleardevice();
		Sleep(1);
	}
}

void Board::display_rule()
{
	wchar_t t[10];							//����ת�ַ���
	_itow_s(TIME, t, 10, 10);
	t[2] = 'S'; t[3] = '\0';
	wstring str(t);

	cleardevice();
	settextstyle(50, 0, _T("����"));	//��������
	settextcolor(RGB(255, 255, 255));	//������ɫ����
	RECT r = { 0, BOARD_CORNER_Y, WINDOS_X, BOARD_CORNER_Y + 100 };
	drawtext(_T("1.��ö��������һ�߻�һ��ʱ��ľ�����Ϸ����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, BOARD_CORNER_Y + 200, WINDOS_X, BOARD_CORNER_Y + 300 };
	drawtext(_T("2.����Ϸ�����а� Z �����壬�� ESC ֱ�ӽ�����Ϸ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, BOARD_CORNER_Y + 400, WINDOS_X, BOARD_CORNER_Y + 500 };
	drawtext(_T("3.������Ϸ����ÿ�������ʱΪ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	r = { 0, BOARD_CORNER_Y + 500, WINDOS_X, BOARD_CORNER_Y + 600 };
	drawtext(t, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void Board::draw_board()
{
	//����������
	cleardevice();
	for (int i = 40; i <= 150; i += 1) {
		setbkcolor(RGB(i, i, i));		//���±�����ɫ
		Sleep(1);
		cleardevice();
	}
	BeginBatchDraw();
	for (int i = 0; i != BOARD_SIZE; i += 10) {
		setlinecolor(RGB(255, 255, 255));
		setlinestyle(PS_SOLID, 3);
		//���Ʊ���
		line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X + i, BOARD_CORNER_Y);
		line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X, BOARD_CORNER_Y + i);
		line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE - i, BOARD_CORNER_Y + BOARD_SIZE);
		line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE - i);
		//����װ����
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
	//���Ƹ��ӣ�����Ч��
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
	//����������Ϣ
}

bool Board::time_judge()
{
	if (num == -1) {						//��ʱ���Է�ʤ
		who_win = (who == 1) ? 2 : 1;
		return false;
	}

	wchar_t c[10];							//����ת�ַ���
	_itow_s(num, c, 10, 10);
	wstring str(c);

	if (who == 2) {
		RECT r = { 50, 50, 350, 150 };
		settextstyle(50, 0, _T("����"));	//��������
		settextcolor(RGB(255, 255, 255));	//������ɫ����
		drawtext(_T("�ȴ��׷�ִ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		r = { 50, 150, 350, 250 };
		settextstyle(70, 0, _T("����"));	//��������
		settextcolor(RGB(255, 255, 255));	//������ɫ����
		if (num <= WARNING) {
			settextstyle(125, 0, _T("����"));
			settextcolor(RGB(254, 63, 66));
		}
		drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		RECT r = { 1250, 50, 1550, 150 };
		settextstyle(50, 0, _T("����"));	//��������
		settextcolor(RGB(0, 0, 0));	//������ɫ����
		drawtext(_T("�ȴ��ڷ�ִ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		r = { 1250, 150, 1550, 250 };
		settextstyle(70, 0, _T("����"));	//��������
		settextcolor(RGB(0, 0, 0));	//������ɫ����
		if (num <= WARNING) {
			settextstyle(125, 0, _T("����"));
			settextcolor(RGB(254, 63, 66));
		}
		drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	settextstyle(50, 0, _T("����"));
	return true;
}

void Board::fight()
{
	ExMessage mouse;								// ������Ϣ����
	clock_t start = clock(), end = clock();			//��ʱ��
	num = TIME - ((end - start) / 1000);			//��ʼ����ʱ������һ��ʼ��������
	cleardevice(); renew_board();
	flushmessage();									//ˢ�»�������ֹ��û��ʼ��������
	while (!who_win && time_judge() && account != LINE * LINE)//�ҳ���û��Ӯ���������ǰ�
	{
		end = clock();								//��ʱ��
		peekmessage(&mouse, EM_MOUSE | EM_KEY);		// ��ȡһ�����򰴼���Ϣ
		num = TIME - ((end - start) / 1000);		//��ʱ��
		switch (mouse.message)
		{
		case WM_LBUTTONDOWN:
			// ��������
			if (locate(mouse.x, mouse.y)) {			//����judge�����ж�����λ������Ӯ
				who = (who == 1) ? 2 : 1;			//�л�ִ����
				sum_time += (end - start);			//��ʱ
				start = clock();					//���ü�ʱ��
				end = clock();
				num = TIME - ((end - start) / 1000);//��ʼ����ʱ��
				flushmessage();						//ˢ�»�����
			}
			break;

		case WM_KEYDOWN:
			//����м�������
			//if (mouse.ctrl) {
			if (mouse.vkcode == 90) {
				if (account != 0) {
					traceback();						//�� Z ������һ��
					who = (who == 1) ? 2 : 1;			//�л�ִ����
					start = clock();					//���ü�ʱ��
					end = clock();
					num = TIME - ((end - start) / 1000);//��ʼ����ʱ��
					flushmessage();						//ˢ�»�����
					mouse.vkcode = -1;
				}
			}
			if (mouse.vkcode == VK_ESCAPE)				// �� ESC ���˳�����
				return;
			break;
		}
	}
}

void Board::dice()
{
	int black, white;
	srand((unsigned)time(NULL));		//�������
	settextstyle(100, 0, _T("����"));	//��������
	settextcolor(RGB(240, 240, 240));	//������ɫ����
	outtextxy(160, 165, _T("����"));	//��ӡ����ͺ���
	settextcolor(RGB(109, 109, 109));	//������ɫ����
	outtextxy(1220, 165, _T("����"));
	settextstyle(300, 0, _T("����"));	//��������
	settextcolor(WHITE);				//������ɫ����
	BeginBatchDraw();					//��ʼ������ͼ�û��治����
	//����
	for (int i = 70; i < 100; i++) {
		black = rand() % 6 + 1;
		white = rand() % 6 + 1;
		while (black == white) {		//��ֹ������ȵ����ξ���
			black = rand() % 6 + 1;
			white = rand() % 6 + 1;
		}
		outtextxy(190, 350, _T('0' + black));
		outtextxy(1250, 350, _T('0' + white));
		Sleep(i);						//����������Խ��Խ��
		FlushBatchDraw();
	}
	EndBatchDraw();
	settextcolor(RGB(8, 118, 202));		//������ɫ����
	outtextxy(190, 350, _T('0' + white));
	settextcolor(RGB(250, 135, 35));	//������ɫ����
	outtextxy(1250, 350, _T('0' + black));
	who = (black > white) ? 1 : 2;
	RECT r = { 0, 0, 1600, 900 };
	settextstyle(50, 0, _T("����"));	//����Ļ�м��ӡ���
	if (who == 1) {
		settextcolor(RGB(109, 109, 109));
		drawtext(_T("�ڷ����֣����ļ�����ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		settextcolor(RGB(240, 240, 240));
		drawtext(_T("�׷����֣����ļ�����ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

bool Board::locate(int x, int y)
{
	int location_x = 0, location_y = 0;			//�������λ��
	int correct_x = 0, correct_y = 0;			//�����λ�ã�lacation����������
	//����任�����������Ͻ�Ϊԭ���y��x
	location_x = (x - BOARD_CORNER_X) / GRID;	//��ȡ�����λ�����Ϸ�����ĵ���ȷ������
	location_y = (y - BOARD_CORNER_Y) / GRID;	//��ʱ�û��������ڸ��ӵ�����һ�����壬��һ���ж�
	//������λ�������һ�ǣ�ȷ��������
	correct_x = ((x - BOARD_CORNER_X) - (location_x * GRID)) / (GRID / 2);
	correct_y = ((y - BOARD_CORNER_Y) - (location_y * GRID)) / (GRID / 2);
	//����location
	location_x += correct_x;
	location_y += correct_y;
	//�������Ӿ��˳�
	if (record[location_x][location_y] != 0) {
		return false;
	}
	//x����Ƿ�
	if ((location_x > LINE) || (location_x < 0)) {
		return false;
	}
	//y����Ƿ�
	if ((location_y > LINE) || (location_y < 0)) {
		return false;
	}
	//�ڼ�¼�и��������е�����
	record[location_x][location_y] = who;
	//��¼�´˲��壨��ջ��
	step.push(pair<int, int>(location_x, location_y));
	//�ж���Ӯ
	judge(location_x, location_y);
	//��¼���Ӹ���
	account++;
	//��������
	cleardevice();
	renew_board();
	return true;
}

void Board::judge(int location_x, int location_y) {
	//�ж���Ӯ
	int count = 0;
	//����
	for (int i = location_x; (i >= 0 && i <= LINE) && record[i][location_y] == who; i++) {
		count++;
	}
	for (int i = location_x; (i >= 0 && i <= LINE) && record[i][location_y] == who; i--) {
		count++;
	}
	count -= 1;				//��ȥ�����ظ�����
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//���ü�����
	//����
	for (int i = location_y; (i >= 0 && i <= LINE) && record[location_x][i] == who; i++) {
		count++;
	}
	for (int i = location_y; (i >= 0 && i <= LINE) && record[location_x][i] == who; i--) {
		count++;
	}
	count -= 1;				//��ȥ�����ظ�����
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//���ü�����
	//���Խ���
	for (int i = location_x, j = location_y; (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE) && record[i][j] == who; i++, j++) {
		count++;
	}
	for (int i = location_x, j = location_y; (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE) && record[i][j] == who; i--, j--) {
		count++;
	}
	count -= 1;				//��ȥ�����ظ�����
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//���ü�����
	//�ζԽ���
	for (int i = location_x, j = location_y; (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE) && record[i][j] == who; i++, j--) {
		count++;
	}
	for (int i = location_x, j = location_y; (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE) && record[i][j] == who; i--, j++) {
		count++;
	}
	count -= 1;				//��ȥ�����ظ�����
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//���ü�����
}

void Board::renew_board()
{
	BeginBatchDraw();
	setlinestyle(PS_SOLID, 3);
	//��д����������
	line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y);
	line(BOARD_CORNER_X, BOARD_CORNER_Y, BOARD_CORNER_X, BOARD_CORNER_Y + BOARD_SIZE);
	line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE - BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE);
	line(BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + BOARD_SIZE - BOARD_SIZE);
	line(BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y - DECORATE, BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y - DECORATE);
	line(BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y - DECORATE, BOARD_CORNER_X - DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE);
	line(BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE, BOARD_CORNER_X + BOARD_SIZE - BOARD_SIZE - DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE);
	line(BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE + DECORATE, BOARD_CORNER_X + BOARD_SIZE + DECORATE, BOARD_CORNER_Y + BOARD_SIZE - BOARD_SIZE - DECORATE);
	setlinestyle(PS_SOLID, 1);
	//���Ƹ���
	for (int i = 0; i <= LINE; i++) {
		line(BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y, BOARD_CORNER_X + i * GRID, BOARD_CORNER_Y + BOARD_SIZE);
		line(BOARD_CORNER_X, BOARD_CORNER_Y + i * GRID, BOARD_CORNER_X + BOARD_SIZE, BOARD_CORNER_Y + i * GRID);
	}
	//��д���Ƹ���
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
	//������һ��������
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
			setbkcolor(RGB(i, i, i));		//���±�����ɫ
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
		settextstyle(100, 0, _T("����"));	//��������
		settextcolor(RGB(255, 255, 255));	//������ɫ����
		drawtext(_T("�׷�����ʤ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	if (who_win == 1) {
		for (int i = 150; i >= 50; i -= 1) {
			renew_board();
			setbkcolor(RGB(i, i, i));		//���±�����ɫ
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
		settextstyle(100, 0, _T("����"));	//��������
		settextcolor(RGB(0, 0, 0));	//������ɫ����
		drawtext(_T("�ڷ�����ʤ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	if (who_win == 0) {
		for (int i = 150; i >= 50; i -= 1) {
			renew_board();
			setbkcolor(RGB(i, i, i));		//���±�����ɫ
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
		settextstyle(100, 0, _T("����"));	//��������
		settextcolor(RGB(0, 0, 0));	//������ɫ����
		drawtext(_T("ƽ�֣�ʤ��δ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	EndBatchDraw();
}

void Board::traceback()
{
	//�������һ��
	record[step.top().first][step.top().second] = 0;
	//��ջ��ɾ�����һ��ʵ�ֻ���
	step.pop();
	//���Ӽ�һ
	account--;
	//ˢ��
	cleardevice();
	renew_board();
	//��ֹ����һֱ����Z��
	Sleep(300);
}

void Board::review()
{
	RECT r = { 0, 0, 0, 0 };
	int x = 0, y = 0;
	//��ֹrenew_board�ٻ�����
	int i = account;
	sum_time /= 1000;			//�������
	account = 0;				//��0������
	//�ػ�����
	draw_board();
	renew_board();
	//�����в�����˳��
	for (; i != 0 && !step.empty(); i--) {
		//��¼�����ջ
		x = BOARD_CORNER_X + step.top().first * GRID;
		y = BOARD_CORNER_Y + step.top().second * GRID;
		step.pop();
		//����ת�ַ���
		wchar_t c[10];
		_itow_s(i, c, 10, 10);
		wstring str(c);
		//��������
		settextstyle(45, 0, _T("����"));
		setbkmode(TRANSPARENT);
		settextcolor(RGB(254, 63, 66));//������ɫ����
		r = { x + RADIUS, y + RADIUS,x - RADIUS, y - RADIUS };
		//�������100�����Ӿʹ�ӡ����ɫ
		if (i >= 100) {
			settextstyle(30, 0, _T("����"));
			settextcolor(RGB(8, 118, 202));
			r = { x + 2 * RADIUS, y + 2 * RADIUS,x - 2 * RADIUS, y - 2 * RADIUS };
		}
		drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	//��ӡ���ߵ���
	{
		r = { 1250, 50, 1550, 150 };
		settextstyle(50, 0, _T("����"));	//��������
		settextcolor(RGB(0, 0, 0));	//������ɫ����
		drawtext(_T("���ĸ���"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		r = { 50, 50, 350, 150 };
		settextstyle(50, 0, _T("����"));	//��������
		settextcolor(RGB(255, 255, 255));	//������ɫ����
		drawtext(_T("��������ʱ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		r = { 0, 150, 550, 250 };
		settextstyle(70, 0, _T("����"));	//��������
		settextcolor(RGB(255, 255, 255));	//������ɫ����
		wchar_t c[10];
		_itow_s(sum_time, c, 10, 10);
		wstring str(c);
		drawtext(c, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	system("pause");
}