#pragma once

#include <iostream>
#include <string>
#include <vector>

class Core
{
public:
	Core() :midterm(0), final(0) {}
	Core(std::istream& is) { read(is); }
	virtual ~Core() {}

	std::string name() const;

	virtual std::istream& read(std::istream&);
	virtual double grade() const;
protected:
	std::istream& read_common(std::istream&);
	double midterm, final;
	std::vector<double> homework;
private:
	std::string n;
};


bool compare(const Core& c1, const Core& c2)
{
	return c1.name() < c2.name();
}

bool compare_Core_ptrs(const Core* cp1, const Core* cp2)
{
	return compare(*cp1, *cp2);
}
