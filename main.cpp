#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "cmath"
#include "cstring"
#include "vector"
#include "math.h"
#include "string.h"
#include "Enemy.h"

//�ÓI�����o�ϐ�
int Enemy::EnemyCount;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	char key[256];
	char oldKey[256] = {0};

	const int WindowWidth = 600;
	const int WindowHeight = 400;

	//�G
	const int enemyVol = 5;	//�G�̐�
	Enemy* enemy[enemyVol];
	
	ChangeWindowMode(true);
	SetWindowSize(WindowWidth, WindowHeight);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

		for (int i = 0; i < enemyVol; i++)
		{
			enemy[i] = new Enemy;	//�G����
		}
	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GetHitKeyStateAll(key);
		ClearDrawScreen();


		if (key[KEY_INPUT_1] == 1)
		{
			enemy[0]->Dead();
		}

		//�G�X�V
		for (int i = 0; i < enemyVol; i++)
		{
			enemy[i]->Update();
			//���S�t���O�̗������G���폜
			if (enemy[i]->GetDeathFlag())
			{
				delete enemy[i];
			}
			//�`��
			enemy[i]->Draw();
		}

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}