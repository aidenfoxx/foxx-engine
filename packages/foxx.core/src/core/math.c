#include "core/math.h"

Vec2 vec2(float x, float y)
{
	Vec2 vector = {x, y};
	return vector;
}

Vec3 vec3(float x, float y, float z)
{
	Vec3 vector = {x, y, z};
	return vector;
}

Vec4 vec4(float x, float y, float z, float w)
{
	Vec4 vector = {x, y, z, w};
	return vector;
}

/**
 * Vector negative.
 */
Vec2 vec2Negative(Vec2 v)
{
	return vec2(-v.x, -v.y);
}

Vec3 vec3Negative(Vec3 v)
{
	return vec3(-v.x, -v.y, -v.z);
}

Vec4 vec4Negative(Vec4 v)
{
	return vec4(-v.x, -v.y, -v.z, -v.w);
}

/**
 * Vector normalize.
 */
Vec2 vec2Normalize(Vec2 v)
{	
	float length = sqrtf((v.x * v.x) + (v.y * v.y));
	return length == 0.0f ? vec2(0.0f, 0.0f) : vec2DivideVec2(v, vec2(length, length));
}

Vec3 vec3Normalize(Vec3 v)
{	
	float length = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return length == 0.0f ? vec3(0.0f, 0.0f, 0.0f) : vec3DivideVec3(v, vec3(length, length, length));
}

Vec4 vec4Normalize(Vec4 v)
{
	float length = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
	return length == 0.0f ? vec4(0.0f, 0.0f, 0.0f, 0.0f) : vec4DivideVec4(v, vec4(length, length, length, length));
}

/**
 * Vector functions.
 */
Vec2 vec2AddVec2(Vec2 v1, Vec2 v2)
{
	return vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec3 vec3AddVec3(Vec3 v1, Vec3 v2)
{
	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec4 vec4AddVec4(Vec4 v1, Vec4 v2)
{
	return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

Vec2 vec2SubtractVec2(Vec2 v1, Vec2 v2)
{
	return vec2(v1.x - v2.x, v1.y - v2.y);
}

Vec3 vec3SubtractVec3(Vec3 v1, Vec3 v2)
{
	return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec4 vec4SubtractVec4(Vec4 v1, Vec4 v2)
{
	return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

Vec2 vec2MultiplyVec2(Vec2 v1, Vec2 v2)
{
	return vec2(v1.x * v2.x, v1.y * v2.y);
}

Vec3 vec3MultiplyVec3(Vec3 v1, Vec3 v2)
{
	return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vec4 vec4MultiplyVec4(Vec4 v1, Vec4 v2)
{
	return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

Vec2 vec2DivideVec2(Vec2 v1, Vec2 v2)
{
	return vec2(v1.x / v2.x, v1.y / v2.y);
}

Vec3 vec3DivideVec3(Vec3 v1, Vec3 v2)
{
	return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vec4 vec4DivideVec4(Vec4 v1, Vec4 v2)
{
	return vec4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

Vec2 vec2MultiplyMat4(Vec2 v, Mat4 m)
{
	Vec2 vector = {
		(v.x * m.xx) + (v.y * m.yx),
		(v.x * m.xy) + (v.y * m.yy)
	};

	return vector;
}

Vec3 vec3MultiplyMat4(Vec3 v, Mat4 m)
{
	Vec3 vector = {
		(v.x * m.xx) + (v.y * m.yx) + (v.z * m.zx),
		(v.x * m.xy) + (v.y * m.yy) + (v.z * m.zy),
		(v.x * m.xz) + (v.y * m.yz) + (v.z * m.zz),
	};

	return vector;
}

Vec4 vec4MultiplyMat4(Vec4 v, Mat4 m)
{
	Vec4 vector = {
		(v.x * m.xx) + (v.y * m.yx) + (v.z * m.zx) + (v.w * m.wx),
		(v.x * m.xy) + (v.y * m.yy) + (v.z * m.zy) + (v.w * m.wy),
		(v.x * m.xz) + (v.y * m.yz) + (v.z * m.zz) + (v.w * m.wz),
		(v.x * m.xw) + (v.y * m.yw) + (v.z * m.zw) + (v.w * m.ww)
	};

	return vector;
}

Vec3 vec3CrossProduct(Vec3 v1, Vec3 v2)
{
	Vec3 vector = {
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	};

	return vector;
}

/**
 * Quaternian math.
 */
Vec4 quatRotationX(float angle)
{
	return quatRotationAxis(vec3(1.0f, 0.0f, 0.0f), angle);
}

Vec4 quatRotationY(float angle)
{
	return quatRotationAxis(vec3(0.0f, 1.0f, 0.0f), angle);
}

Vec4 quatRotationZ(float angle)
{
	return quatRotationAxis(vec3(0.0f, 0.0f, 1.0f), angle);
}

Vec4 quatRotationAxis(Vec3 axis, float angle)
{
	float sin = sinf(angle / 2.0f);
	float cos = cosf(angle / 2.0f);

	Vec4 rotation = {axis.x * sin, axis.y * sin, axis.z * sin, cos};

	return vec4Normalize(rotation);
}

Vec4 quatMultiplyQuat(Vec4 q1, Vec4 q2)
{
	Vec4 quat = {
		(q1.w * q2.x) + (q1.x * q2.w) + (q1.y * q2.z) - (q1.z * q2.y),
		(q1.w * q2.y) - (q1.x * q2.z) + (q1.y * q2.w) + (q1.z * q2.x),
		(q1.w * q2.z) + (q1.x * q2.y) - (q1.y * q2.x) + (q1.z * q2.w),
		(q1.w * q2.w) - (q1.x * q2.x) - (q1.y * q2.y) - (q1.z * q2.z)
	};

    return quat;
}

/**
 * Matricies.
 */
Mat4 mat4Empty()
{
	Mat4 matrix = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	return matrix;
}

Mat4 mat4Identity()
{
	Mat4 matrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return matrix;
}

Mat4 mat4Translation(Vec3 t)
{
	Mat4 matrix = mat4Identity();

	matrix.wx = t.x;
	matrix.wy = t.y;
	matrix.wz = t.z;

	return matrix;
}

Mat4 mat4Scale(Vec3 s)
{
	Mat4 matrix = mat4Identity();

	matrix.xx = s.x;
	matrix.yy = s.y;
	matrix.zz = s.z;

	return matrix;
}

Mat4 mat4RotationEuler(Vec3 e)
{
	Mat4 matrix = mat4Identity();

	float cosX = cos(e.x);
	float cosY = cos(e.y);
	float cosZ = cos(e.z);

	float sinX = sin(e.x); 
	float sinY = sin(e.y); 
	float sinZ = sin(e.z); 

	matrix.xx = cosZ * cosY;
	matrix.xy = cosZ * sinY * sinX - sinZ * cosX;
	matrix.xz = cosZ * sinY * cosX + sinZ * sinX;

	matrix.yx = sinZ * cosY;
	matrix.yy = cosZ * cosX + sinZ * sinY * sinX;
	matrix.yz = sinZ * sinY * cosX - cosZ * sinX;

	matrix.zx = -sinY;
	matrix.zy = cosY * sinX;
	matrix.zz = cosY * cosX;
	 
	return matrix;
}

Mat4 mat4RotationQuat(Vec4 q)
{
	Mat4 matrix = mat4Identity();

    float xx = q.x * q.x;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float xw = q.x * q.w;

    float yy = q.y * q.y;
    float yz = q.y * q.z;
    float yw = q.y * q.w;

    float zz = q.z * q.z;
    float zw = q.z * q.w;

	matrix.xx = 1.0f - 2.0f * (yy + zz);
	matrix.xy = 2.0f * (xy + zw);
	matrix.xz = 2.0f * (xz - yw);

	matrix.yx = 2.0f * (xy - zw); 
	matrix.yy = 1.0f - 2.0f * (xx + zz);
	matrix.yz = 2.0f * (yz + xw);

	matrix.zx = 2.0f * (xz + yw);
	matrix.zy = 2.0f * (yz - xw);
	matrix.zz = 1.0f - 2.0f * (xx + yy);

	return matrix;
}

float mat4Determinant(Mat4 m)
{
	return m.xw * m.yz * m.zy * m.wx - m.xz * m.yw * m.zy * m.wx - 
		   m.xw * m.yy * m.zz * m.wx + m.xy * m.yw * m.zz * m.wx +
		   m.xz * m.yy * m.zw * m.wx - m.xy * m.yz * m.zw * m.wx - 
		   m.xw * m.yz * m.zx * m.wy + m.xz * m.yw * m.zx * m.wy +
		   m.xw * m.yx * m.zz * m.wy - m.xx * m.yw * m.zz * m.wy - 
		   m.xz * m.yx * m.zw * m.wy + m.xx * m.yz * m.zw * m.wy +
		   m.xw * m.yy * m.zx * m.wz - m.xy * m.yw * m.zx * m.wz - 
		   m.xw * m.yx * m.zy * m.wz + m.xx * m.yw * m.zy * m.wz +
		   m.xy * m.yx * m.zw * m.wz - m.xx * m.yy * m.zw * m.wz - 
		   m.xz * m.yy * m.zx * m.ww + m.xy * m.yz * m.zx * m.ww +
		   m.xz * m.yx * m.zy * m.ww - m.xx * m.yz * m.zy * m.ww - 
		   m.xy * m.yx * m.zz * m.ww + m.xx * m.yy * m.zz * m.ww;
}

Mat4 mat4Inverse(Mat4 m)
{
	Mat4 matrix = mat4Empty();

	float indentity = 1.0f / mat4Determinant(m);

	matrix.xx = (m.yz * m.zw * m.wy - m.yw * m.zz * m.wy + m.yw * m.zy * m.wz - m.yy * m.zw * m.wz - m.yz * m.zy * m.ww + m.yy * m.zz * m.ww) * indentity;
	matrix.xy = (m.xw * m.zz * m.wy - m.xz * m.zw * m.wy - m.xw * m.zy * m.wz + m.xy * m.zw * m.wz + m.xz * m.zy * m.ww - m.xy * m.zz * m.ww) * indentity;
	matrix.xz = (m.xz * m.yw * m.wy - m.xw * m.yz * m.wy + m.xw * m.yy * m.wz - m.xy * m.yw * m.wz - m.xz * m.yy * m.ww + m.xy * m.yz * m.ww) * indentity;
	matrix.xw = (m.xw * m.yz * m.zy - m.xz * m.yw * m.zy - m.xw * m.yy * m.zz + m.xy * m.yw * m.zz + m.xz * m.yy * m.zw - m.xy * m.yz * m.zw) * indentity;

	matrix.yx = (m.yw * m.zz * m.wx - m.yz * m.zw * m.wx - m.yw * m.zx * m.wz + m.yx * m.zw * m.wz + m.yz * m.zx * m.ww - m.yx * m.zz * m.ww) * indentity;
	matrix.yy = (m.xz * m.zw * m.wx - m.xw * m.zz * m.wx + m.xw * m.zx * m.wz - m.xx * m.zw * m.wz - m.xz * m.zx * m.ww + m.xx * m.zz * m.ww) * indentity;
	matrix.yz = (m.xw * m.yz * m.wx - m.xz * m.yw * m.wx - m.xw * m.yx * m.wz + m.xx * m.yw * m.wz + m.xz * m.yx * m.ww - m.xx * m.yz * m.ww) * indentity;
	matrix.yw = (m.xz * m.yw * m.zx - m.xw * m.yz * m.zx + m.xw * m.yx * m.zz - m.xx * m.yw * m.zz - m.xz * m.yx * m.zw + m.xx * m.yz * m.zw) * indentity;
	
	matrix.zx = (m.yy * m.zw * m.wx - m.yw * m.zy * m.wx + m.yw * m.zx * m.wy - m.yx * m.zw * m.wy - m.yy * m.zx * m.ww + m.yx * m.zy * m.ww) * indentity;
	matrix.zy = (m.xw * m.zy * m.wx - m.xy * m.zw * m.wx - m.xw * m.zx * m.wy + m.xx * m.zw * m.wy + m.xy * m.zx * m.ww - m.xx * m.zy * m.ww) * indentity;
	matrix.zz = (m.xy * m.yw * m.wx - m.xw * m.yy * m.wx + m.xw * m.yx * m.wy - m.xx * m.yw * m.wy - m.xy * m.yx * m.ww + m.xx * m.yy * m.ww) * indentity;
	matrix.zw = (m.xw * m.yy * m.zx - m.xy * m.yw * m.zx - m.xw * m.yx * m.zy + m.xx * m.yw * m.zy + m.xy * m.yx * m.zw - m.xx * m.yy * m.zw) * indentity;
	
	matrix.wx = (m.yz * m.zy * m.wx - m.yy * m.zz * m.wx - m.yz * m.zx * m.wy + m.yx * m.zz * m.wy + m.yy * m.zx * m.wz - m.yx * m.zy * m.wz) * indentity;
	matrix.wy = (m.xy * m.zz * m.wx - m.xz * m.zy * m.wx + m.xz * m.zx * m.wy - m.xx * m.zz * m.wy - m.xy * m.zx * m.wz + m.xx * m.zy * m.wz) * indentity;
	matrix.wz = (m.xz * m.yy * m.wx - m.xy * m.yz * m.wx - m.xz * m.yx * m.wy + m.xx * m.yz * m.wy + m.xy * m.yx * m.wz - m.xx * m.yy * m.wz) * indentity;
	matrix.ww = (m.xy * m.yz * m.zx - m.xz * m.yy * m.zx + m.xz * m.yx * m.zy - m.xx * m.yz * m.zy - m.xy * m.yx * m.zz + m.xx * m.yy * m.zz) * indentity;

	return matrix;
}

Mat4 mat4Transpose(Mat4 m)
{
	Mat4 matrix = mat4Empty();

	matrix.xx = m.xx;
	matrix.xy = m.yx;
	matrix.xz = m.zx;
	matrix.xw = m.wx;

	matrix.yx = m.xy;
	matrix.yy = m.yy;
	matrix.yz = m.zy;
	matrix.yw = m.wy;

	matrix.zx = m.xz;
	matrix.zy = m.yz;
	matrix.zz = m.zz;
	matrix.zw = m.wz;

	matrix.wx = m.xw;
	matrix.wy = m.yw;
	matrix.wz = m.zw;
	matrix.ww = m.ww;

	return matrix;
}

Mat4 mat4LookAt(Vec3 position, Vec3 target, Vec3 up)
{
	Mat4 matrix = mat4Identity();

	Vec3 z = vec3Normalize(vec3AddVec3(target, vec3Negative(position)));
	Vec3 x = vec3Normalize(vec3CrossProduct(z, up));
	Vec3 y = vec3CrossProduct(x, z);

	matrix.xx = x.x;
	matrix.xy = y.x;
	matrix.xz = -z.x;

	matrix.yx = x.y;
	matrix.yy = y.y;
	matrix.yz = -z.y;

	matrix.zx = x.z;
	matrix.zy = y.z;
	matrix.zz = -z.z;

	matrix.wx = -(x.x * position.x + x.y * position.y + x.z * position.z);
	matrix.wy = -(y.x * position.x + y.y * position.y + y.z * position.z);
	matrix.wz = (z.x * position.x + z.y * position.y + z.z * position.z);

	return matrix;
}

Mat4 mat4Orthographic(float x, float right, float top, float bottom, float near, float far)
{
	Mat4 matrix = mat4Identity();

	matrix.xx = 2.0f / (right - x); 
	matrix.yy = 2.0f / (top - bottom);
	matrix.zz = -2.0f / (far - near); 

	matrix.wx = -(right + x) / (right - x); 
	matrix.wy = -(top + bottom) / (top - bottom); 
	matrix.wz = -(far + near) / (far - near); 

	return matrix;
}

Mat4 mat4Perspective(float fov, float ratio, float near, float far)
{
	Mat4 matrix = mat4Empty();

	float cotan = 1.0f / tanf(fov / 2.0f); 

	matrix.xx = cotan / ratio;
	matrix.yy = cotan;
	matrix.zz = (far + near) / (near - far);

	matrix.wz = (2.0f * far * near) / (near - far);
	matrix.zw = -1.0f;

	return matrix;
}

Mat4 mat4MultiplyMat4(Mat4 m1, Mat4 m2)
{
	Mat4 matrix = mat4Empty();

	matrix.xx = (m1.xx * m2.xx) + (m1.xy * m2.yx) + (m1.xz * m2.zx) + (m1.xw * m2.wx);
	matrix.xy = (m1.xx * m2.xy) + (m1.xy * m2.yy) + (m1.xz * m2.zy) + (m1.xw * m2.wy);
	matrix.xz = (m1.xx * m2.xz) + (m1.xy * m2.yz) + (m1.xz * m2.zz) + (m1.xw * m2.wz);
	matrix.xw = (m1.xx * m2.xw) + (m1.xy * m2.yw) + (m1.xz * m2.zw) + (m1.xw * m2.ww); 

	matrix.yx = (m1.yx * m2.xx) + (m1.yy * m2.yx) + (m1.yz * m2.zx) + (m1.yw * m2.wx);
	matrix.yy = (m1.yx * m2.xy) + (m1.yy * m2.yy) + (m1.yz * m2.zy) + (m1.yw * m2.wy);
	matrix.yz = (m1.yx * m2.xz) + (m1.yy * m2.yz) + (m1.yz * m2.zz) + (m1.yw * m2.wz);
	matrix.yw = (m1.yx * m2.xw) + (m1.yy * m2.yw) + (m1.yz * m2.zw) + (m1.yw * m2.ww);

	matrix.zx = (m1.zx * m2.xx) + (m1.zy * m2.yx) + (m1.zz * m2.zx) + (m1.zw * m2.wx);
	matrix.zy = (m1.zx * m2.xy) + (m1.zy * m2.yy) + (m1.zz * m2.zy) + (m1.zw * m2.wy);
	matrix.zz = (m1.zx * m2.xz) + (m1.zy * m2.yz) + (m1.zz * m2.zz) + (m1.zw * m2.wz);
	matrix.zw = (m1.zx * m2.xw) + (m1.zy * m2.yw) + (m1.zz * m2.zw) + (m1.zw * m2.ww); 

	matrix.wx = (m1.wx * m2.xx) + (m1.wy * m2.yx) + (m1.wz * m2.zx) + (m1.ww * m2.wx); 
	matrix.wy = (m1.wx * m2.xy) + (m1.wy * m2.yy) + (m1.wz * m2.zy) + (m1.ww * m2.wy);
	matrix.wz = (m1.wx * m2.xz) + (m1.wy * m2.yz) + (m1.wz * m2.zz) + (m1.ww * m2.wz); 
	matrix.ww = (m1.wx * m2.xw) + (m1.wy * m2.yw) + (m1.wz * m2.zw) + (m1.ww * m2.ww);

	return matrix;
}

float degreesToRadians(float degrees)
{
	return degrees * M_PI / 180.0;
}

float radiansToDegrees(float radians)
{
	return radians * 180.0 / M_PI;
}