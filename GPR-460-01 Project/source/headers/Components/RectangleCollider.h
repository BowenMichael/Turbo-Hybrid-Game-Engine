#pragma once
namespace TurboHybrid {
	class GameObject;
	class ComponentSystem;
	class RectangleCollider
	{
	public:
		RectangleCollider();
		RectangleCollider(GameObject* gm);

		static enum { kCompID = 'CLID' };
		static void CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator);
		void load();

		void Update(const float& deltaTime);
		bool CheckCollision(RectangleCollider* other);
		void SetOnCollision(void (*onCollisionCallback)());
		bool GetIsColliding() { return isColliding; };
		void OnCollisionWithOther(RectangleCollider* other);
		GameObject* gameObject;

	private:
		void (*OnCollision)();
	
		bool isColliding;
	};
}


