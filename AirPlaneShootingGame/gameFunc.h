#include "common.h"
#include "screenOut.h"

//Create and set player and enemys
void CreatePlayer(void);
void PlacePlayerToStartPoint(void);
void CreateEnemy(void);
void MemAllocateStructPointerArr(void);

//Move Player
void ShiftLeft(void);
void ShiftRight(void);
void ShiftUp(void);
void ShiftDown(void);

//Player shoot
void ShootAttack(void);
void ShootSkill(void);
void UseUlt(void);

//Delete enemy, player's and enemy's bullet
void DeleteEnemy(int enemyIdx);
void DeletePBullet(int pBulletIdx);
void DeleteEBullet(int eBulletIdx);

//Check and implement summoning and moving enemys and bullets
int EnemySummonCheck(void);
void EnemyMovCheck(void);
void PBulletMovCheck(void);
void EBulletShootCheck(void);
void EBulletMovCheck(void);
void SkillMovCheck(void);

//Check Collision 
int CheckPlayerAndEnemyBulletCollision(void);
void CheckEnemyAndPlayerBulletCollision(void);
void CheckSkillAndEnemyOrBulletCollision(void);
int CheckEnemyAndPlayerCollision(void);

//Plus One to Timer
void UpTimer(void);

//Game Over
void GameOver(void);

//Process Checking 
int ProcessCheck(void);
int ProcessEnemySummonAndUpLevelCheck(void);
void BulletMovCheck(void);
int CollisionCheck(void);
void ProcessTimerAndPlayerState(void);

//Display Info
void ShowPlayerState(void);
void CheckPlayerStateAmend(void);
