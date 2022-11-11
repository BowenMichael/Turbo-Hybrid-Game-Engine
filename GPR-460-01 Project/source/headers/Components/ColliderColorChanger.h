#pragma once
#include "headers/Util/Color.h"

namespace TurboHybrid {
	class RectangleRenderer;
	class GameObject;
	class ColliderColorChanger
	{
	public:
		ColliderColorChanger();
		ColliderColorChanger(GameObject* gameobject, const Color& color);
		void Update(const float& deltatime);

		void setCollidedColor(const Color& color) { collidedColor = color; };
		void setOriginalColor(const Color& color) { originalColor = color; };
		GameObject* gameobject;

		Color getCollidedColor() { return collidedColor; };
		Color getOriginalColor() { return originalColor; };
	private:
		Color collidedColor;
		Color originalColor;
		
	};
}

