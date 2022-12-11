#pragma once

#include "headers/Components/ColliderColorChanger.h"
#include "headers/Components/PlayerController.h"
#include "headers/Components/RectangleCollider.h"
#include "headers/Components/RectangleRenderer.h"
#include "headers/Components/Transform.h"
#include "headers/Components/CubeRenderer.h"

#include <unordered_map>

typedef void (*CompFn)(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator);

#define REGISTER_COMPONENT(t) mCreationMap[t::kCompID] = t::CreateComponent

namespace TurboHybrid {
	const int MAX_COMPONENTS = 1000;
	const int KEY_SIZE = 4;

	class GameObject;
	struct Components {
		Components()
		{
		};

		ColliderColorChanger sCollorChangerComponents[MAX_COMPONENTS];
		PlayerController sPlayerControllerComponents[MAX_COMPONENTS];
		RectangleCollider sRectangleColliders[MAX_COMPONENTS];
		CubeRenderer sCubeRenderer[MAX_COMPONENTS];
		RectangleRenderer sRectangleRenderers[MAX_COMPONENTS];
		Transform sTransforms[MAX_COMPONENTS];

		int sNumOfColorChangers = 0;
		int sNumOfPlayerControllers = 0;
		int sNumOfRectangleColliders = 0;
		int sNumOfRectangleRenderers = 0;
		int sNumOfCubeRenderers = 0;
		int sNumOfTransforms = 0;
	};

	class ComponentSystem
	{
	public:
		static void InitInstance();
		static ComponentSystem* GetComponentSystem();
		static void DeleteInstance();

		//RectangleRenderer* CreateRenderer();
		//RectangleCollider* CreateCollider();
		//PlayerController* CreatePlayerController();
		//ColliderColorChanger* CreateColliderColorChanger();
		
		static ColliderColorChanger* allocateCollorChanger();
		static PlayerController* allocatePlayerController();
		static RectangleCollider* allocateRectangleCollider();
		static RectangleRenderer* allocateRectangleRenderer();
		static CubeRenderer* allocateCubeRenderer();
		static Transform* allocateTransform();
		static void assignCubeBuffers(const bgfx::VertexBufferHandle& vbh, const bgfx::IndexBufferHandle& ibh, const bgfx::ProgramHandle& ph);

		void AddComponentToGameObject(const int& indexLiteral, GameObject* gameObject);

		static void update(const float& deltatime);
		static void render(SDL_Renderer* sdlRenderer);
		static void renderCubes(const float& deltatime);
	private:
		ComponentSystem();
		static Components mComponents;
		static ComponentSystem* self;
		std::unordered_map<int32_t, CompFn> mCreationMap;
		
	};
}

