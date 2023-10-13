#pragma once

#ifndef ENTRY
#define ENTRY

#include "includes.hpp"

//#include "backend/game/world/entity.hpp"
//#include "backend/game/world/overlay/overlay.hpp"
//#include "backend/game/world/overlay/render.hpp"
//#include "backend/game/world/sdk/worldtoscreen.hpp"

auto Cinit() -> void
{
	for (;;)
	{
		entity->cache();
		std::this_thread::sleep_for(std::chrono::milliseconds(11));
	}
}

DWORD GetProcessId(LPCWSTR processName)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	DWORD procID = NULL;

	if (handle == INVALID_HANDLE_VALUE)
		return procID;

	PROCESSENTRY32W entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32W);

	if (Process32FirstW(handle, &entry)) {
		if (!_wcsicmp(processName, entry.szExeFile)) {
			procID = entry.th32ProcessID;
		}
		else while (Process32NextW(handle, &entry)) {
			if (!_wcsicmp(processName, entry.szExeFile)) {
				procID = entry.th32ProcessID;
			}
		}
	}

	CloseHandle(handle);
	return procID;
}

auto main() -> int
{

	globals->width = GetSystemMetrics(SM_CYSCREEN);
	globals->height = GetSystemMetrics(SM_CXSCREEN);

	if (!render->hijack())
	{
		if (globals->developermode)
		{
			MessageBoxA(0, _("overlay failure"), _(" "), MB_OK);
			exit(0);
		}
		else
		{
			MessageBoxA(0, _("{!} Cheat failed"), _(""), MB_ICONINFORMATION);
			exit(0);
		}
	}

	render->initiate();
	render->draw();

	std::thread([&]() { for (;;) { Cinit(); } }).detach();

	system(_("pause"));
}

#endif