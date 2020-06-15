#pragma once

class Matrix4f
{
public:
    Matrix4f();
    ~Matrix4f();

    Matrix4f& Identity();

private:
    float m[4][4];
};
