#ifndef GLMATH_H
#define GLMATH_H

#include <stdio.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} Vec2;

typedef struct {
	float x;
	float y;
	float z;
} Vec3;

typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4;

typedef struct {
	float xx; float yx; float zx; float wx;
	float xy; float yy; float zy; float wy;
	float xz; float yz; float zz; float wz; 
	float xw; float yw; float zw; float ww;
} Matrix;

Vec2 vec2New(float, float);
Vec3 vec3New(float, float, float);
Vec4 vec4New(float, float, float, float);

Vec3 quatConvertEuler(Vec4);
Vec4 eulerConvertQuat(Vec3);

Matrix matrixEmpty();
Matrix matrixIdentity();
Matrix matrixTranslate(Vec3);
Matrix matrixScale(Vec3);
Matrix matrixRotateEuler(Vec3);
Matrix matrixRotateQuat(Vec4);
Matrix matrixPerspective(float, float, float, float);

Vec2 vec2MultiplyMatrix(Vec2, Matrix);
Vec3 vec3MultiplyMatrix(Vec3, Matrix);
Vec4 vec4MultiplyMatrix(Vec4, Matrix);
Matrix matrixMultiplyMatrix(Matrix, Matrix);

#endif