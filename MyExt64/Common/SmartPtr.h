
#pragma once

#include <Common/CLog.h>
#include <windows.h>

template<class T>
class SmartPtr {
public:
	SmartPtr() :
		obj(0),
		type(0)
	{
	}

	__forceinline SmartPtr(T *obj, int type = 0) :
		obj(obj),
		type(type)
	{
		if (obj) {
			IncRef(__FILE__, __LINE__);
		}
	}

	__forceinline SmartPtr(const SmartPtr &other) :
		obj(other.obj),
		type(other.type)
	{
		if (obj) {
			IncRef(__FILE__, __LINE__);
		}
	}

	__forceinline ~SmartPtr()
	{
		if (obj) {
			DecRef(__FILE__, __LINE__);
		}
	}

	__forceinline SmartPtr& operator=(const SmartPtr &other)
	{
		if (obj) {
			DecRef(__FILE__, __LINE__);
		}
		obj = other.obj;
		type = other.type;
		if (obj) {
			IncRef(__FILE__, __LINE__);
		}
		return *this;
	}

	__forceinline SmartPtr& Reset(T *obj_, UINT32 type_)
	{
		if (obj) {
			DecRef(__FILE__, __LINE__);
		}
		obj = obj_;
		type = type_;
		if (obj) {
			IncRef(__FILE__, __LINE__);
		}
	}

	T* operator*()
	{
		return obj;
	}

	T* operator->()
	{
		return obj;
	}

	operator bool()
	{
		return obj;
	}

protected:
	void IncRef(const char *file, const int line)
	{
		reinterpret_cast<void(*)(T*, const char*, int, UINT32)>(
			(*reinterpret_cast<void***>(obj))[1])(obj, file, line, type);
	}

	void DecRef(const char *file, const int line)
	{
		reinterpret_cast<void(*)(T*, const char*, int, UINT32)>(
			(*reinterpret_cast<void***>(obj))[2])(obj, file, line, type);
	}

	T *obj;
	UINT32 type;
};

