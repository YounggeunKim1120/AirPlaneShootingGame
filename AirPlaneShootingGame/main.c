#include "common.h"
#include "gameData.h"
#include "gameFunc.h"
#include "keyProcess.h"

#define DELAY_BETWEEN_COLLION_AND_ENEMY_MOV 5

int main(void)
{
	MemAllocateStructPointerArr();
	SetConsoleSize(ROW_LEN, 25);
	RemoveCursor();

	CreatePlayer();

	ShowPlayerState();

	while (1)
	{
		ProcessKeyInput();
		if (ProcessCheck() == 1)
			return 0;
	}
}