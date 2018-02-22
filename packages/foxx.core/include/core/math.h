#ifndef CORE_MATH_H
#define CORE_MATH_H

#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
	float xx; float xy; float xz; float xw;
	float yx; float yy; float yz; float yw;
	float zx; float zy; float zz; float zw;
	float wx; float wy; float wz; float ww;
} Mat4;

/**
 * Vector functions.
 */
Vec2 vec2(float, float);
Vec3 vec3(float, float, float);
Vec4 vec4(float, float, float, float);

Vec2 vec2Negative(Vec2);
Vec3 vec3Negative(Vec3);
Vec4 vec4Negative(Vec4);

Vec2 vec2Normalize(Vec2);
Vec3 vec3Normalize(Vec3);
Vec4 vec4Normalize(Vec4);

Vec2 vec2AddVec2(Vec2, Vec2);
Vec3 vec3AddVec3(Vec3, Vec3);
Vec4 vec4AddVec4(Vec4, Vec4);

Vec2 vec2SubtractVec2(Vec2, Vec2);
Vec3 vec3SubtractVec3(Vec3, Vec3);
Vec4 vec4SubtractVec4(Vec4, Vec4);

Vec2 vec2MultiplyVec2(Vec2, Vec2);
Vec3 vec3MultiplyVec3(Vec3, Vec3);
Vec4 vec4MultiplyVec4(Vec4, Vec4);

Vec2 vec2DivideVec2(Vec2, Vec2);
Vec3 vec3DivideVec3(Vec3, Vec3);
Vec4 vec4DivideVec4(Vec4, Vec4);

/**
 * TODO: Test these are correct.
 */
Vec2 vec2MultiplyMat4(Vec2, Mat4);
Vec3 vec3MultiplyMat4(Vec3, Mat4);
Vec4 vec4MultiplyMat4(Vec4, Mat4);

Vec3 vec3CrossProduct();

/**
 * Quaternion functions.
 */
Vec4 quatRotationX(float);
Vec4 quatRotationY(float);
Vec4 quatRotationZ(float);
Vec4 quatRotationAxis(Vec3, float);

Vec4 quatMultiplyQuat(Vec4, Vec4);

/**
 * Matrix functions.
 */
Mat4 mat4Empty();
Mat4 mat4Identity();

Mat4 mat4Translation(Vec3);
Mat4 mat4Scale(Vec3);

Mat4 mat4RotationEuler(Vec3);
Mat4 mat4RotationQuat(Vec4);

float mat4Determinant(Mat4);
Mat4 mat4Inverse(Mat4);
Mat4 mat4Transpose(Mat4);

Mat4 mat4LookAt(Vec3, Vec3, Vec3);
Mat4 mat4Orthographic(float, float, float, float, float, float);
Mat4 mat4Perspective(float, float, float, float);

Mat4 mat4MultiplyMat4(Mat4, Mat4);

/**
 * Helper functions.
 */
float degreesToRadians(float);
float radiansToDegrees(float);

#endif