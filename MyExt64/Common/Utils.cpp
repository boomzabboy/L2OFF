
#include <Common/Utils.h>
#include <algorithm>

HANDLE server = NULL;

extern BOOL(*WriteProcessMemoryCopy)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*);

void WriteMemoryBYTES(unsigned int address, void *bytes, unsigned int len)
{
	DWORD flOldProtect;
	SIZE_T uNumberOfBytesWritten;
	HANDLE handle;
	
	if ((handle = server) && len) {
		VirtualProtectEx(handle, (LPVOID)address, len, PAGE_WRITECOPY, &flOldProtect);
		WriteProcessMemoryCopy(handle, (LPVOID)address, bytes, len, &uNumberOfBytesWritten);
		FlushInstructionCache(handle, (LPVOID)address, len);
		VirtualProtectEx(handle, (LPVOID)address, len, flOldProtect, &flOldProtect);
	}
}

void ReadMemoryBYTES(unsigned int address, void *bytes, unsigned int len)
{
	DWORD flOldProtect;
	SIZE_T uNumberOfBytesRead;
	HANDLE handle;
	
	if ((handle = server) && len) {
		VirtualProtectEx(handle, (LPVOID)address, len, PAGE_WRITECOPY, &flOldProtect);
		ReadProcessMemory(handle, (LPVOID)address, bytes, len, &uNumberOfBytesRead);
		FlushInstructionCache(handle, (LPVOID)address, len);
		VirtualProtectEx(handle, (LPVOID)address, len, flOldProtect, &flOldProtect);
	}
}

void WriteMemoryQWORD(unsigned int address, unsigned __int64 value)
{
    WriteMemoryBYTES(address, &value, sizeof(unsigned __int64));
}

void WriteMemoryDWORD(unsigned int address, unsigned int value)
{
    WriteMemoryBYTES(address, &value, sizeof(unsigned int));
}

void WriteMemoryWORD(unsigned int address, unsigned short value)
{
    WriteMemoryBYTES(address, &value, sizeof(unsigned short));
}

void WriteMemoryBYTE(unsigned int address, unsigned char value)
{
    WriteMemoryBYTES(address, &value, sizeof(unsigned char));
}

unsigned __int64 ReadMemoryQWORD(unsigned int address)
{
    unsigned __int64 value;
    ReadMemoryBYTES(address, &value, sizeof(unsigned __int64));
    return value;
}

unsigned int ReadMemoryDWORD(unsigned int address)
{
    unsigned int value;
    ReadMemoryBYTES(address, &value, sizeof(unsigned int));
    return value;
}

unsigned short ReadMemoryWORD(unsigned int address)
{
    unsigned short value;
    ReadMemoryBYTES(address, &value, sizeof(unsigned short));
    return value;
}

unsigned char ReadMemoryBYTE(unsigned int address)
{
    unsigned char value;
    ReadMemoryBYTES(address, &value, sizeof(unsigned char));
    return value;
}

void NOPMemory(unsigned int address, unsigned int len)
{
	unsigned int dword_count = (len / 4), byte_count = (len % 4);
	unsigned char Byte = 0x90; 
	unsigned int Dword = 0x90666666;

	DWORD flOldProtect;
	SIZE_T uNumberOfBytesWritten;
	HANDLE handle;

	if ((handle = server) && len) {
		VirtualProtectEx(handle, (LPVOID)address, len, PAGE_WRITECOPY, &flOldProtect);
		while (dword_count) {
			WriteProcessMemoryCopy(handle, (LPVOID)address, &Dword, sizeof(unsigned int), &uNumberOfBytesWritten);
			address += sizeof(unsigned int);
			dword_count--;
		}
		while(byte_count) {
			WriteProcessMemoryCopy(handle, (LPVOID)address, &Byte, sizeof(unsigned char), &uNumberOfBytesWritten);
			address += sizeof(unsigned char);
			byte_count--;
		}
		FlushInstructionCache(handle, (LPVOID)address, len);
		VirtualProtectEx(handle, (LPVOID)address, len, flOldProtect, &flOldProtect);
	}
}

void NULLMemory(unsigned int address, unsigned int len)
{
	unsigned int dword_count = (len / 4), byte_count = (len % 4);
	unsigned char Byte = 0x00; 
	unsigned int Dword = 0x00000000;

	DWORD flOldProtect;
	SIZE_T uNumberOfBytesWritten;
	HANDLE handle;

	if((handle = server) && len) {
		VirtualProtectEx(handle, (LPVOID)address, len, PAGE_WRITECOPY, &flOldProtect);
		while(dword_count) {
			WriteProcessMemoryCopy(handle, (LPVOID)address, &Dword, sizeof(unsigned int), &uNumberOfBytesWritten);
			address += sizeof(unsigned int);
			dword_count--;
		}
		while(byte_count) {
			WriteProcessMemoryCopy(handle, (LPVOID)address, &Byte, sizeof(unsigned char), &uNumberOfBytesWritten);
			address += sizeof(unsigned char);
			byte_count--;
		}
		FlushInstructionCache(handle, (LPVOID)address, len);
		VirtualProtectEx(handle, (LPVOID)address, len, flOldProtect, &flOldProtect);
	}
}

void WriteInstruction(unsigned int address, unsigned int uDestination, unsigned char uFirstByte)
{
	unsigned char execLine[5];
	execLine[0] = uFirstByte;
	*((int*)(execLine + 1)) = (((int)uDestination) - (((int)address) + 5));
	WriteMemoryBYTES(address, execLine, 5);
}

void WriteInstructionCallJmpEax(unsigned int address, unsigned int uDestination, unsigned int uNopEnd)
{
	unsigned char execLine[7];
	execLine[0] = 0xE8;
	*((int*)(execLine + 1)) = (((int)uDestination) - (((int)address) + 5));
	*((unsigned short*)(execLine + 5)) = 0xE0FF;
	WriteMemoryBYTES(address, execLine, 7);
	if(uNopEnd && uNopEnd > (address + 7))
		NOPMemory((address + 7), (uNopEnd - (address + 7)));
}

void WriteInstructionCall(unsigned int address, unsigned int uDestination, unsigned int uNopEnd)
{
	unsigned char execLine[5];
	execLine[0] = 0xE8;
	*((int*)(execLine + 1)) = (((int)uDestination) - (((int)address) + 5));
	WriteMemoryBYTES(address, execLine, 5);
	if(uNopEnd && uNopEnd > (address + 5))
		NOPMemory((address + 5), (uNopEnd - (address + 5)));
}

void WriteInstructionJmp(unsigned int address, unsigned int uDestination, unsigned int uNopEnd)
{
	unsigned char execLine[5];
	execLine[0] = 0xE9;
	*((int*)(execLine + 1)) = (((int)uDestination) - (((int)address) + 5));
	WriteMemoryBYTES(address, execLine, 5);
	if(uNopEnd && uNopEnd > (address + 5))
		NOPMemory((address + 5), (uNopEnd - (address + 5)));
}

bool ReplaceString(unsigned int address, const wchar_t *from, const wchar_t *to)
{
    int fromLen = (int) wcslen(from);
    int delta = fromLen - (int) wcslen(to);
    if (delta < 0) {
        return false;
    }
    const wchar_t *pos = wcsstr((const wchar_t*) address, from);
    if (!pos) {
        return false;
    }
    for (int i = 0 ; pos[delta] ; ++pos, ++i) {
        WriteMemoryWORD((UINT32)pos, i < fromLen - delta ? to[i] : pos[delta]);
    }
    WriteMemoryWORD((UINT32)pos, 0);
    return true;
}

void WriteAddress(unsigned int uAddress, UINT32 absAddr)
{
	WriteMemoryDWORD(uAddress, absAddr - (uAddress + 4));
}

Assemble_t Assemble = reinterpret_cast<Assemble_t>(0x68F99C);
Disassemble_t Disassemble = reinterpret_cast<Disassemble_t>(0x68ED10);

std::basic_string<wchar_t> Widen(const std::string &s)
{
	std::wstring result;
	std::copy(s.begin(), s.end(), std::back_inserter(result));
	return result;
}

size_t Guard::off1 = 0;
size_t Guard::off2 = 0;
size_t Guard::off3 = 0;

