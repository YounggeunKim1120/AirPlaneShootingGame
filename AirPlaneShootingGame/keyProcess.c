#include "common.h"
#include "gameFunc.h"

#define SYS_DELAY 5

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32


void Goto(int x, int y) 
{
	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ProcessKeyInput(void)
{
	int i;
	int key;


	if (_kbhit() != 0)
	{
		key = _getch();

		switch (key)
		{
		case LEFT:
			ShiftLeft();
			break;
		case RIGHT:
			ShiftRight();
			break;
		case UP:
			ShiftUp();
			break;
		case DOWN:
			ShiftDown();
			break;
		case SPACE:
			ShootAttack();
			break;
		case 'a':
			ShootSkill();
			break;
		case 's' :
			UseUlt();
		}
	}

	Sleep(SYS_DELAY);
}