#pragma once
#include "Component_Common.h"

#include "headers/Util/Color.h"
#include "headers/Util/Rect.h"
#include "headers/Util/Vector3.h"

namespace TurboHybrid {
	class RectangleRenderer
	{
	public:
		RectangleRenderer();
		~RectangleRenderer();
		RectangleRenderer(const Rect& rect, const Color& color);
		RectangleRenderer(const float& height, const float& width);

		Rect GetRect();
		Color GetColor();

		Rect SetRect(const Rect& rect);
		Color SetColor(const Color& color);


	protected:
		Rect rect;
		Color color;
	};
}



