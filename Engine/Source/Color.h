#pragma once
#include "MathUtils.h"
#include <cmath>

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color() = default;
	Color(float r, float g, float b, float a) { this->r = r, this->g = g; this->b = b; this->a = a; }

	//Color Add(Color v) { return Color{ x + v.x, y + v.y }; }

	float operator [] (unsigned int index) const { return  (&r)[index]; }
	float& operator [] (unsigned int index) { return  (&r)[index]; }

	/*Color operator + (Color& v) const { return Color{ r + v.x, y + v.y }; }
	Color operator - (Color& v) const { return Color{ x - v.x, y - v.y }; }
	Color operator * (Color& v) const { return Color{ x * v.x, y * v.y }; }
	Color operator / (Color& v) const { return Color{ x / v.x, y / v.y }; }

	Color operator + (float s) const { return Color{ x + s, y + s }; }
	Color operator - (float s) const { return Color{ x - s, y - s }; }
	Color operator * (float s) const { return Color{ x * s, y * s }; }
	Color operator / (float s) const { return Color{ x / s, y / s }; }

	float LengthSqr() const { return (x * x) + (y * y); }
	float Length() const { return Math::Sqrt((x * x) + (y * y)); }

	float Angle() { return Math::Atan2(y, x); }*/

};