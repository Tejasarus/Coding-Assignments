#include <dht.h>
#include <Servo.h>


Servo garage_servo;
Servo lock_servo;

dht DHT;



#define led1 2
#define temp_sensor 5
#define but1 4
#define echoPin 53 
#define trigPin 52
#define button1 7
#define garage_pin 3
#define lock_pin 8
#define button2 9
#define warm 50
#define cool 44

bool temp_asked = false;
bool temp_read = false;
bool led_on = false;
int distance;
long duration;
int buttonPushed1 = 0;
int buttonPushed2 = 0;
bool lock_open = false;
bool garage_open = false;
String str;
int light_int = 1;
int garage_int;
int lock_int;
int temp_int;
int actual_temperature;
int sensor;
int wanted_temp;

////////////////////////////// message ////////////////////////////
void message()
{
   if (Serial.available() > 0) 
    {
      str = Serial.readStringUntil('\n');
      light_int = str.charAt(0) - '0';
      lock_int = str.charAt(2) - '0';
      garage_int = str.charAt(4) - '0';
      temp_int = str.substring(6).toInt();
      if(temp_int != 2)
      {
        temp_asked = true;
      }
      else
      {
        temp_asked = false;
      }
    }
   // Serial.println(String(sensor) + String(actual_temperature));
    //Serial.print("hello");
}

//////////////////////////// light checker //////////////////////
void check_light()
{
  if(light_int == 1) 
  {
    digitalWrite(led1, HIGH);
    Serial.println("light on");
  }
  else
  {
    digitalWrite(led1, LOW);
    //Serial.println("light off");
  }
      
}

/////////////////////////////// check temp //////////////////////////
void check_temp()
{
  int chk = DHT.read11(temp_sensor);
  
  //Serial.print("Temperature = ");
  int temp_F = (DHT.temperature * 9/5) + 32;
  actual_temperature = temp_F;
  if(!temp_read)
  {
    wanted_temp = temp_F;
    temp_read = true;
  }
  if(temp_int == 1 || temp_int == 0)
  {
    
    if(temp_asked)
    {
      if(temp_int == 1)
      {
        ++wanted_temp;
      }
      else
      {
        --wanted_temp;
      }
      //Serial.println(wanted_temp);
      Serial.print(temp_F);
      temp_asked = false;
    }
    
  }
  if(wanted_temp > temp_F)
  {
    digitalWrite(cool,HIGH);
    digitalWrite(warm,LOW);
  }
  else if(wanted_temp < temp_F)
  {
   digitalWrite(cool,LOW);
    digitalWrite(warm,HIGH);
  }
  else
  {
    digitalWrite(cool,LOW);
    digitalWrite(warm,LOW);
  }
  
  
}
////////////////////////////////////pulse/////////////////////////////
unsigned long Pulse(int pin, int value, int ping) 
{  
    unsigned long current_time = micros();
    while(digitalRead(pin) == value) 
    {
      if (micros() - current_time > (ping*1000)) 
      {
        return 0;
      }
    }
    current_time = micros(); 
    while (digitalRead(pin) != value) 
    {
      if (micros() - current_time > (ping*1000)) 
      { 
        return 0;
      }
    }
    current_time = micros();
    while (digitalRead(pin) == value) 
    { 
      if (micros() - current_time > (ping*1000))
      {
        return 0;
      }
    }
    return micros() - current_time;
}
/////////////////////////////// ultrasonic /////////////////////

void ultrasonic()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = Pulse(echoPin, HIGH,37);
  distance = duration * 0.034 / 2;
  //Serial.println(distance);
}

//////////////////////////////// garage door ////////////////////////
void garage_door()
{
  //garage_open
  //garage_servo.write(90);
  //Serial.println(digitalRead(button1));
  if(garage_int == 1)
  {
    if(distance > 10)
    {
      garage_servo.write(180);
      Serial.println("yess");
      sensor = 0;
    }
    else
    {
      Serial.println("no");
    }
  }
  else if(garage_int == 0)
  {
    garage_servo.write(0);
    sensor = 1;
  }
  garage_int = 2;
}

////////////////////////////// lock ///////////////////////
void lock_door()
{
  if(lock_int == 1)
  {
    lock_servo.write(180);
  }
  else if(lock_int == 0)
  {
    lock_servo.write(0);
  }
}

//////////////////////////// states ///////////////////////////
typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 6; //number of states
task tasks[tasksNum];

///////////////////////// light control state ///////////////////////

enum SM1_States{SM1_INIT,lights};
int SM1_Tick(int state1)
{
  switch (state1)
  {
    case SM1_INIT:
      state1 = lights;
      break;
    
   
    case lights:
      state1 = lights;
      break;
  }

  switch (state1)
  {
    case SM1_INIT:
      break;
    
    case lights:
      check_light();
      break;
  }

  return state1;
}

///////////////////////// temperature state ///////////////////////

enum SM2_States{SM2_INIT,temp};
int SM2_Tick(int state2)
{
  switch (state2)
  {
    case SM2_INIT:
      state2 = temp;
      break;
    
   
    case temp:
      state2 = temp;
      break;
  }

  switch (state2)
  {
    case SM2_INIT:
      break;
    
    case temp:
      check_temp();
      break;
  }

  return state2;
}

///////////////////////ultrasonic state////////////////////////////
enum SM3_States{SM3_INIT,ultra};
int SM3_Tick(int state3)
{
  switch (state3)
  {
    case SM3_INIT:
      state3 = ultra;
      break;
    
    case ultra:
      state3 = ultra;
      break;
  }

  switch (state3)
  {
    case SM3_INIT:
      break;
    
    case ultra:
      ultrasonic();
      break;
  }

  return state3;
}

////////////////////////////// garage door state///////////////////////
enum SM4_States{SM4_INIT,garage};
int SM4_Tick(int state4)
{
  switch (state4)
  {
    case SM4_INIT:
      state4 = garage;
      break;
    
    
    case garage:
      state4 = garage;
      break;
  }

  switch (state4)
  {
    case SM4_INIT:
      break;
    
    case garage:
      garage_door();
      break;
  }

  return state4;
}

/////////////////////// lock servo state /////////////////////////////
enum SM5_States{SM5_INIT,lock};
int SM5_Tick(int state5)
{
  switch (state5)
  {
    case SM5_INIT:
      state5 = lock;
      break;
    
    
    case lock:
      state5 = lock;
      break;
  }

  switch (state5)
  {
    case SM5_INIT:
      break;
    
    case lock:
      lock_door();
      break;
  }

  return state5;
}
//////////////////////// recieve message ////////////////////////
enum SM6_States{SM6_INIT,mes};
int SM6_Tick(int state6)
{
  switch (state6)
  {
    case SM6_INIT:
      state6 = mes;
      break;
    
    
    case lock:
      state6 = mes;
      break;
  }

  switch (state6)
  {
    case SM6_INIT:
      break;
    
    case mes:
      message();
      break;
  }

  return state6;
}
/////////////////////// setup ///////////////////////////////////
void setup() {
  
  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 500; 
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  ++i;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 1000; 
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 10; 
  tasks[i].elapsedTime = 0; 
  tasks[i].TickFct = &SM3_Tick;
  ++i;
  tasks[i].state = SM4_INIT;
  tasks[i].period = 0; 
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM4_Tick;
  ++i;
  tasks[i].state = SM5_INIT;
  tasks[i].period = 0; 
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM5_Tick;
  ++i;
  tasks[i].state = SM6_INIT;
  tasks[i].period = 0; 
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM6_Tick;

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(but1, INPUT);
  garage_servo.attach(garage_pin);
  lock_servo.attach(lock_pin);
  pinMode(button1,INPUT_PULLUP);
  pinMode(button2,INPUT_PULLUP);
  pinMode(warm, OUTPUT);
  pinMode(cool,OUTPUT);
  
}

/////////////////////////////////// loop ///////////////////////////////

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) 
  {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }

}
