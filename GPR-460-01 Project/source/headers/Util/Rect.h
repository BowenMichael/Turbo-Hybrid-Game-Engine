#pragma once


struct Rect {
	Rect() 
	{
		width = 100;
		height = 100;
	}
	Rect(const float& w, const float& h) 
	{
		width = w;
		height = h;
	}

	float width;
	float height;
};