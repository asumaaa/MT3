#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "cmath"
#include "cstring"
#include "vector"
#include "math.h"
#include "string.h"
#include "Enemy.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	char key[256];
	char oldKey[256] = {0};

	const int WindowWidth = 600;
	const int WindowHeight = 400;

	//“G
	Enemy* enemy = new Enemy(100,100);
	
	ChangeWindowMode(true);
	SetWindowSize(WindowWidth, WindowHeight);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	//ƒQ[ƒ€ƒ‹[ƒv
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GetHitKeyStateAll(key);
		ClearDrawScreen();

		//“G‚ÌXV•`‰æ
		enemy->Update();
		enemy->Draw();

		ScreenFlip();
	}

	delete enemy;

	DxLib_End();
	return 0;
}