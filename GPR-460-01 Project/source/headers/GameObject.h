#pragma once
#include <SDL.h>
#include "Components/Transform.h"


namespace TurboHybrid {

	class RectangleRenderer;
	class RectangleCollider;
	class PlayerController;
	class ColliderColorChanger;

	class GameObject
	{
	public:
		GameObject();
		~GameObject();
		
		RectangleRenderer* CreateRenderer();
		RectangleCollider* CreateCollider();
		PlayerController* CreatePlayerController();
		ColliderColorChanger* CreateColliderColorChanger();

		Transform* GetTransform() { return &transform; };
		RectangleCollider* GetCollider() { return collider; };
		RectangleRenderer* GetRenderer() { return renderer; };

		void CheckCollision(GameObject* other);


		void Draw(SDL_Renderer* sdlRenderer);
		void Update(const float& deltatime);
	protected:
		Transform transform;
		RectangleRenderer* renderer;
		RectangleCollider* collider;
		PlayerController* player;
		ColliderColorChanger* colorChanger;
	};

}

