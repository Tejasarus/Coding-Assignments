# Calendar with Weather Advisor

 > Authors: [Martin Mejia Martinez](https://github.com/Marteen13), [Timothy Thomas](https://github.com/BlargBetaa), [Tejas Shah](https://github.com/Tejasarus), [Adam Carpenter](https://github.com/Adamcarp24)
 
## Project Description

We have noticed how sporadic the weather has been recently making it difficult to make plans that are outdoors. Our project "Calendar with Weather Advisor" is a calendar application which allows the user to better schedule events by allowing them to plan around the weather and other events. The application would have an hourly weather forcast in the graphical interface, so the user can immediately see what the weather is at that time and can plan accordingly. 

#### Tools for this project: ####

* [C++](https://www.cplusplus.com/) - The programming language we will be using for this project, it's a general purpose programming language built as an extension of the C programming language
* [github](https://github.com/) - the provider we will be using to host, facilitate, and collaborate our project from.
* [SFML](https://www.sfml-dev.org/) - the Simple and Fast Multimedia Library is desgined to help developers create simple graphical application interfaces.

#### Inputs, Outputs, and Features ####

Inputs:
* Email
* Event name
* Event date/time
* Event location
* Event description/notes

Outputs:
* Visual representation of events
* Email notification 30min before event
* Warnings if weather poses an inconvienice to event (occurs during event creation stage)

Features:
* Ability to create multiple accounts with seperate calendars tied to them
* Ability to see real time weather while scheduling events
* Create and view events
* Obtain notifications/reminders of events
* Application gives warnings of potential hinderences to events based on weather predictions

## UML Class Diagram ##
![Calendar Class Diagram](https://user-images.githubusercontent.com/50884660/166127922-b3ff5fbe-edc8-4d39-bd72-fd1f55e4839b.png)
 
 This class diagram represents what classes and functions we will be using. The project consists of five classes: Account, CurrentDateTime, Calendar, Weather, and Notif.
 
#### Account: ####

This class focuses on anything that has to do with the users account. The user can create an account if they don't have one, log in if they have an account, change their password, and delete their account if need be.

#### CurrentDateTime: ####

This class focuses on functions revolving the date and time. Getter functions allow the children classes Calendar and Weather to obtain the respective data for their functions. The setter functions are meant for the Calendar and Weather classes to set the time when creating events, essentially for the two children classes to "talk" to each other.

#### Calendar: ####

This class does everything revolving the main calendar itself. This includes creating an event, deleting an event, and modifying an event. It inherits from the CurrentDateTime class and the Notif class.

#### Weather: ####

This class contains all of the functions regarding the weather. This includes checking what the weather is and reporting it to the user. In the event that the weather is not ideal at the time the user, then it would send a notification to the user warning them about the potential weather conflict (through the notif class).

#### Notif: ####

This parent class has the purpose of sending notifications based on conflicts in the weather or 30 minutes before an event takes place.
 
 
 > ## Phase III
 > You will need to schedule a check-in for the second scrum meeting with the same reader you had your first scrum meeting with (using Calendly). Your entire team must be present. This meeting will occur on week 8 during lab time.
 > * Before the meeting you should perform a sprint plan like you did in Phase II.
 > * You should also update this README file by adding the following:
 >   * What design pattern(s) did you use? For each pattern you must explain in 4-5 sentences:
 >     * Why did you pick this pattern? And what feature did you implement with it?
 >     * How did the design pattern help you write better code?
 >   * An updated class diagram that reflects the design pattern(s) you used. You may combine multiple design patterns into one diagram if you'd like, but it needs to be clear which portion of the diagram represents which design pattern (either in the diagram or in the description).
 >   * Make sure your README file (and Project board) are up-to-date reflecting the current status of your project. Previous versions of the README file should still be visible through your commit history.
> 
> During the meeting with your reader you will discuss: 
 > * How effective your last sprint was (each member should talk about what they did)
 > * Any tasks that did not get completed last sprint, and how you took them into consideration for this sprint
 > * Any bugs you've identified and created issues for during the sprint. Do you plan on fixing them in the next sprint or are they lower priority?
 > * What tasks you are planning for this next sprint.

 
 > ## Final deliverable
 > All group members will give a demo to the TA/reader during lab time. The TA/reader will check the demo and the project GitHub repository and ask a few questions to all the team members. 
 > Before the demo, you should do the following:
 > * Complete the sections below (i.e. Screenshots, Installation/Usage, Testing)
 > * Plan one more sprint (that you will not necessarily complete before the end of the quarter). Your In-progress and In-testing columns should be empty (you are not doing more work currently) but your TODO column should have a full sprint plan in it as you have done before. This should include any known bugs (there should be some) or new features you would like to add. These should appear as issues/cards on your Project board.
 > * Make sure your README file and Project board are up-to-date reflecting the current status of your project (e.g. any changes that you have made during the project such as changes to your class diagram). Previous versions should still be visible through your commit history. 
 
 ## Screenshots
 > Screenshots of the input/output after running your application
 ## Installation/Usage
 > Instructions on installing and running your application
 ## Testing
 > How was your project tested/validated? If you used CI, you should have a "build passing" badge in this README.
 
