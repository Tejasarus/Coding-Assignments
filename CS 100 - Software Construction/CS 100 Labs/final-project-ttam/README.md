# Calendar with Weather Advisor

 > Authors: [Martin Mejia Martinez](https://github.com/Marteen13), [Timothy Thomas](https://github.com/BlargBetaa), [Tejas Shah](https://github.com/Tejasarus), [Adam Carpenter](https://github.com/Adamcarp24)
 
## Project Description

We have noticed how sporadic the weather has been recently making it difficult to make plans that are outdoors. Our project "Calendar with Weather Advisor" is a calendar application which allows the user to better schedule events by allowing them to plan around the weather and other events. When the user is creating an event, they will be shown the weather forecast for the next two weeks to help them better plan their schedule. All of their events will be linked to their account for future reference.
#### Tools for this project: ####

* [C++](https://www.cplusplus.com/): The programming language we will be using for this project, it's a general purpose programming language built as an extension of the C programming language
* [Github/Git](https://github.com/): The provider we will be using to host, facilitate, and collaborate our project from.
* [SFML](https://www.sfml-dev.org/): the Simple and Fast Multimedia Library is desgined to help developers create simple graphical application interfaces.
* [cpr](https://github.com/libcpr/cpr): C++ Requests is a simple wrapper around libcurl inspired by the excellent Python Requests project.
* [Valgrind](https://valgrind.org/): an instrumentation framework for building dynamic analysis tools which we will be using to help with memory management
* [GoogleTest](https://github.com/google/googletest): Also known as gtest, Google Test is a unit testing library for C++

#### Inputs, Outputs, and Features ####

Inputs:
* `Account Info`: username, password
* `Events`: event name, event time, event description

Outputs:
* `Events`: view all scheduled events
* `Weather`: Displays forecast for the next two weeks (becomes increasingly inaccurate after 2 weeks)

Features:
* `Accounts`: Ability to create multiple accounts with seperate calendars tied to them
* `Create and view events`: View the most upcoming event or the whole list
* `Weather`: View weather predictions for the next two weeks

## UML Class Diagram ##

![UML](https://user-images.githubusercontent.com/94268418/171923729-dd7cbb73-cd31-4b7a-b09f-8568cfb229dc.png) 

This class diagram represents what classes and functions we will be using. The project consists of six classes: Displayers, Calendar_with_Weather, Account, Weather, Calendar, and Event_Alert.

#### Design Pattern ####
* `Strategy` - Due to the nature of our application we decided to go with the strategy design pattern. This is because our application displays various sets of data to the user such as their calendar event data or the weather forecast from a certain city. Our application links these various strategies to a single object (Displayers) through the Display() function in order to make the program more managable to work with and change in the future. 

#### Displayers: ####

This class acts as a base class to any subclass that displays to the terminal and in the future to any class that would also display to the Gui.

#### Calendar_with_Weather: ####

This class acts as the main connection to the user. It communicates directly to the user and uses the Account, Calendar, and Weather classes to perform the desired actions of the user.

#### Account: ####

This class focuses on anything that has to do with the users account. The user can create an account if they don't have one and log in if they do. All of their event data will be saved and linked to their account for future reference.

#### Calendar: ####

This class does everything revolving events. The user can create events by including the event name, date, time, and description. The user can also view all of the events they have created or the most upcoming one.

#### Weather: ####

This class contains all actions regarding the weather. It gets the real time weather forecast for the user's location and can display it to the terminal.

#### Event_Alert: ####

This class checks the events that an account has made and can alert the user of changes to events that are happening soon.

 ## Screenshots
 Title Screen:
 
![Title Screen](https://user-images.githubusercontent.com/50884660/171546684-54a67af8-aae0-41ba-a29e-7de14f64ba43.png)

Creating an account:

![Creating account](https://user-images.githubusercontent.com/50884660/171900668-ae6fc576-f0e5-46a7-8152-c8604e969dfc.png)

Login:

![Logging in](https://user-images.githubusercontent.com/50884660/171900866-c50e163c-6007-4ddf-bfd7-a2e9c7adada8.png)

Creating an event:

![Creating an Event](https://user-images.githubusercontent.com/50884660/171901884-511ba2be-73cf-4e4b-ad59-1aca8db1c77e.png)

Viewing all events:

![viewing all events](https://user-images.githubusercontent.com/50884660/171902087-cf3ff12f-6a61-4688-8f67-8e8a85a94930.png)

View the most upcoming event:

![viewing most upcomming event](https://user-images.githubusercontent.com/50884660/171902136-7f668639-c329-4856-b05d-c23d069344a4.png)

Logging out:

![logging out](https://user-images.githubusercontent.com/50884660/171902206-9334172c-cd5a-42fa-9f0e-d1a7dad81a4b.png)

## Installation/Usage ##
There's a few simple steps you have to follow to use this program. You'll be up and running in no time.
1) Clone this repository
2) Go to the root folder of the clone (final-project-ttam) and add cpr and gtest by running `git submodule add https://github.com/google/googletest.git` and `git submodule add https://github.com/libcpr/cpr`
3) Run `cmake .` or `cmake3 .` if on hammer followed by `make` to generate the two executables `calendar_application` and `test`
4) To run the application, run `./calendar_application` or `./test` to run the unit tests
 ## Testing

To test the application, we have created unit tests to test the most critical parts of the program. We made sure that all of our unit tests for that feature passed before working on other features. We also used Valgrind to check for memory leaks and made sure to fix an issues/bugs before moving forward with other items.

Unit Tests:

![Unit Tests](https://user-images.githubusercontent.com/50884660/171897956-b1c37afd-a60f-4b41-b537-327a8dfc7f57.png)

Valgrind:

![Valgrind](https://user-images.githubusercontent.com/50884660/171952536-074ff66d-281d-416c-9df8-9b0ec3da4346.png)
 
