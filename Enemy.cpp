#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(int x, int y)
{
	this->posX = x;
	this->posY = y;
}

void Enemy::Update()
{
	//シーンマネージャー
	SceneManager();

	(this->*Scene[scene])();
}

void Enemy::Approach()
{
	posX += 2;
}

void Enemy::Shot()
{
}

void Enemy::Leave()
{
	posX -= 2;
}

void Enemy::SceneManager()
{
	//300でリセットするタイマーを更新
	sceneTimer++;
	if (sceneTimer >= 300)sceneTimer = 0;

	//タイマーによってシーンチェンジ
	if (sceneTimer >= 0 && sceneTimer < 100)scene = static_cast<size_t>(Scene::Approach);
	if (sceneTimer >= 100 && sceneTimer < 200)scene = static_cast<size_t>(Scene::Shot);
	if (sceneTimer >= 200 && sceneTimer < 300)scene = static_cast<size_t>(Scene::Leave);
}

void Enemy::Draw()
{
	DrawCircle(posX, posY, r, 0xffffff, false);
	if (scene == static_cast<size_t>(Scene::Approach))	DrawFormatString(0, 0, 0xffffff, "Scene:Approach");
	if (scene == static_cast<size_t>(Scene::Shot))		DrawFormatString(0, 0, 0xffffff, "Scene:Shot");
	if (scene == static_cast<size_t>(Scene::Leave))		DrawFormatString(0, 0, 0xffffff, "Scene:Leave");
}

void(Enemy::* Enemy::Scene[])() =
{
	&Enemy::Approach,
	&Enemy::Shot,
	&Enemy::Leave,
};