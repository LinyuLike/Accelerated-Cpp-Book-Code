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
    void regrade(double d1, double d2);
    Grad* clone() const;
    
protected:
    // move clone to public

private:
    double thesis;
};
