#include <AlfredoConnect.h>
#include <Alfredo_NoU2.h>

NoU_Motor wheelMotor(4);
int count;

void setup() {

    RSL::initialize();
    RSL::setState(RSL_ENABLED);
}

void loop() {
    float throttle = pow((count / 10000), 3);
    //wheelMotor.set(throttle);

    delay(1);
    count++;
    RSL::update();
}
