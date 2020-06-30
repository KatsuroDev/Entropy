#pragma once

class Vector3f
{
public:
    float X, Y, Z;

    Vector3f(float x = 0, float y = 0, float z = 0)
        : X(x), Y(y), Z(z)
    {
    }

    float Length();

    // Modifies the instance
    Vector3f& Normalize();

    // Modifies the instance
    Vector3f& Rotate(float angle, const Vector3f& axis);
};
