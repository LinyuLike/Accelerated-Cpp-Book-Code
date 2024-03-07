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
#include "Vec.h"
#include "Core.h"
#include "Grad.h"
#include "Handle.h"


using std::cin;				using std::setprecision;
using std::cout;			using std::sort;
using std::domain_error;	using std::streamsize;
using std::endl;			using std::string;
using std::max;				using std::vector;
using std::isspace;			using std::ostream;
using std::map;				using std::istream;
using std::ofstream;		using std::ifstream;
using std::cerr;

int main()
{
	vector<Handle<Core> > students;
	Handle<Core> record;
	char ch;
	string::size_type maxlen = 0;

	// read and store data
	while (cin >> ch)
	{
		// 1.Handle(T* t) make a template var
		// 2.operator= make a copy to record
		// 3.~Handle deconstruct the template var
		if (ch == 'U')
			record = new Core;
		else
			record = new Grad;

		record->read(cin);
		maxlen = max(maxlen, record->name().size());
		students.push_back(record);
	}

	// pass the version of compare that works on pointers
	sort(students.begin(), students.end(), compare_Core_handles);

	// write the name and grades
	for (vector<Student_info>::size_type i = 0;
		i != students.size(); ++i)
	{
		cout << students[i]->name()
			<< string(maxlen + 1 - students[i]->name().size(), ' ');
		try
		{
			double final_grade = students[i]->grade();
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
