#include "glmath.h"

Vec2 vec2New(float x, float y)
{
	Vec2 vec = { x, y };
	return vec;
}

Vec3 vec3New(float x, float y, float z)
{
	Vec3 vec = { x, y, z };
	return vec;
}

Vec4 vec4New(float x, float y, float z, float w)
{
	Vec4 vec = { x, y, z, w };
	return vec;
}

Vec3 quatConvertEuler(Vec4 q)
{
	Vec3 euler;

	float sqrX = q.x * q.x; 
	float sqrY = q.y * q.y; 
	float sqrZ = q.z * q.z; 
	float sqrW = q.w * q.w; 

	euler.x = asinf(-2.0f * (q.x * q.z - q.y * q.w));
	euler.y = atan2f(2.0f * (q.y * q.z + q.x * q.w), (-sqrX - sqrY + sqrZ + sqrW));
	euler.z = atan2f(2.0f * (q.x * q.y + q.z * q.w), (sqrX - sqrY - sqrZ + sqrW));

	return euler;
}

Vec4 eulerConvertQuat(Vec3 e)
{
	Vec4 quat;

	float cosX = cosf(e.x / 2.0f); 
	float cosY = cosf(e.y / 2.0f); 
	float cosZ = cosf(e.z / 2.0f); 

	float sinX = sinf(e.x / 2.0f);
	float sinY = sinf(e.y / 2.0f); 
	float sinZ = sinf(e.z / 2.0f); 
	 
	quat.x = cosX * sinY * cosZ - sinX * cosY * sinZ;
	quat.y = sinX * cosY * cosZ + cosX * sinY * sinZ;
	quat.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
	quat.w = cosX * cosY * cosZ + sinX * sinY * sinZ;

	return quat;
}

Matrix matrixEmpty()
{
	Matrix mat = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	return mat;
}

Matrix matrixIdentity()
{
	Matrix mat = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return mat;
}

Matrix matrixTranslate(Vec3 t)
{
	Matrix mat = matrixIdentity();

	mat.xw = t.x;
	mat.yw = t.y;
	mat.zw = t.z;

	return mat;
}

Matrix matrixScale(Vec3 s)
{
	Matrix mat = matrixIdentity();

	mat.xx = s.x;
	mat.yy = s.y;
	mat.zz = s.z;

	return mat;
}

Matrix matrixRotateEuler(Vec3 e)
{
	Matrix mat = matrixIdentity();

	float cosX = cos(e.x);
	float cosY = cos(e.y);
	float cosZ = cos(e.z);

	float sinX = sin(e.x); 
	float sinY = sin(e.y); 
	float sinZ = sin(e.z); 

	mat.xx = cosY * cosZ;
	mat.xy = cosY * sinZ;
	mat.xz = -sinY; 

	mat.yx = -cosX * sinZ + sinX * sinY * cosZ;
	mat.yy = cosX * cosZ + sinX * sinY * sinZ;
	mat.yz = sinX * cosY; 

	mat.zx = sinX * sinZ + cosX * sinY * cosZ; 
	mat.zy = -sinX * cosZ + cosX * sinY * sinZ; 
	mat.zz = cosX * cosY; 
	 
	return mat;
}

Matrix matrixRotateQuat(Vec4 q)
{
	Matrix mat = matrixIdentity();

    float xx = q.x * q.x;
    float xy = q.x * q.y;
    float xz = q.x * q.z;
    float xw = q.x * q.w;

    float yy = q.y * q.y;
    float yz = q.y * q.z;
    float yw = q.y * q.w;

    float zz = q.z * q.z;
    float zw = q.z * q.w;

	mat.xx = 1.0f - 2.0f * (yy + zz);
	mat.xy = 2.0f * (xy - zw);
	mat.xz = 2.0f * (xz + yw);

	mat.yx = 2.0f * (xy + zw);
	mat.yy = 1.0f - 2.0f * (xx + zz);
	mat.yz = 2.0f * (yz - xw);

	mat.zx = 2.0f * (xz - yw);
	mat.zy = 2.0f * (yz + xw);
	mat.zz = 1.0f - 2.0f * (xx + yy);

	return mat;
}

Matrix matrixPerspective(float fov, float aspectRatio, float nearClip, float farClip)
{
	Matrix mat = matrixEmpty();

	float cotan = 1.0f / tanf(fov / 2.0f); 

	mat.xx = cotan / aspectRatio;
	mat.yy = cotan;
	mat.zz = (farClip + nearClip) / (nearClip - farClip);
	mat.zw = (2.0f * farClip * nearClip) / (nearClip - farClip);
	mat.wz = -1.0f;

	return mat;
}

Vec2 vec2MultiplyMatrix(Vec2 v, Matrix m)
{
	Vec2 vec = {
		(v.x * m.xx) + (v.y * m.xy),
		(v.x * m.yx) + (v.y * m.yy)
	};

	return vec;
}

Vec3 vec3MultiplyMatrix(Vec3 v, Matrix m)
{
	Vec3 vec = {
		(v.x * m.xx) + (v.y * m.xy) + (v.z * m.xz),
		(v.x * m.yx) + (v.y * m.yy) + (v.z * m.yz),
		(v.x * m.zx) + (v.y * m.zy) + (v.z * m.zz)
	};

	return vec;
}

Vec4 vec4MultiplyMatrix(Vec4 v, Matrix m)
{
	Vec4 vec = {
		(v.x * m.xx) + (v.y * m.xy) + (v.z * m.xz) + (v.z * m.xw),
		(v.x * m.yx) + (v.y * m.yy) + (v.z * m.yz) + (v.z * m.yw),
		(v.x * m.zx) + (v.y * m.zy) + (v.z * m.zz) + (v.z * m.zw),
		(v.x * m.wx) + (v.y * m.wy) + (v.z * m.wz) + (v.z * m.ww)
	};

	return vec;
}

Matrix matrixMultiplyMatrix(Matrix m1, Matrix m2)
{
	Matrix mat = matrixEmpty();

	mat.xx = (m1.xx * m2.xx) + (m1.xy * m2.yx) + (m1.xz * m2.zx) + (m1.xw * m2.wx);
	mat.yx = (m1.yx * m2.xx) + (m1.yy * m2.yx) + (m1.yz * m2.zx) + (m1.yw * m2.wx);
	mat.zx = (m1.zx * m2.xx) + (m1.zy * m2.yx) + (m1.zz * m2.zx) + (m1.zw * m2.wx);
	mat.wx = (m1.wx * m2.xx) + (m1.wy * m2.yx) + (m1.wz * m2.zx) + (m1.ww * m2.wx); 

	mat.xy = (m1.xx * m2.xy) + (m1.xy * m2.yy) + (m1.xz * m2.zy) + (m1.xw * m2.wy);
	mat.yy = (m1.yx * m2.xy) + (m1.yy * m2.yy) + (m1.yz * m2.zy) + (m1.yw * m2.wy);
	mat.zy = (m1.zx * m2.xy) + (m1.zy * m2.yy) + (m1.zz * m2.zy) + (m1.zw * m2.wy);
	mat.wy = (m1.wx * m2.xy) + (m1.wy * m2.yy) + (m1.wz * m2.zy) + (m1.ww * m2.wy);

	mat.xz = (m1.xx * m2.xz) + (m1.xy * m2.yz) + (m1.xz * m2.zz) + (m1.xw * m2.wz);
	mat.yz = (m1.yx * m2.xz) + (m1.yy * m2.yz) + (m1.yz * m2.zz) + (m1.yw * m2.wz);
	mat.zz = (m1.zx * m2.xz) + (m1.zy * m2.yz) + (m1.zz * m2.zz) + (m1.zw * m2.wz);
	mat.wz = (m1.wx * m2.xz) + (m1.wy * m2.yz) + (m1.wz * m2.zz) + (m1.ww * m2.wz); 

	mat.xw = (m1.xx * m2.xw) + (m1.xy * m2.yw) + (m1.xz * m2.zw) + (m1.xw * m2.ww); 
	mat.yw = (m1.yx * m2.xw) + (m1.yy * m2.yw) + (m1.yz * m2.zw) + (m1.yw * m2.ww); 
	mat.zw = (m1.zx * m2.xw) + (m1.zy * m2.yw) + (m1.zz * m2.zw) + (m1.zw * m2.ww); 
	mat.ww = (m1.wx * m2.xw) + (m1.wy * m2.yw) + (m1.wz * m2.zw) + (m1.ww * m2.ww);

	return mat;
}