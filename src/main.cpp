// To complete the VEXcode V5 Text project upgrade process, please follow the
// steps below.
//
// 1. You can use the Robot Configuration window to recreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
//
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window.
//
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "vision-config.h"

using namespace vex;

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*    Module:       main.cpp    F */
/*    Author:       VEX */
/*    Created:      Thu Sep 26 2019 */
/*    Description:  Competition Template */
/* */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// rightWheelMotorB     motor         1
// rightWheelMotorD     motor         2
// leftWheelMotorA      motor         3
// leftWheelMotorC      motor         4
// leftIntakeMotor      motor         5
// rightIntakeMotor     motor         6
// armMotor             motor         7
// pistonMotor          motor         8
// Controller          controller
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "ControlScheme.cpp"
#include "ObjectTracking.cpp"

#include <vector>

distanceUnits cm = distanceUnits::cm;

// A global instance of competition
competition Competition;

// updateVision event for vision
event ObjectTracking = event();

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  // setting up sensor
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

void usercontrol(void) {
  // User control code here, inside the loop
  Brain.Screen.render(true);

  while (1) {
    //~~~ Pressed Functions ~~~

    // left 1,2 3
    Controller.ButtonL1.pressed(ControllerInteraction::bL1Pressed);
    Controller.ButtonL2.pressed(ControllerInteraction::bL2Pressed);
    Controller.ButtonRight.pressed(ControllerInteraction::bL3Pressed);

    // right 1,23
    Controller.ButtonR1.pressed(ControllerInteraction::bR1Pressed);
    Controller.ButtonR2.pressed(ControllerInteraction::bR2Pressed);
    Controller.ButtonY.pressed(ControllerInteraction::bR3Pressed);

    //
    Controller.ButtonDown.pressed(ControllerInteraction::cLPressed);
    Controller.ButtonB.pressed(ControllerInteraction::cRPressed);

    // left 1,2 released
    Controller.ButtonL1.released(ControllerInteraction::bLReleased);
    Controller.ButtonL2.released(ControllerInteraction::bLReleased);

    // right 1,2 released
    Controller.ButtonR1.released(ControllerInteraction::bRReleased);
    Controller.ButtonR2.released(ControllerInteraction::bRReleased);

    Controller.ButtonRight.released(ControllerInteraction::bL3Released);
    Controller.ButtonY.released(ControllerInteraction::bR3Released);

    // ~~~ JoyStick Controllers ~~~
    // TL left,right
    Controller.Axis3.changed(ControllerInteraction::leftJoystickChange);

    // TR left,right
    Controller.Axis2.changed(ControllerInteraction::rightJoystickChange);

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

static void updateVisionSensor() {
  // setting up screen
  Brain.Screen.setFont(mono40);

  // fetch the list of objects that match our signature
  Vision.takeSnapshot(GREEN_CUBE);
  Brain.Screen.printAt(0, 50, true, "Updated Screen.");
}

static void adjustTurn() {
  /*VexVisionObject object = Vision.largestObject;

  if (object.originX < 76) {
    Brain.Screen.printAt(0, 150, true, "%d", object.originX);
    // leftMotors.spinFor(fwd, leftMotors.rotation(deg) + 5, deg, 20,
    //                 velocityUnits::pct, false);
    leftMotors.setPosition(leftMotors.rotation(deg) + 30, deg);
    return false;
  }

  if (object.originX > 84) {
    Brain.Screen.printAt(1, 150, true, "%d", object.originX);
    // rightMotors.spinFor(fwd, rightMotors.rotation(deg) + 5, deg, 20,
    //                   velocityUnits::pct, false);
    rightMotors.setPosition(leftMotors.rotation(deg) + 30, deg);
    return false;
  }

  leftMotors.stop();
  rightMotors.stop();
  return true;*/
}

static bool adjustDistance() {
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(3, black); // sd
  Brain.Screen.setCursor(3, 1);
  VexVisionObject object = Vision.largestObject;

  if (object.width < 158 || object.height < 152) {
    leftMotors.spinFor(
        fwd,
        (leftWheelMotorB.rotation(deg) + leftWheelMotorD.rotation(deg)) / 2 + 5,
        deg, 100, velocityUnits::pct, false);
    rightMotors.spinFor(
        fwd,
        (rightWheelMotorA.rotation(deg) + rightWheelMotorC.rotation(deg)) / 2 +
            5,
        deg, 100, velocityUnits::pct, false);
    return false;
  } else if (object.width > 165 || object.height < 150) {
    leftMotors.spinFor(
        reverse,
        (leftWheelMotorB.rotation(deg) + leftWheelMotorD.rotation(deg)) / 2 + 5,
        deg, 100, velocityUnits::pct, false);
    rightMotors.spinFor(
        reverse,
        (rightWheelMotorA.rotation(deg) + rightWheelMotorC.rotation(deg)) / 2 +
            5,
        deg, 100, velocityUnits::pct, false);
    return false;
  }
  printf("test");
  return true;
}

static void intiSensor() {
  // setting up sensor
  Vision.setWhiteBalanceMode(vision::whiteBalanceMode::automatic);
  Vision.setMode(vision::detectionMode::objectDetect);
  Vision.setWifiMode(vision::wifiMode::off);
  Vision.setLedMode(vision::ledMode::automatic);
  leftWheelMotorB.setBrake(coast);
  leftWheelMotorD.setBrake(coast);
  rightWheelMotorA.setBrake(coast);
  rightWheelMotorC.setBrake(coast);
}

void callBack() {
  updateVisionSensor();
  Brain.Screen.printAt(1, 100, true, "ObjectCount: %d", Vision.objectCount);
  adjustTurn();
}

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // pickup first 4
  /* ControllerInteraction::driveForDistance(
       fwd, 38.5, inches, 25, velocityUnits::pct, false, leftMotors);

   ControllerInteraction::driveForDistance(
       fwd, 38.5, inches, 25, velocityUnits::pct, true, rightMotors);

   // turn to face wall
   ControllerInteraction::driveForDistance(
       reverse, 4, inches, 25, velocityUnits::pct, false, leftMotors);
   ControllerInteraction::driveForDistance(
       fwd, 4, inches, 25, velocityUnits::pct, true, rightMotors);


 //reverse
   ControllerInteraction::driveForDistance(
       reverse, 38, inches, 25, velocityUnits::pct, false, leftMotors);

   ControllerInteraction::driveForDistance(
       reverse, 38, inches, 25, velocityUnits::pct, true, rightMotors);

   // Prevent main from exiting with an infinite loop.
   */
  while (true) {
    // ObjectTracking.broadcastAndWait();
    wait(100, msec);
  }
}

/*
  TODO:
-Test values that the sensor returns we know the following
  a) all x values grabbed from object will be between 0 and 315
  b) all y values grabbed from object will be betweenn 0 and 211
  c) we have methods that can grab the width, height, angle, centerX, centerY,
      orginX and orginY. Values

    Questions:
      -Lets say we fetch the centerX value of the object.
        what does this value represent?
        is 0 the very left limit of the sensors view and 315 the right limit?
        If so is an x val of 157.5 -                            dead center?
        How precice are the values, do we need to add a range of .5 or 5?
      -What is the max range of the sensor?
      -What is the max effetive range of the sensor?
      -What is the poll rate of the sensor?
      -Correct brightness setting of the vision sensor on init see vision docs
          for details
      -Effectivness of automatic brightness setting vs manaul
      -LED interaction
      -

*/
