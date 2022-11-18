#include "headers/Components/RectangleRenderer.h"
#include <headers/Components/Component_System.h>
#include <headers/GameObject.h>

TurboHybrid::RectangleRenderer::RectangleRenderer()
	: _rect(),
	_color()
{
}

TurboHybrid::RectangleRenderer::~RectangleRenderer()
{
}

TurboHybrid::RectangleRenderer::RectangleRenderer(const Rect& rect, const Color& color)
	: _rect(rect),
	_color(color)
{
}

TurboHybrid::RectangleRenderer::RectangleRenderer(const float& height, const float& width)
	: _rect(width, height),
	_color()
{
}

void TurboHybrid::RectangleRenderer::CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator)
{
	RectangleRenderer* tmp = allocator->allocateRectangleRenderer();
	tmp->gameObject = gm;
	gm->SetRenderer(tmp);
}

void TurboHybrid::RectangleRenderer::load(const Rect& rect, const Color& color)
{
	SetRect(rect);
	SetColor(color);
}

Rect TurboHybrid::RectangleRenderer::GetRect()
{
	return _rect;
}

Color TurboHybrid::RectangleRenderer::GetColor()
{
	return _color;
}

Rect TurboHybrid::RectangleRenderer::SetRect(const Rect& r)
{
	_rect = r;
	return _rect;
}

Color TurboHybrid::RectangleRenderer::SetColor(const Color& c)
{
	_color = c;
	return _color;
}

