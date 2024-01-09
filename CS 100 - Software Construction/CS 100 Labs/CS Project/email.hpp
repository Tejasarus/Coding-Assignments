// C++ program for the above approach
#ifndef __EMAIL_HPP__
#define __EMAIL_HPP__

#include <iostream>
using namespace std;

class Email:
{

    public:
    Email(){};

    // Function to check the character
    // is an alphabet or not
    bool isChar(char c)
    {
        return ((c >= 'a' && c <= 'z')
                || (c >= 'A' && c <= 'Z'));
    };

    // Function to check the character
    // is an digit or not
    bool isDigit(const char c)
    {
        return (c >= '0' && c <= '9');
    }

    // Function to check email id is
    // valid or not
    bool is_valid(string email)
    {
        // Check the first character
        // is an alphabet or not
        if (!isChar(email[0])) {

            // If it's not an alphabet
            // email id is not valid
            return 0;
        }
        // Variable to store position
        // of At and Dot
        int At = -1, Dot = -1;

        // Traverse over the email id
        // string to find position of
        // Dot and At
        for (int i = 0;
            i < email.length(); i++) {

            // If the character is '@'
            if (email[i] == '@') {

                At = i;
            }

            // If character is '.'
            else if (email[i] == '.') {

                Dot = i;
            }
        }

        // If At or Dot is not present
        if (At == -1 || Dot == -1)
            return 0;

        // If Dot is present before At
        if (At > Dot)
            return 0;

        // If Dot is present at the end
        return !(Dot >= (email.length() - 1));
    }\
};
#endif

