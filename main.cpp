#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "cmath"
#include "cstring"
#include "vector"
#include "Quaternion.h"

//カメラ設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//カメラの位置
	const Vector3& cameraTarget,	//カメラの注視点
	const Vector3& cameraUp	//カメラの上の向き
);

void Draw(int x,int y,Quaternion q);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	const int WindowWidth = 1024;
	const int WindowHeight = 576;

	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(0, 0, 0);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	Vector3 direction1 = { 1.0f,0.0f,1.0f };
	Vector3 direction2 = { 1.0f,1.0f,0.0f };
	Quaternion dirToDir = DirectionToDirection(direction1, direction2);

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//更新
		
		//描画
		Draw(0, 0, dirToDir);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}

//カメラ設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//カメラの位置
	const Vector3& cameraTarget,	//カメラの注視点
	const Vector3& cameraUp	//カメラの上の向き
)
{
	VECTOR position = { cameraPosition.x ,cameraPosition.y ,cameraPosition.z };
	VECTOR target = { cameraTarget.x ,cameraTarget.y ,cameraTarget.z };
	VECTOR up = { cameraUp.x ,cameraUp.y ,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

void Draw(int x, int y, Quaternion q)
{
	DrawFormatString(x, y, 0xffffff, "%f %f %f %f", q.v.x, q.v.y, q.v.z, q.w);
}
