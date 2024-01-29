#include "main.h"


void drivetrain(double direction, double distance, double speed){
    // fwd = 1 ;; back = 2 ;; right = 11 ;; left = 12
    int var1 = 1;
    int var2 = 1;
    int var3 = 1;
    int var4 = 1;
    if(direction == 1){
        return 0;
    } else if(direction == 2){
        var1 = -1;
        var2 = -1;
        var3 = -1;
        var4 = -1;
    } else if(direction == 11){
        var1 = -1;
        var2 = 1;
        var3 = -1;
        var4 = 1;
    } else if(direction == 12){
        var1 = 1;
        var2 = -1;
        var3 = 1;
        var4 = -1;
    }

    motor_move_absolute(FRONT_LEFT_MOTOR, distance, var1 * speed);
    motor_move_absolute(FRONT_RIGHT_MOTOR, distance, var2 * speed);
    motor_move_absolute(BACK_LEFT_MOTOR, distance, var3 * speed);
    motor_move_absolute(BACK_RIGHT_MOTOR, distance, var4 * speed);
}

void moveForward(double dist, double speed){
    motor_move_absolute(FRONT_LEFT_MOTOR, dist, speed);
    motor_move_absolute(FRONT_RIGHT_MOTOR, dist, speed);
    motor_move_absolute(BACK_LEFT_MOTOR, dist, speed);
    motor_move_absolute(BACK_RIGHT_MOTOR, dist, speed);
}

void moveBackward(double dist, double speed){
    motor_move_absolute(FRONT_LEFT_MOTOR, dist, -(speed));
    motor_move_absolute(FRONT_RIGHT_MOTOR, dist, -(speed));
    motor_move_absolute(BACK_LEFT_MOTOR, dist, -(speed));
    motor_move_absolute(BACK_RIGHT_MOTOR, dist, -(speed));
}

void turnLeft(double angle, double speed){
    motor_move_absolute(FRONT_LEFT_MOTOR, angle, speed);
    motor_move_absolute(FRONT_RIGHT_MOTOR, angle, -(speed));
    motor_move_absolute(BACK_LEFT_MOTOR, angle, speed);
    motor_move_absolute(BACK_RIGHT_MOTOR, angle, -(speed));
}

void turnRight(double angle, double speed){
    motor_move_absolute(FRONT_LEFT_MOTOR, angle, -(speed));
    motor_move_absolute(FRONT_RIGHT_MOTOR, angle, speed);
    motor_move_absolute(BACK_LEFT_MOTOR, angle, -(speed));
    motor_move_absolute(BACK_RIGHT_MOTOR, angle, speed);
}

void launch(double time){
    motor_move(FLY_WHEEL_MOTOR, 127);
    delay(time);
    motor_brake(FLY_WHEEL_MOTOR);
}

void intake(double speed){
    motor_move(FLY_WHEEL_MOTOR, -(speed));
}

void stopFlywheel(){
    motor_brake(FLY_WHEEL_MOTOR);
}
