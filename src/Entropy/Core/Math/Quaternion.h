#pragma once

#include "Vector3f.h"

class Quaternion
{
public:
    float X, Y, Z, W;

    Quaternion(float x, float y, float z, float w)
        : X(x), Y(y), Z(z), W(w)
    {

    }

    float length();

    // Modifies the instance
    Quaternion& normalize();

    // Does NOT modify the instance
    // Reverses all components of quaternion
    Quaternion conjugate();

    // Does NOT modify the instance
    Quaternion operator* (const Quaternion& r);

    // Does NOT modify the instance
    Quaternion operator* (const Vector3f& r);
};
