#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Grad.h"
#include "Handle.h"

class Student_info {
public:
	// constructors and copy control
	Student_info(){}
	Student_info(std::istream& is) { read(is); }
	// no copy,assign,or destructor:they're no longer needed

	// operations
	std::istream& read(std::istream&);

	std::string name() const {
		if (cp) return cp->name();
		else throw std::runtime_error("uninitialized Student");
	}
	double grade() const {
		if (cp) return cp->grade();
		else throw std::runtime_error("uninitialized Student");
	}
	static bool compare(const Student_info& s1,
		const Student_info& s2) {
		return s1.name() < s2.name();
	}

private:
	Handle<Core> cp;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);
std::list<Student_info> extract_fails(std::list<Student_info>&);

bool did_all_hw(const Student_info&);
