#pragma once

#include <cstddef>
#include <stdexcept>

#include "Vec.h"

#include "template_func.h"




template <class T>
class Ptr
{
public:
	void make_unique();
	//{
	//	if (*refptr != 1)
	//	{
	//		--*refptr;
	//		refptr = new std::size_t(1);
	//		p = p ? p->clone() : 0;
	//	}
	//}

	Ptr() :p(0), refptr(new std::size_t(1)) {}
	Ptr(T* t) :p(t), refptr(new std::size_t(1)) {}
	Ptr(const Ptr& h) :p(h.p), refptr(h.refptr) { ++*refptr; }

	Ptr& operator=(const Ptr&);
	~Ptr();
	
	operator bool() const { return p; }
	T& operator*() const;
	T* operator->() const;

private:
	T* p;
	std::size_t* refptr;
};

template <class T>
void Ptr<T>::make_unique()
{
	if (*refptr != 1)
	{
		--*refptr;
		refptr = new std::size_t(1);
		p = p ? make_clone(p) : 0; // call the global(not member) version of clone
	}
}

template<class T>
inline Ptr<T>& Ptr<T>::operator=(const Ptr& rhs)
{
	if (&rhs != this)
	{
		--*refptr;
		if (*refptr == 0)
		{
			delete p;
			delete refptr;
		}
		p = rhs.p;
		refptr = rhs.refptr;
		refptr++;
	}
	return *this;
}

template<class T>
inline Ptr<T>::~Ptr()
{
	if (--*refptr == 0)
	{
		delete p;
		delete refptr;
	}
}

template<class T>
inline T& Ptr<T>::operator*() const
{
	if (p)
		return *p;
	throw std::runtime_error("unbound Ptr");
}

template<class T>
inline T* Ptr<T>::operator->() const
{
	if (p)
		return p;
	throw std::runtime_error("umbound Ptr");
}
