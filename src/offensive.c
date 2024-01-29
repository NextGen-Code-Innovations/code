#include "main.h"



void offensive(){

moveForward(200, 100);
turnRight(90, 100);
moveForward(600, 100);
intake(100);
moveForward(600, 100);

stopFlywheel();

moveBackward(1200, 100);
turnRight(-90, 100);
moveBackward(200, 100);

}
