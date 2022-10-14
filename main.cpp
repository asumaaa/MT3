#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "cmath"
#include "cstring"

//���̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//�J�����ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//�J�����̈ʒu
	const Vector3& cameraTarget,	//�J�����̒����_
	const Vector3& cameraUp	//�J�����̏�̌���
);

//�����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned Color);

//�~���̕`��
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//x,y,z���̕`��
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

	//���̂̍��W
	Vector3 SpherePos(-10.0f, 0, 0);

	//�J�����ݒ�
	Vector3 cameraPosition(0.0f, 300.0f, 0.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 0.0f, 1.0f);
	//		�N���b�v��
	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,
		cameraTarget,
		cameraUp
	);

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	//���Ԍv���ɕK�v�ȃf�[�^
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	//��ԂŎg���f�[�^
	Vector3 p0(-200.0f, 0.0f, 0.0f);	//�X�^�[�g�n�_
	Vector3 p1(-100.0f, 0.0f, +100.0f);	//����_
	Vector3 p2(+100.0f, 0.0f, -100.0f);	//����_
	Vector3 p3(+200.0f, 0.0f, 0.0f);	//�G���h�n�_
	float	maxTime = 5.0f;				//�S�̎���[s]
	float	timeRate;					//�������Ԃ��i�񂾂�(��)

	//���̈ʒu
	Vector3 position;

	//���s�O�ɃJ�E���^�l���擾
	startCount = GetNowHiPerformanceCount();

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//[R]�L�[�Ń��X�^�[�g
		if (CheckHitKey(KEY_INPUT_R))
		{
			startCount = GetNowHiPerformanceCount();
		}

		//�X�V
		//�o�ߎ��Ԃ̌v�Z
		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;
		float elapsedTime = static_cast<float>(elapsedCount) / 1'000'000.0f;

		timeRate = min(elapsedTime / maxTime, 1.0f);

		//2���x�W�G�Ȑ�
		Vector3 a = lerp(p0, p1, timeRate);
		Vector3 b = lerp(p1, p2, timeRate);
		Vector3 c = lerp(p2, p3, timeRate);

		Vector3 d = lerp(a, b, timeRate);
		Vector3 e = lerp(b, c, timeRate);

		position = lerp(d, e, timeRate);
		
		//�`��
		ClearDrawScreen();	//��ʂ�����
		DrawAxis3D(500.0f);	//x,y,z���̕`��
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


//���̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };
	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

//�J�����ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//�J�����̈ʒu
	const Vector3& cameraTarget,	//�J�����̒����_
	const Vector3& cameraUp	//�J�����̏�̌���
)
{
	VECTOR position = { cameraPosition.x ,cameraPosition.y ,cameraPosition.z };
	VECTOR target = { cameraTarget.x ,cameraTarget.y ,cameraTarget.z };
	VECTOR up = { cameraUp.x ,cameraUp.y ,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

//�����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y ,Pos1.z };
	VECTOR p2 = { Pos2.x,Pos2.y ,Pos2.z };

	return  DrawLine3D(p1, p2, Color);
}

//�~���̕`��
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