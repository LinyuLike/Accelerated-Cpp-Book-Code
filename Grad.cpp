#include "Grad.h"
#include "Student_info.h"

#include <iostream>
#include <algorithm>

std::istream& Grad::read(std::istream& in)
{
	read_common(in);
	in >> thesis;
	read_hw(in, Core::homework);
	return in;
}

double Grad::grade() const
{
	return std::min(Core::grad(), thesis);
}