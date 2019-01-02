#pragma once

struct Color
{
	float r;
	float g;
	float b;
	float a;

	Color() : r(0), g(0), b(0), a(1) {}
	Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b), a(1) {}
	Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}

	static const Color clear;
	static const Color white;
	static const Color black;
	static const Color gray;
	static const Color red;
	static const Color green;
	static const Color blue;
	static const Color yellow;

};

Color operator + (const Color& left, const Color& right);
Color operator - (const Color& left, const Color& right);
Color operator * (const Color& left, const Color& right);
Color& operator *= (Color& left, const Color& right);
Color& operator *= (Color& left, float right);
Color operator * (const Color& c, float t);
Color operator * (float t, const Color& c);
Color operator / (const Color& c, float t);