#include "vex.h"
// this comment is here because they auto format formats include lines by
// alphabetical order which fucks up some dependancies
#include <iostream>

class ControllerInteraction {

public:
  static void leftJoystickChange() {
    leftMotors.setVelocity(Controller.Axis3.position(pct), velocityUnits::pct);
    leftMotors.spin(fwd);
  }

  static void rightJoystickChange() {
    rightMotors.setVelocity(Controller.Axis2.position(pct), velocityUnits::pct);
    rightMotors.spin(fwd);
  }

  // Intake Motor fwd 50% power
  static void bL1Pressed() {
    intakeMotors.setVelocity(100, velocityUnits::pct);
    intakeMotors.spin(fwd);
  }

  // Intake Motor rev 50% power

  static void bL2Pressed() {
    intakeMotors.setVelocity(100, velocityUnits::pct);
    intakeMotors.spin(directionType::rev);
  }
  // Arm Motor Forward

  static void bL3Pressed() {
    armMotor.setVelocity(100, pct);
    armMotor.spin(fwd);
  }

  // Arm Motor Reverse 50% power
  static void cLPressed() {
    Brain.Screen.printAt(1, 50, true, "armDownWasCalled");
    armMotor.setVelocity(100, pct);
    armMotor.spin(directionType::rev);
  }

  static void bR1Pressed() {}
  static void bR2Pressed() {}
  static void bR3Pressed() { pistonMotor.spin(fwd, 100, pct); }
  static void cRPressed() { pistonMotor.spin(fwd, 100, pct); }

  /* ~~~~ Released Functions ~~~~ */

  static void bLReleased() {
    // Stopping Left Intake Motor
    intakeMotors.stop();
  }

  static void bL3Released() {
    // Stopping Arm Motor
    armMotor.stop();
  }

  static void cLReleased() {
    // Stopping Arm Motor
    armMotor.stop();
  }

  // R1,R2 release
  static void bRReleased() { intakeMotors.stop(); }

  // Stopping  Piston Motor
  static void bR3Released() { pistonMotor.stop(); }

  static void cRReleased() { pistonMotor.stop(); }

  static void driveForDistance(directionType dir, double distanceVal,
                               double velVal, velocityUnits velcUnit, bool wait,
                               motor_group motorGroup) {
    distanceVal = distanceVal * (360 / (3.14159 * 3.25));

    motorGroup.spinFor(dir, distanceVal, deg, velVal, velcUnit, wait);
  }
};