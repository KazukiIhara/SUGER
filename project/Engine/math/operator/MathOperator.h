#pragma once
#include "math/types/Vector2.h"
#include "math/types/Vector3.h"
#include "math/types/Vector4.h"
#include "math/types/Matrix4x4.h"
#include "math/types/Quaternion.h"

///
/// Vector2
///

Vector2 operator-(const Vector2& v);
Vector2 operator+(const Vector2& v);

///
/// Vector2 & Vector2
///

Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
Vector2 operator*(const Vector2& v1, const Vector2& v2);
Vector2 operator/(const Vector2& v1, const Vector2& v2);

///
/// Vector2 & Scaler
///

Vector2 operator/(const Vector2& v, float s);
Vector2 operator*(float s, const Vector2& v);
Vector2 operator*(const Vector2& v, float s);

///
/// Vector3
///

Vector3 operator-(const Vector3& v);
Vector3 operator+(const Vector3& v);

///
/// Vector3 & Vector3
///

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v1, const Vector3& v2);
Vector3 operator/(const Vector3& v1, const Vector3& v2);

///
/// Vector3 & Scaler
///

Vector3 operator*(float s, const Vector3& v);
Vector3 operator*(const Vector3& v, float s);
Vector3 operator/(const Vector3& v, float s);

///
/// Vector4
///

Vector4 operator-(const Vector4& v);
Vector4 operator+(const Vector4& v);

///
/// Vector4 & Vector4
///

Vector4 operator+(const Vector4& v1, const Vector4& v2);
Vector4 operator-(const Vector4& v1, const Vector4& v2);
Vector4 operator*(const Vector4& v1, const Vector4& v2);
Vector4 operator/(const Vector4& v1, const Vector4& v2);

///
/// Vector4 & Scaler
///

Vector4 operator*(float s, const Vector4& v);
Vector4 operator*(const Vector4& v, float s);
Vector4 operator/(const Vector4& v, float s);

///
/// Matrix4x4
///

///
/// Matrix4x4 & Matrix4x4
///

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

///
/// Quaternion
///

///
/// Quaternion & Quaternion
///

Quaternion operator+(const Quaternion& q1, const Quaternion& q2);
Quaternion operator-(const Quaternion& q1, const Quaternion& q2);

///
/// Quaternion & Scaler
///