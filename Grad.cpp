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

void Grad::regrade(double d1, double d2)
{
	final = d1;
	thesis = d2;
}

Grad* Grad::clone() const
{
	return new Grad(*this);
}

double Grad::grade() const
{
	return std::min(Core::grade(), thesis);
}