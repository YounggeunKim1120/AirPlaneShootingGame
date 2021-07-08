#ifndef __PLAYER_STATE_STRUCT_H_
#define __PLAYER_STATE_STRUCT_H_

typedef struct _playerState {
	int x;
	int y;
	int Health;
	int Mana;
	int Power;
	int AttDelay;
	int MovDelay;
	int AttTimer;
	int MovTimer;
	int HitDelay;
	int HitTimer;
	int Exp;
} playerState;

typedef struct _enemyState {
	int grade;
	int x; 
	int y;
	int Health;
	int AttDelay;
	int MovDelay;
	int AttTimer;
	int MovTimer;
	int MovMode;
	int Exp;
} enemyState;

typedef struct _bullet {
	int x;
	int y;
	int Power;
	int MovDelay;
	int MovTimer;
} bullet;

typedef struct _skill {
	int x;
	int y;
	int Power;
	int MovDelay;
	int MovTimer;
} skill;
#endif