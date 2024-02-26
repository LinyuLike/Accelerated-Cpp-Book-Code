#include "sentence.h"
#include "use_std.h"
#include <iostream>

using std::istream;
using std::string;
using std::vector;
using std::map;
using std::cin;
using std::cout;
using std::endl;


// read a grammar from a given input stream
Grammar read_grammar(std::istream& in)
{
	Grammar ret;
	string line;

	// read the input
	while (getline(in, line))
	{
		// split the input into words
		vector<string> entry = split(line);

		if (!entry.empty())
			// use the category to store the associated rule
			ret[entry[0]].push_back(
				Rule(entry.begin() + 1, entry.end()));
	}
	return ret;
}

bool bracketed(const string& s)
{
	return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

// return a random interger in the range [0, n)
int nrand(int n)
{
	if (n <= 0 || n > RAND_MAX)
		throw std::domain_error("Argument to nrand is out of range");

	const int bucket_size = RAND_MAX / n;
	int r;
	do r = rand() / bucket_size;
	while (r >= n);

	return r;
}

void
gen_aux(const Grammar& g, const string& word, vector<string>& ret)
{
	if (!bracketed(word)) {
		ret.push_back(word);
	}
	else {
		// locate the rule that corresponds to word
		Grammar::const_iterator it = g.find(word);
		if (it == g.end())
			throw std::logic_error("empty rule");

		// fetch the set of possible rules
		const Rule_collection& c = it->second;

		// from which we selected one at random
		const Rule& r = c[nrand(c.size())];

		// recursively expand the selected rule
		for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
			gen_aux(g, *i, ret);
	}
}

vector<string> gen_sentence(const Grammar& g)
{
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}

// 7.4 make sentence
int gen_sentence_main()
{
	// generate the sentence
	vector<string> sentence = gen_sentence(read_grammar(cin));

	// write the first word, if any
	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty())
	{
		cout << *it;
		++it;
	}

	// write the rest of the words, each preceded by a space
	while (it != sentence.end())
	{
		cout << " " << *it;
		++it;
	}

	cout << endl;
	return 0;
}



// chapter 7.2
int count()
{
	string s;
	map<string, int> counters;

	while (cin >> s)
		++counters[s];

	for (map<string, int>::const_iterator it = counters.begin();
		it != counters.end(); ++it)
	{
		cout << it->first << "\t" << it->second << endl;
	}
	return 0;
}

/*
// chapter 7.3
int main()
{
	// call xref using split by default
	map<string, vector<int> > ret = xref(cin);

	// write the results
	for (map<string, vector<int> >::const_iterator it = ret.begin();
		it != ret.end(); ++it)
	{
		// write the word
		cout << it->first << " occurs on line(s): ";

		// followed by one or more line numbers
		vector<int>::const_iterator line_it = it->second.begin();
		cout << *line_it; // write the first line number

		++line_it;
		// write the rest of the line numbers, if any
		while (line_it!=it->second.end())
		{
			cout << ", " << *line_it;
			++line_it;
		}
		// write a new line to separate each word from the next
		cout << endl;
	}
	return 0;
}
*/