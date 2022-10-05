#pragma once
namespace TurboHybrid {
	class InputSystem
	{
	public:
		static void InitInstance();
		static InputSystem* GetInputSystem();
		static void DeleteInstance();

	private:
		static InputSystem* self;

		InputSystem();

		
		
	};
}

