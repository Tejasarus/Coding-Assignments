#include "Weather.hpp"
#include <iostream>
#include <cpr/cpr.h>
#include <string>
#include <vector>
#include <time.h>

Weather::Weather(std::string loc){
    location = loc;
}

void Weather::updateLocation(std::string new_location){
    location = new_location;
}

void Weather::setTemperature(int temp){
    temperature = temp;
}

int Weather::getTemperature(){
    return temperature;
}

void Weather::forecast(){ 
     cpr::Response info = cpr::Get(cpr::Url{"http://api.weatherbit.io/v2.0/forecast/daily"},
                          cpr::Parameters{{"days", "14"}, {"units", "I"}, {"city", location}, {"key", api_key}});
    std::vector<std::string> weatherByDay;
    weatherByDay = convertJson(info.text);

    settheWeather(weatherByDay);
}

std::vector<std::string> Weather::convertJson(std::string api_json){
    std::string value = "";
    std::string search_weather = "des";
    std::string search_temp = "\"temp\"";
    int pos;
    int pos_start = 0;
    std::vector<std::string> weathers;

    for (int i = 0; i < 14; ++i) {   //finds weather description
        pos = api_json.find(search_weather, pos_start) + 14;
        value = api_json.substr(pos, (api_json.find("}", pos) - (pos + 1)));
        if (value != "")
            weathers.push_back(value);
        pos_start = pos;
    }

    pos = 0; pos_start = 0;
    for (int i = 0; i < 14; ++i) {   //finds temperature
        pos = api_json.find(search_temp, pos_start) + 7;
        value = api_json.substr(pos, (api_json.find(",", pos) - (pos)));
        if (value != "")
            weathers.push_back(value);
        pos_start = pos;
    }

    return weathers;
}

void Weather::printForecast(std::vector<std::string> weatherByDay){
    //nessecary to get the current weekday
    const std::string DAY[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
    time_t rawtime;
    tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    int weekDay = timeinfo->tm_wday;

    for(int i = 0; i < 14; ++i){

        if(i == 0) 
            std::cout << "Today:" << std::endl;
        else if(i == 1) 
            std::cout << "Tomorrow:" << std::endl;

        else 
            std::cout << DAY[(weekDay+i)%7] << ":" << std::endl;

        std::cout << weatherByDay[i] << ", " << weatherByDay[i+14] << "F" << std::endl;

    }
}

