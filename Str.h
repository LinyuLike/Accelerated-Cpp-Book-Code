#pragma once

#include "Vec.h"

#include <algorithm>
#include <iterator>
#include <iostream>


class Str
{
	friend std::istream& operator>> (std::istream&, Str&);
public:
	typedef Vec<char>::size_type size_type;

	// Constructors
	Str() {}
	Str(size_type n, char c) : data(n, c) {}
	Str(const char* cp)
	{
		std::copy(cp, cp + strlen(cp), std::back_inserter(data));
	}
	template <class In> Str(In b, In e)
	{
		std::copy(b, e, std::back_inserter(data));
	}

	// Operators
	char& operator[](size_type i) { return data[i]; }
	const char& operator[](size_type i) const { return data[i]; }

	Str& operator+=(const Str& s)
	{
		std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
		return *this;
	}

	size_type size() const { return data.size(); }

private:
	Vec<char> data;
};


std::ostream& operator<<(std::ostream&, const Str&);

Str operator+(const Str&, const Str&);
