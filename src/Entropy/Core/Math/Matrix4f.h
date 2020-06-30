//#pragma once
//
//#include "Vector3f.h"
//
//class Matrix4f
//{
//public:
//	Matrix4f();
//	~Matrix4f();
//
//	Matrix4f& Identity();
//
//	Matrix4f& Translate(const Vector3f& amount);
//	Matrix4f& Translate(float x, float y, float z);
//	Matrix4f& Rotate(float angle, const Vector3f& axis);
//	Matrix4f& Scale(const Vector3f& amount);
//	Matrix4f& Scale(float x, float y, float z);
//
//	Matrix4f& PerspectiveProjection(float fovDegrees, float aspectRatio, float near, float far);
//
//	// Does not modify this
//	Matrix4f& operator* (const Matrix4f& other) const;
//
//	// Modifies instance
//	Matrix4f& operator*= (const Matrix4f& other);
//
//public:
//	float m[4][4] = { 0 };
//};
