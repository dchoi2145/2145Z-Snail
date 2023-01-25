#include "main.h"
pros::Motor flywheel(12, MOTOR_GEARSET_06, false);

void flywheelRPM(int speed){
  flywheel.move_velocity(speed);
}


void flywheelPID(double target) {
  // Constants
  double kP = 0.2;//.1
  double kV = .0354;
  double threshold = 200;

  double error = 0;
  double prevError = 0;

  double output = 0;

  //reset sensors


  while (true) {

    // Proportional
    error = target - flywheel.get_actual_velocity()*6;

    // Set speed of flywheel
    if (error > threshold){
      output = 127;
    }
    else if (error < -threshold){
      output = 0;
    }
    else{
      output = (kV * target) + (kP * error) ;
    }

    // Sets the speed of the flywheel
    
    if(output > 127){
      output = 127;
    }
    else if(output < 0){
      output = 0; 
    }

    flywheel.move(output);

   //printf("flywheel: %f", flywheel.get_actual_velocity()*6-target);
   //printf("\n");

    prevError = error;
    
    pros::delay(10);

  }
  
}


/*void flywheelPID(double target) {
  // Constants
  double kP = 0.3;//.1
  double kI = 0;
  double kD = 0;
  double kV = .0354;

  double error = 0;
  double errorInertial = 0;
  double totalError = 0;
  double prevError = 0;

  double derivative;


  //reset sensors


  while (true) {

    // Proportional
    error = target - flywheel.get_actual_velocity()*6;

    // Integral
    totalError += error;

    // Derivative
    derivative = error - prevError;

    // Set speed of flywhell
    double motorPower = (kP * error) + (kI * totalError) + (kD * derivative);

    // Sets the speed of the flywheel
    
    if(motorPower > 127){
      motorPower = 127;
    }
    else if(motorPower < 0){
      motorPower = 0; 
    }

    flywheel.move(target*kV + motorPower);

    printf("flywheel: %f", flywheel.get_actual_velocity()*6);
    printf("\n");

    prevError = error;
    
    pros::delay(10);

  }
  
}*/

void shoot(int target, int shots){
    int counter = 0;
    while(counter < shots){
  
        if(flywheel.get_actual_velocity()*6 > (target - 30)){
            printf("flywheel: %f", flywheel.get_actual_velocity()*6);
    printf("\n");
            pros::delay(600);
            indexerShoot();
            pros::delay(300);
            indexerRetract();
            counter++;
        }
        pros::delay(10);
    }
}
void shootFast(int target, int shots){
    int counter = 0;
    while(counter < shots){
  
        if(flywheel.get_actual_velocity()*6 > (target - 60)){
            printf("flywheel: %f", flywheel.get_actual_velocity()*6);
    printf("\n");
            pros::delay(300);
            indexerShoot();
            pros::delay(600);
            indexerRetract();
            counter++;
        }
        pros::delay(10);
    }
}

double test(){
  while(true){
    printf("flywheel: %f", flywheel.get_actual_velocity()*6);
    printf("\n");
    flywheel.move(40);
    pros::delay(10);
  }
}

void set_flywheel_speed(int speed) {
  static std::unique_ptr<pros::Task> pidTask {};
  if (pidTask != nullptr) { pidTask->remove(); }
  pidTask = (speed == -1) ? nullptr : std::make_unique<pros::Task>([=]{ flywheelPID(speed); });
}