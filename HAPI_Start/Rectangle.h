#pragma once
#include "algorithm"
#include "Vector2.h"

class Rectangle
{
public:
	int left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };

	Rectangle() {
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}

	Rectangle(int w, int h, Vector2 Position = Vector2(0,0)) {
		left = (int)Position.x;
		right = (int)Position.x + w;
		top = (int)Position.y;
		bottom = (int)Position.y + h;
	}

	Rectangle(int l, int r, int t, int b) {
		left = l;
		right = r;
		top = t;
		bottom = b;
	}

	int Width() const { return right - left; }
	int Height() const { return bottom - top; }

	void ClipTo(const Rectangle& other) {
		left = std::max(left, other.left);
		right = std::min(right, other.right);
		top = std::max(top, other.top);
		bottom = std::min(bottom, other.bottom);
	}

	bool CompletelyContains(const Rectangle& other) {
		if (other.left > left && other.right < right && other.top > top && other.bottom < bottom)
			return true;

		return false;
	}

	bool CompletelyOutside(const Rectangle& other) {
		if (other.left > right || other.right < left || other.top > bottom || other.bottom < top)
			return true;

		return false;
	}

	void Translate(int dx, int dy) {
		left += dx;
		right += dx;
		top += dy;
		bottom += dy;
	}

	bool isCollide(const Rectangle& other) {

		if (left >= other.right)
			return false;

		if (top >= other.bottom)
			return false;

		if (other.left >= right)
			return false;

		if (other.top >= bottom)
			return false;

		return true;
	}
};

