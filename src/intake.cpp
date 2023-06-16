#include "main.h"

pros::MotorGroup intake_({15,-16});

void intake() {
    if (master.get_digital(DIGITAL_R1)) {
        intake_.move(-127);
    } else if (master.get_digital(DIGITAL_R2)) {
        intake_.move(127);
    } else { intake_.brake(); }
}