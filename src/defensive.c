#include "main.h"


void defensive(){

moveForward(1800, 100);
turnRight(90, 100);
moveForward(400, 100);
intake(100);
delay(3000);

stopFlywheel();

moveBackward(400, 100);
turnRight(-90, 100);
moveBackward(1800, 100);

}
