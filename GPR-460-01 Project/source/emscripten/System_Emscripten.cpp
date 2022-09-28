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
	emscripten_run_script("alert(message)");

}

void TurboHybrid::System_Emscripten::LogToErrorFile(const TurboHybrid::string& message)
{
	emscripten_run_script("console.log(message)");
}
#endif // __EMSCRIPTEN__