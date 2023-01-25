#include "main.h"
pros::Motor intake(11,false);
pros::ADIDigitalOut intakePivot(7);
pros::ADIDigitalOut indexer(8);
pros::ADIDigitalOut angleChanger(2);

void indexerShoot(){
  indexer.set_value(true);
}
void indexerRetract(){
  indexer.set_value(false);
}

void angleChangerUp(){
    angleChanger.set_value(false);
}
void angleChangerDown(){
    angleChanger.set_value(true);
}

void intakeSpeed(int speed){
    intake = speed;
}

bool angleChange = false;

void angleChangeButton(){
    if(master.get_digital_new_press(DIGITAL_L2)){
        angleChange = !angleChange;
        angleChanger.set_value(angleChange);
  }
}

void intakeButton(){
  if(master.get_digital(DIGITAL_R1)){
    intake = 127;

  }
  else if(master.get_digital(DIGITAL_R2)){
    intake = -127;
  }

  else{
    intake = 0;
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  }
}
  void indexerControl(){
  if(master.get_digital(DIGITAL_L1)){
    indexerShoot();
  }
  else{
    indexerRetract();
  }
}

void intakeLower(){
  intakePivot.set_value(false);
}
void intakeLift(){
  intakePivot.set_value(true);
}
