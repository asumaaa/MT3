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

//’PˆÊQuaternion‚ğ•Ô‚·
Quaternion IdentityQuaternion();
//Ï
Quaternion Multiply(const Quaternion& q1, const Quaternion& q2);
//‹¤–ğQuaternion‚ğ•Ô‚·
Quaternion Conjugate(const Quaternion& q);
//Quaternion‚Ìnorm‚ğ•Ô‚·
float Norm(const Quaternion& q);
//³‹K‰»
Quaternion Normalize(const Quaternion& q);
//‹tQuaternion‚ğ•Ô‚·
Quaternion Inverse(const Quaternion& q);

