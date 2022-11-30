#include "DxLib.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "cmath"
#include "cstring"
#include "vector"
#include "math.h"

POINT MousePoint;

struct Vec2
{
	int x;
	int y;
};

bool CircleCollision(Vec2 circle, int r, Vec2 vector1, Vec2 vector2);

float vectorLength(Vec2 vector);

Vec2 vectorNormalize(Vec2 vector);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	const int WindowWidth = 600;
	const int WindowHeight = 400;

	ChangeWindowMode(true);
	SetWindowSize(WindowWidth, WindowHeight);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	// �}�E�X��\����Ԃɂ���
	SetMouseDispFlag(TRUE);
	// �}�E�X�J�[�\���̃X�N���[�����W���擾
	GetCursorPos(&MousePoint);
	//�}�E�X���W
	Vec2 mouse;

	//���̎n�_���W
	Vec2 point = { 100,100 };

	//�~���W
	Vec2 circle = { 200,200 };
	//�~���a
	int r = 32;
	//�~�̐F
	int color = 0xffffff;

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		// �}�E�X�̈ʒu���擾
		GetMousePoint(&mouse.x, &mouse.y);

		//�����蔻��ɂ���ĐF�ύX
		if (CircleCollision(circle, r, point, mouse))
		{
			color = 0xff00ff;
		}
		else
		{
			color = 0xffffff;
		}

		//����`��
		DrawLine(point.x, point.y, mouse.x, mouse.y, 0xffffff, true);
		//�~��`��
		DrawCircle(circle.x, circle.y, r, color, true);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}

bool CircleCollision(Vec2 circle, int r, Vec2 vector1, Vec2 vector2)
{
	//�����̃x�N�g��
	Vec2 vec1= { vector2.x - vector1.x ,vector2.y - vector1.y };
	//���K��
	Vec2 vec1Normal = vectorNormalize(vec1);

	//�����̎n�_����~�̒��S
	Vec2 vec2 = { circle.x - vector1.x,circle.y - vector1.y };
	//�����̏I�_����~�̒��S
	Vec2 vec3 = { circle.x - vector2.x,circle.y - vector2.y };

	//�����Ɖ~�̋���
	int Vec4 = vec3.x * vec1Normal.y - vec1Normal.x * vec3.y;

	if (fabs(Vec4) < r)
	{
		int dot1 = vec2.x * vec1.x + vec2.y * vec1.y;
		int dot2 = vec3.x * vec1.x + vec3.y * vec1.y;
		if (dot1 * dot2 < 0)
		{
			return true;
		}
	}


	return false;
}

float vectorLength(Vec2 vector)
{
	float x2 = vector.x * vector.x;
	float y2 = vector.y * vector.y;
	return sqrt(x2 + y2);
}

Vec2 vectorNormalize(Vec2 vector)
{
	Vec2 v;
	v.x = vector.x / vectorLength(vector);
	v.y = vector.y / vectorLength(vector);

	return v;
}
