#include <list>
#include <algorithm>

#include "grade.h"
#include "Student_info.h"

using std::istream;
using std::vector;
using std::list;

istream& Student_info::read(istream& is)
{
	char ch;
	is >> ch;

	if (ch == 'U')
		cp = new Core(is);
	else
		cp = new Grad(is);
	return is;
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