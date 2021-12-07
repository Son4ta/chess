#include"Board.h"

Board::Board()
{
	//��������λ�ó�ʼ��Ϊ0
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
	initgraph(1600, 900);				//���ڳ�ʼ��
	setbkcolor(RGB(30, 30, 30));		//���±�����ɫ
	cleardevice();
	dice();						//�������Ӻ���
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
	//����������
	cleardevice();
	//���Ʊ���
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

void Board::fight()
{
	ExMessage mouse;		// ������Ϣ����
	while (!who_win)		//�ҳ���û��Ӯ���������ǰ�
	{
		mouse = getmessage(EM_MOUSE | EM_KEY);	// ��ȡһ�����򰴼���Ϣ

		switch (mouse.message)
		{
		case WM_LBUTTONDOWN:
			// ��������
			locate(mouse.x, mouse.y);			//����judge�����ж�����λ������Ӯ
			who = (who == 1) ? 2 : 1;			//�л�ִ����
			break;

		case WM_KEYDOWN:
			if (mouse.vkcode == VK_ESCAPE)
				break;							// �� ESC ���˳�����
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
	//HRGN rgn = CreateRectRgn(0, 390, 1600, 900);
	// ���þ�����������Ϊ�ü���
	//setcliprgn(rgn);
	//clearcliprgn();
	//DeleteObject(rgn);
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
	//�ڼ�¼�и��������е�����
	record[location_x][location_y] = who;
	//�ж���Ӯ
	judge(location_x, location_y);
	//��������
	renew_board();
	return false;
}

void Board::judge(int location_x, int location_y) {
	//�ж���Ӯ
	int count = 0;
	//����
	for (int i = location_x; record[i][location_y] == who && (i >= 0 && i <= LINE); i++) {
		count++;
	}
	for (int i = location_x; record[i][location_y] == who && (i >= 0 && i <= LINE); i--) {
		count++;
	}
	count -= 1;				//��ȥ�����ظ�����
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//���ü�����
	//����
	for (int i = location_y; record[location_x][i] == who && (i >= 0 && i <= LINE); i++) {
		count++;
	}
	for (int i = location_y; record[location_x][i] == who && (i >= 0 && i <= LINE); i--) {
		count++;
	}
	count -= 1;				//��ȥ�����ظ�����
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//���ü�����
	//���Խ���
	for (int i = location_x, j = location_y; record[i][j] == who && (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE); i++, j++) {
		count++;
	}
	for (int i = location_x, j = location_y; record[i][j] == who && (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE); i--, j--) {
		count++;
	}
	count -= 1;				//��ȥ�����ظ�����
	if (count >= 5) {
		who_win = who;
	}
	count = 0;				//���ü�����
	//�ζԽ���
	for (int i = location_x, j = location_y; record[i][j] == who && (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE); i++, j--) {
		count++;
	}
	for (int i = location_x, j = location_y; record[i][j] == who && (i >= 0 && i <= LINE) && (j >= 0 && j <= LINE); i--, j++) {
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