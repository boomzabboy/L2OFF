
#pragma once

#include <windows.h>
#include <string>
#include <list>

class NPCFunctionPtr {
public:
	NPCFunctionPtr();

	/* 0x0000 */ void *functionPtr;
	/* 0x0008 */ INT32 unknown;
	/* 0x000C */ unsigned char padding0x000C[0x0010-0x000C];
};

class NPCFunction {
public:
	enum Type {
		TYPE_VOID = 1,
		TYPE_INT = 2,
		TYPE_FLOAT = 3,
		TYPE_STRING = 4,
		TYPE_CREATURE = 8,
		TYPE_PARTY = 11,
		TYPE_NPCMAKER = 13,
		TYPE_NPC = 14,
		TYPE_HATEINFO = 15,
		TYPE_GLOBALOBJECT = 16,
		TYPE_SPAWNDEFINE = 17,
		TYPE_CODEINFO = 18,
		TYPE_CODEINFOLIST = 19,
		TYPE_ATOMICVALUE = 21,
		TYPE_ROOMINFO = 22,
		TYPE_ROOMINFOLIST = 23,
		TYPE_POSITIONLIST = 25,
		TYPE_BUYSELLLIST = 30,
		TYPE_ITEMINDEXLIST = 31,
		TYPE_INTLIST = 32,
		TYPES_END
	};

	static void Init();
	static void AddFunctions();

	template<UINT32 address, Type type>
	static void RegisterFunctions(void *unknown, void *registry)
	{
		reinterpret_cast<void(*)(void*, void*)>(address)(unknown, registry);
		for (std::list<NPCFunction*>::iterator i = functionsToRegister[type].begin() ; i != functionsToRegister[type].end() ; ++i) {
			(*i)->Register(registry);
		}
	}

	template<Type type, class T>
	static void AddFunction()
	{
		functionsToRegister[type].push_back(new T());
	}

	NPCFunction(const wchar_t *name, void *functionPtr);
	virtual ~NPCFunction();
	virtual void* CallFn(void *caller, void **params);
	virtual void* Call(void *caller, void **params) = 0;
	virtual void SetTypes() = 0;
	void SetReturnType(Type type);
	void AddParameter(Type type);
	void Register(void *registry);

	static std::list<NPCFunction*> functionsToRegister[TYPES_END];

	unsigned char padding0x0008[0x0010-0x0008];
	std::wstring name;
	void *returnType;
	void *parameters;
	unsigned char padding0x0048[0x0060-0x0048];
	NPCFunctionPtr functionPtr;
};

