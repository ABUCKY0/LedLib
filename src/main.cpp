#include "main.h"
#include "LedLib/LedLib.hpp"
#include "LedLib/effects/RainbowEffect.hpp"
using namespace LedLib;
using namespace pros;
using namespace std;

LedLib::LedLib strip(14, 1, 58);
RainbowEffect rainbow;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
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
void autonomous() {}

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
void opcontrol()
{
    // while (true) {
    //     // Increment the hue value
    //     color.hue += .05; // You can adjust the increment value to change the speed of color change
    // 	if (color.hue > 255) {
    // 		color.hue = 0;
    // 	}

    // Set all LEDs to the current color
    // strip.setAll(color);

    strip.setActiveEffect(strip.addEffect(new RainbowEffect));
    while (true)
    {
        // Delay to control the speed of color change
        strip.updateEffects();
        delay(10); 
    }
}