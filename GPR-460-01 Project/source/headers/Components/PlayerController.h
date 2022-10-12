#pragma once

namespace TurboHybrid {
	class GameObject;
	class PlayerController
	{
	public:
		PlayerController(GameObject* gameobject);
		~PlayerController();
		void update(const float& deltatime);

	private:
		GameObject* gameObject;
	};
}
