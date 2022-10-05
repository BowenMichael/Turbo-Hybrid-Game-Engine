#pragma once
#include "Component_Common.h"

#include "../Util/Color.h"
#include "../Util/Rect.h"

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



