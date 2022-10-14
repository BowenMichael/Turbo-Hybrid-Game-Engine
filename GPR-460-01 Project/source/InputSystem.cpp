#include "../source/headers/InputSystem.h"

TurboHybrid::InputSystem* TurboHybrid::InputSystem::self = nullptr;

void TurboHybrid::InputSystem::InitInstance()
{
	if (self == nullptr) {
		self = new InputSystem();
	}
}

TurboHybrid::InputSystem* TurboHybrid::InputSystem::GetInputSystem()
{
	return self;
}

void TurboHybrid::InputSystem::DeleteInstance()
{
	delete self;
	self = nullptr;
}

//bool TurboHybrid::InputSystem::GetKey(const Uint8& key)
//{
//	const Uint8* keystate = SDL_GetKeyboardState(NULL);
//}

TurboHybrid::InputSystem::InputSystem()
{
}




