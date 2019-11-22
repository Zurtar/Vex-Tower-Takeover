#include "vex.h"
// this comment is here because they auto format formats include lines by
// alphabetical order which fucks up some dependancies
#include <iostream>

class ControllerInteraction {

public:
  static void leftJoystickChange() {
    leftMotors.spin(fwd, Controller.Axis3.position(pct), pct);
  }

  static void rightJoystickChange() {
    rightMotors.spin(fwd, Controller.Axis2.position(pct), pct);
  }

  static void bL1Pressed() {
    // Intake Motor fwd 50% power
    intakeMotors.spin(fwd, 50, pct);
  }

  static void bL2Pressed() {
    // Intake Motor rev 50% power
    pistonMotor.spin(reverse, 100, pct);
  }

  static void bL3Pressed() {}

  static void cLPressed() {
    // Arm Motor Reverse 50% power
    armMotors.spin(reverse, 50, pct);
  }

  /* empty functions will be called later once the drive team figures out their
   * layout*/
  static void bR1Pressed() { intakeMotors.spin(reverse, 50, pct); }

  static void bR2Pressed() { pistonMotor.spin(fwd, 100, pct); }

  static void bR3Pressed() {}

  static void cRPressed() {
    // Arm Motor Forward 50% power
    armMotors.spin(fwd, 50, pct);
  }

  // Released Functions
  static void bLReleased() {
    // Stopping Left Intake Motor
    intakeMotors.stop();
  }

  static void bL3Released() {
    // Stopping Arm Motor
    armMotors.stop();
  }

  static void cLReleased() { armMotors.stop(); }

  // right bumper release
  static void bRReleased() { intakeMotors.stop(); }

  static void bR3Released() {
    // Stopping  Piston Motor
    pistonMotor.stop();
  }

  static void driveForDistance(distanceUnits distanceUnit, double distanceVal,
                               velocityUnits velcUnit, double velVal,
                               motor_group motorGroup) {
    if (distanceUnit == distanceUnits::cm) {
      distanceVal = distanceVal / 2.54;
    } else if (distanceUnit == mm) {
      distanceVal = (distanceVal * 10) / 2.54;
    }

    double inchesPerDegree = (3.14159 * 3.25) / 360;
    distanceVal = distanceVal / inchesPerDegree;

    motorGroup.rotateTo(distanceVal, deg, velVal, velcUnit, false);
  }
};