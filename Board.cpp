#include"Board.h"

Board::Board()
{
	record[0][0] = { 0 };//��������λ�ó�ʼ��Ϊ0
	black = false;
}

void Board::main_thread()
{
	initgraph(1600, 900);				//���ڳ�ʼ��
	setbkcolor(RGB(30, 30, 30));		//���±�����ɫ
	cleardevice();
	black = dice();						//�������Ӻ���
	RECT r = { 0, 0, 1600, 900 };
	settextstyle(50, 0, _T("����"));	//����Ļ�м��ӡ���
	if (black) {
		settextcolor(RGB(109, 109, 109));
		drawtext(_T("�ڷ����֣����ļ�����ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else {
		settextcolor(RGB(240, 240, 240));
		drawtext(_T("�׷����֣����ļ�����ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	Sleep(3000);
	draw_board();
	Sleep(3000);
}

void Board::welcome()
{
}

void Board::draw_board()
{
	cleardevice();
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
		Sleep(1);
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
}

bool Board::dice()
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
	outtextxy(190, 350, _T('0' + black));
	settextcolor(RGB(250, 135, 35));	//������ɫ����
	outtextxy(1250, 350, _T('0' + white));
	return black > white;				//��������
}

bool Board::judge(int x, int y)
{
	return false;
}