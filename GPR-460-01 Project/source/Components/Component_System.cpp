#include "headers/Components/Component_System.h" 
#include "headers/GameObject.h"
#include "headers/System_Common.h"
#include <sstream>
#include <iostream>

TurboHybrid::ComponentSystem* TurboHybrid::ComponentSystem::self = nullptr;
TurboHybrid::Components TurboHybrid::ComponentSystem::mComponents = Components();

void TurboHybrid::ComponentSystem::InitInstance()
{
	if (self == nullptr) {
		self = DBG_NEW ComponentSystem();

		
	}
}

TurboHybrid::ComponentSystem* TurboHybrid::ComponentSystem::GetComponentSystem()
{
	return self;
}

void TurboHybrid::ComponentSystem::DeleteInstance()
{
	delete self;
	self = nullptr;
}

TurboHybrid::ColliderColorChanger* TurboHybrid::ComponentSystem::allocateCollorChanger()
{
	mComponents.sNumOfColorChangers++;
	if (mComponents.sNumOfColorChangers <= MAX_COMPONENTS) {
		ColliderColorChanger* colorChanger = &mComponents.sCollorChangerComponents[mComponents.sNumOfColorChangers-1];
		return colorChanger;
	}
	SDL_assert(false);
	return nullptr;
}

TurboHybrid::PlayerController* TurboHybrid::ComponentSystem::allocatePlayerController()
{
	mComponents.sNumOfPlayerControllers++;
	if (mComponents.sNumOfPlayerControllers <= MAX_COMPONENTS) {
		PlayerController* playerController = &mComponents.sPlayerControllerComponents[mComponents.sNumOfPlayerControllers-1];
		return playerController;
	}
	SDL_assert(false);
	return nullptr;
}

TurboHybrid::RectangleCollider* TurboHybrid::ComponentSystem::allocateRectangleCollider()
{
	mComponents.sNumOfRectangleColliders++;
	if (mComponents.sNumOfRectangleColliders <= MAX_COMPONENTS) {
		RectangleCollider* collider = &mComponents.sRectangleColliders[mComponents.sNumOfRectangleColliders-1];
		return collider;
	}
	SDL_assert(false);
	return nullptr;
}

TurboHybrid::RectangleRenderer* TurboHybrid::ComponentSystem::allocateRectangleRenderer()
{
	mComponents.sNumOfRectangleRenderers++;
	if (mComponents.sNumOfRectangleRenderers <= MAX_COMPONENTS) {
		RectangleRenderer* renderer = &mComponents.sRectangleRenderers[mComponents.sNumOfRectangleRenderers-1];
		return renderer;
	}
	SDL_assert(false);
	return nullptr;
}

TurboHybrid::CubeRenderer* TurboHybrid::ComponentSystem::allocateCubeRenderer()
{
	mComponents.sNumOfCubeRenderers++;
	if (mComponents.sNumOfCubeRenderers <= MAX_COMPONENTS) {
		CubeRenderer* renderer = &mComponents.sCubeRenderer[mComponents.sNumOfCubeRenderers - 1];
		return renderer;
	}
	SDL_assert(false);
	return nullptr;
}

TurboHybrid::Transform* TurboHybrid::ComponentSystem::allocateTransform()
{
	mComponents.sNumOfTransforms++;
	if (mComponents.sNumOfTransforms <= MAX_COMPONENTS) {
		Transform* transform = &mComponents.sTransforms[mComponents.sNumOfTransforms-1];
		return transform;
	}
	SDL_assert(false);
	return nullptr;
}

void TurboHybrid::ComponentSystem::assignCubeBuffers(const bgfx::VertexBufferHandle& vbh, const bgfx::IndexBufferHandle& ibh, const bgfx::ProgramHandle& ph)
{
	for (int i = 0; i < MAX_COMPONENTS; i++) {
		mComponents.sCubeRenderer[i].SetBuffers(vbh, ibh, ph);
	}
}

void TurboHybrid::ComponentSystem::AddComponentToGameObject(const int& indexLiteral, GameObject* gameObject)
{
	mCreationMap[indexLiteral](gameObject, this);
}

void TurboHybrid::ComponentSystem::update(const float& deltatime)
{
	for (int i = 0; i < mComponents.sNumOfColorChangers; i++) {
		mComponents.sCollorChangerComponents[i].Update(deltatime);
	}
	for (int i = 0; i < mComponents.sNumOfPlayerControllers; i++) {
		mComponents.sPlayerControllerComponents[i].update(deltatime);
	}
	/*for (int i = 0; i < mComponents.sNumOfRectangleColliders; i++) {
		for (int j = 0; j < mComponents.sNumOfRectangleColliders; j++) {
			if (i != j)
				mComponents.sRectangleColliders[i].CheckCollision(&mComponents.sRectangleColliders[j]);

		}
	}*/
	/*for (int i = 0; i < mComponents.sNumOfRectangleColliders; i++) 
	{
		if (mComponents.sRectangleColliders[i].GetIsColliding()) {
			mComponents.sRectangleColliders[i].OnCollisionWithOther();
		}
	}*/
}

void TurboHybrid::ComponentSystem::render(SDL_Renderer* sdlRenderer)
{
	//I don't like doing this every fram but it works for now
	//SDL_Rect* rects = DBG_NEW SDL_Rect[mComponents.sNumOfRectangleRenderers];
	for (int i = mComponents.sNumOfRectangleRenderers - 1; i >= 0; i--) {
		RectangleRenderer* renderer = &mComponents.sRectangleRenderers[i];
		Transform* transform = renderer->gameObject->GetTransform();
		if (!transform)
			continue;
		Rect rect = renderer->GetRect();
		Color color = renderer->GetColor();
		SDL_Rect r = {
			static_cast<int>(transform->GetLocation().x),
			static_cast<int>(transform->GetLocation().y),
			static_cast<int>(rect.width),
			static_cast<int>(rect.height)
		};

		SDL_SetRenderDrawColor(sdlRenderer, (Uint8)(color.r * 255), (Uint8)(color.g * 255), (Uint8)(color.b * 255), (Uint8)(color.a * SDL_ALPHA_OPAQUE));
		SDL_RenderDrawRect(sdlRenderer, &r);
		SDL_RenderFillRect(sdlRenderer, &r);

		//rects[i] = r;
	}
	
	Uint8 r, g, b, a;
	//SDL_GetRenderDrawColor(sdlRenderer, &r, &g, &b, &a);
	//SDL_SetRenderDrawColor(sdlRenderer, 75, 75, 75, 255);
	////SDL_RenderFillRects(sdlRenderer, rects, mComponents.sNumOfRectangleRenderers);
	//SDL_SetRenderDrawColor(sdlRenderer, r, g, b, a);
	//SDL_RenderDrawRects(sdlRenderer, rects, mComponents.sNumOfRectangleRenderers);
	//delete rects;
	
}

void TurboHybrid::ComponentSystem::renderCubes(const float& deltatime)
{
	for (int i = mComponents.sNumOfCubeRenderers - 1; i >= 0; i--) {
		CubeRenderer* renderer = &mComponents.sCubeRenderer[i];

		renderer->render(deltatime);
	}
}

TurboHybrid::ComponentSystem::ComponentSystem()
{
	REGISTER_COMPONENT(TurboHybrid::Transform);
	//REGISTER_COMPONENT(TurboHybrid::RectangleRenderer);

	mCreationMap[RectangleRenderer::kCompID] = RectangleRenderer::CreateComponent;
	REGISTER_COMPONENT(TurboHybrid::RectangleCollider);
	REGISTER_COMPONENT(TurboHybrid::PlayerController);
	REGISTER_COMPONENT(TurboHybrid::ColliderColorChanger);
	REGISTER_COMPONENT(TurboHybrid::CubeRenderer);
}

