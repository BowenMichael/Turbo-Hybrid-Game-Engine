#pragma once

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include <string>
#include <SDL.h>
#include <bgfx/include/bgfx/platform.h>
#include "bgfx/include/bgfx/bgfx.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#include <Windows.h>

#endif





namespace TurboHybrid {
#ifdef __EMSCRIPTEN__
	typedef std::string string;
#else
	typedef std::wstring string;
#endif


	class System
	{
	public:
		virtual ~System() {};
		virtual void Init() = 0;
		virtual void Shutdown() = 0;
		virtual void ShowError(const TurboHybrid::string& message) = 0;
		virtual void LogToErrorFile(const TurboHybrid::string& message) = 0;
		static System* Create();
	};

}