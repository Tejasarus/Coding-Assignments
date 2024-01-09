#include <stdio.h>


void TimerISR();
void EnableDisableTasks();

// BEGIN Items to mimick RIMS. Don't modify this code. 

unsigned short A7,A6,A5,A4,A3,A2,A1,A0; // Note: Setting or reading A or B as a group, as in B = 0, isn't supported
unsigned short B7,B6,B5,B4,B3,B2,B1,B0;
char inputValues[100][8]; // Inputs A7..A0 for up to 100 ticks.
int currTick = 0;

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


// task struct used by the task scheduler. TODO: add another field for enabling/disabling tasks
typedef struct task {
  int state; // Current state of the task
  unsigned long period; // Rate at which the task should tick
  unsigned long elapsedTime; // Time since task's previous tick
  int (*TickFct)(int); // Function to call for task's tick
  int enabled;
} task;

task tasks[3];



// Tasks parameters; don't modify this code 
const unsigned char tasksNum = 3;
const unsigned long tasksPeriodGCD = 500;
const unsigned long periodBlinkLED = 500;
const unsigned long periodCtrLED = 500;
const unsigned long periodThreeLEDs = 500;

// Task scheduler code. TODO: Modify this function to check whether tasks are enabled
void TimerISR() {
   
  //TODO: call EnableDisableTasks function before scheduling tasks. 
  //TODO: And, you'll  want to modify the heart of the scheduler code to avoid executing disabled tasks
  EnableDisableTasks();
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) { // Heart of the scheduler code
     if ( (tasks[i].elapsedTime >= tasks[i].period)) { // Ready
            if(tasks[i].enabled == 1)
            {
                tasks[i].state = tasks[i].TickFct(0);
                tasks[i].elapsedTime = 0;
            }
            else
            {
                tasks[i].state = tasks[i].TickFct(tasks[i].state);
                tasks[i].elapsedTime = 0;
            }
            

        
     }
     tasks[i].elapsedTime += tasksPeriodGCD;
  }
}

enum BL_States { BL_SMStart, BL_s1 };
int TickFct_BlinkLED(int state);

enum TL_States { TL_SMStart, TL_s1, TL_s2, TL_s3 };
int TickFct_ThreeLEDs(int state);

enum CL_States { CL_SMStart, CL_s1, CL_s2, CL_s3, CL_s4 };
int TickFct_CtrLED(int state);


// State transition functions for the tasks; don't modify this code 
int TickFct_BlinkLED(int state) {
  switch(state) { // Transitions
     case BL_SMStart: // Initial transition
        B0 = 0; // Initialization behavior
        state = BL_s1;
        break;
     case BL_s1:
        state = BL_s1;
        break;
     default:
        state = BL_SMStart;
   } // Transitions

  switch(state) { // State actions
     case BL_s1:
        B0 = !B0;
        break;
     default:
        break;
  } // State actions
  return state;
}

int TickFct_ThreeLEDs(int state) {
  switch(state) { // Transitions
     case TL_SMStart: // Initial transition
        state = TL_s1;
        break;
     case TL_s1:
        state = TL_s2;
        break;
     case TL_s2:
        state = TL_s3;
        break;
     case TL_s3:
        state = TL_s1;
        break;
     default:
        state = TL_SMStart;
   } // Transitions

  switch(state) { // State actions
     case TL_s1:
        B2 = 1; B3 = 0; B4 = 0;
        break;
     case TL_s2:
        B2 = 0; B3 = 1; B4 = 0;
        break;
     case TL_s3:
        B2 = 0; B3 = 0; B4 = 1;
        break;
     default:
        break;
  } // State actions
  return state;
}


int TickFct_CtrLED(int state) {
  switch(state) { // Transitions
     case CL_SMStart: // Initial transition
        state = CL_s1;
        break;
     case CL_s1:
        state = CL_s2;
        break;
     case CL_s2:
        state = CL_s3;
        break;
     case CL_s3:
        state = CL_s4;
        break;
     case CL_s4:
        state = CL_s1;
        break;
     default:
        state = CL_SMStart;
   } // Transitions

  switch(state) { // State actions
     case CL_s1:
        B7 = 0; B6 = 0;
        break;
     case CL_s2:
        B7 = 0; B6 = 1;
        break;
     case CL_s3:
        B7 = 1; B6 = 0;
        break;
      case CL_s4:
        B7 = 1; B6 = 1;
        break;  
     default:
        break;
  } // State actions
  return state;
}

void EnableDisableTasks()
{
   //TODO: implement this function which checks the values on A0, A1, and A2 
   // and based on that enables or disalbes tasks 0, 1, or 2 respectively
   if(A0 == 1)
   {
    tasks[0].enabled = 1;
   }
   else
   {
    tasks[0].enabled = 1;
   }
   if(A1 == 1)
   {
    tasks[1].enabled = 0;
   }
   else
   {
    tasks[1].enabled = 1;
   }
   if(A2 == 1)
   {
    tasks[2].enabled = 0;
   }
   else
   {
    tasks[2].enabled = 1;
   }
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

   // TODO: set the enabled field for the tasks when creating them. Tasks are enabled by default
   unsigned char i=0;
   tasks[i].state = BL_SMStart;
   tasks[i].period = periodBlinkLED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_BlinkLED;
   tasks[i].enabled = 1;
   ++i;
   tasks[i].state = TL_SMStart;
   tasks[i].period = periodThreeLEDs;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_ThreeLEDs;
   tasks[i].enabled = 1;
  
   ++i;
   tasks[i].state = CL_SMStart;
   tasks[i].period = periodCtrLED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_CtrLED;
   tasks[i].enabled = 1;
   
   while (currTick < numInputVectors) 
      TimerTick(); // This function prints all B output values and updates a global tick variable and calls the timer ISR
   
   return 0;
}
