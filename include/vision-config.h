/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature GREEN_CUBE = vex::vision::signature (1, -8705, -6553, -7629, -5141, -3505, -4323, 5.1, 0);
vex::vision::signature ORANGE_CUBE = vex::vision::signature (2, 8673, 10649, 9661, -3423, -2813, -3118, 3.6, 0);
vex::vision::signature PURPLE_CUBE = vex::vision::signature (3, -1, 1395, 697, 9691, 12029, 10860, 3.2, 0);
vex::vision::signature SHARPIE = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision = vex::vision (vex::PORT9, 65, GREEN_CUBE, ORANGE_CUBE, PURPLE_CUBE, SHARPIE, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/