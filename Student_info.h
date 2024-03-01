#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>

class Student_info {
public:
	// interface goes here
	Student_info();
	Student_info(std::istream&);
	bool valid() const { return !homework.empty(); }
	std::istream& read(std::istream&);
	double grade(); // cosnt
	std::string name() const { return n; }

private:
	// implementation goes here
	std::string n;
	double midterm, final;
	std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);
std::list<Student_info> extract_fails(std::list<Student_info>&);

bool did_all_hw(const Student_info&);
