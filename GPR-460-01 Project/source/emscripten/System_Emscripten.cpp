#include "headers/System_Emscripten.h"
#ifdef __EMSCRIPTEN__

TurboHybrid::System* TurboHybrid::System::Create() {
	return new TurboHybrid::System_Emscripten();
}


void TurboHybrid::System_Emscripten::Init()
{
}

void TurboHybrid::System_Emscripten::Shutdown()
{
}

void TurboHybrid::System_Emscripten::ShowError(const TurboHybrid::string& message)
{
	emscripten_run_script(((TurboHybrid::string)"alert('" + message.c_str() + "')").c_str());

}

void TurboHybrid::System_Emscripten::LogToErrorFile(const TurboHybrid::string& message)
{
	emscripten_run_script(((TurboHybrid::string)"console.error('" + message.c_str() + "')").c_str());
}
#endif // __EMSCRIPTEN__