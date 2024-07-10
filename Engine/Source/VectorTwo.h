#pragma once
#include "MathUtils.h"
#include <cmath>

struct VectorTwo
{
	float x;
	float y;

	VectorTwo() = default;
	VectorTwo(float x, float y) { this->x = x, this->y = y; }
	VectorTwo(int x, int y) { this->x = (float)x, this->y = (float)y; }

	VectorTwo Add(VectorTwo v) { return VectorTwo{x + v.x, y + v.y}; }

	float operator [] (unsigned int index) const { return  (&x)[index]; }
	float& operator [] (unsigned int index) { return  (&x)[index]; }

	VectorTwo operator + (VectorTwo& v) const { return VectorTwo{ x + v.x, y + v.y }; }
	VectorTwo operator - (VectorTwo& v) const { return VectorTwo{ x - v.x, y - v.y }; }
	VectorTwo operator * (VectorTwo& v) const { return VectorTwo{ x * v.x, y * v.y }; }
	VectorTwo operator / (VectorTwo& v) const { return VectorTwo{ x / v.x, y / v.y }; }

	VectorTwo operator + (float s) const { return VectorTwo{ x + s, y + s }; }
	VectorTwo operator - (float s) const { return VectorTwo{ x - s, y - s }; }
	VectorTwo operator * (float s) const { return VectorTwo{ x * s, y * s }; }
	VectorTwo operator / (float s) const { return VectorTwo{ x / s, y / s }; }

	float LengthSqr() const { return (x * x) + (y * y); }
	float Length() const { return Math::Sqrt((x * x) + (y * y)); }

	float Angle() { return Math::Atan2(y, x); }
	VectorTwo Rotate(float radians) const;
};

VectorTwo VectorTwo::Rotate(float radians) const
{
	float x_ = x * Math::Cos(radians) - y * Math::Sin(radians);
	float y_ = x * Math::Cos(radians) + y * Math::Cos(radians);

	return { x_, y_ };
}