#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "cmath"
#include "cstring"
#include "vector"
#include "math.h"
#include "string.h"
#include "Enemy.h"

//静的メンバ変数
int Enemy::EnemyCount;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	char key[256];
	char oldKey[256] = {0};

	const int WindowWidth = 600;
	const int WindowHeight = 400;

	//敵
	const int enemyVol = 5;	//敵の数
	Enemy* enemy[enemyVol];
	
	ChangeWindowMode(true);
	SetWindowSize(WindowWidth, WindowHeight);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

		for (int i = 0; i < enemyVol; i++)
		{
			enemy[i] = new Enemy;	//敵生成
		}
	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GetHitKeyStateAll(key);
		ClearDrawScreen();


		if (key[KEY_INPUT_1] == 1)
		{
			enemy[0]->Dead();
		}

		//敵更新
		for (int i = 0; i < enemyVol; i++)
		{
			enemy[i]->Update();
			//死亡フラグの立った敵を削除
			if (enemy[i]->GetDeathFlag())
			{
				delete enemy[i];
			}
			//描画
			enemy[i]->Draw();
		}

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}