#include <AccelStepper.h>
#include "ros.h"
#include "std_msgs/Float64MultiArray.h"
#include "std_msgs/Int64MultiArray.h"

#define ARRAY_SIZE 12
#define STEP_MAX_SPEED 1000

int step1=5, step2, step3, step4;
int dir1=26, dir2, dir3, dir4;

//bool step1_flag=false , step2_flag=false, step3_flag=false, step4_flag=false;

/*dc 1
int enA;
int in1, in2;

//dc 2
int enB;
int in3, in4;

int dc_speed=0;
int dc_speed_data; 
int dc_data1; // dc 1
int dc_data2; //dc 2
int toggle_data;

int dc1_active=0;
int dc2_active=0;
int dc_direction=0; 

int dc_direction_data; */

int step_speed=0;

//int toggle_mode=0;


//stepper pins config
AccelStepper stepper1(1, step1, dir1);
AccelStepper stepper2(1, step2, dir2);
AccelStepper stepper3(1, step3, dir3);
AccelStepper stepper4(1, step4, dir4);

std_msgs::Float64MultiArray control_array;
ros::Publisher controlPub("controlTopic", &control_array);

void scienceCallback(const std_msgs::Float64MultiArray &science_joystick_multiarray);
ros::NodeHandle nh;
ros::Subscriber <std_msgs::Float64MultiArray> science_joystcik_subs("science_joystick", &scienceCallback);



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

  /*dc pins config
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);*/


}

void loop() {
  nh.spinOnce();
  
  if (step1_flag){
    stepper1.setSpeed(step_speed);
    stepper2.setSpeed(0);
    stepper3.setSpeed(0);
    stepper4.setSpeed(0);
  }if(step2_flag){
    stepper1.setSpeed(0);
    stepper2.setSpeed(step_speed);
    stepper3.setSpeed(0);
    stepper4.setSpeed(0);
  }if(step3_flag){
    stepper1.setSpeed(0);
    stepper2.setSpeed(0);
    stepper3.setSpeed(step_speed);
    stepper4.setSpeed(0);
  }if(step4_flag){
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
  

  /*if(dc1_active==1){
    if(dc_direction=!0){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, dc_speed);
    }else{
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, dc_speed);
    }
  }
  if(dc2_active==1){
    if(dc_direction=!0){
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB, dc_speed);
    }else{
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enB, dc_speed);
    }
  }
  if(toggle_data=!0){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA, dc_speed);
      delay(50);
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(enA, dc_speed);
      delay(50);
  }*/
}

  

void scienceCallback(const std_msgs::Float64MultiArray &science_joystick_multiarray){
  step_speed = science_joystick_multiarray.data[0]*900;
  if(science_joystick_multiarray.data[4]==1){
    bool step1_flag=true;
  }if(science_joystick_multiarray.data[5]==1){
    bool step2_flag=true;
  }if(science_joystick_multiarray.data[6]==1){
    bool step3_flag=true;
  }if(science_joystick_multiarray.data[7]==1){
    bool step4_flag=true;
  }
  /*dc_speed = abs(science_joystick_multiarray.data[dc_speed_data]*255;
  dc1_active = science_joystick_multiarray.data[dc_data1];
  dc2_active = science_joystick_multiarray.data[dc_data2];
  dc_direction = science_joystick_multiarray.data[dc_direction_data];
  toggle_mode = science_joystick_multiarray.data[toggle_data];*/
  control_array.data[0]=step_speed;
  controlPub.publish(&control_array);
}
