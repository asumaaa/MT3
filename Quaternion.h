#pragma once
#include "Vector3.h"
#include "Matrix4.h"

struct Quaternion
{
	Vector3 v;
	float w;
	Quaternion(float x, float y, float z, float w)
	{
		this->v.x = x;
		this->v.y = y;
		this->v.z = z;
		this->w = w;
	}
	Quaternion()
	{
		this->v.x = 0;
		this->v.y = 0;
		this->v.z = 0;
		this->w = 0;
	};
};

//�P��Quaternion��Ԃ�
Quaternion IdentityQuaternion();
//��
Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);
//����Quaternion��Ԃ�
Quaternion Conjugate(const Quaternion& q);
//Quaternion��norm��Ԃ�
float Norm(const Quaternion& q);
//���K��
Quaternion Normalize(const Quaternion& q);
//�tQuaternion��Ԃ�
Quaternion Inverse(const Quaternion& q);
//Quaternion�̓��ς�Ԃ�
float dot(const Quaternion& q0, const Quaternion& q1);

//�C�ӎ���]��\��Quaternion�̐���
Quaternion MakeAxisAngle(const Vector3& vector, float angle);
//�x�N�g����Quaternion�ŉ�]���������ʂ̃x�N�g�������߂�
Vector3 RotateVector(const Vector3& v, const Quaternion& q);
//quaternion�����]�s������߂�
Matrix4 MakeRotateMatrix(const Quaternion& q);

//���ʐ��`���
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

