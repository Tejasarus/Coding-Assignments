#include <stdio.h>
#include <sys/time.h>

void TimerISR();

struct timeval timer;
struct timeval start_timer;

// Return timer in milliseconds
unsigned long TimerRead(){
   gettimeofday(&timer, NULL);
   return (timer.tv_sec - start_timer.tv_sec) * 1000 + (timer.tv_usec - start_timer.tv_usec) / 1000 ;
}

void TimerOn(){
   gettimeofday(&start_timer, NULL);
}

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

   currTick += 1;

   TimerISR();
}

// END Items to mimick RIMS


// task struct used by the task scheduler. TODO: add another field for wcet of tasks
typedef struct task {
  int state; // Current state of the task
  unsigned long period; // Rate at which the task should tick
  unsigned long elapsedTime; // Time since task's previous tick
  int (*TickFct)(int); // Function to call for task's tick
  unsigned long WCET;
} task;

task tasks[3];



// Tasks parameters; don't modify this code 
const unsigned char tasksNum = 3;
const unsigned long tasksPeriodGCD = 50;
const unsigned long tasksPeriodLCM = 1800;
const unsigned long periodBlinkLED = 150;
const unsigned long periodCtrLED = 450;
const unsigned long periodThreeLEDs = 200;

// Task scheduler code. 
// TODO: WCET calculation for each task, TimerRead() returns a unsigned long
void TimerISR() {
    
  unsigned char i;

  for (i = 0; i < tasksNum; ++i) { // Heart of the scheduler code
     
     if ( (tasks[i].elapsedTime >= tasks[i].period)) { // Ready
        unsigned long start = TimerRead();
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = 0;
        unsigned long end = TimerRead();

        unsigned long wcet = end - start;
        tasks[i].WCET = wcet;
     }     
   
     tasks[i].elapsedTime += tasksPeriodGCD;
  }
   

}

enum BL_States {BL_s1 };
int TickFct_BlinkLED(int state);

enum TL_States {TL_s1};
int TickFct_ThreeLEDs(int state);

enum CL_States {CL_s1};
int TickFct_CtrLED(int state);


// State transition functions for the tasks; don't modify this code 
int TickFct_BlinkLED(int state) {
  
  unsigned int i;
  
  switch(state) { // Transitions
     case BL_s1:
        state = BL_s1;
        break;
     default:
        state = BL_s1;
   } // Transitions

  switch(state) { // State actions
     case BL_s1:
      for (i = 0; i < 1000000; i++)
      B0 = 1;
    for (i = 0; i < 10000000; i++)
      B0 = 0;
    
        break;
     default:
        break;
  } // State actions
  return state;
}

int TickFct_ThreeLEDs(int state) {
  
  unsigned int i;
  
  switch(state) { // Transitions
     case TL_s1: // Initial transition
        state = TL_s1;
        break;
     default:
        state = TL_s1;
   } // Transitions

  switch(state) { // State actions
     case TL_s1:  
    for (i = 0; i < 1000000; i++)
      B1 = 1;
    for (i = 0; i < 500000; i++)
      B1 = 0;
        break;
     default:
        break;
  } // State actions
  return state;
}


int TickFct_CtrLED(int state) {
   
  unsigned int i;
   
  switch(state) { // Transitions
     case CL_s1:
        state = CL_s1;
        break;
     default:
        state = CL_s1;
   } // Transitions

  switch(state) { // State actions
     case CL_s1:    
    for (i = 0; i < 5000000; i++)
      B2 = 1;
    for (i = 0; i < 100000; i++)
      B2 = 0;
    
        break;
     default:
        break;
  } // State actions
  return state;
}


int main() {
   // The items below mimick RIMS by pre-reading all input vectors; don't modify this code 
   int numInputVectors; 
   
   numInputVectors = tasksPeriodLCM/tasksPeriodGCD;

   // TODO: initialize the WCET field for the tasks when creating them
   unsigned char i = 0;
   tasks[i].state = BL_s1;
   tasks[i].period = periodBlinkLED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_BlinkLED;
   tasks[i].WCET = 0;
   ++i;
   tasks[i].state = TL_s1;
   tasks[i].period = periodThreeLEDs;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_ThreeLEDs;
   tasks[i].WCET = 0;
   ++i;
   tasks[i].state = CL_s1;
   tasks[i].period = periodCtrLED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_CtrLED;
   tasks[i].WCET = 0;
   // Start the timer 
   TimerOn();
   
   unsigned long cur_time;
   
   while (currTick < numInputVectors) 
   {
      
      cur_time = TimerRead();
      
    // This function calls the timer ISR    
      TimerTick();   
      
    // Wait for the timer so that tasksPeriodGCD (50ms) is passed
      while(TimerRead() - cur_time <  tasksPeriodGCD);
      
   }
   
   // TODO: calculate and print utilization
   for(int i = 0; i < 3; ++i)
   {
    printf("Task %d WCET: %lu ms\n", i, tasks[i].WCET);
   }
   return 0;
}
