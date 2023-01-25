#include "main.h"
pros::ADIDigitalOut endgameRight(4);
pros::ADIDigitalOut endgameLeft(3);

void endgameShoot(){
    endgameRight.set_value(true);
    endgameLeft.set_value(true);
}

void endgameShootRight(){
    endgameRight.set_value(true);

}

void endgameShootLeft(){
    endgameLeft.set_value(true);
}

void endgameShootButton1(){
    if(master.get_digital_new_press(DIGITAL_RIGHT)){
        endgameShootLeft();
  }
    if(master.get_digital_new_press(DIGITAL_Y)){
        endgameShootRight();
  }

}