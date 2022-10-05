#include "../source/headers/Components/RectangleRenderer.h"

TurboHybrid::RectangleRenderer::RectangleRenderer()
	: rect(),
	color()
{
}

TurboHybrid::RectangleRenderer::~RectangleRenderer()
{
}

TurboHybrid::RectangleRenderer::RectangleRenderer(const Rect& rect, const Color& color)
	: rect(rect),
	color(color)
{
}

TurboHybrid::RectangleRenderer::RectangleRenderer(const float& height, const float& width)
	: rect(width, height),
	color()
{
}

Rect TurboHybrid::RectangleRenderer::GetRect()
{
	return rect;
}

Color TurboHybrid::RectangleRenderer::GetColor()
{
	return color;
}

Rect TurboHybrid::RectangleRenderer::SetRect(const Rect& r)
{
	rect = r;
	return rect;
}

Color TurboHybrid::RectangleRenderer::SetColor(const Color& c)
{
	color = c;
	return color;
}

