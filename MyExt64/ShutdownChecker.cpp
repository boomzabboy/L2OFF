
#include "ShutdownChecker.h"
#include <fstream>
#include <string>

void ShutdownChecker::Init()
{
	std::ofstream ofs("status.txt");
	if (ofs) {
		ofs << "starting" << std::endl;
		ofs.close();
	}
}

void ShutdownChecker::StartChecking()
{
	std::ofstream ofs("status.txt");
	if (ofs) {
		ofs << "running" << std::endl;
		ofs.close();
	}

	CreateThread(0, 0, CheckForShutdown, 0, 0, 0);
}

DWORD ShutdownChecker::CheckForShutdown(void *v)
{
	(void) v;

	for (;;) {
		Sleep(1000);
		std::ifstream ifs("status.txt");
		if (ifs) {
			std::string status;
			ifs >> status;
			ifs.close();
			if (status == "shutdown") {
				reinterpret_cast<void(*)(HWND, UINT, WPARAM, LPARAM)>(0x6AF4B4)(
					GetActiveWindow(), 0x111, 0x97, 0x0);
				std::ofstream ofs("status.txt");
				if (ofs) {
					ofs << "shutdown_in_progress" << std::endl;
					ofs.close();
				}
				break;
			}
		}
	}
	return 0;
}

