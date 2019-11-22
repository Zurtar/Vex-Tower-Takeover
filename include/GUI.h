#include "vex.h"
#include <vector>
using namespace std;

enum STATE { MAIN_MENU, AUTO_SELECT, RUNNING };
class Circle {

public:
  Circle(int dx_, int dy_, int r_, STATE triggerState_);
  int getDX();
  int getDY();
  int getRadius();
  STATE getTriggerState();

  void setDX(int dx_);
  void setDY(int dy_);
  void setRadius(int r_);
  void getTriggerState(STATE triggerState_);
};

class GUI {
  static void displayMainMenu();

  static void displayAutoSelect();
  static void displayRunning();
  static bool isCirclePressed(Circle bound, int pX, int pY);

public:
  static void updateScreen();

  static void screenPressed();
};