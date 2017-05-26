
#pragma once

#include <windows.h>

class NPCd {
public:
    static void Init();

protected:
	static void DisableSendMail();
	static void HookStart();
	static void ChangePaths();
	
public:
	static void Send(const char *format, ...);
	static void SendV(const char *format, va_list va);

protected:
	static HWND __cdecl CreateWindowEx(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
	static void __cdecl StartHook(void *logger, int level, const char *fmt);

public:
	enum PacketEx {
		WHISPER = 1
	};
};

