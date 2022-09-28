#include "../../headers/System_Common.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>

#include <SDL.h>

namespace TurboHybrid {
	const string ERROR_K = "Do not press K!!!\n";
	const string LOG_ERROR_K = "Error: User pressed 'k'\n";

	class System_Emscripten : public System
	{
	public:
		~System_Emscripten() {};
		void Init() override;
		void Shutdown() override;
		void ShowError(const TurboHybrid::string& message) override;
		void LogToErrorFile(const TurboHybrid::string& message) override;


	};

}
#endif