#include "main.h"
int stopRachet = 0; 

void initialize() {
    //reversing
    motor_set_reversed(BACK_LEFT_MOTOR, BACK_LEFT_MOTOR_REV);
    motor_set_reversed(FRONT_LEFT_MOTOR, FRONT_LEFT_MOTOR_REV);
	//motor_set_reversed(BACK_RIGHT_MOTOR, BACK_RIGHT_MOTOR_REV);
    //motor_set_reversed(FRONT_RIGHT_MOTOR, FRONT_RIGHT_MOTOR_REV);
    motor_set_reversed(ARM_RIGHT, true);
    motor_set_reversed(support, false);
    motor_set_reversed(rachet, true);

    //brake mode
    motor_set_brake_mode(FRONT_RIGHT_MOTOR, MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(FRONT_LEFT_MOTOR, MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(BACK_RIGHT_MOTOR, MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(BACK_LEFT_MOTOR, MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(FLY_WHEEL_MOTOR, MOTOR_BRAKE_BRAKE);
    motor_set_brake_mode(ARM_LEFT, MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(ARM_RIGHT, MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(support, MOTOR_BRAKE_HOLD);
    motor_set_brake_mode(rachet, MOTOR_BRAKE_HOLD);

    //adi ports
    adi_port_set_config(1, ADI_DIGITAL_IN); // port a
    adi_port_set_config(PNU_PORT, ADI_DIGITAL_OUT);
}

void disabled() {}

void competition_initialize() {}

void autonomous(){
    if(adi_digital_read(1) == LOW){
        motor_move_absolute(BACK_RIGHT_MOTOR, 3850, 100);
        motor_move_absolute(BACK_LEFT_MOTOR, 3850, 100);
        motor_move_absolute(FRONT_LEFT_MOTOR, 3850, 100);
        motor_move_absolute(FRONT_RIGHT_MOTOR, 3850, 100);

        delay(2000);
        motor_move(FLY_WHEEL_MOTOR, -127);
        delay(1500);

        motor_move(BACK_RIGHT_MOTOR, -100);
        motor_move(BACK_LEFT_MOTOR, -100);
        motor_move(FRONT_LEFT_MOTOR, -100);
        motor_move(FRONT_RIGHT_MOTOR, -100);

        delay(1000);

        motor_brake(FLY_WHEEL_MOTOR); 
        motor_brake(BACK_LEFT_MOTOR);
        motor_brake(BACK_RIGHT_MOTOR);
        motor_brake(FRONT_LEFT_MOTOR);
        motor_brake(FRONT_RIGHT_MOTOR);

    } else if (adi_digital_read(1) == HIGH) {
        motor_move(FLY_WHEEL_MOTOR, -127);
        delay(500);

        motor_move_absolute(support, 100, 100);
        delay(20);

        motor_brake(support);
        motor_move(ARM_LEFT, -127);
        motor_move(ARM_RIGHT, -127);
        delay(3000);

        motor_brake(FLY_WHEEL_MOTOR);
        motor_brake(ARM_LEFT);
        motor_brake(ARM_RIGHT);
    }
}

void drive_FN(){  // this is the main drive function for the robot for op control -- DO NOT CHANGE
                  // You can change the direction under 'variables.h' setting section
    for (;;) {
        int y = controller_get_analog(CONTROLLER_MASTER, /*drivingReversed **/ ANALOG_LEFT_Y);
        int t = controller_get_analog(CONTROLLER_MASTER, /*turningReversed **/ ANALOG_RIGHT_X);
        if (y == 0 && t == 0) {
            motor_brake(FRONT_RIGHT_MOTOR);
            motor_brake(BACK_RIGHT_MOTOR);
            motor_brake(FRONT_LEFT_MOTOR);
            motor_brake(BACK_LEFT_MOTOR);

        } else {
            motor_move(FRONT_RIGHT_MOTOR, y - t);
            motor_move(FRONT_LEFT_MOTOR, y + t);
            motor_move(BACK_LEFT_MOTOR, y + t);
            motor_move(BACK_RIGHT_MOTOR, y - t);
        }
        task_delay(20);
    }
}

void FlyWheel_FN(){
    static bool launch_on = false;
    static bool rev_on = false;
    static bool in_on = false;

    for (;;) {
        if (controller_get_digital_new_press(CONTROLLER_MASTER, DIGITAL_A)) //launch
            launch_on = !launch_on;
        if (controller_get_digital_new_press(CONTROLLER_MASTER, DIGITAL_R2)) //out
            rev_on = !rev_on;
        if (controller_get_digital_new_press(CONTROLLER_MASTER, DIGITAL_R1)) //in
            in_on = !in_on;
        if (launch_on && !rev_on && !in_on) // launch
            motor_move(FLY_WHEEL_MOTOR, 125);
        else if (!launch_on && rev_on && !in_on) // out
            motor_move(FLY_WHEEL_MOTOR, -125);
        else if (!launch_on && !rev_on && in_on)  // in
            motor_move(FLY_WHEEL_MOTOR, 80);
        else
            motor_brake(FLY_WHEEL_MOTOR);
        task_delay(2);
    }
}

void ARM_FN(){
    for (;;) {
        if (controller_get_digital(CONTROLLER_MASTER, DIGITAL_L1)) {// up
            motor_move(ARM_LEFT, 60);
            motor_move(ARM_RIGHT, 60);
        } else if (controller_get_digital(CONTROLLER_MASTER, DIGITAL_L2)) { //down
            motor_move(ARM_LEFT, -60);
            motor_move(ARM_RIGHT, -60);
        } else {
            motor_brake(ARM_LEFT);
            motor_brake(ARM_RIGHT);
        }
        task_delay(2);
    }
}

void support_FN(){
    for (;;) {
        if (controller_get_digital(CONTROLLER_MASTER, DIGITAL_Y)){
            motor_move(support, 20);
        } else {
            motor_brake(support);
        }
        task_delay(2);
    }
}

void climb_FN(){
    for (;;) {
        if (controller_get_digital(CONTROLLER_MASTER, DIGITAL_UP)) {// engage
            motor_move_relative(rachet, 30, 100);
        } else if (controller_get_digital(CONTROLLER_MASTER, DIGITAL_DOWN)) { //down
            motor_move_relative(rachet, -30, 100);
        } else {
            motor_brake(rachet);
        }
        task_delay(2);
    }
}

void PNU_FN(){
    for (;;) {
        if(controller_get_digital(CONTROLLER_MASTER, DIGITAL_LEFT)) {
            adi_digital_write(PNU_PORT, HIGH);
        } else {
            adi_digital_write(PNU_PORT, LOW);
        }
        task_delay(2);
    }
}

void rachet_FN(){ // X and left engage otherwise timer
// 104000 ms is one second from end of game

    for (;;) {
        if(controller_get_digital(CONTROLLER_MASTER, DIGITAL_X) && controller_get_digital(CONTROLLER_MASTER, DIGITAL_LEFT)) {
            motor_move(rachet, 125);
        } else {
            motor_brake(rachet);
        }
        task_delay(2);
    }
}
void endgameRachet(){
    for(;;){
        delay(104000);
        motor_move(rachet, 125);
        delay(1000);
        motor_brake(rachet);
    }
}

void opcontrol(){  //----------------------------------------------------------- Threading
    task_create(endgameRachet, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "rachet engage ");
    task_create(drive_FN, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Drive");
    task_create(FlyWheel_FN, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Fly Wheel launch");
    task_create(ARM_FN, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Arm down");
    task_create(support_FN, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "support movement");
    task_create(climb_FN, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "racheting for the thing");
    task_create(PNU_FN, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "Air thing");
    task_create(rachet_FN, NULL, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "rachet");
}
