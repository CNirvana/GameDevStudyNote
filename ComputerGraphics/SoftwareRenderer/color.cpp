#include "color.h"

const Color Color::clear = Color(0, 0, 0, 0);
const Color Color::white = Color(1, 1, 1);
const Color Color::black = Color(0, 0, 0);
const Color Color::gray = Color(0.5, 0.5, 0.5);
const Color Color::red = Color(1, 0, 0);
const Color Color::green = Color(0, 1, 0);
const Color Color::blue = Color(0, 0, 1);
const Color Color::yellow = Color(1, 1, 0);

Color operator + (const Color& left, const Color& right)
{
	return Color(
		left.r + right.r,
		left.g + right.g,
		left.b + right.b,
		left.a + right.a
	);
}

Color operator - (const Color& left, const Color& right)
{
	return Color(
		left.r - right.r,
		left.g - right.g,
		left.b - right.b,
		left.a - right.a
	);
}

Color operator * (const Color& left, const Color& right)
{
	return Color(
		left.r * right.r,
		left.g * right.g,
		left.b * right.b,
		left.a * right.a
	);
}

Color& operator *= (Color& left, const Color& right)
{
	left.r *= right.r;
	left.g *= right.g;
	left.b *= right.b;
	left.a *= right.a;
	return left;
}

Color operator * (const Color& c, float t)
{
	return Color(
		c.r *t,
		c.g *t,
		c.b *t,
		c.a *t
	);
}

Color operator * (float t, const Color& c)
{
	return c * t;
}

Color operator / (const Color& c, float t)
{
	return Color(
		c.r / t,
		c.g / t,
		c.b / t,
		c.a / t
		);
}