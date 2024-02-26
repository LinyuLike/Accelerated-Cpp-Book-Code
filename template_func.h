#pragma once

#include <string>
#include <vector>

template <class T>
T median(std::vector<T> v)
{
	typedef typename std::vector<T>::size_type vec_sz;

	vec_sz size = v.size();
	if (size == 0)
		throw domain_error("median of an empty std::vector");

	sort(v.begin(), v.end());

	vec_sz mid = size / 2;

	return size % 2 == 0 ? (v[mid] + v[mid - 1]) / 2 : v[mid];
}

template <class In, class X>
In find(In begin, In end, const X& x)
{
	while (begin != end && *begin != x)
		++begin;
	return begin;
}

template <class In, class Out>
Out copy(In begin, In end, Out dest)
{
	while (begin != end)
		*dest++ = *begin++;
	return dest;
}

template <class For, class X>
void replace(For beg, For end, const X& x, const X& y)
{
	while (beg != end)
	{
		if (*beg == x)
			*beg = y;
		++beg;
	}
}

template <class Bi>
void reverse(Bi begin, Bi end)
{
	while (begin != end)
	{
		--end;
		if (begin != end)
			swap(*begin++, *end);
	}
}

template <class Ran, class X>
bool binary_search(Ran begin, Ran end, const X& x)
{
	while (begin < end)
	{
		// find the midpoint of the range
		Ran mid = begin + (end - begin) / 2;
		// see which part of the range contains x;keep looking only in that part
		if (x < *mid)
			end = mid;
		else if (*mid < x)
			begin = mid + 1;
		// if we got here, then *mid == x so we're done
		else return true;
	}
	return false;
}

template <class Out>
void split(const std::string& str, Out os)
{
	typedef std::string::const_iterator iter;

	iter i = str.begin();
	while (i != str.end())
	{
		// ignore leading blanks
		i = find_if(i, str.end(), not_space);

		// find end of next word
		iter j = find_if(i, str, end(), space);

		// copy the characters in [i,j)
		if (i£¡ = str.end())
			*os++ = std::string(i, j);
		i = j;
	}
}