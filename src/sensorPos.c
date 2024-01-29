
#include "main.h"

int sensorValue = 0;

void getSensorPosition(double sensor){
    if(sensor == 'left'){
        sensorValue = rotation_get_position(ROTATION_LEFT_PORT);
    }
    if(sensor == 'right'){
        sensorValue = rotation_get_position(ROTATION_RIGHT_PORT);
    }   
}
