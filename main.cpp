#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "cmath"
#include "cstring"

//球の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//カメラ設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//カメラの位置
	const Vector3& cameraTarget,	//カメラの注視点
	const Vector3& cameraUp	//カメラの上の向き
);

//線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned Color);

//円錐の描画
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//x,y,z軸の描画
void DrawAxis3D(const float length);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	const int WindowWidth = 1024;
	const int WindowHeight = 576;

	ChangeWindowMode(true);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetBackgroundColor(0, 0, 64);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//球体の座標
	Vector3 SpherePos(-10.0f, 0, 0);

	//カメラ設定
	Vector3 cameraPosition(0.0f, 300.0f, 0.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 0.0f, 1.0f);
	//		クリップ面
	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,
		cameraTarget,
		cameraUp
	);

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	//時間計測に必要なデータ
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	//補間で使うデータ
	Vector3 p0(-200.0f, 0.0f, 0.0f);	//スタート地点
	Vector3 p1(-100.0f, 0.0f, +100.0f);	//制御点
	Vector3 p2(+100.0f, 0.0f, -100.0f);	//制御点
	Vector3 p3(+200.0f, 0.0f, 0.0f);	//エンド地点
	float	maxTime = 5.0f;				//全体時間[s]
	float	timeRate;					//何％時間が進んだか(率)

	//球の位置
	Vector3 position;

	//実行前にカウンタ値を取得
	startCount = GetNowHiPerformanceCount();

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//[R]キーでリスタート
		if (CheckHitKey(KEY_INPUT_R))
		{
			startCount = GetNowHiPerformanceCount();
		}

		//更新
		//経過時間の計算
		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;
		float elapsedTime = static_cast<float>(elapsedCount) / 1'000'000.0f;

		timeRate = min(elapsedTime / maxTime, 1.0f);

		//2次ベジエ曲線
		Vector3 a = lerp(p0, p1, timeRate);
		Vector3 b = lerp(p1, p2, timeRate);
		Vector3 c = lerp(p2, p3, timeRate);

		Vector3 d = lerp(a, b, timeRate);
		Vector3 e = lerp(b, c, timeRate);

		position = lerp(d, e, timeRate);
		
		//描画
		ClearDrawScreen();	//画面を消去
		DrawAxis3D(500.0f);	//x,y,z軸の描画
		DrawSphere3D(position, 8.0f, 32.0f, GetColor(255, 0, 0), GetColor(255, 255, 255), true);
		DrawSphere3D(p0, 4.0f, 32.0f, GetColor(0, 255, 0), GetColor(255, 255, 255), true);
		DrawSphere3D(p1, 4.0f, 32.0f, GetColor(0, 255, 0), GetColor(255, 255, 255), true);
		DrawSphere3D(p2, 4.0f, 32.0f, GetColor(0, 255, 0), GetColor(255, 255, 255), true);
		DrawSphere3D(p3, 4.0f, 32.0f, GetColor(0, 255, 0), GetColor(255, 255, 255), true);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}


//球の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };
	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
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

//線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y ,Pos1.z };
	VECTOR p2 = { Pos2.x,Pos2.y ,Pos2.z };

	return  DrawLine3D(p1, p2, Color);
}

//円錐の描画
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR topPos = { TopPos.x,TopPos.y,TopPos.z };
	VECTOR bottomPos = { BottomPos.x,BottomPos.y,BottomPos.z };

	return DrawCone3D(topPos, bottomPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

void DrawAxis3D(const float length)
{
	DrawLine3D(Vector3(-length, 0, 0), Vector3(+length, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(Vector3(0, -length, 0), Vector3(0, +length, 0), GetColor(0, 255, 0));
	DrawLine3D(Vector3(0, 0, -length), Vector3(0, 0, +length), GetColor(0, 0, 255));

	const float coneSize = 10.0f;
	/*DrawCone3D(Vector3(length, 0, 0), Vector3(length - coneSize, 0, 0), coneSize / 2, 16,
		GetColor(255, 0, 0), GetColor(255, 255, 255), true);
	DrawCone3D(Vector3(0, length, 0), Vector3(0, length - coneSize, 0), coneSize / 2, 16,
		GetColor(0, 255, 0), GetColor(255, 255, 255), true);
	DrawCone3D(Vector3(0, 0, length), Vector3(0, 0, length - coneSize), coneSize / 2, 16,
		GetColor(0, 0, 255), GetColor(255, 255, 255), true);*/
}