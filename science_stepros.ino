#include <AccelStepper.h>
#include "ros.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Int64MultiArray.h"

#define ARRAY_SIZE 12
#define STEP_MAX_SPEED 1000

int step1=5, step2, step3, step4;
int dir1=26, dir2, dir3, dir4;

AccelStepper stepper1(1, step1, dir1);
AccelStepper stepper2(1, step2, dir2);
AccelStepper stepper3(1, step3, dir3);
AccelStepper stepper4(1, step4, dir4);

std_msgs::Float64MultiArray control_array;
ros::Publisher controlPub("controlTopic", &control_array);

void scienceCallback(const std_msgs::Float64MultiArray &science_joystick_multiarray);
ros::NodeHandle nh;
ros::Subscriber <std_msgs::Float64MultiArray> science_joystcik_subs("science_joystick", &scienceCallback);

int step_speed=0;

void setup() {
  nh.initNode();
  nh.subscribe(science_joystcik_subs);
  nh.advertise(controlPub);
  
  stepper1.setMaxSpeed(STEP_MAX_SPEED);
  stepper2.setMaxSpeed(STEP_MAX_SPEED);
  stepper3.setMaxSpeed(STEP_MAX_SPEED);
  stepper4.setMaxSpeed(STEP_MAX_SPEED);

  control_array.data=(float *)malloc(sizeof(uint64_t)*1);  
  control_array.data_length=1;

}

void loop() {
  nh.spinOnce();
  if (science_joystick_multiarray.data[4]=1){
    stepper1.setSpeed(step_speed);
    stepper2.setSpeed(0);
    stepper3.setSpeed(0);
    stepper4.setSpeed(0);
  }else if(science_joystick_multiarray.data[5]=1){
    stepper1.setSpeed(0);
    stepper2.setSpeed(step_speed);
    stepper3.setSpeed(0);
    stepper4.setSpeed(0);
  }else if(science_joystick_multiarray.data[6]=1){
    stepper1.setSpeed(0);
    stepper2.setSpeed(0);
    stepper3.setSpeed(step_speed);
    stepper4.setSpeed(0);
  }else{
    stepper1.setSpeed(0);
    stepper2.setSpeed(0);
    stepper3.setSpeed(0);
    stepper4.setSpeed(step_speed);
  }
  //delay(2);
  stepper1.runSpeed();
  stepper2.runSpeed();
  stepper3.runSpeed();
  stepper4.runSpeed();
  }

void scienceCallback(const std_msgs::Float64MultiArray &science_joystick_multiarray){
  step_speed = science_joystick_multiarray.data[0]*900;
  control_array.data[0]=step_speed;
  controlPub.publish(&control_array);
}
