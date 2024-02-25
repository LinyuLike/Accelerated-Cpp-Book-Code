#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <cctype>

#include "grade.h"
#include "Student_info.h"
#include "use_std.h"


using std::cin;				using std::setprecision;
using std::cout;			using std::sort;
using std::domain_error;	using std::streamsize;
using std::endl;			using std::string;
using std::max;				using std::vector;
using std::isspace;			using std::ostream;
using std::map;				using std::istream;


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


// TODO move to another file later
void write_analysis(ostream& out, const string& name,
	double analysys(const vector<Student_info>&),
	const vector<Student_info>& did,
	const vector<Student_info>& didnt)
{
	out << name << ": median(did) = " << analysys(did) <<
		", median(didnt) = " << analysys(didnt) << endl;
}

/*
int main()
{
	// students who did and didn't do all their homework
	vector<Student_info> did, didnt;

	// read the student records and partition them
	Student_info student;
	while (read(cin, student)) {
		if (did_all_hw(student))
			did.push_back(student);
		else
			didnt.push_back(student);
	}

	// verify that the analysys will show us something
	if (did.empty()) {
		cout << "No student did all the homework!" << endl;
		return 1;
	}
	if (didnt.empty()) {
		cout << "Every student did all the homework!" << endl;
		return 1;
	}

	// do the analysys
	write_analysis(cout, "median", median_analysis, did, didnt);
	write_analysis(cout, "average", average_analysis, did, didnt);
	write_analysis(cout, "median if honework turned in",
		optimistic_median_analysis, did, didnt);
	return 0;
}
*/