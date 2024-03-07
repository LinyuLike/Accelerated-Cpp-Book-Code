#pragma once
#include "Core.h"

class Grad :
    public Core
{
public:
    Grad() :thesis(0) {}
    Grad(std::istream& is) { read(is); }

    double grade() const;
    std::istream& read(std::istream&);

protected:
    Grad* clone() const { return new Grad(*this); }

private:
    double thesis;
};

