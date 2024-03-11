#pragma once

#include "Ptr.h"

#include <algorithm>
#include <iterator>
#include <iostream>


class Str
{
	friend std::istream& operator>> (std::istream&, Str&);
public:
	Str& operator+=(const Str& s)
	{
		data.make_unique();
		std::copy(s.data->begin(), s.data->end(),
			std::back_inserter(*data));
		return *this;
	}

	typedef Vec<char>::size_type size_type;

	Str() :data(new Vec<char>) {}
	Str(const char* cp) :data(new Vec<char>)
	{
		std::copy(cp, cp + std::strlen(cp),
			std::back_inserter(*data));
	}

	Str(size_type n, char c) :data(new Vec<char>(n, c)) {}
	template <class In> Str(In i, In j) : data(new Vec<char>)
	{
		std::copy(i, j, std::back_inserter(*data));
	}

	// call make_unique is necessary
	char& operator[](size_type i) 
	{
		data.make_unique();
		return (*data)[i];
	}
	const char& operator[](size_type i) const { return (*data)[i]; }
	size_type size() const { return data->size(); }

private:
	Ptr< Vec<char> > data;
};


std::ostream& operator<<(std::ostream&, const Str&);
Str operator+(const Str&, const Str&);
