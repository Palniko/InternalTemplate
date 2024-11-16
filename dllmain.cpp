#pragma once
#include <Windows.h>
#include <thread>
#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace std;

DWORD WINAPI Initialize(LPVOID moduleInstance)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	BlackHat::GUI form;
	Application::Run(% form);
	FreeLibraryAndExitThread(static_cast<HMODULE>(moduleInstance), EXIT_SUCCESS);
}

#pragma managed(push, off)
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID previous)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);
		const auto thread = CreateThread(NULL,
			NULL,
			Initialize,
			instance,
			NULL,
			nullptr);

		if (thread)
			CloseHandle(thread);
	}

	return TRUE;
}
#pragma managed(pop)