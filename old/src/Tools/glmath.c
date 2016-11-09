#include "Tools/glmath.h"

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

float matrix4Determinant(Matrix4 m)
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

Matrix4 matrix4Invert(Matrix4 m)
{
	Matrix4 matrix = matrix4Empty();

	float determinant = 1.0f / matrix4Determinant(m);

	matrix.xx = (m.yz * m.zw * m.wy - m.yw * m.zz * m.wy + m.yw * m.zy * m.wz - m.yy * m.zw * m.wz - m.yz * m.zy * m.ww + m.yy * m.zz * m.ww) * determinant;
	matrix.xy = (m.xw * m.zz * m.wy - m.xz * m.zw * m.wy - m.xw * m.zy * m.wz + m.xy * m.zw * m.wz + m.xz * m.zy * m.ww - m.xy * m.zz * m.ww) * determinant;
	matrix.xz = (m.xz * m.yw * m.wy - m.xw * m.yz * m.wy + m.xw * m.yy * m.wz - m.xy * m.yw * m.wz - m.xz * m.yy * m.ww + m.xy * m.yz * m.ww) * determinant;
	matrix.xw = (m.xw * m.yz * m.zy - m.xz * m.yw * m.zy - m.xw * m.yy * m.zz + m.xy * m.yw * m.zz + m.xz * m.yy * m.zw - m.xy * m.yz * m.zw) * determinant;

	matrix.yx = (m.yw * m.zz * m.wx - m.yz * m.zw * m.wx - m.yw * m.zx * m.wz + m.yx * m.zw * m.wz + m.yz * m.zx * m.ww - m.yx * m.zz * m.ww) * determinant;
	matrix.yy = (m.xz * m.zw * m.wx - m.xw * m.zz * m.wx + m.xw * m.zx * m.wz - m.xx * m.zw * m.wz - m.xz * m.zx * m.ww + m.xx * m.zz * m.ww) * determinant;
	matrix.yz = (m.xw * m.yz * m.wx - m.xz * m.yw * m.wx - m.xw * m.yx * m.wz + m.xx * m.yw * m.wz + m.xz * m.yx * m.ww - m.xx * m.yz * m.ww) * determinant;
	matrix.yw = (m.xz * m.yw * m.zx - m.xw * m.yz * m.zx + m.xw * m.yx * m.zz - m.xx * m.yw * m.zz - m.xz * m.yx * m.zw + m.xx * m.yz * m.zw) * determinant;
	
	matrix.zx = (m.yy * m.zw * m.wx - m.yw * m.zy * m.wx + m.yw * m.zx * m.wy - m.yx * m.zw * m.wy - m.yy * m.zx * m.ww + m.yx * m.zy * m.ww) * determinant;
	matrix.zy = (m.xw * m.zy * m.wx - m.xy * m.zw * m.wx - m.xw * m.zx * m.wy + m.xx * m.zw * m.wy + m.xy * m.zx * m.ww - m.xx * m.zy * m.ww) * determinant;
	matrix.zz = (m.xy * m.yw * m.wx - m.xw * m.yy * m.wx + m.xw * m.yx * m.wy - m.xx * m.yw * m.wy - m.xy * m.yx * m.ww + m.xx * m.yy * m.ww) * determinant;
	matrix.zw = (m.xw * m.yy * m.zx - m.xy * m.yw * m.zx - m.xw * m.yx * m.zy + m.xx * m.yw * m.zy + m.xy * m.yx * m.zw - m.xx * m.yy * m.zw) * determinant;
	
	matrix.wx = (m.yz * m.zy * m.wx - m.yy * m.zz * m.wx - m.yz * m.zx * m.wy + m.yx * m.zz * m.wy + m.yy * m.zx * m.wz - m.yx * m.zy * m.wz) * determinant;
	matrix.wy = (m.xy * m.zz * m.wx - m.xz * m.zy * m.wx + m.xz * m.zx * m.wy - m.xx * m.zz * m.wy - m.xy * m.zx * m.wz + m.xx * m.zy * m.wz) * determinant;
	matrix.wz = (m.xz * m.yy * m.wx - m.xy * m.yz * m.wx - m.xz * m.yx * m.wy + m.xx * m.yz * m.wy + m.xy * m.yx * m.wz - m.xx * m.yy * m.wz) * determinant;
	matrix.ww = (m.xy * m.yz * m.zx - m.xz * m.yy * m.zx + m.xz * m.yx * m.zy - m.xx * m.yz * m.zy - m.xy * m.yx * m.zz + m.xx * m.yy * m.zz) * determinant;

	return matrix;
}

Matrix4 matrix4Transpose(Matrix4 m)
{
	Matrix4 matrix = matrix4Empty();

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

Matrix4 matrix4Orthographic(float left, float right, float bottom, float top, float nearClip, float farClip)
{
	Matrix4 matrix = matrix4Empty();

	matrix.xx = 2.0f / (right - left); 
	matrix.yy = 2.0f / (top - bottom); 
	matrix.zz = 1.0f / (nearClip - farClip); 
	   
	matrix.xw = -1.0f - 2.0f * left / (right - left); 
	matrix.yw = 1.0f + 2.0f * top  / (bottom - top); 
	matrix.zw = nearClip / (nearClip - farClip); 

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