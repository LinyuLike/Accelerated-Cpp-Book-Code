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
	vector<Core*> students;
	Core* record;
	char ch;
	string::size_type maxlen = 0;

	// read and store data
	while (cin >> ch)
	{
		if (ch == 'U')
			record = new Core;
		else
			record = new Grad;
		record->read(cin);
		maxlen = max(maxlen, record->name().size());
		students.push_back(record);
	}

	// pass the version of compare that works on pointers
	sort(students.begin(), students.end(), compare_Core_ptrs);

	// write the name and grades
	for (vector<Core*>::size_type i = 0;
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
		delet students[i];
	}
	return 0;
}
