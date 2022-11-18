#pragma once
#include <headers/Util/Color.h>
#include <headers/Util/Rect.h>


namespace TurboHybrid {
	class GameObject;
	class ComponentSystem;
	class PlayerController
	{
	public:
		PlayerController();
		PlayerController(GameObject* gameobject);
		~PlayerController();

		static enum { kCompID = 'PLRC' };
		static void CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator);
		void load();

		void update(const float& deltatime);
		
		GameObject* gameObject;
	private:
		
	};
}
