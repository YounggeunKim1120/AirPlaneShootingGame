#include "common.h"
#include "keyProcess.h"
#include "gameData.h"
#include "struct.h"


void PrintToXY(int Shape, int x, int y)
{
	Goto(2 * x, y);
	switch (Shape) {
	case PLAYER :
		printf("▲");
		break;
	case P_BULLET1 :
		printf("Λ");
		break;
	case P_BULLET2 :
		printf("↑");
		break;
	case P_BULLET3 :
		printf("♤");
		break;
	case P_SKILL :
		printf("☆");
		break;
	case E_BULLET :
		printf("＊");
		break;
	case E_METEOR :
		if (x <= 9 && y <= 15)
		{
			printf("┏━┓");
			Goto(2 * x, y + 1);
			printf("┃  ┃");
			Goto(2 * x, y + 2);
			printf("┗━┛");
		}
		if (x <= 9 && y == 16)
		{
			printf("┏━┓");
			Goto(2 * x, y + 1);
			printf("┃  ┃");
		}
		if (x <= 9 && y == 17)
		{
			printf("┏━┓");
		}
		break;
	case ENEMY1 :
		printf("◇");
		break;
	case ENEMY2 :
		printf("◆");
		break;
	case ENEMY3 :
		printf("♡");
		break;
	case ENEMY4 :
		printf("♥");
		break;
	case ENEMY5 :
		printf("◈");
		break;
	case ENEMY6 : 
		printf("▣");
		break;
	case BLANK :
		printf("  ");
	}
}


void SetConsoleSize(int col, int lines)
{
	char setText[100];
	sprintf(setText, "mode con cols=%d lines=%d", 2*col, lines);
	system(setText);
}

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}