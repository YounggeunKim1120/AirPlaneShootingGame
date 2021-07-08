#include "common.h"
#include "struct.h"
#include "keyProcess.h"
#include "gameData.h"

#define UP 72
#define DOWN 80
#define SPACE 32

#define CURSOR_X 20

extern playerState player;
extern int manaUpDelay;
extern int stageLevel;

int cursorY = 2;
int choice1Time = 0;
int choice2Time = 0;
int choice3Time = 0;
int choice4Time = 0;

void PrintBlank(int y)
{
	Goto(CURSOR_X, y);
	printf("  ");
}

void ChoiceCursorMov(int y)
{
	Goto(CURSOR_X, y);
	printf("¢Ð");
}

void ChoiceAbility(void)
{
	if (cursorY == 2)
		if (choice1Time < MAX_POWER_UP_TIME)
		{
			if (player.Exp >= 40)
			{
				player.Power++;
				choice1Time++;
				player.Exp -= 40;
				cursorY = 2;
				ChoiceCursorMov(cursorY);
			}
		}
	if (cursorY == 3)
		if (choice2Time < MAX_ATT_DELAY_DOWN_TIME)
		{
			if (player.Exp >= 20)
			{
				player.AttDelay -= 15;
				choice2Time++;
				player.Exp -= 20;
				cursorY = 2;
				ChoiceCursorMov(cursorY);
			}
		}
	if (cursorY == 4)
		if (choice3Time < MAX_MOV_DELAY_DOWN_TIME)
		{
			if (player.Exp >= 20)
			{
				player.MovDelay -= 10;
				choice3Time++;
				player.Exp -= 20;
				cursorY = 2; 
				ChoiceCursorMov(cursorY);
			}
		}
	if (cursorY == 5)
		if (choice4Time < MAX_MANA_DELAY_DOWN_TIME)
		{
			if (player.Exp >= 20)
			{
				manaUpDelay -= 500;
				choice4Time++;
				player.Exp -= 20;
				cursorY = 2;
				ChoiceCursorMov(cursorY);
			}
		}
	if (cursorY == 6)
	{
		player.Health++;
		player.Exp -= 20;
	}
}

void SetUpBeforeNextLevelScreen(void)
{
	system("cls");
	
	if (choice1Time < MAX_POWER_UP_TIME)
	{
		Goto(0, 2);
		printf("Att Power (40)");
	}
	if (choice2Time < MAX_ATT_DELAY_DOWN_TIME)
	{
		Goto(0, 3);
		printf("Att Faster (20)");
	}
	if (choice3Time < MAX_MOV_DELAY_DOWN_TIME)
	{
		Goto(0, 4);
		printf("Move Faster (20)");
	}
	if (choice4Time < MAX_MANA_DELAY_DOWN_TIME)
	{
		Goto(0, 5);
		printf("Get Mana Faster(20)");
	}
	Goto(0, 6);
	printf("Get One Health (20)");
	Goto(0, 7);
	printf("Quit : 'q'");
}

void PrintCurrentExp(void)
{
	Goto(0, 9);
	printf("Remain Exp : %d", player.Exp);
}

int KeyProcesssInBeforeNextLevel(void)
{
	int key;

	if (_kbhit() != 0)
	{
		key = getch();

		switch (key) {
		case UP :
			if (cursorY > 2)
			{
				PrintBlank(cursorY);
				cursorY--;
				ChoiceCursorMov(cursorY);
			}
			break;
		case DOWN :
			if (cursorY < 6)
			{
				PrintBlank(cursorY);
				cursorY++;
				ChoiceCursorMov(cursorY);
			}
			break;
		case SPACE :
			ChoiceAbility();
			SetUpBeforeNextLevelScreen();
			PrintCurrentExp();
			break;
		case 'q' :
			system("cls");
			return 1;
		}
	}
	return 0;
}

void BeforeNextLevel(void)
{
	SetUpBeforeNextLevelScreen();

	ChoiceCursorMov(cursorY);

	PrintCurrentExp();

	while (1)
	{
		if (KeyProcesssInBeforeNextLevel() == 1)
			return;
	}
}