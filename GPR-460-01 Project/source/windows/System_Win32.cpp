#include "Headers/System_Win32.h"

TurboHybrid::System* TurboHybrid::System::Create() {
	return new TurboHybrid::System_Win32();
}

void TurboHybrid::System_Win32::Init()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	_CrtMemCheckpoint(&memState);

	if (!AllocConsole()) {
		ShowError(L"Failed to alloc console");
	}

	freopen("CONOUT$", "w", stdout);

	mhFile = CreateFileW(L"GameErrors.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!mhFile) {
		ShowError(L"Failed to open log File");
	}
}

void TurboHybrid::System_Win32::Shutdown()
{
	_CrtMemDumpAllObjectsSince(&memState);
	CloseHandle(mhFile);
}

void TurboHybrid::System_Win32::ShowError(const TurboHybrid::string& message)
{
	MessageBox(NULL, message.c_str(), L"Warning", MB_OK | MB_ICONWARNING);
}

void TurboHybrid::System_Win32::LogToErrorFile(const TurboHybrid::string& message)
{
	string logMessage = L"[Date:Time] " + message;
	WriteFile(mhFile, logMessage.c_str() , logMessage.size() * sizeof(string::value_type), NULL, NULL);
}






