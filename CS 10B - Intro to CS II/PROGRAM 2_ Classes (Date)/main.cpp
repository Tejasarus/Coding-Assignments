#include <iostream>
#include <string>

using namespace std;

class Date {
 private:
   unsigned day;
   unsigned month;
   string monthName;
   unsigned year;

 public:
   // creates the date January 1st, 2000.
   Date();


   /* parameterized constructor: month number, day, year 
       - e.g. (3, 1, 2010) will construct the date March 1st, 2010

       If any of the arguments are invalid (e.g. 15 for month or 32 for day)
       then the constructor will construct instead a valid Date as close
       as possible to the arguments provided - e.g. in above example,
       Date(15, 32, 2010), the Date would be corrected to Dec 31st, 2010.
       In case of such invalid input, the constructor will issue a console error message: 

       Invalid date values: Date corrected to 12/31/2010.
       (with a newline at the end).
   */
   Date(unsigned m, unsigned d, unsigned y);


   /* parameterized constructor: month name, day, year
      - e.g. (December, 15, 2012) will construct the date December 15th, 2012

       If the constructor is unable to recognize the string argument as a valid month name,
       then it will issue a console error message: 

       Invalid month name: the Date was set to 1/1/2000.
       (with a newline at the end).
 
       If the day argument is invalid for the given month (but the month name was valid),
       then the constructor will handle this error in the same manner as the other
       parameterized constructor. 

       This constructor will recognize both "december" and "December"
       as month name.
   */
   Date(const string &mn, unsigned d, unsigned y);


   /* Outputs to the console (cout) a Date exactly in the format "3/15/2012". 
      Does not output a newline at the end.
   */
   void printNumeric() const;


   /* Outputs to the console (cout) a Date exactly in the format "March 15, 2012".
      The first letter of the month name is upper case, and the month name is
      printed in full - January, not Jan, jan, or january. 
      Does not output a newline at the end.
   */
   void printAlpha() const;

 private:

   /* Returns true if the year passed in is a leap year, otherwise returns false.
   */
   bool isLeap(unsigned y) const;


   /* Returns number of days allowed in a given month
      -  e.g. daysPerMonth(9, 2000) returns 30.
      Calculates February's days for leap and non-leap years,
      thus, the reason year is also a parameter.
   */
   unsigned daysPerMonth(unsigned m, unsigned y) const;

   /* Returns the name of a given month
      - e.g. name(12) returns the string "December"
   */
   string name(unsigned m) const;

   /* Returns the number of a given named month
      - e.g. number("March") returns 3
   */
   unsigned number(const string &mn) const;
};


// Implement the Date member functions here
Date::Date()
{
    day = 1;
    month = 1;
    year = 2000;
    monthName = "January";
}
Date::Date(unsigned m, unsigned d, unsigned y)
{
    /* parameterized constructor: month number, day, year 
       - e.g. (3, 1, 2010) will construct the date March 1st, 2010

       If any of the arguments are invalid (e.g. 15 for month or 32 for day)
       then the constructor will construct instead a valid Date as close
       as possible to the arguments provided - e.g. in above example,
       Date(15, 32, 2010), the Date would be corrected to Dec 31st, 2010.
       In case of such invalid input, the constructor will issue a console error message: 

       Invalid date values: Date corrected to 12/31/2010.
       (with a newline at the end).
   */
    int c = 0;
    if(m < 1 || m >= 13)
    {
        if(m < 1)
        {
            m = 1;
            c=1;
        }
        else if(m >= 13)
        {
            m = 12;
            c=1;
        }
    }
    
        if(m == 1)
        {
            if(d < 32 && d > 0)
            {
                month = 1;
                monthName = "January";
                day = d;
                year = y; 
            }
            else
            {
                if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }

        }
        else if(m == 2)
        {
            if(isLeap(y))
            {
                
                if(d < 30 && d > 0)
                {
                    month = 2;
                    monthName = "February";
                    day = d;
                    year = y; 
                }
                else
                {
                    if(d > 29)
                    {
                        d = 29;
                    }
                    else if(d < 1)
                    {
                        d = 1;
                    }
                    cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
                }
            }
            else
            {
                if(d < 29 && d > 0)
                {
                    month = 2;
                    monthName = "February";
                    day = d;
                    year = y; 
                }
                else
                {
                    if(d > 28)
                    {
                        d = 28;
                    }
                    else if(d < 1)
                    {
                        d = 1;
                    }
                    cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
                }
            }

        }
        else if(m == 3)
        {
             if(d < 32 && d > 0)
            {
            month = 3;
            monthName = "March";
            day = d;
            year = y;
             }
            else
            {
               if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 4)
        {
            if(d < 31 && d > 0)
            {
            month = 4;
            monthName = "April";
            day = d;
            year = y;
            }
            else
            {
              if(d > 30)
                {
                    d = 30;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 5)
        {
             if(d < 32 && d > 0)
            {
            month = 5;
            monthName = "May";
            day = d;
            year = y;
             }
            else
            {
               if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 6)
        {
            if(d < 31 && d > 0)
            {
            month = 6;
            monthName = "June";
            day = d;
            year = y;
            }
            else
            {
                if(d > 30)
                {
                    d = 30;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 7)
        {
             if(d < 32 && d > 0)
            {
            month = 7;
            monthName = "July";
            day = d;
            year = y;
             }
            else
            {
                if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 8)
        {
             if(d < 32 && d > 0)
            {
            month = 8;
            monthName = "August";
            day = d;
            year = y;
             }
            else
            {
               if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 9)
        {
            if(d < 31 && d > 0)
            {
            month = 9;
            monthName = "September";
            day = d;
            year = y;
            }
            else
            {
               if(d > 30)
                {
                    d = 30;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 10)
        {
             if(d < 32 && d > 0)
            {
            month = 10;
            monthName = "October";
            day = d;
            year = y;
             }
            else
            {
                if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 11)
        {
            if(d < 31 && d > 0)
            {
            month = 11;
            monthName = "November";
            day = d;
            year = y;
            }
            else
            {
               if(d > 30)
                {
                    d = 30;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
        }
        else if(m == 12)
        {
             if(d < 32 && d > 0)
            {
            month = 12;
            monthName = "December";
            day = d;
            year = y;
             }
            else
            {
                if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"." << endl;
                c = 0;
            }
            if(c == 1)
            {
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"." << endl;
            }
        }
        
    month = m;
    day = d;
    year = y;
    monthName = name(m);
}

Date::Date(const string &mn, unsigned d, unsigned y)
{
    /* parameterized constructor: month name, day, year
      - e.g. (December, 15, 2012) will construct the date December 15th, 2012

       If the constructor is unable to recognize the string argument as a valid month name,
       then it will issue a console error message: 

       Invalid month name: the Date was set to 1/1/2000.
       (with a newline at the end).
 
       If the day argument is invalid for the given month (but the month name was valid),
       then the constructor will handle this error in the same manner as the other
       parameterized constructor. 

       This constructor will recognize both "december" and "December"
       as month name.
       */
    int m = number(mn);
   // cout << m << endl;
   // cout << "lol" << endl;
    if(mn == "January" || mn == "january")
    {
           if(d < 32 && d > 0)
            {
                month = 1;
                monthName = "January";
                day = d;
                year = y; 
            }
            else
            {
                if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "February"|| mn == "february")
    {
         if(isLeap(y))
            {
                
                if(d < 30 && d > 0)
                {
                    month = 2;
                    monthName = "February";
                    day = d;
                    year = y; 
                }
                else
                {
                    if(d > 29)
                    {
                        d = 29;
                    }
                    else if(d < 1)
                    {
                        d = 1;
                    }
                    cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
                }
            }
            else
            {
                if(d < 29 && d > 0)
                {
                    month = 2;
                    monthName = "February";
                    day = d;
                    year = y; 
                }
                else
                {
                    if(d > 28)
                    {
                        d = 28;
                    }
                    else if(d < 1)
                    {
                        d = 1;
                    }
                    cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
                }
            }
    }
    else if(mn == "March"|| mn == "march")
    {
         if(d < 32 && d > 0)
            {
            month = 3;
            monthName = "March";
            day = d;
            year = y;
             }
            else
            {
               if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                
                cout << "Invalid date values: Date corrected to " <<  m<<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "April"|| mn == "april")
    {
       if(d < 31 && d > 0)
            {
            month = 4;
            monthName = "April";
            day = d;
            year = y;
            }
            else
            {
              if(d > 30)
                {
                    d = 30;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "May"|| mn == "may")
    {
         if(d < 32 && d > 0)
            {
            month = 5;
            monthName = "May";
            day = d;
            year = y;
             }
            else
            {
               if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "June"|| mn == "june")
    {
       // cout << "June" << endl;
         if(d < 31 && d > 0)
            {
            month = 6;
            monthName = "June";
            day = d;
            year = y;
            }
            else
            {
                if(d > 30)
                {
                    d = 30;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "July"|| mn == "july")
    {
         if(d < 32 && d > 0)
            {
            month = 7;
            monthName = "July";
            day = d;
            year = y;
             }
            else
            {
                if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "August"|| mn == "august")
    {
         if(d < 32 && d > 0)
            {
            month = 8;
            monthName = "August";
            day = d;
            year = y;
             }
            else
            {
               if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "September"|| mn == "september")
    {
            if(d < 31 && d > 0)
            {
            month = 9;
            monthName = "September";
            day = d;
            year = y;
            }
            else
            {
               if(d > 30)
                {
                    d = 30;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "October"|| mn == "october")
    {
          if(d < 32 && d > 0)
            {
            month = 10;
            monthName = "October";
            day = d;
            year = y;
             }
            else
            {
                if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "November"|| mn == "november")
    {
        if(d < 31 && d > 0)
            {
            month = 11;
            monthName = "November";
            day = d;
            year = y;
            }
            else
            {
               if(d > 30)
                {
                    d = 30;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"."<< endl;
            }
    }
    else if(mn == "December"|| mn == "december")
    {
           if(d < 32 && d > 0)
            {
            month = 12;
            monthName = "December";
            day = d;
            year = y;
             }
            else
            {
                if(d > 31)
                {
                    d = 31;
                }
                else if(d < 1)
                {
                    d = 1;
                }
                cout << "Invalid date values: Date corrected to " << m <<"/" <<d<<"/"<<y<<"." << endl;
            }
    }
    else
    {
    /*If the day argument is invalid for the given month (but the month name was valid),
       then the constructor will handle this error in the same manner as the other
       parameterized constructor. 
       */
        d = 1;
        y = 2000;
        cout << "Invalid month name: the Date was set to " <<  m<<"/" <<d<<"/"<<y<<"."<< endl;
      //  cout << "Invalid date values: Date corrected to: " << 
        //cout << "Invalid month name: the Date was set to 1/1/2000." << endl;
    }
    month = number(mn);
    day = d;
    year = y;
    monthName = name(number(mn));
   
}

void Date::printNumeric() const
{
    /* Outputs to the console (cout) a Date exactly in the format "3/15/2012". 
      Does not output a newline at the end.
   */
    cout << month << "/" << day << "/" << year;
}
void Date::printAlpha() const
{
    cout << monthName << " " << day << ", " << year;
}

bool Date::isLeap(unsigned y) const
{
    if(y%4 == 0)
    {
        if(y%100 == 0)
        {
            if(y%400 == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
        
    }
    else
    {
        return false;
    }
    
}

string Date::name(unsigned m) const
{
    /* Returns the name of a given month
      - e.g. name(12) returns the string "December"
   */
    if(m == 1)
    {
        return "January";
    }
    else if(m == 2)
    {
        return "February";
    }
    else if(m == 3)
    {
        return "March";
    }
    else if(m == 4)
    {
        return "April";
    }
    else if(m == 5)
    {
        return "May";
    }
    else if(m == 6)
    {
        return "June";
    }
    else if(m == 7)
    {
        return "July";
    }
    else if(m == 8)
    {
        return "August";
    }
    else if(m == 9)
    {
        return "September";
    }
    else if(m == 10)
    {
        return "October";
    }
    else if(m == 11)
    {
        return "November";
    }
    else if(m == 12)
    {
        return "December";
    }
    else
    {
        return "January";
    }
}

unsigned Date::number(const string &mn) const
{
    /* Returns the number of a given named month
      - e.g. number("March") returns 3
   */
     if(mn == "January" ||mn == "january")
    {
      //  monthName = "January";
        return 1;
         
    }
    else if(mn == "February"||mn == "february")
    {
       // monthName = "February";
        return 2;
    }
    else if(mn == "March"||mn == "march")
    {
       // monthName = "March";
        return 3;
    }
    else if(mn == "April"|| mn =="april")
    {
        //monthName = "April";
        return 4;
    }
    else if(mn == "May"||mn == "may")
    {
      //  monthName = "May";
        return 5;
    }
    else if(mn == "June"|| mn =="june")
    {
      //  monthName = "June";
        return 6;
    }
    else if(mn == "July"||mn == "july")
    {
        //monthName = "July";
        return 7;
    }
    else if(mn == "August"||mn == "august")
    {
       // monthName = "August";
        return 8;
    }
    else if(mn == "September"||mn == "september")
    {
       // monthName = "September";
        return 9;
    }
    else if(mn == "October"||mn == "october")
    {
       // monthName = "October";
        return 10;
    }
    else if(mn == "November"||mn == "november")
    {
       // monthName = "November";
        return 11;
    }
    else if(mn == "December"||mn == "december")
    {
        //monthName = "December";
        return 12;
    }
    else
    {
        return 1;
    }
}

unsigned Date::daysPerMonth(unsigned m, unsigned y) const
{
     /* Returns number of days allowed in a given month
      -  e.g. daysPerMonth(9, 2000) returns 30.
      Calculates February's days for leap and non-leap years,
      thus, the reason year is also a parameter.
   */
    if(isLeap(y) && m == 2)
    {
        return 29;
    }
    else
    {
        if(m == 1)
        {
            return 31;
        }
        else if(m == 2)
        {
            return 28;
        }
        else if(m == 3)
        {
            return 31;
        }
        else if(m == 4)
        {
            return 30;
        }
        else if(m == 5)
        {
            return 31;
        }
        else if(m == 6)
        {
            return 30;
        }
        else if(m == 7)
        {
            return 31;
        }
        else if(m == 8)
        {
            return 31;
        }
        else if(m == 9)
        {
            return 30;
        }
        else if(m == 10)
        {
            return 31;
        }
        else if(m == 11)
        {
            return 30;
        }
        else if(m == 12)
        {
            return 31;
        }
        else
        {
            exit(1);
        }
    }
}
// Don't change the code below this line.
// You may comment them out if you want to build your own test harness
// while in develope mode, but you will need these to pass tets in submit mode.

Date getDate();

int main() {
   
   Date testDate;
   testDate = getDate();
   cout << endl;
   cout << "Numeric: ";
   testDate.printNumeric();
   cout << endl;
   cout << "Alpha:   ";
   testDate.printAlpha();
   cout << endl;
   
   return 0;
}

Date getDate() {
   int choice;
   unsigned monthNumber, day, year;
   string monthName;

   cout << "Which Date constructor? (Enter 1, 2, or 3)" << endl
      << "1 - Month Number" << endl
      << "2 - Month Name" << endl
      << "3 - default" << endl;
   cin >> choice;
   cout << endl;

   if (choice == 1) {
      cout << "month number? ";
      cin >> monthNumber;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthNumber, day, year);
   } else if (choice == 2) {
      cout << "month name? ";
      cin >> monthName;
      cout << endl;
      cout << "day? ";
      cin >> day;
      cout << endl;
      cout << "year? ";
      cin >> year;
      cout << endl;
      return Date(monthName, day, year);
   } else {
      return Date();
   }
}
