#include "RIMS.h"
volatile int TimerFlag = 0;
const double Kp = 0.05;
const double Ki = 0.001;
const double Kd = 2.5;
double error;
double integ
double deriv;
double prev = 0;
int desired;
int actual;
int actuator;

void PID()
{
    error = desired - actual;
    integ += error;

    if (integ > 255) 
    {
        integ = 255;
    } 
    else if (integ < 0) 
    {
        integ = 0;
    }

    deriv = error - prev;
    actuator = Kp * error + Ki * integ + Kd * deriv;

    if (actuator > 255) 
    {
        actuator = 255;
    } 
    else if (actuator < 0) 
    {
        actuator = 0;
    }

    prev = error;


}

void TimerISR() {
   TimerFlag = 1;
}

int main(){
   TimerSet(1000);
   TimerOn();
   while(1){
        desired = A3 * 8 + A2 * 4 + A1 * 2 + A0;
        actual = A7 * 8 + A6 * 4 + A5 * 2 + A4; 
        PID();
        B0 = actuator & 0b0001;
        B1 = (actuator >> 1) & 0b0001;
        B2 = (actuator >> 2) & 0b0001;
        B3 = (actuator >> 3) & 0b0001;
        while(!TimerFlag);
        TimerFlag=0;
   }
}
