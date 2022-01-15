#include "main.h"
#include "pros/rtos.hpp"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	pros::Motor bleft_mtr(10);
	pros::Motor bright_mtr(1);
	pros::Motor fleft_mtr(20);
	pros::Motor fright_mtr(11);
	pros::Motor llift(6);
	pros::Motor rlift(5);
	pros::Motor BackLift(15);
	BackLift = 100;
	pros::delay(500);
	BackLift = 0;
	bleft_mtr = 100;
	fleft_mtr = 100;
	bright_mtr = -100;
	fright_mtr = -100;
	pros::delay(1000);
	bleft_mtr = 0;
	fleft_mtr = 0;
	bright_mtr = 0;
	fright_mtr = 0;
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::Motor bleft_mtr(10);
	pros::Motor bright_mtr(1);
	pros::Motor fleft_mtr(20);
	pros::Motor fright_mtr(11);
	pros::Motor llift(6);
	pros::Motor rlift(5);
  pros::Motor Ringlift(7);
	pros::Motor BackLift(15);
	BackLift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	llift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	rlift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	while (true) {
		pros::lcd::print(0, "%d %d", master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_Y));
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = -master.get_analog(ANALOG_RIGHT_Y);
		int up = 75 * master.get_digital(DIGITAL_A);
		int down = 75 * master.get_digital(DIGITAL_B);
		fright_mtr = right;
		fleft_mtr = left;
		bleft_mtr = left;
		bright_mtr = right;
		if(up > 0 && down == 0) {
			llift = -up;
			rlift = up;
		}
		else if (down > 0 && up == 0){
		llift = down;
		rlift = -down;
		}
		else {llift = 0; rlift = 0;}
    if(master.get_digital(DIGITAL_R1)){
    Ringlift = -128;
    }
    else if (master.get_digital(DIGITAL_R2)){
    Ringlift = -64;
    }
		else{Ringlift = 0;}
		if(master.get_digital(DIGITAL_L1)){
			BackLift = -100;
		}
		else if (master.get_digital(DIGITAL_L2)){
			BackLift = 100;
		}
		else{BackLift = 0;}
		pros::delay(20);
	}
}
