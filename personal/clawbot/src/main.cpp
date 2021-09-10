#include "../include/main.h"


std::int32_t motor_move ( const std::int8_t voltage );
std::int32_t std::pros::Motor:: ( const int32_t velocity );
std::int32_t std::pros::Controller::get_digital (pros::controller_digital_e_t button );
std::int32_t std::pros::Controller::get_analog ( pros::controller_analog_e_t channel );

/*
 * Runs initialization code. This occurs as soon as the program is started.
 */
void initialize() {}

/*
 * Runs while the robot is in the disabled state
 */
void disabled() {}

/*
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch.
 */
void competition_initialize() {}

/*
 * Runs the user autonomous code
 */
void autonomous() {}

/*
 * Runs the operator control code.
 */
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10
#define ARM_PORT 8
#define CLAW_PORT 3

#define LEFT_BUMPER_PORT 'a'
#define RIGHT_BUMPER_PORT 'b'

void opcontrol()
{
  std::pros::Motor left_wheels (LEFT_WHEELS_PORT);
  std::pros::Motor right_wheels (RIGHT_WHEELS_PORT, true);
  std::pros::Motor arm (ARM_PORT, MOTOR_GEARSET_36); // The arm motor has the 100rpm (red) gearset
  std::pros::Motor claw (CLAW_PORT, MOTOR_GEARSET_36);

  std::pros::ADIDigitalIn left_bumper (LEFT_BUMPER_PORT);
  std::pros::ADIDigitalIn right_bumper (RIGHT_BUMPER_PORT);

  std::pros::Controller master (CONTROLLER_MASTER);

  while (true) {
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    int left = power + turn;
    int right = power - turn;

    if (left_bumper.get_value() || right_bumper.get_value()) {
      // One of the bump switches is currently pressed
      if (left < 0) {
        left = 0;
      }
      if (right < 0) {
        right = 0;
      }
    }
    left_wheels.move(left);
    right_wheels.move(right);

    if (master.get_digital(DIGITAL_R1)) {
      arm.move_velocity(100); // This is 100 because it's a 100rpm motor
    }
    else if (master.get_digital(DIGITAL_R2)) {
      arm.move_velocity(-100);
    }
    else {
      arm.move_velocity(0);
    }

    if (master.get_digital(DIGITAL_L1)) {
      claw.move_velocity(100);
    }
    else if (master.get_digital(DIGITAL_L2)) {
      claw.move_velocity(-100);
    }
    else {
      claw.move_velocity(0);
    }

    pros::delay(2);
  }
}
