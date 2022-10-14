#pragma once
#include "../Util/Color.h"

namespace TurboHybrid {
	class RectangleRenderer;
	class GameObject;
	class ColliderColorChanger
	{
	public:
		ColliderColorChanger(GameObject* gameobject, const Color& color);
		void Update(const float& deltatime);

	private:
		Color collidedColor;
		Color originalColor;
		GameObject* gameobject;
	};
}

