#ifndef EVT_HPP
#define EVT_HPP

#include <iostream>
#include <ctime>
#include "calendar.hpp"
#include "Weather.hpp"



void weatherAlert(std::vector<std::string> temp, Calendar Host)
{
time_t t = time(NULL);

tm* timePtr = localtime(&t);

    int deadline = Host.getEventDay() - timePtr->tm_mday;
    
    if(deadline <= 14 && deadline >= 0 && Host.getEventMonth() == timePtr->tm_mon){
        std::cout << "Alert! Temperature will be " << temp[deadline+14] << " with " << temp[deadline] << '.';
    }
//delete timePtr;
//free(timePtr);
}

void eventAlert(Calendar Host)
{
time_t t = time(NULL);

tm* timePtr = localtime(&t);

    int deadline = Host.getEventDay() - timePtr->tm_mday;
        
    if(deadline <= 14 && deadline >= 0 && Host.getEventMonth() == timePtr->tm_mon){
        std::cout << "Reminder: in " << deadline << " day(s) you have " << Host.getEventName() << ',';
    }
//	free(timePtr);
//delete timePtr;
}



#endif
