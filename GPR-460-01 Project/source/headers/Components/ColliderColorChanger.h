#pragma once
#include "headers/Util/Color.h"

namespace TurboHybrid {
	class RectangleRenderer;
	class GameObject;
	class ComponentSystem;
	class ColliderColorChanger
	{
	public:
		ColliderColorChanger();
		ColliderColorChanger(GameObject* gameobject, const Color& color);

		static enum { kCompID = 'ZCCR' };
		static void CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator);
		void load(const Color& collidedColor);

		void Update(const float& deltatime);

		void setCollidedColor(const Color& color) { _collidedColor = color; };
		void setOriginalColor(const Color& color) { _originalColor = color; };
		GameObject* gameObject;

		Color getCollidedColor() { return _collidedColor; };
		Color getOriginalColor() { return _originalColor; };
	private:
		Color _collidedColor;
		Color _originalColor;
		
	};
}

