#include <stdio.h>
#include <iostream>
using namespace std;

void TimerISR();

// BEGIN Items to mimick RIMS. Don't modify this code. 

unsigned short A7,A6,A5,A4,A3,A2,A1,A0; // Note: Setting or reading A or B as a group, as in B = 0, isn't supported
unsigned short B7,B6,B5,B4,B3,B2,B1,B0;
char inputValues[100][8]; // Inputs A7..A0 for up to 100 ticks.
int currTick = 0;
double w = 0.0;
double cal()
{
   double w = 0;
    if(A2 == 1)
    {
        w += 0.5;
    }
    if(A1 == 1)
    {
        w += 0.25;
    }
    if(A0 == 1)
    {
        w += 0.125;
    }
    if(A3 == 1)
    {
        w += 1;
    }
    return w;
}

void SetAInputs() {
   A0 = (inputValues[currTick][7] == '0') ? 0 : 1;
   A1 = (inputValues[currTick][6] == '0') ? 0 : 1;
   A2 = (inputValues[currTick][5] == '0') ? 0 : 1;
   A3 = (inputValues[currTick][4] == '0') ? 0 : 1;
   A4 = (inputValues[currTick][3] == '0') ? 0 : 1;
   A5 = (inputValues[currTick][2] == '0') ? 0 : 1;
   A6 = (inputValues[currTick][1] == '0') ? 0 : 1;
   A7 = (inputValues[currTick][0] == '0') ? 0 : 1;
}

void InitializeOutputs() {
   // B = 0 itself doesn't work, so assign all bits individually
   B7 = 0; B6 = 0; B5 = 0; B4 = 0;
   B3 = 0; B2 = 0; B1 = 0; B0 = 0;
}

void TimerTick() {
   printf("%d: %d%d%d%d%d%d%d%d\n",currTick, B7,B6,B5,B4,B3,B2,B1,B0);
   currTick += 1;
   SetAInputs();
   TimerISR();
}

// END Items to mimick RIMS


// task struct used by the task scheduler.
typedef struct task {
  int state; // Current state of the task
  unsigned long period; // Rate at which the task should tick
  unsigned long elapsedTime; // Time since task's previous tick
  int (*TickFct)(int); // Function to call for task's tick
} task;

task tasks[1];



// Tasks parameters; don't modify this code 
const unsigned char tasksNum = 1;
const unsigned long tasksPeriodGCD = 500;
const unsigned long periodPattrnRec = 500;

// Task scheduler code.
void TimerISR() {
   
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) { // Heart of the scheduler code
     if ( (tasks[i].elapsedTime >= tasks[i].period)) { // Ready
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = 0;
     }
     tasks[i].elapsedTime += tasksPeriodGCD;
  }
}

enum PR_States { PR_SMStart, PR_s1 };


// State transition functions for the task;  TODO: complete the implementation for this function
int TickFct_PattrnRec(int state) {
  switch(state) { // Transitions
     case PR_SMStart: // Initial transition
        B0 = 0; // Initialization behavior
        state = PR_s1;
        break;
     case PR_s1:
        state = PR_s1;
        break;
     default:
        state = PR_SMStart;
   } // Transitions

  switch(state) { // State actions
     case PR_s1:
         
        if(A6)
        {
            w = cal();
            cout << "w: " << w << endl;
            if(A7)
            {
               B1 = 1;
               break;
            }

            //white
            if(!A5 && A4)
            {
               
                if(w >= 1.25)
                {
                  B0 = 1;
                  break;
                }
                else
                {
                  B4 = 1;
                  break;
                }
            }

            //brown
            if(A5 && A4)
            {
               
               if(w <= 0.75)
               {
                  B2 = 1;
                  B0 = 0;
                  break;
               }
               B0 = 0;
               B1 = 0;
               B3 = 0;
               B4 = 0;
               B5 = 0;
               B6 = 0;
            } 

            //black
            if(A5 && !A4)
            {
               if(w <= 0.75)
               {
                  B3 = 1;
                  B0 = 0;
                  break;
               }
               else if(w < 1.25)
               {
                  B6 = 1;
               }
               B0 = 0;
               B5 = 0;
               B2 = 0;
               B1 = 0;
            }

            //green
            if(!A5 && !A4)
            {
               if(w < 1.25 && w > 0.75)
               {
                  B0 = 0;
                  B5 = 1;
                  B4 = 0;
               }
            }
        }
        break;
     
     default:
        break;
  } // State actions
  return state;
}


int main() {
   // The items below mimick RIMS by pre-reading all input vectors; don't modify this code 
   int numInputVectors; 
   scanf("%d", &numInputVectors); // Reads input test vectors

   for (int i = 0; i < numInputVectors; ++i) {
      scanf("%s", inputValues[i]);
   }

   SetAInputs(); // Set initial values for input A
   InitializeOutputs();

   unsigned char i=0;
   tasks[i].state = PR_SMStart;
   tasks[i].period = periodPattrnRec;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_PattrnRec;
  
   
   while (currTick < numInputVectors) 
      TimerTick(); // This function prints all B output values and updates a global tick variable and calls the timer ISR
   
   return 0;
}
