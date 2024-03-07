#pragma once

#include <vector>
#include <string>
#include "Student_info.h"


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

