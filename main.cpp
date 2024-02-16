#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cctype>
#include "grade.h"
#include "Student_info.h"
#include "use_std.h"


using std::cin;				using std::setprecision;
using std::cout;			using std::sort;
using std::domain_error;	using std::streamsize;
using std::endl;			using std::string;
using std::max;				using std::vector;
using std::isspace;


int main()
{
	string s;
	// read and split each line of input
	while (getline(cin, s)) {
		vector<string> v = split(s);

		// write each word in v 
		for (vector<string>::size_type i = 0; i != v.size(); ++i)
			cout << v[i] << endl;
	}
	return 0;
}

/*
int main()
{
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0; // the length of the longest name

	// read and store all the student's data.
	// Invariant:	students contains all the student records read so far
	//				maxlen contain the length of the longest name in students
	while (read(cin, record)) {
		// find length of longest name
		maxlen = max(maxlen, record.name.size());
		students.push_back(record);
	}

	// alphabetize the student records
	sort(students.begin(), students.end(), compare);

	// write the names and grades
	for (vector<Student_info>::size_type i = 0;
		i != students.size(); ++i) {

		// write the name,padded on the right to maxlen + 1 characters
		cout << students[i].name
			<< string(maxlen + 1 - students[i].name.size(), ' ');

		// compute and write the grade
		try {
			double final_grade = grade(students[i]);
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade
				<< setprecision(prec);
		}
		catch (domain_error e) {
			cout << e.what();
		}
		cout << endl;
	}
	return 0;
}
*/
