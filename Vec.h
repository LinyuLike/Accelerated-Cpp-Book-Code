#pragma once
#include <cstddef>
#include <memory>

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

