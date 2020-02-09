#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <rosserial_arduino/Test.h>

ros::NodeHandle  nh;


//initializations
int mtr1_pin = 5; //left wheel
int in1_pin = 6; 
int mtr2_pin = 9; //right wheel
int in2_pin = 10;

int val = 0;

int current_gear = 0;
int const_gear_diff = 62;


//functions
//set velocity
void set_vel(const std_msgs::Float64& vel_msg){
  switch (int(vel_msg.data)){
    case 2:
      nh.loginfo("Forward velocity");
      analogWrite(mtr1_pin, current_gear*const_gear_diff);
      analogWrite(mtr2_pin, current_gear*const_gear_diff);
      break;
    case 0:
      nh.loginfo("Breaks");
      analogWrite(mtr1_pin, 62);
      analogWrite(mtr2_pin, 62);
      delay(1000);
      analogWrite(mtr1_pin, 0);
      analogWrite(mtr2_pin, 0);
      break;
    case 3:
      nh.loginfo("Right turn velocity");
      analogWrite(mtr2_pin, 0.5*current_gear*const_gear_diff);
      analogWrite(mtr1_pin, current_gear*const_gear_diff);
      break;
    case 1:
      nh.loginfo("Left turn velocity");
      analogWrite(mtr2_pin, current_gear*const_gear_diff);
      analogWrite(mtr1_pin, 0.5*current_gear*const_gear_diff);
      break;
  }
}
//setgear

void set_gear(const std_msgs::Float64& gear_msg){
  switch (int(gear_msg.data)){
    case 1:
      nh.loginfo("First gear");
      current_gear = 1;
      break;
    case 2:
      nh.loginfo("Second gear");
      current_gear = 2;
      break;
    case 3:
      nh.loginfo("Third gear");
      current_gear = 3;
      break;
    case 4:
      nh.loginfo("Fourth gear");
      current_gear = 4;
      break;
  }
}

ros::Subscriber<std_msgs::Float64> vel_sub("/bot/cmd_vel",set_vel);
ros::Subscriber<std_msgs::Float64> gear_sub("/bot/cmd_gear",set_gear);

void setup(){
  nh.initNode();
  nh.subscribe(vel_sub);
  nh.subscribe(gear_sub);

  //pin setups
  pinMode(in1_pin, OUTPUT);
  pinMode(mtr1_pin, OUTPUT);
  pinMode(in2_pin, OUTPUT);
  pinMode(mtr2_pin, OUTPUT);
  
  analogWrite(in1_pin, 0);
  analogWrite(mtr1_pin, 0);
  analogWrite(in2_pin, 0);
  analogWrite(mtr2_pin, 0);
  
}

void loop(){
  nh.spinOnce();
  delay(500);
}
