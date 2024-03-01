#include <list>
#include <algorithm>

#include "grade.h"
#include "Student_info.h"

using std::istream;
using std::vector;
using std::list;

Student_info::Student_info() :midterm(0), final(0) {}

Student_info::Student_info(istream& is) { read(is); }

istream& Student_info::read(istream& in)
{
	in >> n >> midterm >> final;
	read_hw(in, homework);
	return in;
}

double Student_info::grade() // const
{
	return ::grade(midterm, final, homework);
}

bool compare(const Student_info& x, const Student_info& y)
{
	return x.name() < y.name();
}

// read homework grades from an input stream into a vector<double>
istream& read_hw(istream& in, vector<double>& hw)
{
	if (in) {
		// get rid of previous contents
		hw.clear();

		// read homework grades
		double x;
		while (in >> x)
			hw.push_back(x);

		// clear the stream so that input will work for the next student
		in.clear();
	}
	return in;
}

//istream& read(istream& is, Student_info& s)
//{
//	// read and store the student's name and midterm and final exam grades
//	is >> s.name() >> s.midterm >> s.final;
//
//	read_hw(is, s.homework); // read and store all the student's homework grades
//	return is;
//}

list<Student_info> 
extract_fails(list<Student_info>& students)
{
	list<Student_info> fail;

	// copy all the students that didn't pass to fail
	remove_copy_if(students.begin(), students.end(),
		back_inserter(fail), pgrade);
	// move all the students that pass to the front,
	// then delete the records which didn't moved.
	students.erase(remove_if(students.begin(), students.end(),
		fgrade), students.end());
	return fail;
}

//bool did_all_hw(const Student_info& s)
//{
//	return((find(s.homework.begin(), s.homework.end(), 0))
//		== s.homework.end());
//}