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
	//�O�̃t���[�������G�̐����������玀�S�t���O�𗧂Ă�
	if (EnemyCount < preEnemyCount)
	{
		deathFlag = true;
	}

	//�O�t���[���̓G�̐��擾
	preEnemyCount = EnemyCount;
}

void Enemy::Draw()
{
	DrawCircle(posX, posY, r, 0xffffff, false);
}
