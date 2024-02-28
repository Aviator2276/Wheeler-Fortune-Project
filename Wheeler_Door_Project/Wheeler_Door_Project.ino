#include <AlfredoConnect.h>
#include <Alfredo_NoU2.h>

NoU_Motor wheelMotor(4);
NoU_Motor relaySwitch(3);
int buzzerButtonPIN = 25;

const int encoderAPIN = 16;
const int encoderBPIN = 17;
volatile int encoderPosition = 0;

bool isRunning = false;
bool lightsActivated = false;

int buttonState;
float throttle;

void setup() {
    Serial.begin(9600);

    encoderPosition = 0;

    pinMode(buzzerButtonPIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(encoderAPIN), ISR_A, CHANGE);

    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}
void loop() {
    buttonState = digitalRead(buzzerButtonPIN);

    if (!buttonState && !isRunning) {
      runFunctions();
    }

    Serial.println(encoderPosition);
    RSL::update();
}

void runFunctions() {
  isRunning = true;
  delay(3000);
  spin();
  delay(7000);
  stop();
  delay(20000);
  reset();
}


void spin() {
  throttle = 1;
  wheelMotor.set(throttle);
}

void stop() {
  for (float power = 1; power > 0; power = power - 0.02) {
    wheelMotor.set(power);
    delay(100);
    if (power <= 0.2 && !lightsActivated) {
      lights();
    }
  }
  wheelMotor.set(0);
}

void lights() {
  lightsActivated = true;
  relaySwitch.set(1);
}

void reset() {
  isRunning = false;
  lightsActivated = false;
  relaySwitch.set(0);
  wheelMotor.set(0);
}


void ISR_A() {
  if (digitalRead(encoderAPIN) == digitalRead(encoderBPIN)) {
    encoderPosition++;
  } else {
    encoderPosition--;
  }
}