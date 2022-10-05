#pragma once
#include <SDL.h>
#include "Components/ColliderColorChanger.h"
#include "Components/PlayerController.h"
#include "Components/RectangleCollider.h"
#include "Components/RectangleRenderer.h"
#include "Components/Transform.h"


namespace TurboHybrid {

	class GameObject
	{
	public:
		GameObject();
		~GameObject();
		
		RectangleRenderer* CreateRenderer();
		RectangleCollider* CreateCollider();
		PlayerController* CreatePlayerController();
		ColliderColorChanger* CreateColliderColorChanger();

		void Draw(SDL_Renderer* sdlRenderer);
		void Update();
	protected:
		Transform transform;
		RectangleRenderer* renderer;
		RectangleCollider* collider;
		PlayerController* player;
		ColliderColorChanger* colorChanger;
	};

}

