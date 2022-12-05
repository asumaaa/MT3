#pragma once
class Enemy
{
protected:
public:
	Enemy(int x,int y);
	~Enemy() {};
public:
	void Update();
	void Approach();
	void Shot();
	void Leave();
	void SceneManager();
	void Draw();
	void Dead() { deathFlag = true; };
	bool GetDeathFlag() { return deathFlag; };
private:
	int posX, posY;
	int r = 32;
	int preEnemyCount;
	bool deathFlag = false;
	//シーン用のタイマー
	int sceneTimer = 0;
	//シーン
	enum class Scene
	{
		Approach,
		Shot,
		Leave,
	};
	//シーン	最初がタイトル
	size_t scene = static_cast<size_t>(Scene::Approach);
	//メンバ関数のポインタテーブル
	static void (Enemy::* Scene[])();
};

