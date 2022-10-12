#include "../source/headers/Components/PlayerController.h"
#include "../source/headers/GameObject.h"
#include <SDL.h>

TurboHybrid::PlayerController::PlayerController(GameObject* gameobject)
	:gameObject(gameobject)
{
}

TurboHybrid::PlayerController::~PlayerController()
{
}

void TurboHybrid::PlayerController::update(const float& deltatime)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_W]) {
		gameObject->GetTransform()->TranslateRect(Vector3(0, -1, 0));
	}
	if (keystate[SDL_SCANCODE_S]) {
		gameObject->GetTransform()->TranslateRect(Vector3(0, 1, 0));
	}
	if (keystate[SDL_SCANCODE_A]) {
		gameObject->GetTransform()->TranslateRect(Vector3(-1, 0, 0));
	}
	if (keystate[SDL_SCANCODE_D]) {
		gameObject->GetTransform()->TranslateRect(Vector3(1, 0, 0));
	}
}
