#include "headers/Components/PlayerController.h"
#include "headers/GameObject.h"
#include <SDL.h>
#include <headers/Components/Component_System.h>

TurboHybrid::PlayerController::PlayerController()
	:gameObject(nullptr)
{
}

TurboHybrid::PlayerController::PlayerController(GameObject* gameobject)
	:gameObject(gameobject)
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

void TurboHybrid::PlayerController::load()
{
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
	gameObject->GetTransform()->TranslateRect(dir * .1f);
}
