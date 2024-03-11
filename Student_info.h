#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>

#include "Ptr.h"
#include "Grad.h"

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
	void regrade(double final, double thesis);

private:
	Ptr<Core> cp;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);
std::list<Student_info> extract_fails(std::list<Student_info>&);

bool did_all_hw(const Student_info&);


double grade(double, double, double);
double grade(double, double, std::vector<double>&);
double grade(const double, const double, const std::vector<double>&);
double grade(const Student_info&);

bool fgrade(const Student_info&);
bool pgrade(const Student_info&);

double grade_aux(const Student_info& s);

double median_analysis(const std::vector<Student_info>& students);

double average(const std::vector<double>& v);
double average_grade(const Student_info& s);
double average_analysis(const std::vector<Student_info>& students);

double optimistic_median(const Student_info& s);
double optimistic_median_analysis(const std::vector<Student_info>& students);

void write_analysis(std::ostream&, const std::string&, double, const std::vector<Student_info>&, const std::vector<Student_info>&);

std::string letter_grade(double grade);

double median(std::vector<double>);
