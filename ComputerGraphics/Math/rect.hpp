#pragma once

template<typename T>
struct Rect
{
	T xMin;
	T yMin;
	T xMax;
	T yMax;

	Rect(T _xMin, T _yMin, T _xMax, T _yMax) : xMin(_xMin), yMin(_yMin), xMax(_xMax), yMax(_yMax) {}

	T getWidth() const { return xMax - xMin; }
	T getHeight() const { return yMax - yMin; }
};

typedef Rect<int> Recti;
typedef Rect<float> Rectf;