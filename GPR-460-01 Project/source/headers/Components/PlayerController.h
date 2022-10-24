#pragma once

namespace TurboHybrid {
	class GameObject;
	class PlayerController
	{
	public:
		PlayerController();
		PlayerController(GameObject* gameobject);
		~PlayerController();
		void update(const float& deltatime);
		
		GameObject* gameObject;
	private:
		
	};
}
