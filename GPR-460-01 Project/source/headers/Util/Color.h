#pragma once

struct Color
{
	Color()
	{
		r = 1;
		g = 1;
		b = 1;
		a = 1;
	}

	Color(const float& r, const float& g, const float& b, const float& a) 
		: r(r),
		g(g),
		b(b),
		a(a)
	{
	}

	

	float r, g, b, a;
};