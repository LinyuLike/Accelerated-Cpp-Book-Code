#include "Str.h"

#include <ctype.h>

std::ostream& operator<< (std::ostream& os, const Str& s)
{
	for (Str::size_type i = 0; i != s.size(); ++i)
		os << s[i];
	return os;
}

std::istream& operator>> (std::istream& is, Str& s)
{
	s.data->clear();	// Error data is private

	char c;
	while (is.get(c) && std::isspace(c))
		;

	if (is)
	{
		do s.data->push_back(c);
		while (is.get(c) && !std::isspace(c));

		// if we read whitespace, then put it back on the stream
		if (is)
			is.unget();
	}
	return is;
}

Str operator+(const Str& s, const Str& t)
{
	Str r = s;
	r += t;
	return r;
}