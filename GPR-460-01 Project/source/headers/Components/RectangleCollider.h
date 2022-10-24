#pragma once
namespace TurboHybrid {
	class GameObject;
	class RectangleCollider
	{
	public:
		RectangleCollider();
		RectangleCollider(GameObject* gm);

		void Update(const float& deltaTime);
		bool CheckCollision(RectangleCollider* other);
		void SetOnCollision(void (*onCollisionCallback)());
		bool GetIsColliding() { return isColliding; };
		GameObject* gameObject;

	private:
		void (*OnCollision)();
	
		bool isColliding;
	};
}


