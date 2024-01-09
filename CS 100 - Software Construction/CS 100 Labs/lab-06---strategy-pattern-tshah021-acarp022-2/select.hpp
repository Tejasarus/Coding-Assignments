#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
#include <iostream>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select_Column
{
    private:

	std::string str;

    public:
	Select_Contains(const Spreadsheet* sheet, const std::string& collumn_name, const std::string& strr) : Select_Column(sheet, collumn_name) 
    {
	    str = strr;
    }

    //for pure virtual function
	virtual bool select(const std::string& s) const 
    {
        if(s.find(str) != std::string::npos)
        {
            return true;
        }
        return false;
    }
};

class Select_And: public Select
{
    private:
    Select* and1;
    Select* and2;

    public:
    Select_And(Select* value1, Select* value2) 
    {
        and1 = value1;
        and2 = value2;
    }

    //and is 1 & 1 => 1
    bool select(const Spreadsheet* sheet, int row) const 
    {
        if(and1->select(sheet, row) == true && and2->select(sheet, row) == true) 
        {
            return true;
        } 
       
       return false;
    }
    
    virtual ~Select_And() 
    {
        delete and1;
        delete and2;
    }
};

class Select_Not: public Select
{
    private:
    Select* not1;

    public:
    Select_Not(Select* value)
    {
       not1 = value;
    }

    //not: 1 -> 0 or 0 -> 1
    bool select(const Spreadsheet* sheet, int row) const
    {
        if(not1->select(sheet, row) == true)
        {
            return false;
        }

        return true;
    }

    virtual ~Select_Not() 
    {
        delete not1;
    }

};

class Select_Or: public Select
{
    private:
    Select* or1;
    Select* or2;

    public:
    Select_Or(Select* value1, Select* value2) 
    {
        or1 = value1;
        or2 = value2;
    }

    //or is 1 OR 1 => 1
    bool select(const Spreadsheet* sheet, int row) const 
    {
        if(or1->select(sheet, row) == true || or2->select(sheet, row) == true) 
        {
            return true;
        } 
       
       return false;
    }
    
    virtual ~Select_Or() 
    {
        delete or1;
        delete or2;
    }
};
#endif //__SELECT_HPP__
