#include "GUI.h"

// setting up our constructor
int dx, dy, r;
static STATE currentState;
static STATE triggerState;

/*
@param dx_ = center_x of the circle
@param dy_ = center_y of the circle
@param r_ = radius of the circle
@param triggerState = when the circle/bound is pressed the currentState of GUI
    will switch to this value
*/

/*
TODO:
  -Convert Circle -> Button
    -Add a string x,y postion arg
    -Add a string text arg
    -Add a buttonName to output ButtonName was selected debug feature that
will be removed later

  way more then that just all I can think of its 11pm and I wrote this all in
one day without any testing so you know bugs
*/
Circle::Circle(int dx_, int dy_, int r_, STATE triggerState_) {
  dx = dx_;
  dy = dy_;
  r = r_;
  triggerState = triggerState_;
}

// getter functions
int Circle::getDX() { return dx; }
int Circle::getDY() { return dy; }
int Circle::getRadius() { return r; }
STATE Circle::getTriggerState() { return triggerState; }

// setter function
void Circle::setDX(int dx_) { dx = dx_; }
void Circle::setDY(int dy_) { dy = dy_; }
void Circle::setRadius(int r_) { r = r_; }
void Circle::getTriggerState(STATE triggerState_) {
  triggerState = triggerState_;
}

// i did math to get these values it should look peRfeCTo or trash
// ¯\_(ツ)_/¯
vector<Circle> menuBounds = {
    Circle(119, 120, 112, RUNNING),    // start circle
    Circle(361, 120, 112, AUTO_SELECT) // auto select circle
};

vector<Circle> autoBounds = {
    Circle(63, 120, 56, MAIN_MENU),  // auto 1 circle
    Circle(181, 120, 56, MAIN_MENU), // auto 2 circle
    Circle(299, 120, 56, MAIN_MENU), // auto 3 circle
    Circle(417, 120, 56, MAIN_MENU)  // auto 4 circle
};

// placeholder ***
vector<Circle> runningBounds = {};

// god this is ugly

void GUI::displayMainMenu() {
  for (Circle circle : menuBounds) {
    Brain.Screen.drawCircle(circle.getDX(), circle.getDY(), circle.getRadius());
  }

  // VALUES ARE PLACEHOLDERS MOVE TO ENHCANCED FOR LOOP AFTER
  Brain.Screen.printAt(20, 110, true, "Start");
  Brain.Screen.printAt(270, 110, true, "Auto Select");

  currentState = MAIN_MENU;
}

void GUI::displayAutoSelect() {
  for (Circle circle : autoBounds) {
    // Drawing circle bounds
    Brain.Screen.drawCircle(circle.getDX(), circle.getDY(), circle.getRadius());
  }

  // VALUES ARE PLACEHOLDERS MOVE TO ENHCANCED FOR LOOP AFTER
  Brain.Screen.printAt(20, 110, true, "Start");
  Brain.Screen.printAt(270, 110, true, "Auto Select");
  Brain.Screen.printAt(20, 110, true, "Start");
  Brain.Screen.printAt(270, 110, true, "Auto Select");

  currentState = AUTO_SELECT;
  Controller.Screen.print(currentState);
}

// placeholder
void GUI::displayRunning() {
  for (Circle circle : runningBounds) {
    Brain.Screen.drawCircle(circle.getDX(), circle.getDY(), circle.getRadius());
  }

  for (int i = 0; i < runningBounds.size(); i++) {
    Circle circle = runningBounds.at(i);
    Brain.Screen.drawCircle(circle.getDX(), circle.getDY(), circle.getRadius());
  }
}

// https://stackoverflow.com/questions/481144/equation-for-testing-if-a-point-is-inside-a-circle#481150

void GUI::updateScreen() {
  /*see screen pressed so this makes sense
  thats right folks I am using a function with a switch statment to call a
   * function with the exact same switch statement but with a different
   * operation within it. */

  switch (currentState) {
  case MAIN_MENU:
    displayMainMenu();
    break;
  case AUTO_SELECT:
    displayAutoSelect();
    break;
  case RUNNING:
    displayRunning();
    break;
  }
}

void checkBound(vector<Circle> boundList, int pX, int pY) {
  for (Circle bound : boundList) {
    if (pow((pX - bound.getDX()), 2) + pow((pY - bound.getDY()), 2) <
        pow(r, 2)) {
      currentState = bound.getTriggerState();
      return;
    }
  }
}

/*ok so here is the thing I fucking hate this right now. Let me clarify the
 * function is just ugly. a return and break function come on. Yes they server
 * a purpose but there has to be and is a better way to do this but its 11:30
 * and I am tired. see updateScreen for the other issue with this\

  We calll the update screen function which has this same switch statement
 because we dont know what the state is going to change to once a button is
 pressed we know it will be that buttons triggerState but we dont know what
 that state is so we cannont display the correct ui. We to call another
 function and check the current state their we could have a chain of ifs in
 teh switch but I would hang myself first this is ugly already

 end rant

 oh also we do not need to call it in every case we can just call it after the
 switch but we have to change up the return and breaks. The return is to
 prevent wasted resources looping through the rest of the array again a
 miiscule impact but good practice


void GUI::screenPressed() {
  switch (currentState) {
  case MAIN_MENU:
    for (Circle bound : menuBounds) {
      if (isCirclePressed(bound)) {
        currentState = bound.getTriggerState();
        updateScreen();
        return;
      }
    }
    break;

  case AUTO_SELECT:
    for (Circle bound : autoBounds) {
      if (isCirclePressed(bound)) {
        currentState = bound.getTriggerState();
        updateScreen();
        return;
      }
    }
    break;

  case RUNNING:
    for (Circle bound : runningBounds) {
      if (isCirclePressed(bound)) {
        currentState = bound.getTriggerState();
        updateScreen();
        return;
      }
    }
    break;
  }
}
*/
