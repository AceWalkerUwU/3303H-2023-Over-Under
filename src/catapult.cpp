#include "main.h"

pros::Motor cata_1(11, MOTOR_GEARSET_06, true);
pros::Motor cata_2(20, MOTOR_GEARSET_06, false);
pros::Motor_Group CATAPULT({cata_1, cata_2});
// 290, 18-16

pros::Rotation rotSensor(17);

bool rotSensorReset = false;

bool loaded = false;

bool fire = false;

void catapult() {
    if (!rotSensorReset) {
        rotSensor.reset();
        rotSensorReset = true;
        CATAPULT.set_brake_modes(MOTOR_BRAKE_HOLD);
    }

    if ((abs(rotSensor.get_angle()/100-290) > 7) || fire) {
        CATAPULT.move(65);
        loaded = false;

        if ((abs(rotSensor.get_angle()/100-360) < 5) || abs(rotSensor.get_angle()/100) < 5) {
            fire = false;
        }
    } else {
        CATAPULT.brake();
        loaded = true;
    }

    if (master.get_digital_new_press(DIGITAL_A) && loaded) {
        fire = true;
    }

    print_to_screen(to_string(rotSensor.get_angle()/100));
}