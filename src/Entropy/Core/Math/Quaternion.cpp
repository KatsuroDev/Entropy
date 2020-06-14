#include "Quaternion.h"

#include <math.h>

float Quaternion::length()
{
    return (float)sqrt(X * X + Y * Y + Z * Z + W * W);
}

Quaternion& Quaternion::normalize()
{
    float length = this->length();
    X /= length;
    Y /= length;
    Z /= length;
    W /= length;
    return *this;
}

Quaternion Quaternion::conjugate()
{
    // The 'real' component W keeps it's value
    return Quaternion(-X, -Y, -Z, W);
}

Quaternion Quaternion::operator* (const Quaternion& r)
{
    return Quaternion
    (X * r.W + W * r.X + Y * r.Z - Z * r.Y,
     Y * r.W + W * r.Y + Z * r.X - X * r.Z,
     Z * r.W + W * r.Z + X * r.Y - Y * r.X,
     W * r.W - X * r.X - Y * r.Y - Z * r.Z);
}

Quaternion Quaternion::operator* (const Vector3f& r)
{
    float x = W * r.X + Y * r.Z - Z * r.Y;
    float y = W * r.Y + Z * r.X - X * r.Z;
    float z = W * r.Z + X * r.Y - Y * r.X;
    float w = -X * r.X - Y * r.Y - Z * r.Z;

    return Quaternion(x, y ,z ,w);
}
