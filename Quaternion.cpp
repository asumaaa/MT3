#include "Quaternion.h"
#include "cmath"
#include "math.h"

Quaternion IdentityQuaternion()
{
    Quaternion i(0, 0, 0, 0);
    return i;
}

Quaternion Multiply(const Quaternion& q1, const Quaternion& q2)
{
    Quaternion q = IdentityQuaternion();

    q.w = (q1.w * q2.w) - q1.v.dot(q2.v);
    q.v = q1.v.cross(q2.v) + (q1.v * q2.w) + (q2.v * q1.w);

    return q;
}

Quaternion Conjugate(const Quaternion& q)
{
    return Quaternion(-q.v.x, -q.v.y, -q.v.z, q.w);
}

float Norm(const Quaternion& q)
{
    return sqrt(pow(q.v.x,2.0f) + pow(q.v.y, 2.0f) + pow(q.v.z, 2.0f) + pow(q.w, 2.0f));
}

Quaternion Normalize(const Quaternion& q)
{
    return Quaternion(q.v.x / Norm(q), q.v.y / Norm(q), q.v.z / Norm(q), q.w / Norm(q));
}

Quaternion Inverse(const Quaternion& q)
{
    float n = pow(Norm(q),2.0f);
    return Quaternion(Conjugate(q).v.x/n, Conjugate(q).v.y / n, Conjugate(q).v.z / n, Conjugate(q).w / n);
}
