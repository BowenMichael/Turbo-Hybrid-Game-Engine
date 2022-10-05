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

TurboHybrid::InputSystem::InputSystem()
{
}




