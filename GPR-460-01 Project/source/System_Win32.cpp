#include "../headers/System_Win32.h"


void TurboHybrid::System::Init()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	if (!AllocConsole()) {
		ShowError(L"Failed to alloc console");
	}

	freopen("CONOUT$", "w", stdout);

	mhFile = CreateFileW(L"GameErrors.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!mhFile) {
		ShowError(L"Failed to open log File");
	}
}

void TurboHybrid::System::Shutdown()
{
	CloseHandle(mhFile);
}

void TurboHybrid::System::ShowError(const TurboHybrid::string& message)
{
	LogToErrorFile(message);
	MessageBox(NULL, message.c_str(), L"Warning", MB_OK | MB_ICONWARNING);

}

void TurboHybrid::System::LogToErrorFile(const TurboHybrid::string& message)
{
	WriteFile(mhFile, message.c_str(), message.size(), NULL, NULL);
}
