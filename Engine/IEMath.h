/*
	Copyright (c) 2013 Randy Gaul http://RandyGaul.net

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:
	  1. The origin of this software must not be misrepresented; you must not
		 claim that you wrote the original software. If you use this software
		 in a product, an acknowledgment in the product documentation would be
		 appreciated but is not required.
	  2. Altered source versions must be plainly marked as such, and must not be
		 misrepresented as being the original software.
	  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef IEMATH_H
#define IEMATH_H

// Impulse Engine Math : IEMath

#include <cmath> // abs, sqrt
#include <cassert> // assert
#include <algorithm> // max, min

typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
#ifdef WIN32 // these types are not standard, only exist in windows
typedef __int64 int64;
typedef unsigned __int64 uint64;
#endif
typedef float f32;
typedef double f64;

const float PI = 3.141592741f;
const float EPSILON = 0.0001f;

struct Vec2
{
	union
	{
		float m[1][1];
		float v[2];

		struct
		{
			float x;
			float y;
		};
	};

	Vec2() {}
	Vec2(float x_, float y_)
		: x(x_)
		, y(y_)
	{
	}

	void Set(float x_, float y_)
	{
		x = x_;
		y = y_;
	}

	Vec2 operator-(void) const
	{
		return Vec2(-x, -y);
	}

	Vec2 operator*(float s) const
	{
		return Vec2(x * s, y * s);
	}

	Vec2 operator/(float s) const
	{
		return Vec2(x / s, y / s);
	}

	void operator*=(float s)
	{
		x *= s;
		y *= s;
	}

	Vec2 operator+(const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	Vec2 operator+(float s) const
	{
		return Vec2(x + s, y + s);
	}

	void operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}

	Vec2 operator-(const Vec2& rhs) const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}

	void operator-=(const Vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
	}

	float LenSqr(void) const
	{
		return x * x + y * y;
	}

	float Len(void) const
	{
		return std::sqrt(x * x + y * y);
	}

	void Rotate(float radians)
	{
		float c = std::cos(radians);
		float s = std::sin(radians);

		float xp = x * c - y * s;
		float yp = x * s + y * c;

		x = xp;
		y = yp;
	}

	void Normalize(void)
	{
		float len = Len();

		if (len > EPSILON)
		{
			float invLen = 1.0f / len;
			x *= invLen;
			y *= invLen;
		}
	}
};

inline Vec2 operator*(float s, const Vec2& v)
{
	return Vec2(s * v.x, s * v.y);
}

struct Mat2
{
	union
	{
		struct
		{
			float m00, m01;
			float m10, m11;
		};

		float m[2][2];
		float v[4];
	};

	Mat2() {}
	Mat2(float radians)
	{
		float c = std::cos(radians);
		float s = std::sin(radians);

		m00 = c; m01 = -s;
		m10 = s; m11 = c;
	}

	Mat2(float a, float b, float c, float d)
		: m00(a), m01(b)
		, m10(c), m11(d)
	{
	}

	void Set(float radians)
	{
		float c = std::cos(radians);
		float s = std::sin(radians);

		m00 = c; m01 = -s;
		m10 = s; m11 = c;
	}

	Mat2 Abs(void) const
	{
		return Mat2(std::abs(m00), std::abs(m01), std::abs(m10), std::abs(m11));
	}

	Vec2 AxisX(void) const
	{
		return Vec2(m00, m10);
	}

	Vec2 AxisY(void) const
	{
		return Vec2(m01, m11);
	}

	Mat2 Transpose(void) const
	{
		return Mat2(m00, m10, m01, m11);
	}

	const Vec2 operator*(const Vec2& rhs) const
	{
		return Vec2(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y);
	}

	const Mat2 operator*(const Mat2& rhs) const
	{
		// [00 01]  [00 01]
		// [10 11]  [10 11]

		return Mat2(
			m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
			m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
			m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
			m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
		);
	}
};

inline Vec2 Min(const Vec2& a, const Vec2& b)
{
	return Vec2(std::min(a.x, b.x), std::min(a.y, b.y));
}

inline Vec2 Max(const Vec2& a, const Vec2& b)
{
	return Vec2(std::max(a.x, b.x), std::max(a.y, b.y));
}

inline float Dot(const Vec2& a, const Vec2& b)
{
	return a.x * b.x + a.y * b.y;
}

inline float DistSqr(const Vec2& a, const Vec2& b)
{
	Vec2 c = a - b;
	return Dot(c, c);
}

inline Vec2 Cross(const Vec2& v, float a)
{
	return Vec2(a * v.y, -a * v.x);
}

inline Vec2 Cross(float a, const Vec2& v)
{
	return Vec2(-a * v.y, a * v.x);
}

inline float Cross(const Vec2& a, const Vec2& b)
{
	return a.x * b.y - a.y * b.x;
}

// Comparison with tolerance of EPSILON
inline bool Equal(float a, float b)
{
	// <= instead of < for NaN comparison safety
	return std::abs(a - b) <= EPSILON;
}

inline float Sqr(float a)
{
	return a * a;
}

inline float Clamp(float min, float max, float a)
{
	if (a < min) return min;
	if (a > max) return max;
	return a;
}

inline int32 Round(float a)
{
	return (int32)(a + 0.5f);
}

inline float Random(float l, float h)
{
	float a = (float)rand();
	a /= RAND_MAX;
	a = (h - l) * a + l;
	return a;
}

inline bool BiasGreaterThan(float a, float b)
{
	const float k_biasRelative = 0.95f;
	const float k_biasAbsolute = 0.01f;
	return a >= b * k_biasRelative + a * k_biasAbsolute;
}

const f32 gravityScale = 10.0f;
const Vec2 gravity(0, 20.0f * gravityScale);
const float dt = 1.0f / 60.0f;

#endif // IEMATH_H
