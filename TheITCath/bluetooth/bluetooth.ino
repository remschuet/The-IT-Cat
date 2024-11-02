#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#define BOUTON_PIN 13

const int TICKS_PER_DIRECTION = 2000;
const int DELAY_BEFORE_FORWARD = 8000;

bool directionIsFront = false;
bool motorIsMoving = false;

int stepNumber = 0;
int tickCount = 0;

void setup() {
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(BOUTON_PIN, INPUT);
  Serial.begin(9600);
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

void loop() {
  // Vérifier si le bouton est appuyé pour démarrer un cycle
  if (digitalRead(BOUTON_PIN) == LOW && !motorIsMoving) {
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
