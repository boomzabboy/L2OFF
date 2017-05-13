
#include <Server/CTrade.h>
#include <Common/Utils.h>
#include <Common/CLog.h>
#include <Common/CYieldLock.h>

void CTrade::Init()
{
	WriteMemoryBYTES(0x87944D, "\x48\x89\xE1", 3); // mov rcx, rsp
	WriteInstructionCall(0x879450, reinterpret_cast<UINT32>(PressDoneHelper));
}

void CTrade::PressDoneHelper(void *rsp, int type, const wchar_t *format, ...)
{
	GUARDED;

	va_list va;
	va_start(va, format);
	CLog::AddV(type, format, va);
	va_end(va);

	// lock ptr is at rsp + 0xF0
	CYieldLock *lock = *reinterpret_cast<CYieldLock**>(&reinterpret_cast<char*>(rsp)[0xf0]);
	lock->Leave(__FILEW__, __LINE__);
}

