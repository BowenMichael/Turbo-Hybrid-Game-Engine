#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../../headers/System_Common.h"

namespace TurboHybrid {
	const string ERROR_K = L"Do not press K!!!\n";
	const string LOG_ERROR_K = L"Error: User pressed 'k'\n";
	class System_Win32 : public System
	{
	public:
		~System_Win32() {};
		void Init() override;
		void Shutdown() override;
		void ShowError(const TurboHybrid::string& message) override;
		void LogToErrorFile(const TurboHybrid::string& message) override;
	protected:
	private:
		HANDLE mhFile;
		_CrtMemState memState;
	};

}


