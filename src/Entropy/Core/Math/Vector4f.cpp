#include "Vector4f.h"

#include <math.h>

float Vector4f::Length()
{
    return sqrtf(X * X + Y * Y + Z * Z + W * W);
}

Vector4f& Vector4f::Normalize()
{
    float length = this->Length();
    X /= length;
    Y /= length;
    Z /= length;
    W /= length;
    return *this;
}
