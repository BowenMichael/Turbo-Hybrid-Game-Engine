#include "headers/Components/PlayerController.h"
#include "headers/GameObject.h"
#include <SDL.h>
#include <headers/Components/Component_System.h>

TurboHybrid::PlayerController::PlayerController()
	:gameObject(nullptr),
	mSpeed(0)
{
}

TurboHybrid::PlayerController::PlayerController(GameObject* gameobject)
	:gameObject(gameobject),
	mSpeed(0)
{
}

TurboHybrid::PlayerController::~PlayerController()
{
}

void TurboHybrid::PlayerController::CreateComponent(TurboHybrid::GameObject* gm, TurboHybrid::ComponentSystem* allocator)
{
	PlayerController* tmp = allocator->allocatePlayerController();
	tmp->gameObject = gm;
	gm->SetPlayerController(tmp);
}

void TurboHybrid::PlayerController::load(const float& speed)
{
	mSpeed = speed;
}

void TurboHybrid::PlayerController::update(const float& deltatime)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	Vector3 dir = Vector3();
	if (keystate[SDL_SCANCODE_W]) {
		dir += Vector3(0, -1, 0);
	}
	if (keystate[SDL_SCANCODE_S]) {
		dir += Vector3(0, 1, 0);
	}
	if (keystate[SDL_SCANCODE_A]) {
		dir += Vector3(-1, 0, 0);
	}
	if (keystate[SDL_SCANCODE_D]) {
		dir += Vector3(1, 0, 0);
	}
	if (keystate[SDL_SCANCODE_Q]) {
		dir += Vector3(0, 0, 1);
	}
	if (keystate[SDL_SCANCODE_E]) {
		dir += Vector3(0, 0, -1);
	}
	gameObject->GetTransform()->TranslateRect(dir * mSpeed);
}
