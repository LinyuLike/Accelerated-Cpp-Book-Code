#pragma once

#include <cstddef>
#include <memory>
#include <algorithm>

#include "template_func.h"


template <class T> class Vec
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef T& reference;
	typedef const T& const_reference;

	Vec() { create(); }
	explicit Vec(size_type n, const T& val = T()) { create(n, val); }

	Vec(const Vec& v) { create(v.begin(), v.end()); }
	Vec& operator= (const Vec&);
	~Vec() { uncreate(); }

	T& operator[] (size_type i) { return data[i]; }
	const T& operator[] (size_type i) const { return data[i]; }

	void push_back(const T& val)
	{
		if (avail == limit)
			grow();
		unchecked_append(val);
	}

	size_type size() const { return avail - data; }

	iterator begin() { return data; }
	const_iterator begin() const { return data; }

	iterator end() { return avail; }
	const_iterator end() const { return avail; }

	void erase(iterator it);
	void clear();

private:
	iterator data;
	iterator avail;
	iterator limit;

	// facilities for memory allocation
	std::allocator<T> alloc;	// object to handle memory allocation

	// allocate and initialize the underlying array
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	// destroy the elements in the array and free the memory
	void uncreate();

	// support functions for push_back
	void grow();
	void unchecked_append(const T&);
};


// we need the inline mark, otherwise we'll get some redefined error
template <>
inline Vec<char>* make_clone(const Vec<char>* vp)
{
	return new Vec<char>(*vp);
};


// template function can't be defined in source file

// P176
template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
	// check for self-assignment
	if (&rhs != this)
	{
		// free the array in the left-hand side
		uncreate();

		// copy elements from the right-hand to the left-hand side
		create(rhs.begin(), ths.end());
	}
	return *this;
}

template <class T> void Vec<T>::create()
{
	data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
	data = alloc.allocate(n);
	limit = avail = data + n;
	std::uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
	data = alloc.allocate(j - i);
	limit = avail = std::uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate()
{
	if (data)
	{
		// destroy(in reverse order) this elements that were constructed
		iterator it = avail;
		while (it != data)
			alloc.destroy(--it);

		// return all the space that was allocated
		alloc.deallocate(data, limit - data);
	}
	// reset pointers to indicate that the Vec is empty again
	data = limit = avail = 0;
}

template <class T> void Vec<T>::grow()
{
	// when growing, allocate twice as much space as currently in use
	size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

	// allocate new space and copy existing elements to the new space
	iterator new_data = alloc.allocate(new_size);
	iterator new_avail = std::uninitialized_copy(data, avail, new_data);

	// return the old space
	uncreate();

	// reset pointers to point to the newly allocated space
	data = new_data;
	avail = new_avail;
	limit = data + new_size;
}

// assumes avail points at allocated,but uninitialized space
template <class T> void Vec<T>::unchecked_append(const T& val)
{
	alloc.construct(avail++, val);
}

template <class T> void Vec<T>::erase(iterator it)
{
	if ((it - data) <= (avail - data))
	{
		alloc.destroy(it);
		std::uninitialized_copy(it + 1, avail, it);
		alloc.destroy(avail - 1);
		--avail;
	}
}

template <class T> void Vec<T>::clear()
{
	if (data)
	{
		while (avail != data)
		{
			alloc.destroy(--avail);
		}
	}
}