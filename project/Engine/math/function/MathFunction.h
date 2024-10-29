#pragma once
// Include
#include <cmath>
#include <numbers>
#include <vector>

// MyHedder
#include "math/operator/MathOperator.h"

///
/// Vector2
/// 



///
/// Vector3
/// 

// ベクトルの長さ
float Length(const Vector3& a);

// 正規化
Vector3 Normalize(const Vector3& a);

// ワールド行列からワールド座標取得
Vector3 ExtractionWorldPos(const Matrix4x4& m);

// スプライン曲線補間
Vector3 CatmullRomSpline(const std::vector<Vector3>& controlPoints, float t);

// 線形補完
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);


///
/// Vector4
/// 


///
/// Matrix4x4
/// 

// 単位行列作成関数
Matrix4x4 MakeIdentityMatrix4x4();

// 逆行列作成関数
Matrix4x4 Inverse(const Matrix4x4& a);

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& a);

// 逆転置行列
Matrix4x4 MakeInverseTransposeMatrix(const Matrix4x4& a);

// 拡縮行列作成関数
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// 回転行列作成関数
Matrix4x4 MakeRotateXMatrix(float radian); // X回転
Matrix4x4 MakeRotateYMatrix(float radian); // Y回転
Matrix4x4 MakeRotateZMatrix(float radian); // Z回転
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate); // XYZ回転

// 平行移動行列作成関数
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// アフィン変換関数
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Quaternion& rotate, const Vector3& translate);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRaito, float nearClip, float farClip);

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

// UV用行列作成
Matrix4x4 MakeUVMatrix(const Vector2& scale, const float& rotateZ, const Vector2& translate);

// クオータニオンから回転行列への変換
Matrix4x4 QuaternionToMatrix4x4(const Quaternion& q);


///
/// Quaternion
/// 

// 正規化
Quaternion Normalize(const Quaternion& q);

// 球面線形補完
Quaternion Slerp(Quaternion q1, Quaternion q2, float t);
