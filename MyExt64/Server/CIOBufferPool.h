
#pragma once

#include <Server/CIOBuffer.h>
#include <Common/CriticalSection.h>
#include <Common/Utils.h>

template<size_t size>
class CIOBufferPool {
public:
	static CriticalSection cs[32];
	static CIOBufferPool<size> **pools;

	static void Init()
	{
		if (size == 16384) {
			NOPMemory(0x41B2B2, 14);
			NOPMemory(0x418F86, 6);
			WriteInstructionCall(0x41D75A, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x508D45, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x5094A0, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x50A2BD, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x5D16ED, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x6BB687, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x7C0CFC, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x859274, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x8592B1, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x859509, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x859546, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x8599C1, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x8A90DE, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x41D7AD, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x421DC1, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x422841, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x44EB82, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x4C7613, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x5091B4, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x509290, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x5092F2, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x5094FB, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x509777, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x5097F2, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x509981, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x509A18, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x509D4A, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x5414EC, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x541B54, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x5421CE, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x6115CB, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x72060A, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x7F2E20, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x858CEC, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x858D57, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x858F00, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x858F99, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x85922E, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x859449, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x8595CD, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x85960E, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x859A1B, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x859A52, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x8A9131, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x8AEB62, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x8AEE2D, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x8CAE5F, reinterpret_cast<UINT32>(Release));
			pools = reinterpret_cast<CIOBufferPool<size>**>(0x2308DC0);
		} else if (size == 8192) {
			NOPMemory(0x4567B2, 14);
			NOPMemory(0x4564CA, 6);
			WriteInstructionCall(0x456BF5, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x45735C, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x458291, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x651405, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x7EB235, reinterpret_cast<UINT32>(Allocate));
			WriteInstructionCall(0x457070, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x45714C, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x4571AE, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x4573B7, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x457633, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x4576AE, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x45783D, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x4578D4, reinterpret_cast<UINT32>(Release));
			WriteInstructionCall(0x457C06, reinterpret_cast<UINT32>(Release));
			pools = reinterpret_cast<CIOBufferPool<size>**>(0x2308E50);
		} else {
			exit(1);
		}
	}

	static CIOBuffer<size>* Allocate()
	{
		GUARDED;

		CIOBuffer<size>*(*allocate)() = 0;
		CIOBuffer<size> *ret = 0;

		if (size == 16384) {
			allocate = reinterpret_cast<CIOBuffer<size>*(*)()>(0x41CDB8);
		} else if (size == 8192) {
			allocate = reinterpret_cast<CIOBuffer<size>*(*)()>(0x45691C);
		}

		UINT32 threadIndex = GetThreadIndex();
		CIOBufferPool *pool = pools[threadIndex];
		ScopedLock lock(cs[threadIndex]);
		pool->semaphore = 1;
		ret = allocate();
		pool->semaphore = 0;
		return ret;
	}

	static void Release(CIOBufferPool<size> *pool, CIOBuffer<size> *buffer)
	{
		GUARDED;

		void(*release)(CIOBufferPool<size>*, CIOBuffer<size>*) = 0;

		if (size == 16384) {
			release = reinterpret_cast<void(*)(CIOBufferPool<size>*, CIOBuffer<size>*)>(0x41B2A0);
		} else if (size == 8192) {
			release = reinterpret_cast<void(*)(CIOBufferPool<size>*, CIOBuffer<size>*)>(0x4567A0);
		}

		UINT32 threadIndex = buffer->threadIndex;
		ScopedLock lock(cs[threadIndex]);
		pool->semaphore = 1;
		release(pool, buffer);
		pool->semaphore = 0;
	}

	/* 0x0000 */ UINT32 semaphore;
	/* 0x0004 */ unsigned char padding0x0004[0x0024];
};

template<size_t size>
CriticalSection CIOBufferPool<size>::cs[32];

template<size_t size>
CIOBufferPool<size> **CIOBufferPool<size>::pools;

