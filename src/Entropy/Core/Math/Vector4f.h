#pragma once

class Vector4f
{
public:
    float X, Y, Z, W;

    Vector4f(float x, float y, float z, float w)
        : X(x), Y(y), Z(z), W(w)
    {
    }

    float Length();

    // Modifies the instance
    Vector4f& Normalize();
};
