#include "glmath.h"

Vector2i vector2i(int x, int y)
{
	Vector2i vector = { x, y };
	return vector;
}

Vector3i vector3i(int x, int y, int z)
{
	Vector3i vector = { x, y, z };
	return vector;
}

Vector4i vector4i(int x, int y, int z, int w)
{
	Vector4i vector = { x, y, z, w };
	return vector;
}

Vector2f vector2f(float x, float y)
{
	Vector2f vector = { x, y };
	return vector;
}

Vector3f vector3f(float x, float y, float z)
{
	Vector3f vector = { x, y, z };
	return vector;
}

Vector4f vector4f(float x, float y, float z, float w)
{
	Vector4f vector = { x, y, z, w };
	return vector;
}

Vector3f quatConvertEuler(Vector4f q)
{
	Vector3f euler;

	float sqrX = q.x * q.x; 
	float sqrY = q.y * q.y; 
	float sqrZ = q.z * q.z; 
	float sqrW = q.w * q.w; 

	euler.x = asinf(-2.0f * (q.x * q.z - q.y * q.w));
	euler.y = atan2f(2.0f * (q.y * q.z + q.x * q.w), (-sqrX - sqrY + sqrZ + sqrW));
	euler.z = atan2f(2.0f * (q.x * q.y + q.z * q.w), (sqrX - sqrY - sqrZ + sqrW));

	return euler;
}

Vector4f eulerConvertQuat(Vector3f e)
{
	Vector4f quat;

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

Matrix4 matrix4Empty()
{
	Matrix4 matrix = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	return matrix;
}

Matrix4 matrix4Identity()
{
	Matrix4 matrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return matrix;
}

Matrix4 matrix4Translate(Vector3f t)
{
	Matrix4 matrix = matrix4Identity();

	matrix.xw = t.x;
	matrix.yw = t.y;
	matrix.zw = t.z;

	return matrix;
}

Matrix4 matrix4Scale(Vector3f s)
{
	Matrix4 matrix = matrix4Identity();

	matrix.xx = s.x;
	matrix.yy = s.y;
	matrix.zz = s.z;

	return matrix;
}

Matrix4 matrix4Euler(Vector3f e)
{
	Matrix4 matrix = matrix4Identity();

	float cosX = cos(e.x);
	float cosY = cos(e.y);
	float cosZ = cos(e.z);

	float sinX = sin(e.x); 
	float sinY = sin(e.y); 
	float sinZ = sin(e.z); 

	matrix.xx = cosY * cosZ;
	matrix.xy = cosY * sinZ;
	matrix.xz = -sinY; 

	matrix.yx = -cosX * sinZ + sinX * sinY * cosZ;
	matrix.yy = cosX * cosZ + sinX * sinY * sinZ;
	matrix.yz = sinX * cosY; 

	matrix.zx = sinX * sinZ + cosX * sinY * cosZ; 
	matrix.zy = -sinX * cosZ + cosX * sinY * sinZ; 
	matrix.zz = cosX * cosY; 
	 
	return matrix;
}

Matrix4 matrix4Quat(Vector4f q)
{
	Matrix4 matrix = matrix4Identity();

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
	matrix.xy = 2.0f * (xy - zw);
	matrix.xz = 2.0f * (xz + yw);

	matrix.yx = 2.0f * (xy + zw);
	matrix.yy = 1.0f - 2.0f * (xx + zz);
	matrix.yz = 2.0f * (yz - xw);

	matrix.zx = 2.0f * (xz - yw);
	matrix.zy = 2.0f * (yz + xw);
	matrix.zz = 1.0f - 2.0f * (xx + yy);

	return matrix;
}

Matrix4 matrix4Perspective(float fov, float aspectRatio, float nearClip, float farClip)
{
	Matrix4 matrix = matrix4Empty();

	float cotan = 1.0f / tanf(fov / 2.0f); 

	matrix.xx = cotan / aspectRatio;
	matrix.yy = cotan;
	matrix.zz = (farClip + nearClip) / (nearClip - farClip);
	matrix.zw = (2.0f * farClip * nearClip) / (nearClip - farClip);
	matrix.wz = -1.0f;

	return matrix;
}

Vector2f vector2fMultiplyMatrix4(Vector2f v, Matrix4 m)
{
	Vector2f vector = {
		(v.x * m.xx) + (v.y * m.xy),
		(v.x * m.yx) + (v.y * m.yy)
	};

	return vector;
}

Vector3f vector3fMultiplyMatrix4(Vector3f v, Matrix4 m)
{
	Vector3f vector = {
		(v.x * m.xx) + (v.y * m.xy) + (v.z * m.xz),
		(v.x * m.yx) + (v.y * m.yy) + (v.z * m.yz),
		(v.x * m.zx) + (v.y * m.zy) + (v.z * m.zz)
	};

	return vector;
}

Vector4f vector4fMultiplyMatrix4(Vector4f v, Matrix4 m)
{
	Vector4f vector = {
		(v.x * m.xx) + (v.y * m.xy) + (v.z * m.xz) + (v.z * m.xw),
		(v.x * m.yx) + (v.y * m.yy) + (v.z * m.yz) + (v.z * m.yw),
		(v.x * m.zx) + (v.y * m.zy) + (v.z * m.zz) + (v.z * m.zw),
		(v.x * m.wx) + (v.y * m.wy) + (v.z * m.wz) + (v.z * m.ww)
	};

	return vector;
}

Matrix4 matrix4MultiplyMatrix4(Matrix4 m1, Matrix4 m2)
{
	Matrix4 matrix = matrix4Empty();

	matrix.xx = (m1.xx * m2.xx) + (m1.xy * m2.yx) + (m1.xz * m2.zx) + (m1.xw * m2.wx);
	matrix.yx = (m1.yx * m2.xx) + (m1.yy * m2.yx) + (m1.yz * m2.zx) + (m1.yw * m2.wx);
	matrix.zx = (m1.zx * m2.xx) + (m1.zy * m2.yx) + (m1.zz * m2.zx) + (m1.zw * m2.wx);
	matrix.wx = (m1.wx * m2.xx) + (m1.wy * m2.yx) + (m1.wz * m2.zx) + (m1.ww * m2.wx); 

	matrix.xy = (m1.xx * m2.xy) + (m1.xy * m2.yy) + (m1.xz * m2.zy) + (m1.xw * m2.wy);
	matrix.yy = (m1.yx * m2.xy) + (m1.yy * m2.yy) + (m1.yz * m2.zy) + (m1.yw * m2.wy);
	matrix.zy = (m1.zx * m2.xy) + (m1.zy * m2.yy) + (m1.zz * m2.zy) + (m1.zw * m2.wy);
	matrix.wy = (m1.wx * m2.xy) + (m1.wy * m2.yy) + (m1.wz * m2.zy) + (m1.ww * m2.wy);

	matrix.xz = (m1.xx * m2.xz) + (m1.xy * m2.yz) + (m1.xz * m2.zz) + (m1.xw * m2.wz);
	matrix.yz = (m1.yx * m2.xz) + (m1.yy * m2.yz) + (m1.yz * m2.zz) + (m1.yw * m2.wz);
	matrix.zz = (m1.zx * m2.xz) + (m1.zy * m2.yz) + (m1.zz * m2.zz) + (m1.zw * m2.wz);
	matrix.wz = (m1.wx * m2.xz) + (m1.wy * m2.yz) + (m1.wz * m2.zz) + (m1.ww * m2.wz); 

	matrix.xw = (m1.xx * m2.xw) + (m1.xy * m2.yw) + (m1.xz * m2.zw) + (m1.xw * m2.ww); 
	matrix.yw = (m1.yx * m2.xw) + (m1.yy * m2.yw) + (m1.yz * m2.zw) + (m1.yw * m2.ww); 
	matrix.zw = (m1.zx * m2.xw) + (m1.zy * m2.yw) + (m1.zz * m2.zw) + (m1.zw * m2.ww); 
	matrix.ww = (m1.wx * m2.xw) + (m1.wy * m2.yw) + (m1.wz * m2.zw) + (m1.ww * m2.ww);

	return matrix;
}