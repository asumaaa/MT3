#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
	EnemyCount++;

	posX = EnemyCount * 32;
	posY = 32;
	r = 16;
}

void Enemy::Update()
{
	//前のフレームよりも敵の数が減ったら死亡フラグを立てる
	if (EnemyCount < preEnemyCount)
	{
		deathFlag = true;
	}

	//前フレームの敵の数取得
	preEnemyCount = EnemyCount;
}

void Enemy::Draw()
{
	DrawCircle(posX, posY, r, 0xffffff, false);
}
