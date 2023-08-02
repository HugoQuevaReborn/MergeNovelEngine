#pragma once

#include <math.h>

class Vec2F {
public:
	/// <summary>
	/// The horizontal value of the vector.
	/// </summary>
	float x;
	/// <summary>
	/// The vertical value of the vector.
	/// </summary>
	float y;

	/// <summary>
	/// Initiate a vector2 float with (0,0) coordinates.
	/// </summary>
	Vec2F() : x(0.0f), y(0.0f)
	{}

	/// <summary>
	/// Creates a vector2 float using values.
	/// </summary>
	/// <param name="x_v"></param>
	/// <param name="y_v"></param>
	Vec2F(float x_v, float y_v) : x(x_v), y(y_v){}

	/// <summary>
	/// Create a vector2 float from another one. This function contains a safe
	/// guard if the referenced vector is nullptr.
	/// </summary>
	/// <param name="vec"></param>
	Vec2F(Vec2F& vec) : x(&vec != nullptr ? vec.x : 0), y(&vec != nullptr ? vec.y : 0)
	{}

	Vec2F& operator+=(Vec2F& vec) {
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vec2F& operator-=(Vec2F& vec) {
		x -= vec.x;
		y -= vec.y;

		return *this;
	}
};

class Vec2I {
public:
	/// <summary>
	/// The horizontal value of the vector.
	/// </summary>
	int x;
	/// <summary>
	/// The vertical value of the vector.
	/// </summary>
	int y;

	/// <summary>
	/// Initiate a vector2 float with (0,0) coordinates.
	/// </summary>
	Vec2I() : x(0), y(0)
	{}

	/// <summary>
	/// Creates a vector2 float using values.
	/// </summary>
	/// <param name="x_v"></param>
	/// <param name="y_v"></param>
	Vec2I(int x_v, int y_v) : x(x_v), y(y_v) {}

	/// <summary>
	/// Create a vector2 float from another one. This function contains a safe
	/// guard if the referenced vector is nullptr.
	/// </summary>
	/// <param name="vec"></param>
	Vec2I(Vec2I& vec) : x(&vec != nullptr ? vec.x : 0), y(&vec != nullptr ? vec.y : 0)
	{}
	
	Vec2I& operator+=(Vec2I& vec) {
		x += vec.x;
		y += vec.y;

		return *this;
	}

	Vec2I& operator-=(Vec2I& vec) {
		x -= vec.x;
		y -= vec.y;

		return *this;
	}
};

class Math
{
public:
	static float Lerp(float a, float b, float t) {
		return a * (1.0f - t) + (b * t);
	}

	static float Clamp(float val, float min, float max) {
		return val < min ? min : val > max ? max : val;
	}

	static float Sqrt(float x) {
		return sqrt(x);
	}
};