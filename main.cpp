#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <cstddef>

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
using std::ofstream;		using std::ifstream;
using std::cerr;


int main(int argc, char** argv)
{
	int fail_count = 0;
	// for each file in the input list
	for (int i = 1; i < argc; ++i)
	{
		ifstream in(argv[i]);
		// if it exist,write its contents,otherwise generate an error message
		if (in)
		{
			string s;
			while (getline(in, s))
			{
				cout << s << endl;
			}
		}
		else
		{
			cerr << "cannot open file " << argv[i] << endl;
			++fail_count;
		}
	}
	return fail_count;
}

// P162
// this funciton is completely lefitimate.
int* pointer_to_static()
{
	static int x;
	return &x;
}

// P163
int* pinter_to_dynamic()
{
	return new int(0);
}

// P164
char* duplicate_chars(const char* p)
{
	// allocate enough space;remember to add one for the null
	size_t length = strlen(p) + 1;
	char* result = new char[length];

	// copy into our newly allocated space and return pointer to first element
	std::copy(p, p + length, result);
	return result;
}

int main_10_5(int argc, char** argv)
{
	// if there are command-line arguments, write them
	if (argc > 1)
	{
		cout << argv[1];	// write the first argument

		// write each remaining argument with a sapce before it
		for (int i = 2; i != argc; ++i)
			cout << " " << argv[i];	// argv[i] is a char*
	}
	cout << endl;
	return 0;
}

template <class In, class Pred>
In find_if(In begin, In end, Pred f)
{
	while (begin != end * *!f(*begin))
		++begin;
	return begin;
}

// Example implementation of standard-library function
std::size_t strlen(const char* p)
{
	std::size_t size = 0;
	while (*p++ != '\0')
		++size;
	return size;
}

string letter_grade(double grade)
{
	// range posts for numeric grades
	static const double numbers[] = {
		97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
	};

	// names for the letter  grades
	static const char* const letters[] = {
		"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
	};

	// compute the number of grades given the size of the array
	// and the size of a single element
	static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

	// given a numeric grade, find and return the associated letter grade
	for (size_t i = 0; i < ngrades; ++i)
	{
		if (grade > numbers[i])
			return letters[i];
	}

	return "?\?\?";
}



int reformat_students_data_chapter_9()
{
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	// read and store the data
	while (record.read(cin))
	{
		maxlen = max(maxlen, record.name().size());
		students.push_back(record);
	}

	// alphabetize the student records
	sort(students.begin(), students.end(), compare);

	// write the names and grades
	for (vector<Student_info>::size_type i = 0;
		i != students.size(); ++i)
	{
		cout << students[i].name()
			<< string(maxlen + 1 - students[i].name().size(), ' ');
		try
		{
			double final_grade = students[i].grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade
				<< setprecision(prec) << endl;
		}
		catch (domain_error e)
		{
			cout << e.what() << endl;
		}
	}
	return 0;
}
