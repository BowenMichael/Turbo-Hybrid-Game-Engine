#pragma once

#include "headers/Components/ColliderColorChanger.h"
#include "headers/Components/PlayerController.h"
#include "headers/Components/RectangleCollider.h"
#include "headers/Components/RectangleRenderer.h"
#include "headers/Components/Transform.h"

namespace TurboHybrid {
	const int MAX_COMPONENTS = 1000;

	struct Components {
		Components()
		{
		};
		ColliderColorChanger sCollorChangerComponents[MAX_COMPONENTS];
		PlayerController sPlayerControllerComponents[MAX_COMPONENTS];
		RectangleCollider sRectangleColliders[MAX_COMPONENTS];
		RectangleRenderer sRectangleRenderers[MAX_COMPONENTS];
		Transform sTransforms[MAX_COMPONENTS];

		int sNumOfColorChangers = 0;
		int sNumOfPlayerControllers = 0;
		int sNumOfRectangleColliders = 0;
		int sNumOfRectangleRenderers = 0;
		int sNumOfTransforms = 0;
	};

	class ComponentSystem
	{
	public:
		static void InitInstance();
		static ComponentSystem* GetComponentSystem();
		static void DeleteInstance();

		
		static ColliderColorChanger* allocateCollorChanger();
		static PlayerController* allocatePlayerController();
		static RectangleCollider* allocateRectangleCollider();
		static RectangleRenderer* allocateRectangleRenderer();
		static Transform* allocateTransform();

		static void update(const float& deltatime);
		static void render(SDL_Renderer* sdlRenderer);
	private:
		ComponentSystem();
		static Components mComponents;
		static ComponentSystem* self;
		
	};
}

