
#pragma once

#include <windows.h>

template<class T>
class xvector {
public:
	xvector()
		: reserved_(0), begin_(0), end_(0), reservedEnd_(0)
	{
	}

	~xvector()
	{
	}

	typedef T* iterator;
	typedef T const * const_iterator;

	iterator begin()
	{
		return begin_;
	}

	const_iterator begin() const
	{
		return begin_;
	}

	iterator end()
	{
		return end_;
	}

	const_iterator end() const
	{
		return end_;
	}

	bool empty() const
	{
		return begin_ == end_;
	}

	size_t size() const
	{
		return end_ - begin_;
	}

	operator std::vector<T>()
	{
		return std::vector<T>(begin(), end());
	}

protected:
	void *reserved_;
	T *begin_;
	T *end_;
	T *reservedEnd_;
};

