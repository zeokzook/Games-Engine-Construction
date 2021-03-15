#pragma once
#include <cmath>

class Vector2
{
public:
	float x{ 0 };
	float y{ 0 };
	float w{ x };
	float h{ y };

	Vector2() = default;
	Vector2(float newX, float newY) : x(newX), y(newY) {}

	Vector2 operator + (const Vector2& rhs) const 
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	Vector2 operator - (const Vector2& rhs) const
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2 operator * (float rhs) const
	{
		return Vector2(x * rhs, y * rhs);
	}

	Vector2 operator / (float rhs) const
	{
		return Vector2(x / rhs, y / rhs);
	}

	float Length() const 
	{
		return sqrt(x * x + y * y);
	}

	void NormaliseInPlace() 
	{
		float len = Length();

		if (len == 0)
			return;

		x /= len;
		y /= len;
	}

	float Dot(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}

	float Cross(const Vector2& other) const
	{
		return x * other.y - y * other.x;
	}
};

