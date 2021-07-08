#include "common.h"
#include "keyProcess.h"
#include "screenOut.h"
#include "gameData.h"
#include "struct.h"

#define SYS_DELAY 5

int stageLevel = 1;
int numOfEnemy = 0;
int numOfPBullet = 0;
int numOfEBullet = 0;
int numOfSkill = 0;
int enemySummonDelay = FISRT_STAGE_ENEMY_SUMMON_DELAY;
int enemySummonTimer = 0;
int timeOfSummon = 0;
int timeOfSummonForNextLeve[MAX_STAGE_LEVEL] = { STAGE_SUMMON_TIME1,STAGE_SUMMON_TIME2,STAGE_SUMMON_TIME3,STAGE_SUMMON_TIME4,STAGE_SUMMON_TIME5,STAGE_SUMMON_TIME6,STAGE_SUMMON_TIME7,STAGE_SUMMON_TIME8,STAGE_SUMMON_TIME9,STAGE_SUMMON_TIME10 };
int manaUpDelay = MANA_UP_DELAY;
int manaUpTimer = 0;
int prevHealth; 
int prevMana;
int prevExp;

int enemeyMovDelayArr[MAX_ENEMY_GRADE];

playerState player;
enemyState* enemy[MAX_ENEMY_NUM];
bullet* pBullet[MAX_PLAYER_BULLET_NUM];
bullet* eBullet[MAX_ENEMY_BULLET_NUM];
skill* pSkill[MAX_SKILL_NUM];

void CreatePlayer(void)
{
	player.x = START_X;
	player.y = START_Y;
	player.Health = FULL_HEALTH;
	player.Mana = FULL_MANA;
	player.Power = START_POWER;
	player.AttDelay = START_ATT_DELAY;
	player.MovDelay = START_MOV_DELAY;
	player.AttTimer = START_ATT_DELAY;
	player.MovTimer = START_MOV_DELAY;
	player.Exp = 0;
	PrintToXY(PLAYER, player.x, player.y);
}

void PlacePlayerToStartPoint(void)
{
	player.x = START_X;
	player.y = START_Y;
}

void MemAllocateStructPointerArr(void)
{
	int i;
	for (i = 0; i < MAX_ENEMY_NUM; i++)
		enemy[i] = (enemyState*)malloc(sizeof(enemyState));
	for (i = 0; i < MAX_PLAYER_BULLET_NUM; i++)
		pBullet[i] = (bullet*)malloc(sizeof(bullet));
	for (i = 0; i < MAX_SKILL_NUM; i++)
		pSkill[i] = (skill*)malloc(sizeof(skill));
	for (i = 0; i < MAX_ENEMY_BULLET_NUM; i++)
		eBullet[i] = (bullet*)malloc(sizeof(bullet));
}

void CreateEnemy(void)
{
	if (numOfEnemy < MAX_ENEMY_NUM)
	{
		enemy[numOfEnemy]->x = rand() % 13;
		enemy[numOfEnemy]->y = 0;
		/*if (stageLevel <= MAX_ENEMY_GRADE)
			enemy[numOfEnemy]->grade = rand() % stageLevel + 1;
		else
			enemy[numOfEnemy]->grade = rand() % MAX_ENEMY_GRADE + 1;*/

		enemy[numOfEnemy]->grade = 6;

		if (enemy[numOfEnemy]->grade == 1)
		{
			enemy[numOfEnemy]->Health = ENEMY1_HEALTH;
			enemy[numOfEnemy]->AttDelay = ENEMY1_ATT_DELAY;
			enemy[numOfEnemy]->MovDelay = ENEMY1_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->MovMode = ENEMY1_MOV_MODE;
			enemy[numOfEnemy]->Exp = ENEMY1_EXP;
		}
		if (enemy[numOfEnemy]->grade == 2)
		{
			enemy[numOfEnemy]->Health = ENEMY2_HEALTH;
			enemy[numOfEnemy]->AttDelay = ENEMY2_ATT_DELAY;
			enemy[numOfEnemy]->MovDelay = ENEMY2_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->MovMode = ENEMY2_MOV_MODE;
			enemy[numOfEnemy]->Exp = ENEMY2_EXP;
		}
		if (enemy[numOfEnemy]->grade == 3)
		{
			enemy[numOfEnemy]->Health = ENEMY3_HEALTH;
			enemy[numOfEnemy]->AttDelay = ENEMY3_ATT_DELAY;
			enemy[numOfEnemy]->AttTimer = 0;
			enemy[numOfEnemy]->MovDelay = ENEMY3_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->MovMode = ENEMY3_MOV_MODE;
			enemy[numOfEnemy]->Exp = ENEMY3_EXP;
		}
		if (enemy[numOfEnemy]->grade == 4)
		{
			enemy[numOfEnemy]->Health = ENEMY4_HEALTH;
			enemy[numOfEnemy]->AttDelay = ENEMY4_ATT_DELAY;
			enemy[numOfEnemy]->AttTimer = 0;
			enemy[numOfEnemy]->MovDelay = ENEMY4_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->MovMode = ENEMY4_MOV_MODE;
			enemy[numOfEnemy]->Exp = ENEMY4_EXP;
		}
		if (enemy[numOfEnemy]->grade == 5)
		{
			enemy[numOfEnemy]->Health = ENEMY5_HEALTH;
			enemy[numOfEnemy]->AttDelay = ENEMY5_ATT_DELAY;
			enemy[numOfEnemy]->AttTimer = 0;
			enemy[numOfEnemy]->MovDelay = ENEMY5_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->MovMode = ENEMY5_MOV_MODE;
			enemy[numOfEnemy]->Exp = ENEMY5_EXP;
		}
		if (enemy[numOfEnemy]->grade == 6)
		{
			enemy[numOfEnemy]->Health = ENEMY6_HEALTH;
			enemy[numOfEnemy]->AttDelay = ENEMY6_ATT_DELAY;
			enemy[numOfEnemy]->AttTimer = 0;
			enemy[numOfEnemy]->MovDelay = ENEMY6_MOV_DELAY;
			enemy[numOfEnemy]->MovTimer = 0;
			enemy[numOfEnemy]->MovMode = ENEMY6_MOV_MODE;
			enemy[numOfEnemy]->Exp = ENEMY6_EXP;
		}


		PrintToXY(ENEMY1 + enemy[numOfEnemy]->grade - 1, enemy[numOfEnemy]->x, enemy[numOfEnemy]->y);
		numOfEnemy++;
		enemySummonTimer = 0;
	}
}

void GameOver(void)
{
	system("cls");
	Goto(4, 9);
	printf("Game Over");
}

void GameClear(void)
{
	system("cls");
	Goto(4, 9);
	printf("Game Clear");
}

void ShiftLeft(void)
{
	if (player.MovTimer >= player.MovDelay)
	{
		if (player.x > 0)
		{
			PrintToXY(BLANK, player.x, player.y);
			player.x--;
			PrintToXY(PLAYER, player.x, player.y);
			player.MovTimer = 0;
		}
	}
}

void ShiftRight(void)
{
	if (player.MovTimer >= player.MovDelay)
	{
		if (player.x < ROW_LEN - 1)
		{
			PrintToXY(BLANK, player.x, player.y);
			player.x++;
			PrintToXY(PLAYER, player.x, player.y);
			player.MovTimer = 0;
		}
	}
}

void ShiftUp(void)
{
	if (player.MovTimer >= player.MovDelay)
	{
		if (player.y > 0)
		{
			PrintToXY(BLANK, player.x, player.y);
			player.y--;
			PrintToXY(PLAYER, player.x, player.y);
			player.MovTimer = 0;
		}
	}
}

void ShiftDown(void)
{
	if (player.MovTimer >= player.MovDelay)
	{
		if (player.y < COL_LEN - 1)
		{
			PrintToXY(BLANK, player.x, player.y);
			player.y++;
			PrintToXY(PLAYER, player.x, player.y);
			player.MovTimer = 0;
		}
	}
}


void ShootAttack(void)
{
	if (numOfPBullet < MAX_PLAYER_BULLET_NUM)
	{
		if (player.AttTimer >= (player.AttDelay - 1))
		{
			pBullet[numOfPBullet]->x = player.x;
			pBullet[numOfPBullet]->y = player.y - 1;
			pBullet[numOfPBullet]->Power = player.Power;
			pBullet[numOfPBullet]->MovDelay = PLAYER_BULLET_MOV_DELAY;
			pBullet[numOfPBullet]->MovTimer = 0;

			PrintToXY(P_BULLET1 + pBullet[numOfPBullet]->Power - 1, player.x, player.y - 1);
			player.AttTimer = 0;

			numOfPBullet++;
		}
	}
}

void ShowPlayerState(void)
{
	int i, j;
	Goto(0, 21);
	printf("               ");
	Goto(0, 22);
	printf("                           ");
	Goto(0, 23);
	printf("         ");

	Goto(0, 21);
	printf("Health ");
	for (i = 0; i < player.Health; i++)
		printf("¢¾");
	for (j = i; j < FULL_HEALTH; j++)
		printf("  ");
	Goto(0, 22);
	printf("Mana ");
	for (i = 0; i < player.Mana; i++)
		printf("[]");
	for (j = i; j < FULL_MANA; j++)
		printf("  ");
	Goto(0, 23);
	printf("Exp %d", player.Exp);
}

void ShootSkill(void)
{
	if (numOfSkill < MAX_SKILL_NUM)
	{
		if (player.Mana >= USE_SKILL_MANA)
		{
			pSkill[numOfSkill]->x = player.x;
			pSkill[numOfSkill]->y = player.y - 1;
			pSkill[numOfSkill]->Power = player.Power + SKILL_POWER;
			pSkill[numOfSkill]->MovDelay = SKILL_MOV_DELAY;
			pSkill[numOfSkill]->MovTimer = 0;
			player.Mana--;

			PrintToXY(P_SKILL, pSkill[numOfPBullet]->x, pSkill[numOfPBullet]->y);

			numOfSkill++;
		}
	}
}


void DeleteEnemy(int enemyIdx)
{
	int i;

	free(enemy[enemyIdx]);
	for (i = enemyIdx; i < numOfEnemy - 1; i++)
	{
		enemy[i] = enemy[i + 1];
	}
	enemy[numOfEnemy - 1] = NULL;
	enemy[numOfEnemy - 1] = (enemyState*)malloc(sizeof(enemyState));
	numOfEnemy--;
}

void DeletePBullet(int pBulletIdx)
{
	int i;

	free(pBullet[pBulletIdx]);
	for (i = pBulletIdx; i < numOfPBullet - 1; i++)
	{
		pBullet[i] = pBullet[i + 1];
	}
	pBullet[numOfPBullet - 1] = NULL;
	pBullet[numOfPBullet - 1] = (bullet*)malloc(sizeof(bullet));
	numOfPBullet--;
}

void DeleteEBullet(int eBulletIdx)
{
	int i;

	free(eBullet[eBulletIdx]);
	for (i = eBulletIdx; i < numOfEBullet - 1; i++)
	{
		eBullet[i] = eBullet[i + 1];
	}
	eBullet[numOfEBullet - 1] = NULL;
	eBullet[numOfEBullet - 1] = (bullet*)malloc(sizeof(bullet));
	numOfEBullet--;
}

void DeleteSkill(int skillIdx)
{
	int i;

	free(pSkill[skillIdx]);
	for (i = skillIdx; i < numOfSkill - 1; i++)
	{
		pSkill[i] = pSkill[i + 1];
	}
	pSkill[numOfSkill - 1] = NULL;
	pSkill[numOfSkill - 1] = (skill*)malloc(sizeof(skill));
	numOfSkill--;
}

void UseUlt(void)
{
	int i;

	if (player.Mana == 10)
	{
		while (numOfEnemy != 0)
		{
			DeleteEnemy(numOfEnemy - 2);
			player.Exp += enemy[numOfEnemy - 1]->Exp;
		}
		while (numOfPBullet != 0)
		{
			DeletePBullet(numOfPBullet - 2);
		}
		while (numOfEBullet != 0)
		{
			DeleteEBullet(numOfEBullet - 2);
		}
		system("cls");
		PrintToXY(PLAYER, player.x, player.y);
	}
}

int EnemySummonCheck(void)
{
	if (enemySummonTimer >= enemySummonDelay)
	{
		CreateEnemy();
		timeOfSummon++;
		if (timeOfSummon > timeOfSummonForNextLeve[stageLevel - 1])
		{
			stageLevel++;
			while (numOfEnemy != 0)
				DeleteEnemy(numOfEnemy-1);
			while (numOfEBullet != 0)
				DeleteEBullet(numOfEnemy - 1); 
			if (stageLevel > MAX_STAGE_LEVEL)
			{
				GameClear();
				return 1;
			}
			BeforeNextLevel();
			timeOfSummon = 0;
			enemySummonDelay = FISRT_STAGE_ENEMY_SUMMON_DELAY - 100 * (stageLevel - 1);
			ShowPlayerState();
			PlacePlayerToStartPoint();
			PrintToXY(PLAYER, player.x, player.y);
		}
	}
	return 0;
}

void EnemyMovCheck(void)
{
	int i;
	int movMode;
	int movDir;
	
	srand(time(NULL));

	for (i = 0; i < numOfEnemy; i++)
	{
		if (enemy[i]->MovTimer >= enemy[i]->MovDelay)
		{
			movMode = enemy[i]->MovMode;
			if (movMode == 1)
			{
				if (enemy[i]->y < COL_LEN - 1)
				{
					PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
					enemy[i]->y++;
					PrintToXY(ENEMY1 + enemy[i]->grade - 1, enemy[i]->x, enemy[i]->y);
					enemy[i]->MovTimer = 0;
				}
				else if (enemy[i]->y >= COL_LEN - 1)
				{
					PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
					DeleteEnemy(i);
					i--;
				}
			}

			if (movMode == 2)
			{
				PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
				if (enemy[i]->x < ROW_LEN - 1 && enemy[i]->x > 0)
				{
					movDir = rand() % 2;
					if (movDir == 1)
					{
						enemy[i]->x++;
					}
					else if (movDir == 0)
					{
						enemy[i]->x--;
					}
				}
				else if (enemy[i]->x >= ROW_LEN - 1)
				{
					enemy[i]->x--;
				}
				else if (enemy[i]->x == 0)
				{
					enemy[i]->x++;
				}
				PrintToXY(ENEMY1 + enemy[i]->grade - 1, enemy[i]->x, enemy[i]->y);
				enemy[i]->MovTimer = 0;
			}
		}
	}
}

void PBulletMovCheck(void)
{
	int i;
	
	for (i = 0; i < numOfPBullet; i++)
	{
		if (pBullet[i]->MovTimer >= pBullet[i]->MovDelay)
		{
			if (pBullet[i]->y > 0)
			{
				PrintToXY(BLANK, pBullet[i]->x, pBullet[i]->y);
				pBullet[i]->y--;
				PrintToXY(P_BULLET1 + pBullet[i]->Power - 1, pBullet[i]->x, pBullet[i]->y);
				pBullet[i]->MovTimer = 0;
			}
			else if (pBullet[i]->y <= 0)
			{
				PrintToXY(BLANK, pBullet[i]->x, pBullet[i]->y);
				DeletePBullet(i);
				i--;
			}
		}
	}
}

void SkillMovCheck(void)
{
	int i;
	for (i = 0; i < numOfSkill; i++)
	{
		if (pSkill[i]->MovTimer >= pSkill[i]->MovDelay)
		{
			if (pSkill[i]->y > 0)
			{
				PrintToXY(BLANK, pSkill[i]->x, pSkill[i]->y);
				pSkill[i]->y--;
				PrintToXY(P_SKILL, pSkill[i]->x, pSkill[i]->y);
				pSkill[i]->MovTimer = 0;
			}
			else if(pSkill[i]->y <= 0)
			{
				PrintToXY(BLANK, pSkill[i]->x, pSkill[i]->y);
				DeleteSkill(i);
				i--;
			}
		}
	}
}

void EBulletShootCheck(void)
{
	int i;

	for (i = 0; i < numOfEnemy; i++)
	{
		if (enemy[i]->AttTimer >= enemy[i]->AttDelay)
		{
			eBullet[numOfEBullet]->MovDelay = ENEMY_BULLET_MOV_DELAY;
			eBullet[numOfEBullet]->MovTimer = 0;
			eBullet[numOfEBullet]->Power = 1;
			eBullet[numOfEBullet]->x = enemy[i]->x;
			eBullet[numOfEBullet]->y = enemy[i]->y + 1;

			numOfEBullet++;
			enemy[i]->AttTimer = 0;

			if (enemy[i]->grade == 5)
			{
				eBullet[numOfEBullet]->MovDelay = ENEMY_BULLET_MOV_DELAY;
				eBullet[numOfEBullet]->MovTimer = 0;
				eBullet[numOfEBullet]->Power = 1;
				eBullet[numOfEBullet]->x = enemy[i]->x - 2;
				eBullet[numOfEBullet]->y = enemy[i]->y + 1;
				
				numOfEBullet++;

				eBullet[numOfEBullet]->MovDelay = ENEMY_BULLET_MOV_DELAY;
				eBullet[numOfEBullet]->MovTimer = 0;
				eBullet[numOfEBullet]->Power = 1;
				eBullet[numOfEBullet]->x = enemy[i]->x + 2;
				eBullet[numOfEBullet]->y = enemy[i]->y + 1;

				numOfEBullet++;
			}

			if (enemy[i]->grade == 6)
			{
				eBullet[numOfEBullet]->MovDelay = ENEMY_BULLET_MOV_DELAY;
				eBullet[numOfEBullet]->MovTimer = 0;
				eBullet[numOfEBullet]->Power = 1;
				eBullet[numOfEBullet]->x = enemy[i]->x - 2;
				eBullet[numOfEBullet]->y = enemy[i]->y + 1;

				numOfEBullet++;

				eBullet[numOfEBullet]->MovDelay = ENEMY_BULLET_MOV_DELAY;
				eBullet[numOfEBullet]->MovTimer = 0;
				eBullet[numOfEBullet]->Power = 1;
				eBullet[numOfEBullet]->x = enemy[i]->x + 2;
				eBullet[numOfEBullet]->y = enemy[i]->y + 1;

				numOfEBullet++;
			}
		}
	}
}

void EBulletMovCheck(void)
{
	int i;
	for (i = 0; i < numOfEBullet; i++)
	{
		if (eBullet[i]->MovTimer >= eBullet[i]->MovDelay)
		{
			if (eBullet[i]->y < COL_LEN - 1)
			{
				PrintToXY(BLANK, eBullet[i]->x, eBullet[i]->y);
				eBullet[i]->y++;
				PrintToXY(E_BULLET, eBullet[i]->x, eBullet[i]->y);
				eBullet[i]->MovTimer = 0;
			}
			else 
			{
				PrintToXY(BLANK, eBullet[i]->x, eBullet[i]->y);
				DeleteEBullet(i);
				i--;
			}
		}
	}
}

int CheckPlayerAndEnemyBulletCollision(void)
{
	int i;
	for (i = 0; i < numOfEBullet; i++)
	{
		if (eBullet[i]->x == player.x && eBullet[i]->y == player.y)
		{
			PrintToXY(BLANK, eBullet[i]->x, eBullet[i]->y);
			DeleteEBullet(i);
			if (player.HitTimer >= player.HitDelay)
			{
				player.HitTimer = 0;
				player.Health--;
				PlacePlayerToStartPoint();
				if (player.Health == 0)
				{
					GameOver();
					return 1;
				}
			}
		}
	}
	return 0;
}

void CheckEnemyAndPlayerBulletCollision(void)
{
	int i, j;
	int killEnemy = 0;
	for (i = 0; i < numOfEnemy; i++)
	{
		for (j = 0; j < numOfPBullet; j++)
		{
			if (enemy[i]->x == pBullet[j]->x && enemy[i]->y == pBullet[j]->y)
			{
				enemy[i]->Health -= pBullet[j]->Power;
				PrintToXY(ENEMY1 + enemy[i]->grade - 1, enemy[i]->x, enemy[i]->y);
				DeletePBullet(j);
				j--;
				if (enemy[i]->Health <= 0)
				{
					PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
					player.Exp += enemy[i]->Exp;
					DeleteEnemy(i);
					killEnemy = 1;
				}
				break;
			}
		} 
		if (killEnemy>0)
		{
			i--;
			killEnemy = 0;
		}
	}
}

void CheckSkillAndEnemyOrBulletCollision(void)
{
	int i, j;
	int killEnemy = 0;
	int removeEBulletArr[MAX_ENEMY_BULLET_NUM];
	int tempNumOfEBullet = numOfEBullet;
	int removeIdx = 0;

	for (i = 0; i < numOfEnemy; i++)
	{
		for (j = 0; j < numOfSkill; j++)
		{
			if ((enemy[i]->x == pSkill[j]->x) && (enemy[i]->y == pSkill[j]->y))
			{
				enemy[i]->Health -= pSkill[j]->Power + player.Power;
				if (enemy[i]->Health <= 0)
				{
					player.Exp += enemy[i]->Exp;
					DeleteEnemy(i);
					killEnemy = 1;
					break;
				}
			}
		}
		if (killEnemy == 1)
		{
			i--;
			killEnemy = 0;
		}
	}

	for (i = 0; i < numOfEBullet; i++)
	{
		for (j = 0; j < numOfSkill; j++)
		{
			if ((eBullet[i]->x == pSkill[j]->x) && (eBullet[i]->y == pSkill[j]->y))
			{
				PrintToXY(P_SKILL, eBullet[i]->x, eBullet[i]->y);
				DeleteEBullet(i);
				i--;
				break;
			}
		}
	}
}

int CheckEnemyAndPlayerCollision(void)
{
	int i;
	for (i = 0; i < numOfEnemy; i++)
	{
		if (enemy[i]->x == player.x && enemy[i]->y == player.y)
		{
			PrintToXY(BLANK, enemy[i]->x, enemy[i]->y);
			DeleteEnemy(i);
			if (player.HitTimer >= player.HitDelay)
			{
				player.HitTimer = 0;
				player.Health--;
				PlacePlayerToStartPoint();
				if (player.Health == 0)
				{
					GameOver();
					return 1;
				}
			}
			break;
		}
	}
	return 0;
}

void checkManaUp(void)
{
	if (manaUpTimer >= manaUpDelay)
	{
		if (player.Mana < FULL_MANA)
		{
			player.Mana++;
			manaUpTimer = 0;
		}
	}
}

void CheckPlayerStateAmend(void)
{
	if (prevHealth != player.Health)
	{
		ShowPlayerState();
		prevHealth = player.Health;
	}

	if (prevMana != player.Mana)
	{
		ShowPlayerState();
		prevMana = player.Mana;
	}
	
	if (prevExp != player.Exp)
	{
		ShowPlayerState();
		prevExp = player.Exp;
	}
}

void UpTimer(void)
{
	int i;

	if (enemySummonTimer < enemySummonDelay)
		enemySummonTimer++;

	if (manaUpTimer < manaUpDelay)
		manaUpTimer++;

	if (player.AttTimer < player.AttDelay)
		player.AttTimer++;

	if (player.MovTimer < player.MovDelay)
		player.MovTimer++;

	if (player.HitTimer < player.HitDelay)
		player.HitTimer++;

	for (i = 0; i < numOfEnemy; i++)
	{
		if (enemy[i]->MovTimer < enemy[i]->MovDelay)
			enemy[i]->MovTimer++;
	}

	for (i = 0; i < numOfEnemy; i++)
	{
		if (enemy[i]->AttTimer < enemy[i]->AttDelay)
			enemy[i]->AttTimer++;
	}

	for (i = 0; i < numOfPBullet; i++)
	{
		if (pBullet[i]->MovTimer < pBullet[i]->MovDelay)
			pBullet[i]->MovTimer++;
	}

	for (i = 0; i < numOfSkill; i++)
	{
		if (pSkill[i]->MovTimer < pSkill[i]->MovDelay)
			pSkill[i]->MovTimer++;
	}

	for (i = 0; i < numOfEBullet; i++)
	{
		if (eBullet[i]->MovTimer < eBullet[i]->MovDelay)
			eBullet[i]->MovTimer++;
	}
}

int ProcessCheck(void)
{
	if (EnemySummonCheck() == 1)
		return 1;
	PBulletMovCheck();
	SkillMovCheck();
	EBulletShootCheck();
	EBulletMovCheck();
	Sleep(SYS_DELAY);
	if (CheckPlayerAndEnemyBulletCollision() == 1)
		return 1;
	CheckEnemyAndPlayerBulletCollision();
	CheckSkillAndEnemyOrBulletCollision();
	if (CheckEnemyAndPlayerCollision())
		return 1;
	EnemyMovCheck();
	checkManaUp();
	UpTimer();
	CheckPlayerStateAmend();
	return 0;
}