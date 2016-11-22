#include "Tools/glmath.h"

Vec2 vec2(float x, float y)
{
	Vec2 vector = { x, y };
	return vector;
}

Vec3 vec3(float x, float y, float z)
{
	Vec3 vector = { x, y, z };
	return vector;
}

Vec4 vec4(float x, float y, float z, float w)
{
	Vec4 vector = { x, y, z, w };
	return vector;
}

Vec2 vec2Negative(Vec2 v)
{
	Vec2 vector = {
		-v.x, -v.y
	};

	return vector;
}

Vec3 vec3Negative(Vec3 v)
{
	Vec3 vector = {
		-v.x, -v.y, -v.z
	};

	return vector;
}

Vec4 vec4Negative(Vec4 v)
{
	Vec4 vector = {
		-v.x, -v.y, -v.z, -v.w
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

Vec2 vec2Normalize(Vec2 v)
{	
	float length = sqrt((v.x * v.x) + (v.y * v.y));
	return length == 0.0f ? vec2(0.0f, 0.0f) : vec2DivideVec2(v, vec2(length, length));
}

Vec3 vec3Normalize(Vec3 v)
{	
	float length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return length == 0.0f ? vec3(0.0f, 0.0f, 0.0f) : vec3DivideVec3(v, vec3(length, length, length));
}

Vec4 vec4Normalize(Vec4 v)
{	
	float length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
	return length == 0.0f ? vec4(0.0f, 0.0f, 0.0f, 0.0f) : vec4DivideVec4(v, vec4(length, length, length, length));
}

/**
 * Vector multiplication.
 */
Vec2 vec2MultiplyVec2(Vec2 v1, Vec2 v2)
{
	return vec2(v1.x * v2.x, v1.y * v2.y);
}

Vec2 vec2MultiplyVec3(Vec2 v1, Vec3 v2)
{
	return vec2(v1.x * v2.x, v1.y * v2.y);
}

Vec2 vec2MultiplyVec4(Vec2 v1, Vec4 v2)
{
	return vec2(v1.x * v2.x, v1.y * v2.y);
}

Vec3 vec3MultiplyVec2(Vec3 v1, Vec2 v2)
{
	return vec3(v1.x * v2.x, v1.y * v2.y, v1.z);
}

Vec3 vec3MultiplyVec3(Vec3 v1, Vec3 v2)
{
	return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vec3 vec3MultiplyVec4(Vec3 v1, Vec4 v2)
{
	return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vec4 vec4MultiplyVec2(Vec4 v1, Vec2 v2)
{
	return vec4(v1.x * v2.x, v1.y * v2.y, v1.z, v1.w);
}

Vec4 vec4MultiplyVec3(Vec4 v1, Vec3 v2)
{
	return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w);
}

Vec4 vec4MultiplyVec4(Vec4 v1, Vec4 v2)
{
	return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
}

Vec2 vec2MultiplyMat4(Vec2 v, Mat4 m)
{
	Vec2 vector = {
		(v.x * m.xx) + (v.y * m.xy),
		(v.x * m.yx) + (v.y * m.yy)
	};

	return vector;
}

Vec3 vec3MultiplyMat4(Vec3 v, Mat4 m)
{
	Vec3 vector = {
		(v.x * m.xx) + (v.y * m.xy) + (v.z * m.xz),
		(v.x * m.yx) + (v.y * m.yy) + (v.z * m.yz),
		(v.x * m.zx) + (v.y * m.zy) + (v.z * m.zz)
	};

	return vector;
}

Vec4 vec4MultiplyMat4(Vec4 v, Mat4 m)
{
	Vec4 vector = {
		(v.x * m.xx) + (v.y * m.xy) + (v.z * m.xz) + (v.z * m.xw),
		(v.x * m.yx) + (v.y * m.yy) + (v.z * m.yz) + (v.z * m.yw),
		(v.x * m.zx) + (v.y * m.zy) + (v.z * m.zz) + (v.z * m.zw),
		(v.x * m.wx) + (v.y * m.wy) + (v.z * m.wz) + (v.z * m.ww)
	};

	return vector;
}

/**
 * Vector addition.
 */
Vec2 vec2AddVec2(Vec2 v1, Vec2 v2)
{
	return vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec2 vec2AddVec3(Vec2 v1, Vec3 v2)
{
	return vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec2 vec2AddVec4(Vec2 v1, Vec4 v2)
{
	return vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec3 vec3AddVec2(Vec3 v1, Vec2 v2)
{
	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z);
}

Vec3 vec3AddVec3(Vec3 v1, Vec3 v2)
{
	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 vec3AddVec4(Vec3 v1, Vec4 v2)
{
	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec4 vec4AddVec2(Vec4 v1, Vec2 v2)
{
	return vec4(v1.x + v2.x, v1.y + v2.y, v1.z, v1.w);
}

Vec4 vec4AddVec3(Vec4 v1, Vec3 v2)
{
	return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w);
}

Vec4 vec4AddVec4(Vec4 v1, Vec4 v2)
{
	return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

Vec2 vec2AddMat4(Vec2 v, Mat4 m)
{
	Vec2 vector = {
		v.x + m.xx + v.y + m.xy,
		v.x + m.yx + v.y + m.yy
	};

	return vector;
}

Vec3 vec3AddMat4(Vec3 v, Mat4 m)
{
	Vec3 vector = {
		v.x + m.xx + v.y + m.xy + v.z + m.xz,
		v.x + m.yx + v.y + m.yy + v.z + m.yz,
		v.x + m.zx + v.y + m.zy + v.z + m.zz
	};

	return vector;
}

Vec4 vec4AddMat4(Vec4 v, Mat4 m)
{
	Vec4 vector = {
		v.x + m.xx + v.y + m.xy + v.z + m.xz + v.z + m.xw,
		v.x + m.yx + v.y + m.yy + v.z + m.yz + v.z + m.yw,
		v.x + m.zx + v.y + m.zy + v.z + m.zz + v.z + m.zw,
		v.x + m.wx + v.y + m.wy + v.z + m.wz + v.z + m.ww
	};

	return vector;
}

/**
 * Vector division.
 */
Vec2 vec2DivideVec2(Vec2 v1, Vec2 v2)
{
	return vec2(v1.x / v2.x, v1.y / v2.y);
}

Vec2 vec2DivideVec3(Vec2 v1, Vec3 v2)
{
	return vec2(v1.x / v2.x, v1.y / v2.y);
}

Vec2 vec2DivideVec4(Vec2 v1, Vec4 v2)
{
	return vec2(v1.x / v2.x, v1.y / v2.y);
}

Vec3 vec3DivideVec2(Vec3 v1, Vec2 v2)
{
	return vec3(v1.x / v2.x, v1.y / v2.y, v1.z);
}

Vec3 vec3DivideVec3(Vec3 v1, Vec3 v2)
{
	return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vec3 vec3DivideVec4(Vec3 v1, Vec4 v2)
{
	return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

Vec4 vec4DivideVec2(Vec4 v1, Vec2 v2)
{
	return vec4(v1.x / v2.x, v1.y / v2.y, v1.z, v1.w);
}

Vec4 vec4DivideVec3(Vec4 v1, Vec3 v2)
{
	return vec4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w);
}

Vec4 vec4DivideVec4(Vec4 v1, Vec4 v2)
{
	return vec4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
}

Vec2 vec2DivideMat4(Vec2 v, Mat4 m)
{
	Vec2 vector = {
		(v.x / m.xx) + (v.y / m.xy),
		(v.x / m.yx) + (v.y / m.yy)
	};

	return vector;
}

Vec3 vec3DivideMat4(Vec3 v, Mat4 m)
{
	Vec3 vector = {
		(v.x / m.xx) + (v.y / m.xy) + (v.z / m.xz),
		(v.x / m.yx) + (v.y / m.yy) + (v.z / m.yz),
		(v.x / m.zx) + (v.y / m.zy) + (v.z / m.zz)
	};

	return vector;
}

Vec4 vec4DivideMat4(Vec4 v, Mat4 m)
{
	Vec4 vector = {
		(v.x / m.xx) + (v.y / m.xy) + (v.z / m.xz) + (v.z / m.xw),
		(v.x / m.yx) + (v.y / m.yy) + (v.z / m.yz) + (v.z / m.yw),
		(v.x / m.zx) + (v.y / m.zy) + (v.z / m.zz) + (v.z / m.zw),
		(v.x / m.wx) + (v.y / m.wy) + (v.z / m.wz) + (v.z / m.ww)
	};

	return vector;
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

	matrix.xw = t.x;
	matrix.yw = t.y;
	matrix.zw = t.z;

	return matrix;
}

Mat4 mat4RotationAxis(Vec3 v, float angle)
{
  Mat4 matrix = mat4Identity();

  float cosA = cos(angle);
  float sinA = sin(angle);
  float cosN = 1.0f - cosA;
  
  matrix.xx = v.x * v.x * cosN + cosA;
  matrix.xy = v.x * v.y * cosN - v.z * sinA;
  matrix.xz = v.x * v.z * cosN + v.y * sinA;
  
  matrix.yx = v.y * v.x * cosN + v.z * sinA;
  matrix.yy = v.y * v.y * cosN + cosA;
  matrix.yz = v.y * v.z * cosN - v.x * sinA;
  
  matrix.zx = v.z * v.x * cosN - v.y * sinA;
  matrix.zy = v.z * v.y * cosN + v.x * sinA;
  matrix.zz = v.z * v.z * cosN + cosA;
  
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

Mat4 mat4Scale(Vec3 s)
{
	Mat4 matrix = mat4Identity();

	matrix.xx = s.x;
	matrix.yy = s.y;
	matrix.zz = s.z;

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

	float determinant = 1.0f / mat4Determinant(m);

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

	Vec3 z = vec3Normalize(vec3AddVec3(position, vec3Negative(target)));
	Vec3 x = vec3Normalize(vec3CrossProduct(up, z));
	Vec3 y = vec3CrossProduct(z, x);

	matrix.xx = x.x;
	matrix.xy = x.y;
	matrix.xz = x.z;

	matrix.yx = y.x;
	matrix.yy = y.y;
	matrix.yz = y.z;

	matrix.zx = z.x;
	matrix.zy = z.y;
	matrix.zz = z.z;

	return mat4MultiplyMat4(matrix, mat4Translation(vec3Negative(position)));
}

Mat4 mat4Orthographic(float left, float right, float top, float bottom, float nearClip, float farClip)
{
	Mat4 matrix = mat4Empty();

	matrix.xx = 2.0f / (right - left); 
	matrix.yy = 2.0f / (top - bottom); 
	matrix.zz = 1.0f / (nearClip - farClip); 
	   
	matrix.xw = -1.0f - 2.0f * left / (right - left); 
	matrix.yw = 1.0f + 2.0f * top  / (bottom - top); 
	matrix.zw = nearClip / (nearClip - farClip); 

	return matrix;
}

Mat4 mat4Perspective(float fov, float aspectRatio, float nearClip, float farClip)
{
	Mat4 matrix = mat4Empty();

	float cotan = 1.0f / tanf(fov / 2.0f); 

	matrix.xx = cotan / aspectRatio;
	matrix.yy = cotan;
	matrix.zz = (farClip + nearClip) / (nearClip - farClip);

	matrix.zw = (2.0f * farClip * nearClip) / (nearClip - farClip);
	matrix.wz = -1.0f;

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