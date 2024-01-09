#include "account.hpp"
#include "calendar.hpp"
#include "Weather.hpp"
#include "Displayers.cpp"
#include "Event_Alert.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <limits>
using namespace std;

class Calendar_with_Weather: public Displayers
{
public:
Calendar_with_Weather(){};

void Display(){
    Account all_accounts[100];
    Calendar all_calendars[100];
    Account logged_in_acc; 
    Account placeholder_acc;
    int c = 0; //represents the number of accounts in the system
    int num_cals = 0; //represents the number of calendars in the system
ofstream in;
    ifstream out;


    out.open("accounts.txt", ios::app);
    in.open("accounts.txt", ios::app);
    if(!out.is_open()||!in.is_open())
    {
        cout << "Error connecting to account manager" << endl;
        return;
    }

    //load previously made accounts
    string temp, temp_username, temp_pass;
    int back_and_forth = 0, both_inputs = 0;
    while(out >> temp)
    {
        if(back_and_forth == 0)
        {
            temp_username = temp;
            back_and_forth++;
            ++both_inputs;
        }
        else if(back_and_forth == 1)
        {
            temp_pass = temp;
            back_and_forth = back_and_forth - 1;
            ++both_inputs;
        }

        if(both_inputs == 2)
        {
            Account temp_account = Account(temp_username, temp_pass);
            all_accounts[c] = temp_account;
            c++;
            both_inputs = 0;
        }
        
    }
    out.close();
    while(true)
    {
    cout << "===================================================" << endl;
    cout << "Calendar with Weather Advisor" << endl;
    cout << "By: Tejas Shah, Martin Mejia Martinez, Timothy Thomas, Adam Carpenter" << endl;
    cout << "===================================================" << endl <<endl;
    char input = ' ';
    while(input != 'q')
    {
        cout << "Welcome!" << endl << "Press l to login" << endl << "Press a to create an account" << endl << "Press q to quit" << endl;
        cin >> input;

        if(input == 'l')
        {
            string user, pass;
            cout << "Enter the username: " << endl;
            cin >> user;
            int checker = 0;
            int temp_index; 
            for(int i = 0; i < c; ++i)
            {
                if(user == all_accounts[i].get_username())
                {
                    ++checker;
                    temp_index = i;
                }
            }
            if(checker == 1)
            {
                cout << "Enter password:" << endl;
                cin >> pass;
                if(all_accounts[temp_index].get_password() == pass)
                {

                    logged_in_acc = all_accounts[temp_index];
                    //import saved data
string file = logged_in_acc.get_username() + ".txt";
                    out.open(file, ios::app);
                    string name, desc, til;
                    int m, d, y, h, min;
                    char ap;
		    /*
                    while(!out.fail())
                    {           
                        getline(out,name);
                        getline(out,desc);
                        out.ignore();
                        out >> m;

                        out >> d;

                        out >> y;

                        out >> h;

                        out >> min;

                        out >> ap;
                        Calendar temp = Calendar(name,h,d,y,h,min,ap,desc);
                        all_calendars[num_cals] = temp;
                        num_cals++;
                    }
*/
			out.close();
                    input = 'q';
                    cout << "You are now logged in" << endl;
                }
                else
                {
                    cout << "Wrong password, please try again" << endl;
                }

            }
            else
            {
                cout << "the username doesnt exist, please go make an account" << endl;
            }
        }
        else if(input == 'a')
        {
            string username, password;
            int check = 0;
            bool is_username_here;
            while(check == 0)
            {
                is_username_here = false;
                cout << "Enter a username: " << endl;
                cin >> username;
                int checker = 0;

                for(int i = 0; i < c; ++i)
                {
                    if(username == all_accounts[i].get_username())
                    {
                        is_username_here = true;
                        cout << "this username has already been taken" << endl;
                        
                    }
                }

                if(is_username_here == false)
                {
                    check++;
                }

            }
           
            cout << "Enter a password: " << endl;
            cin >> password;
            Account acc = Account(username, password);
            all_accounts[c] = acc;
            c++;
            in << username << " " << password << endl;
            string create_file_name = username + ".txt";
            ofstream createfile(create_file_name);
            createfile.close();
            cout << "Your account has been created" << endl;
        }
        else if(input == 'q')
        {
            in.close();
            return;
        }
        else
        {
            cout << "This input doesnt exist, please put a valid input" << endl;
        }
    }
    in.close();


    input = ' ';
    
    
    string location;
    
    cout << "Enter your location (ex: Los_Angeles,CA)" << endl;
    cin >> location;

   Weather* wthr = new Weather(location);
   wthr->forecast();
  // Weather wthr = Weather(location);
  // wthr.forecast(); 
    while(input != 'q')
    {
	
	for(int i = 0; i < num_cals; i++){
		eventAlert(all_calendars[i]);
	weatherAlert(wthr->getForecast(), all_calendars[i]);

	}
        cout << endl << "What would you like to do today?" << endl << "C - Create Event" << endl << "R - Review Event" << endl << "O - log out" <<endl<< "V - View Most Recent Event" << endl << "q - Quit" << endl << endl;

        cin >> input;

        if(input == 'C' || input == 'c')
        {
            cout <<endl << "Creating Event..." << endl;
            string eventDesc;
            string eventName;
            int eventDay, eventMonth, eventYear, eventHour, eventMinute;
            char am_pm;

            cout << "Enter event name: " << endl;
            cin.ignore(1,'\n');
            getline(cin,eventName);

		cout << "Upcoming weather in " << location << " is :" << endl;
            wthr->Display();
//wthr.Display();
            cout << "Enter the day of the event: " << endl;
            cin >> eventDay;

            cout << "Enter the month of the event (numerical): " << endl;
            cin >> eventMonth;

            cout << "Enter the year of the event (numerical): " << endl;
            cin >> eventYear;

            cout << "Enter the hour of the event: " << endl;
            cin >> eventHour;

            cout << "Enter the minute of the event: " << endl;
            cin >> eventMinute;

            cout << "Enter a for AM or p for PM" << endl;
            cin >> am_pm;
            cin.ignore(1,'\n');

            cout <<"Enter a short description of the event" << endl;
            getline(cin,eventDesc);

            Calendar temp = Calendar(eventName,eventMonth,eventDay,eventYear,eventHour,eventMinute,am_pm,eventDesc);
            all_calendars[num_cals] = temp;
            num_cals++;
            
            string user = logged_in_acc.get_username();
            string open_file = user + ".txt";
            in.open(open_file,ios::app);
            in << eventName << endl << eventDesc << endl << eventMonth << endl << eventDay << endl << eventYear << endl << eventHour << endl << eventMinute << endl << am_pm  << endl;
            in.close();

            cout << "Event created!" << endl;
        }
        else if (input == 'O' || input == 'o')
        {
            logged_in_acc = placeholder_acc;
	    num_cals = 0;
            cout << "You have successfully logged out." << endl;
            break;

        }
        else if (input == 'r')
        {
            cout << endl;
            for(int i = 0; i < num_cals; i++)
            {
                
            cout << all_calendars[i].getEventName() << endl << all_calendars[i].getEventMonth() <<"-"<< all_calendars[i].getEventDay() << "-" << all_calendars[i].getEventYear() << endl
             << all_calendars[i].getEventHour() << ":" << all_calendars[i].getEventMin() << all_calendars[i].getDayTime() << endl
             << all_calendars[i].getEventDesc() << endl << endl;
             
//	     weatherAlert(wthr->getForecast(), all_calendars[i]);
            }
        }
        else if(input == 'V' || input == 'v' ){
            int n = num_cals - 1;
            int min = all_calendars[0].getEventDay();
          string name1; 
	  int saveI = 0;
          int month1;
           int year1;
          int hour1;
          int min1;
          string ampm;
          string desc1;
            for(int i = 0; i <num_cals; i++){
                if(min > all_calendars[i].getEventDay() && all_calendars[i].getEventDay() != 0){
                    min = all_calendars[i].getEventDay();
                     name1  = all_calendars[i].getEventName();
                     month1 = all_calendars[i].getEventMonth();
                     year1 = all_calendars[i].getEventYear();
                   hour1 = all_calendars[i].getEventHour();
                   min1 = all_calendars[i].getEventMin();
                     ampm = all_calendars[i].getDayTime();
                    desc1 = all_calendars[i].getEventDesc();
		    saveI = i;
                }
            }
            cout << endl <<  "Most Recent Event:" << endl << name1 << endl << month1 << "-" << min << "-" << year1 << endl << hour1 << ":" << min1 << " " << ampm << endl << desc1 << endl;
	  // weatherAlert(wthr->getForecast(), all_calendars[saveI]);
        }
        else if(input == 'q' || input == 'Q')
        {
	    delete wthr;
            return;
        }
    }
    
    delete wthr;
  }


};
};

int main()
{
    
    Displayers*  running_application = new Calendar_with_Weather();
    running_application->Display();
    delete running_application;
    return 0;
}
