#include <AlfredoConnect.h>
#include <Alfredo_NoU2.h>

int encoderAPIN = 16;
int encoderBPIN = 17;
int buzzerButtonPIN = 25;


//outcome = [0,-1,1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0];
//last_AB = 0b00;
byte signalA;
byte signalB;
int encoderPosition;


int buttonState;
float throttle;

NoU_Motor wheelMotor(4);
NoU_Motor relaySwitch(3);
float count;

void setup() {
    Serial.begin(9600);

    pinMode(buzzerButtonPIN, INPUT_PULLUP);
    pinMode(encoderAPIN, INPUT);
    pinMode(encoderBPIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(encoderAPIN),signalA_ISR,CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderBPIN),signalB_ISR,CHANGE);


    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}

void loop() {
    buttonState = digitalRead(buzzerButtonPIN);
    signalA = digitalRead(encoderAPIN);
    signalB = digitalRead(encoderBPIN);
    throttle = 1;

    if (!buttonState) {
        wheelMotor.set(throttle);
    } else {
        wheelMotor.set(0);
    }
    Serial.println(signalA);

    count = count + 0.00001;
    RSL::update();
    delay(1);
}

void signalA_ISR() {
  signalA = !signalA;
}

void signalB_ISR() {
  signalB = !signalB;
}