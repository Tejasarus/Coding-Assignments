#ifndef _CAL_HPP
#define _CAL_HPP

#include <iostream>
#include <string>

using namespace std;

class Calendar{

    public:

    Calendar(){};

    Calendar(string eventName, int M, int day, int Y, int H, int min, char timeyThingy, string eventDescription){
      this->eventName = eventName;
        eventMonth = M;
        eventYear = Y;
        eventHour = H;
        eventMinute = min;
        timeofDay = timeyThingy;
        
      eventDay = day;
      this->eventDescription = eventDescription;
        };
    string getEventName(){ return eventName;};
    int getEventDay(){return eventDay;};

    int getEventMonth(){return eventMonth;};
    int getEventYear(){return eventYear;};
    
    string getEventDesc(){return eventDescription;};
    
    
    int getEventHour(){return eventHour;};
    int getEventMin(){return eventMinute;};
    string getDayTime(){
      if(timeofDay == 'P' || timeofDay == 'p')
        return "PM";
      else{
        return "AM";
      }
      }; // return a or p(am or pm)
    
    void display()
    {
      cout << eventName << endl << eventMonth <<"-"<< eventDay << "-" << eventYear << endl
             << eventHour << ":" << eventMinute << getDayTime() << endl
             << eventDescription << endl << endl;
    }
    
    void setEventName(string name){eventName = name;};
    
    void setEventDate(int M, int D, int Y){eventDay = D; eventMonth = M; eventYear = Y;};
    
    void setEventDesc(string desc){eventDescription = desc;};
    
    
    void setEventTime(int h, int m, char t){ eventHour = h; eventMinute = m; timeofDay = t; };

    private:

    string eventName;
    string eventDescription;
    
    int eventHour;//hr
    int eventMinute;//min
    char timeofDay;//am or pm
    
    int eventDay;
    int eventYear;
    int eventMonth;   
};

#endif
