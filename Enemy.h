#pragma once
class Enemy
{
protected:
public:
	static int EnemyCount;
	Enemy();
	~Enemy() { EnemyCount--; };
public:
	void Update();
	void Draw();
	void Dead() { deathFlag = true; };
	bool GetDeathFlag() { return deathFlag; };
private:
	int posX, posY;
	int r;
	int preEnemyCount;
	bool deathFlag = false;
};

