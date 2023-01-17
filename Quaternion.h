#pragma once
#include "Vector3.h"

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

