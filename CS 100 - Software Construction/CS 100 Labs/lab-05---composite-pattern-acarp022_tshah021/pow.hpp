#ifndef POW_HPP
#define POW_HPP
#include "math.h"
#include "base.hpp"

class Pow: public Base
{
    private:
	Base* val1;
	Base* val2;
     
     public:
	 Pow(Base* value1, Base* value2) : Base() {	val1  = value1;	val2  = value2;}
     virtual double evaluate() {return pow(val1->evaluate(),val2->evaluate());}
     virtual std::string stringify() {return "(" + val1->stringify() + " ** " + val2->stringify() + ")";}
};
#endif