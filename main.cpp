#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "cmath"
#include "cstring"
#include "vector"
#include "Quaternion.h"

//�J�����ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//�J�����̈ʒu
	const Vector3& cameraTarget,	//�J�����̒����_
	const Vector3& cameraUp	//�J�����̏�̌���
);

void DrawString(float x,float y,int color, Quaternion q);


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

	Quaternion q1(2.0f, 3.0f, 4.0f, 1.0f);
	Quaternion q2(1.0f, 3.0f, 5.0f, 2.0f);
	//�P��Quaternion
	Quaternion identity = IdentityQuaternion();
	//����
	Quaternion conj = Conjugate(q1);
	//�t
	Quaternion inv = Inverse(q1);
	//���K��
	Quaternion normal = Normalize(q1);
	//��
	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);
	//norm 
	float norm = Norm(q1);

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�X�V
		
		//�`��
		DrawString(0, 0, 0xffffff, identity);
		DrawString(0, 20, 0xffffff, conj);
		DrawString(0, 40, 0xffffff, inv);
		DrawString(0, 60, 0xffffff, normal);
		DrawString(0, 80, 0xffffff, mul1);
		DrawString(0, 100, 0xffffff, mul2);
		DrawFormatString(0, 120, 0xffffff, "%f", norm);

		DrawFormatString(380, 0, 0xffffff, "Identity");
		DrawFormatString(380, 20, 0xffffff, "Conjugate");
		DrawFormatString(380, 40, 0xffffff, "Inverse");
		DrawFormatString(380, 60, 0xffffff, "Normalize");
		DrawFormatString(380, 80, 0xffffff, "Multiply(q1,q2)");
		DrawFormatString(380, 100, 0xffffff, "Multiply(q2,q1)");
		DrawFormatString(380, 120, 0xffffff, "Normalize");

		ScreenFlip();
	}
	DxLib_End();
	return 0;
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

void DrawString(float x, float y, int color, Quaternion q)
{
	DrawFormatString(x, y, color, "%f %f %f %f", q.v.x, q.v.y, q.v.z, q.w);
}
