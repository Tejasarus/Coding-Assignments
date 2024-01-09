#ifndef WEATHER_HPP
#define WEATHER_HPP
#include <string>
#include <vector>
#include "Displayers.cpp"
class Weather: public Displayers
{
private:
	std::string location;
	int temperature = 0;
	std::string api_key = "bbf1222e16404fa3878db223a9461747";
	std::vector<std::string> theWeather;

	void printForecast(std::vector<std::string> weatherByDay);

public:
	Weather() {};
	~Weather() {};
	Weather(std::string loc);


	std::vector<std::string> convertJson(std::string api_json);
	
	std::vector<std::string> getForecast() {return theWeather;};
	void settheWeather(std::vector<std::string> newWeather){theWeather = newWeather;};

	void updateLocation(std::string new_location);
	void setTemperature(int temp);
	int getTemperature();
    	void Display(){
		forecast();
		printForecast(theWeather);
	};
	
	//Prints 14 day forecast
	void forecast();
	
	
};
	
#endif //WEATHER_HPP
