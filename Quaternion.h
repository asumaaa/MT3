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

//単位Quaternionを返す
Quaternion IdentityQuaternion();
//積
Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);
//共役Quaternionを返す
Quaternion Conjugate(const Quaternion& q);
//Quaternionのnormを返す
float Norm(const Quaternion& q);
//正規化
Quaternion Normalize(const Quaternion& q);
//逆Quaternionを返す
Quaternion Inverse(const Quaternion& q);

