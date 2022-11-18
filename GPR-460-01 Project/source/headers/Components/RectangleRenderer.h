#pragma once
#include "Component_Common.h"

#include "headers/Util/Color.h"
#include "headers/Util/Rect.h"
#include "headers/Util/Vector3.h"

namespace TurboHybrid {
	class GameObject;
	class ComponentSystem;
	class RectangleRenderer
	{
	public:
		RectangleRenderer();
		~RectangleRenderer();
		RectangleRenderer(const Rect& rect, const Color& color);
		RectangleRenderer(const float& height, const float& width);

		static enum { kCompID = 'RECT' };
		static void CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator);
		void load(const Rect& position, const Color& color);

		Rect GetRect();
		Color GetColor();

		Rect SetRect(const Rect& rect);
		Color SetColor(const Color& color);

		GameObject* gameObject;
	protected:
		Rect _rect;
		Color _color;
		
	};
}



