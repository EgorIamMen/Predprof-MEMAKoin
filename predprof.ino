#define Button 30
#define STEP_PIN 5 
#define DIR_PIN 2
#define TIME_DREB 50

#include <Servo.h> 

Servo servo_left; 
Servo servo_middle;
Servo servo_right;
Servo servo_d; 

unsigned long timing;
unsigned long tm_dreb; 

void setup()  
{ 
  Serial.begin(9600); 

  pinMode(STEP_PIN, OUTPUT); 
  pinMode(DIR_PIN, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
 
  servo_left.attach(25); 
  servo_middle.attach(27); 
  servo_right.attach(29);
  servo_d.attach(33);
}

int prevValue = 0; 
int key = 0; 
bool res = 0;
byte step_time = 20000; // чем больше показатель, тем меньше скорость вращения 
unsigned long step_timer; 
const int totalSteps = 2000; 

void moveSteps(int direction, int totalSteps) {
  // Установить направление вращения
  if (direction == 1) {
    digitalWrite(DIR_PIN, HIGH); // Вперед
  } else {
    digitalWrite(DIR_PIN, LOW); // Назад
  }

  // Выполнить указанное количество шагов
  for (int i = 0; i < totalSteps; i++) {
    if (micros() - step_timer > step_time) {
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(1000); // Задержка для обеспечения стабильности импульса
      digitalWrite(STEP_PIN, LOW);
      delay(1);
    }
  }
}

void loop(void) {  
  servo_left.write(90);
  servo_middle.write(90);
  servo_right.write(90);
  int currentValue = !digitalRead(Button); 
  if (res == 0)  { 
    if (currentValue == 1 and prevValue == 0) { 
      prevValue = 1; 
      tm_dreb = millis(); 
    }  
    else if (currentValue == 0 and prevValue == 1 and (millis() - tm_dreb) > TIME_DREB) {
      res = 1; 
      prevValue = 0;
    } 
  } 
  else  { 
    servo_left.write(0);
    servo_middle.write(0);
    servo_right.write(0);
    delay(2000);
    servo_left.write(90);
    servo_middle.write(90);
    servo_right.write(90);
    moveSteps(1, totalSteps);
    delay(4000);
    moveSteps(-1, totalSteps);
    servo_d.write(0);
    delay(4000);
    servo_d.write(90);
    res = !res;
  } 
}