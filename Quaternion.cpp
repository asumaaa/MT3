#include "Quaternion.h"
#include "cmath"
#include "math.h"
#define PI 3.141592

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

Quaternion MakeAxisAngle(const Vector3& vector, float angle)
{
    Quaternion q;

    Vector3 v = vector;
    v.normalize();

    q.w = cos(angle / 2);
    q.v = v.normalize() * sin(angle / 2);

    return q;
}

Vector3 RotateVector(const Vector3& v, const Quaternion& q)
{
    Quaternion q1(v.x, v.y, v.z, 0);
    Quaternion q2;
    q2 = Multiply(Multiply(q, q1),Inverse(q));

    return Vector3(q2.v.x, q2.v.y, q2.v.z);
}

Matrix4 MakeRotateMatrix(const Quaternion& q)
{
    float x = q.v.x;
    float y = q.v.y;
    float z = q.v.z;
    float w = q.w;
    Matrix4 m1
    {
        pow(w,2.0f) + pow(x,2.0f) - pow(y,2.0f) - pow(z,2.0f),  2 * (x * y + w * z),    2 * (x * z - w * y),    0,
        2 * (x * y - w * z),    pow(w,2.0f) - pow(x,2.0f) + pow(y,2.0f) - pow(z,2.0f),  2 * (y * z + w * x),    0,
        2 * (x * z + w * y),    2 * (y * z - w * x),    pow(w,2.0f) - pow(x,2.0f) - pow(y,2.0f) + pow(z,2.0f),  0,
        0,0,0,1
    };
    return m1;
}
