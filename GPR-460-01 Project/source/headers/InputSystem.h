#pragma once



namespace TurboHybrid {
	class InputSystem
	{
	public:
		static void InitInstance();
		static InputSystem* GetInputSystem();
		static void DeleteInstance();
		//static bool GetKey(const Uint8& key);
		//static void update(const float& deltatime);

	private:
		static InputSystem* self;
		InputSystem();

		
		
	};
}

