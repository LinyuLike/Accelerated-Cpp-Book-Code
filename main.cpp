#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
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

int main()
{
	int x = 5;

	// p points to x
	int* p = &x;
	cout << "x = " << x << endl;

	// change the value of x through p
	*p = 6;
	cout << "x = " << x << endl;
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
