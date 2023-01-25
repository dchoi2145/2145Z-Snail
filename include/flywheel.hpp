#pragma once
extern pros::Motor flywheel;
void flywheelButton();
void flywheelRPM(int speed);
void flywheelPID(double target);
void shoot(int target, int shots);
void shootFast(int target, int shots);
double test();
void set_flywheel_speed(int speed);