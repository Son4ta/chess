#include <graphics.h>
#include <conio.h>

int main()
{
	initgraph(640, 480);
	BeginBatchDraw();

	setlinecolor(WHITE);
	setfillcolor(RED);

	for (int i = 50; i < 600; i++)
	{
		circle(i, 100, 40);
		floodfill(i, 100, WHITE);
		FlushBatchDraw();
		Sleep(1);
		cleardevice();
	}

	EndBatchDraw();
	closegraph();

	//initgraph(1360, 900);
	//initgraph(1600, 900);
	//int i = 400, j = 50, k = 40;
	//settextstyle(160, 80, _T("Arial"));
	//BeginBatchDraw();
	//while (1) {
	//	int black, white = 0;

	//	srand((unsigned)time(NULL));//随机数种

	//	black = rand() % 6 + 1;	//骰子
	//	i++;
	//	char c = '0' + black;
	//	outtextxy(1000, 40, c);
	//	//Sleep(1);
	//	FlushBatchDraw();
	//	cleardevice();
	//	white++;
	//	if (white > 100)break;
	//}
	//EndBatchDraw();
	//for (; i <= 400 + 800; i += k) {
	//	line(i, j, i, j + 800);
	//}
	//i = 400;
	//for (; j <= 50 + 800; j += k) {
	//	line(i, j, i + 800, j);
	//}
	//closegraph();
}