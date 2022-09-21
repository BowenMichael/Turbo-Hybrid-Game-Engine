#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include "System_Common.h"
#include <SDL.h>


namespace TurboHybrid {
	typedef std::wstring string;

	class System
	{
	public:
		void Init();
		void Shutdown();
		void ShowError(const TurboHybrid::string& message);
		void LogToErrorFile(const TurboHybrid::string& message);
	protected:
	private:
		HANDLE mhFile;

	};

}


