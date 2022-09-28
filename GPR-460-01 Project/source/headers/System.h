#pragma once

#ifdef __EMSCRIPTEN__
#include "../emscripten/headers/System_Emscripten.h"
#else
#include "../windows/headers/System_Win32.h"
#endif