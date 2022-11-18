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
		GameObject(Transform* transform );
		GameObject(Transform* transform ,  
			RectangleRenderer* rectRend = nullptr, 
			RectangleCollider* rectCol = nullptr, 
			PlayerController* plc = nullptr, 
			ColliderColorChanger* colorChanger = nullptr);
		virtual ~GameObject();
		
		void SetTransform(Transform* transform) { mTransform = transform; };
		void SetRenderer(RectangleRenderer* rectRend) { mRenderer = rectRend; };
		void SetCollider(RectangleCollider* rectCol) { mCollider = rectCol; };
		void SetPlayerController(PlayerController* plc) { mPlayer = plc; };
		void SetColliderColorChanger(ColliderColorChanger* colorChanger) { mColorChanger = colorChanger; };

		Transform* GetTransform() { return mTransform; };
		RectangleCollider* GetCollider() { return mCollider; };
		RectangleRenderer* GetRenderer() { return mRenderer; };
		PlayerController* GetPlayerController() { return mPlayer; };
		ColliderColorChanger* GetColorChanger() { return mColorChanger; };

		bool CheckCollision(GameObject* other);
		void OnCollisionWithOther(RectangleCollider* other);

		void Draw(SDL_Renderer* sdlRenderer);
	protected:
		Transform* mTransform;
		RectangleRenderer* mRenderer;
		RectangleCollider* mCollider;
		PlayerController* mPlayer;
		ColliderColorChanger* mColorChanger;
	};

}

