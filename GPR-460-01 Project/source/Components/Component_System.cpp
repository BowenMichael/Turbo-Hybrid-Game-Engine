#include "headers/Components/Component_System.h" 

TurboHybrid::ComponentSystem* TurboHybrid::ComponentSystem::self = nullptr;
TurboHybrid::Components TurboHybrid::ComponentSystem::mComponents = Components();

void TurboHybrid::ComponentSystem::InitInstance()
{
	if (self == nullptr) {
		self = new ComponentSystem();
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

void TurboHybrid::ComponentSystem::update(const float& deltatime)
{
	for (int i = 0; i < mComponents.sNumOfColorChangers; i++) {
		mComponents.sCollorChangerComponents[i].Update(deltatime);
	}
	for (int i = 0; i < mComponents.sNumOfPlayerControllers; i++) {
		mComponents.sPlayerControllerComponents[i].update(deltatime);
	}
	for (int i = 0; i < mComponents.sNumOfRectangleColliders; i++) {
		for (int j = 0; j < mComponents.sNumOfRectangleColliders; j++) {
			if (i != j)
				mComponents.sRectangleColliders[i].CheckCollision(&mComponents.sRectangleColliders[j]);

		}
	}
}

TurboHybrid::ComponentSystem::ComponentSystem()
{
}
