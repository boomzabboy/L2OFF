
#pragma once

#include <windows.h>
#include <string>
#include <list>
#include <NPCd/Type.h>

class NPCFunctionPtr {
public:
	NPCFunctionPtr();

	/* 0x0000 */ void *functionPtr;
	/* 0x0008 */ INT32 unknown;
	/* 0x000C */ unsigned char padding0x000C[0x0010-0x000C];
};

class NPCFunction {
public:
	static void Init();
	static void AddFunctions();

	template<UINT32 address, Type::TypeID type>
	static void RegisterFunctions(void *unknown, void *registry)
	{
		reinterpret_cast<void(*)(void*, void*)>(address)(unknown, registry);
		for (std::list<NPCFunction*>::iterator i = functionsToRegister[type].begin() ; i != functionsToRegister[type].end() ; ++i) {
			(*i)->Register(registry);
		}
	}

	template<Type::TypeID type, class T>
	static void AddFunction()
	{
		functionsToRegister[type].push_back(new T());
	}

	NPCFunction(const wchar_t *name, void *functionPtr);
	virtual ~NPCFunction();
	virtual void* CallFn(void *caller, void **params);
	virtual void* Call(void *caller, void **params) = 0;
	virtual void SetTypes() = 0;
	void SetReturnType(Type::TypeID type);
	void AddParameter(Type::TypeID type);
	void Register(void *registry);

	static std::list<NPCFunction*> functionsToRegister[Type::TYPES_END];

	unsigned char padding0x0008[0x0010-0x0008];
	std::wstring name;
	void *returnType;
	void *parameters;
	unsigned char padding0x0048[0x0060-0x0048];
	NPCFunctionPtr functionPtr;
};

