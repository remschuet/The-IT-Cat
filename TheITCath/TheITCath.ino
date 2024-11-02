#include <SoftwareSerial.h>

#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#define BLUETOOTH_DATA 5
#define BLEUTOOTH_INPUT 6

SoftwareSerial BluetoothSerial(BLEUTOOTH_INPUT, BLUETOOTH_DATA);

const int TICKS_PER_DIRECTION = 2000;
const int DELAY_BEFORE_FORWARD = 15000;

bool directionIsFront = false;
bool motorIsMoving = false;

int stepNumber = 0;
int tickCount = 0;

void setup() {
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(BLUETOOTH_DATA, OUTPUT);
  pinMode(BLEUTOOTH_INPUT, INPUT);
  Serial.begin(9600);
  BluetoothSerial.begin(9600);
}

void startCycle(){
  motorIsMoving = true;
  directionIsFront = false;
  tickCount = 0;
  Serial.println("Start movement");
}

void resetCycle(){
  directionIsFront = !directionIsFront;
  tickCount = 0;
}

void endCycle(){
  resetCycle();
  motorIsMoving = false;
  Serial.println("End movement");
}

void changeDirection(){
  resetCycle();
  Serial.println("Change direction");
  delay(DELAY_BEFORE_FORWARD);
}

bool isBluetoothData(){
  char var = 'z';
  if (BluetoothSerial.available()){
    var = (char) BluetoothSerial.read();
  }
  return var != 'z';
}

void loop() {
  // Vérifier si le bouton est appuyé pour démarrer un cycle
  if (isBluetoothData() && !motorIsMoving) {
    startCycle();
  }

  if (motorIsMoving) {
    OneStep(directionIsFront);
    delay(2);
    tickCount++;
    
    if (directionIsFront == true && tickCount >= TICKS_PER_DIRECTION) {
      endCycle();
    }

    if (tickCount >= TICKS_PER_DIRECTION) {
      changeDirection();
    }
  
  }
}

void OneStep(bool dir) {
  if (dir) {  // Avancer
    switch (stepNumber) {
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
    }
  } else {  // Reculer
    switch (stepNumber) {
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
    }
  }

  // Incrémenter le compteur de pas pour alterner les phases
  stepNumber++;
  if (stepNumber > 3) {
    stepNumber = 0;
  }
}
