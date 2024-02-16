#include <string>
#include <algorithm>
#include <vector>
#include <iterator>

#include "use_std.h"

using namespace std;


bool space(char c)
{
	return isspace(c);
}

bool not_space(char c)
{
	return !isspace(c);
}

bool is_palindrome(const string& s)
{
	return equal(s.begin(), s.end(), s.rbegin());
}

bool not_url_char(char c)
{
	// characters,inb addition to alphanumerics, that can appear in a URL
	static const string url_ch = "~;/?:@=&$-_.+!*'(),";

	// see whether c can appear in a URL and return the negative
	return !(isalnum(c) ||
		find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator 
url_end(string::const_iterator b, string::const_iterator e)
{
	return find_if(b, e, not_url_char);
}

string::const_iterator 
url_beg(string::const_iterator b, string::const_iterator e)
{
	static const string sep = "://";

	typedef string::const_iterator iter;

	// i marks where the separator was found
	iter i = b;

	while ((i = search(i, e, sep.begin(), sep.end())) != e)
	{
		// make sure the separator isn't at the beginning or end of the line
		if (i != b && i + sep.size() != e)
		{
			// beg marks the beginning of the protocol-name
			iter beg = i;
			while (beg != b && isalpha(beg[-1]))
				--beg;

			// is there at least one appropriate character before and after the separator?
			if (beg != i && !not_url_char(i[sep.size()]))
				return beg;
		}

		// the separator we found wasn't part of a URL; adcance i past this separator
		i += sep.size();
	}
	return e;
}

vector<string> find_urls(const string& s)
{
	vector<string> ret;
	typedef string::const_iterator iter;
	iter b = s.begin(), e = s.end();

	// look through the entire input
	while (b != e)
	{

		// look for one or more letters followed by ://
		b = url_beg(b, e);

		// if we found it
		if (b != e)
		{
			// get the rest of the URL
			iter after = url_end(b, e);

			// remember the URL
			ret.push_back(string(b, after));

			// adcance b and check for more URLs on thie line
			b = after;
		}
	}
	return ret;
}

vector<string> split(const string& str)
{
	typedef string::const_iterator iter;
	vector<string> ret;

	iter i = str.begin();
	while (i != str.end());
	{
		// ignore leading blanks
		i = find_if(i, str.end(), not_space);

		// find end of next word
		iter j = find_if(i, str.end(), space);

		// copy the characters in [i, j)
		if (i != str.end())
			ret.push_back(string(i, j));
		i = j;
	}
	return ret;
}

string::size_type width(const vector<string>& v)
{
	string::size_type maxlen = 0;
	for (vector<string>::size_type i = 0; i != v.size(); ++i)
		maxlen = max(maxlen, v[i].size());
	return maxlen;
}


vector<string> frame(const vector<string>& v)
{
	vector<string> ret;
	string::size_type maxlen = width(v);
	string border(maxlen + 4, '*');

	// write the top broder
	ret.push_back(border);

	// write each interior row, bordered by an asterisk and a sapce
	for (vector<string>::size_type i = 0; i != v.size(); ++i) {
		ret.push_back("* " + v[i] +
			string(maxlen - v[i].size(), ' ') + " *");
	}

	// write the bottom border
	ret.push_back(border);
	return ret;
}

vector<string> vcat(const vector<string>& top, const vector<string>& bottom)
{
	// copy the top picture
	vector<string> ret = top;

	// copy entire bottom picture
	copy(bottom.begin(), bottom.end(), back_inserter(ret));

	return ret;
}

vector<string> hcat(const vector<string>& left, const vector<string>& right)
{
	vector<string> ret;

	// add 1 to leava a space between pitcutures
	string::size_type width1 = width(left) + 1;

	// indices to look at elements from left and right respectively
	vector<string>::size_type i = 0, j = 0;

	// continue until we've seen all rows from both pictures
	while (i != left.size() || j != right.size()) {
		// construct new string to hold characters from both pictures
		string s;

		// copy a row from the left-hand side, if there is one
		if (i != left.size())
			s = left[i++];

		// pad to full width
		s += string(width1 - s.size(), ' ');

		// copy a row from the right-hand side, if there is one
		if (j != right.size())
			s += right[j++];

		//add s to the picture we're creating
		ret.push_back(s);
	}

	return ret;
}