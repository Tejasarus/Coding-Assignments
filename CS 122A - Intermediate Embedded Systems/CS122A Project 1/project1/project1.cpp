#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define MAGENTA 0xF81F

MCUFRIEND_kbv tft;

int p1_x;
int p1_y = 300;

int p2_x;
int p2_y;

int ball_x = 120;
int ball_y = 160;

#define joystick1_sw A7
#define joystick1_x A6
#define joystick1_y A8

#define joystick2_sw A11
#define joystick2_x A9
#define joystick2_y A10


/////////////////////////// move player(s) funcitons ///////////////////////
void move_p1()
{
  int x1 = analogRead(joystick1_x);
  x1 = x1/5;
  tft.fillRect(x1,300,50,10,WHITE);
  //boundary boxes? idk what they're called
  tft.fillRect(x1 + 50,300,100,10,RED);
  tft.fillRect(x1 - 100,300,100,10,MAGENTA);

  /*
  Serial.print(x1);
  Serial.print(" ");
  Serial.println(y1);
  */
}

void move_p2()
{
  int x2 = analogRead(joystick2_x);
  x2 = x2/5;
  tft.fillRect(x2,10,50,10,WHITE);
  //boundary boxes? idk what they're called
  tft.fillRect(x2 + 50,10,100,10,RED);
  tft.fillRect(x2 - 100,10,100,10,MAGENTA);

  /*
  Serial.print(x2);
  Serial.print(" ");
  Serial.println(y2);
  */
}

//////////////////////////// ball movement ///////////////////////
void move_ball()
{
  tft.fillRect(ball_x, ball_y, 15, 15, WHITE);
  tft.fillRect(ball_x - 5, ball_y - 5, 15, 5, BLACK);
  tft.fillRect(ball_x - 5, ball_y - 5, 5, 15, BLACK);
  ball_x += 5;
  ball_y += 5;
  /*
  tft.fillCircle(ball_x,ball_y,10,WHITE);
  tft.fillCircle(ball_x - 15,ball_y - 15,10,BLACK);
  ball_x += 15;
  ball_y += 15;
  */
}
//////////////////////////// states ///////////////////////////
typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 3; //number of states
task tasks[tasksNum];

///////////////////////// move player 1 state ///////////////////////

enum SM1_States{SM1_INIT,move_player1};
int SM1_Tick(int state1)
{
  switch (state1)
  {
    case SM1_INIT:
      state1 = move_player1;
      break;
    
    //loop, constantly get input from joystick
    case move_player1:
      state1 = move_player1;
      break;
  }

  switch (state1)
  {
    case SM1_INIT:
      break;
    
    case move_player1:
      move_p1();
      break;
  }

  return state1;
}

/////////////////////// move player 2 state ////////////////////////////
enum SM2_States{SM2_INIT,move_player2};
int SM2_Tick(int state2)
{
  switch (state2)
  {
    case SM2_INIT:
      state2 = move_player2;
      break;
    
    //loop, constantly get input from joystick
    case move_player2:
      state2 = move_player2;
      break;
  }

  switch (state2)
  {
    case SM2_INIT:
      break;
    
    case move_player2:
      move_p2();
      break;
  }

  return state2;
}

////////////////////////// move ball state ////////////////////////
enum SM3_States{SM3_INIT,move_b};
int SM3_Tick(int state3)
{
  switch (state3)
  {
    case SM3_INIT:
      state3 = move_b;
      break;
    
    //loop, constantly get input from joystick
    case move_b:
      state3 = move_b;
      break;
  }

  switch (state3)
  {
    case SM3_INIT:
      break;
    
    case move_b:
      move_ball();
      break;
  }

  return state3;
}

/////////////////////// setup ///////////////////////////////////
void setup() {
  
  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 0; 
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  ++i;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 0; 
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  ++i;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 25; 
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;

  //screen settings
  tft.reset();
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(0);
  tft.fillScreen(BLACK);

  Serial.begin(9600);
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
