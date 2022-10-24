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
		GameObject* gameobject;
	private:
		Color collidedColor;
		Color originalColor;
		
	};
}

