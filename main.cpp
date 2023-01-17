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

	Quaternion rotation = MakeAxisAngle({ 0.0f, 0.0f, 1.0f }, 3.141592f / 2.0f);
	Vector3 pointY = { 0.0f,1.0f,0.0f };
	Matrix4 rotateMatrix = MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//更新
		
		//描画
		DrawFormatString(0, 0, 0xffffff, "%f %f %f", rotateByQuaternion.x, rotateByQuaternion.y, rotateByQuaternion.z);
		DrawFormatString(0, 20, 0xffffff, "%f %f %f", rotateByMatrix.x, rotateByMatrix.y, rotateByMatrix.z);

		DrawFormatString(300, 0, 0xffffff, "rotateByQuaternion");
		DrawFormatString(300, 20, 0xffffff, "rotateByMatrix");

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
