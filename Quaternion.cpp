#include "Quaternion.h"
#include "cmath"
#include "math.h"
#define PI 3.141592
#define EPSILON 0.000001

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

float dot(const Quaternion& q0, const Quaternion& q1)
{
    return (q0.w * q1.w) + (q0.v.x * q1.v.x) + (q0.v.y * q1.v.y) + (q0.v.z * q1.v.z);
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

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
    Quaternion q2 = q0;
    Quaternion q3 = q1;

    //“àÏ
    float d = dot(q2,q3);

    if(d < 0)
    { 
        q2 = Conjugate(q2);   //‚à‚¤•Ğ•û‚Ì‰ñ“]‚ğ—˜—p‚·‚é
        d = -d;     //“àÏ‚à”½“]
    }

    //‚È‚·Šp‚ª0‚Ìê‡
    if (d >= 1.0f - EPSILON)
    {
        return Quaternion((1.0f - t) * q2.v.x + t * q3.v.x, (1.0f - t) * q2.v.y + t * q3.v.y,
            (1.0f - t) * q2.v.z + t * q3.v.z, (1.0f - t) * q2.w + t * q3.w);
    }

    //‚È‚·Šp‚ğ‹‚ß‚é
    float theta = std::acos(d);

    //theta‚Æsin‚ğg‚Á‚Ä•âŠ®ŒW”scale0,scale1‚ğ‹‚ß‚é
    float scale0 = (sin((1 - t) * theta) / sin(theta));
    float scale1 = (sin(t * theta) / sin(theta));

    return Quaternion(q2.v.x * scale0 + q3.v.x * scale1, q2.v.y * scale0 + q3.v.y * scale1,
        q2.v.z * scale0 + q3.v.z * scale1, q2.w * scale0 + q3.w * scale1);
}

Quaternion DirectionToDirection(const Vector3& u, const Vector3& v)
{
    Vector3 v1 = u;
    Vector3 v2 = v;

    //u‚Æv‚ğ³‹K‰»‚µ‚Ä“àÏ‚ğ‹‚ß‚é
    float dot = v1.normalize().dot(v2.normalize());
    //u,v‚ÌŠOÏ
    Vector3 cross = v1.cross(v2);
    //²‚ğ³‹K‰»
    Vector3 axis = cross.normalize();
    //’PˆÊƒxƒNƒgƒ‹‚Å“àÏ‚ğ‚Æ‚Á‚Ä‚¢‚é‚Ì‚Åacos‚ÅŠp“x‚ğ‹‚ß‚é
    float theta = std::acos(dot);

    return MakeAxisAngle(axis,theta);
}
