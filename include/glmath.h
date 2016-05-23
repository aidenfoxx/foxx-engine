#ifndef GLMATH_H
#define GLMATH_H

#include <stdio.h>
#include <math.h>

typedef struct {
	int x;
	int y;
} Vector2i;

typedef struct {
	int x;
	int y;
	int z;
} Vector3i;

typedef struct {
	int x;
	int y;
	int z;
	int w;
} Vector4i;

typedef struct {
	float x;
	float y;
} Vector2f;

typedef struct {
	float x;
	float y;
	float z;
} Vector3f;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vector4f;

typedef struct {
	float xx; float yx; float zx; float wx;
	float xy; float yy; float zy; float wy;
	float xz; float yz; float zz; float wz;
	float xw; float yw; float zw; float ww;
} Matrix4;

Vector2i vector2i(int, int);
Vector3i vector3i(int, int, int);
Vector4i vector4i(int, int, int, int);

Vector2f vector2f(float, float);
Vector3f vector3f(float, float, float);
Vector4f vector4f(float, float, float, float);

Vector3f quatConvertEuler(Vector4f);
Vector4f eulerConvertQuat(Vector3f);

Matrix4 matrix4Empty();
Matrix4 matrix4Identity();
Matrix4 matrix4Translate(Vector3f);
Matrix4 matrix4Scale(Vector3f);
Matrix4 matrix4Euler(Vector3f);
Matrix4 matrix4Quat(Vector4f);
float matrix4Determinant(Matrix4);
Matrix4 matrix4Invert(Matrix4);
Matrix4 matrix4Transpose(Matrix4);
Matrix4 matrix4Orthographic(float, float, float, float, float, float);
Matrix4 matrix4Perspective(float, float, float, float);

Vector2f vector2fMultiplyMatrix4(Vector2f, Matrix4);
Vector3f vector3fMultiplyMatrix4(Vector3f, Matrix4);
Vector4f vector4fMultiplyMatrix4(Vector4f, Matrix4);
Matrix4 matrix4MultiplyMatrix4(Matrix4, Matrix4);

#endif