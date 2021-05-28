#pragma once
#include <cmath>
#include <iostream>

struct Vec2f
{
	float x = 0;
	float y = 0;

	Vec2f()
	{
		x = 0;
		y = 0;
	}

	Vec2f(float tx, float ty)
	{
		x = tx;
		y = ty;
	}

	Vec2f operator+(Vec2f a)
	{
		return Vec2f(x + a.x, y + a.y);
	}

	Vec2f& operator+=(Vec2f a)
	{
		x += a.x;
		y += a.y;

		return *this;
	}

	Vec2f operator-(Vec2f a)
	{
		return Vec2f(x - a.x, y - a.y);
	}

	Vec2f& operator-=(Vec2f a)
	{
		x -= a.x;
		y -= a.y;

		return *this;
	}

	Vec2f operator*(Vec2f a)
	{
		return Vec2f(x * a.x, y * a.y);
	}

	Vec2f& operator*=(Vec2f a)
	{
		x *= a.x;
		y *= a.y;

		return *this;
	}

	Vec2f operator/(Vec2f a)
	{
		if (a.x == 0 || a.y == 0)
		{
			std::cout << "Divided by zero in vector 3 function." << std::endl;
			return *this;
		}

		return Vec2f(x / a.x, y / a.y);


	}

	Vec2f& operator/=(Vec2f a)
	{
		if (a.x == 0 || a.y == 0)
		{
			std::cout << "Divided by zero in vector 3 function." << std::endl;
			return *this;
		}

		x /= a.x;
		y /= a.y;

		return *this;
	}

	Vec2f operator*(float value)
	{
		return Vec2f(x * value, y * value);
	}

	Vec2f operator*=(float value)
	{
		return Vec2f(x * value, y * value);
	}

	Vec2f operator/(float value)
	{
		if (value == 0)
		{
			std::cout << "Divided by zero in vector 2 function." << std::endl;
			return *this;
		}

		return Vec2f(x / value, y / value);
	}

	Vec2f operator/= (float value)
	{
		if (value == 0)
		{
			std::cout << "Divided by zero in vector 2 function." << std::endl;
			return *this;
		}

		return Vec2f(x / value, y / value);
	}

	float mag()
	{
		return sqrt(x * x + y * y);
	}

	void norm()
	{
		float magnitude = mag();

		x /= magnitude;
		y /= magnitude;
	}

	float dot(Vec2f vec)
	{
		return x * vec.x + y * vec.y;
	}
};