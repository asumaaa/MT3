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

	Quaternion rotation0 = MakeAxisAngle({ 0.71f, 0.71f, 0.0f }, 0.3f);
	Quaternion rotation1 = MakeAxisAngle({ -0.71f, -0.71f, -0.0f }, -0.3f);

	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//更新
		
		//描画
		Draw(0, 0, interpolate0);
		Draw(0, 30, interpolate1);
		Draw(0, 60, interpolate2);
		Draw(0, 90, interpolate3);
		Draw(0, 120, interpolate4);

		DrawFormatString(350, 0, 0xffffff, "interpolate0:Slerp(q0,q1,0.0f)");
		DrawFormatString(350, 30, 0xffffff, "interpolate1:Slerp(q0,q1,0.3f)");
		DrawFormatString(350, 60, 0xffffff, "interpolate2:Slerp(q0,q1,0.5f)");
		DrawFormatString(350, 90, 0xffffff, "interpolate3:Slerp(q0,q1,0.7f)");
		DrawFormatString(350, 120, 0xffffff, "interpolate4:Slerp(q0,q1,1.0f)");

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
