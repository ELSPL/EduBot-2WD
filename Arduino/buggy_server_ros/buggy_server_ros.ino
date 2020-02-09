#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <rosserial_arduino/Test.h>

// ROS NodeHandle
ros::NodeHandle nh;

//initializations (All PWM)
int mtr1_pin = 5; //left wheel <- Forward value
int in1_pin = 6; 
int mtr2_pin = 9; //right wheel
int in2_pin = 10;

int motor_left_ID = 1;
int motor_right_ID = 2;

char data[30];

// ---------------ROS MAP------------------

// Directional Commands (degree, speed)
void on_cmd_dir(const std_msgs::String& msg) {
  sprintf(data, "cmd_dir=%s",msg.data);
  nh.loginfo(data);
}

// Raw L/R motor commands (channel[1/2], speed[-1:1]) 
// Raw String Format ["C:1:S:-1.0"]
void on_cmd_raw(const std_msgs::String& msg) {
  sprintf(data, "cmd_raw=%s",msg.data);
  nh.loginfo(data);
  String cmd = msg.data;

  int channel = cmd.substring(2,3).toInt();
  float speed_sub = cmd.substring(6).toFloat();

  //sprintf(data, "channel:%d speed:%d.%d",channel, (int)speed_sub, (int)(speed_sub*10)%10);
  //nh.loginfo(data);
  set_speed(channel, speed_sub);
}

// simple string commands (left/right/forward/backward/stop)
void on_cmd_str(const std_msgs::String& msg) {
  String cmd;
  cmd = msg.data;
  sprintf(data,"cmd_str=%s",msg.data);
  nh.loginfo(data);

  if (cmd == "left") {
    set_speed(motor_left_ID, -1.0);
    set_speed(motor_right_ID, 1.0);
  }
  else if (cmd == "right") {
    set_speed(motor_left_ID, 1.0);
    set_speed(motor_right_ID, -1.0);
  }
  else if (cmd == "forward") {
    set_speed(motor_left_ID, 1.0);
    set_speed(motor_right_ID, 1.0);
  }
  else if (cmd == "backward") {
    set_speed(motor_left_ID, -1.0);
    set_speed(motor_right_ID, -1.0);
  }
  else if (cmd == "stop") {
    all_stop();
  }
  else {
    sprintf(data, "invalid cmd_str=%s", msg.data);
    nh.loginfo(data);
  }
}


ros::Subscriber<std_msgs::String> dir_sub("/jetbot_motors/cmd_dir",on_cmd_dir);
ros::Subscriber<std_msgs::String> raw_sub("/jetbot_motors/cmd_raw",on_cmd_raw);
ros::Subscriber<std_msgs::String> str_sub("/jetbot_motors/cmd_str",on_cmd_str);

void setup() {
  nh.initNode();
  nh.subscribe(dir_sub);
  nh.subscribe(raw_sub);
  nh.subscribe(str_sub);

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

// -----------LOWER LAYER MAP--------------

// Sets motor speed between [-1.0, 1.0]
void set_speed(int motor_ID, float value) {
  int max_pwm = 255;
  int speed_v = int(min(max(abs(value * max_pwm), 0), max_pwm));
  int in=0;
  int mtr=0;

//  sprintf(data, "speed/_v: %d", speed_v);
//  nh.loginfo(data);/

  if (motor_ID == 1) {
    in = in1_pin;
    mtr = mtr1_pin;
  }
  else if (motor_ID == 2) {
    in = in2_pin;
    mtr = mtr2_pin;
  }
  else {
    nh.loginfo("Wrong motor_ID");
  }

  if (value > 0) {
    // FORWARD
    analogWrite(in, 0);
    analogWrite(mtr, speed_v);
  }
  else {
    // BACKWARD
    analogWrite(in, speed_v);
    analogWrite(mtr, 0);
  }
}

// Stops all motors
void all_stop() {
  analogWrite(mtr1_pin, 0);
  analogWrite(mtr2_pin, 0);  
  analogWrite(in1_pin, 0);
  analogWrite(in2_pin, 0);
}

void loop() {
  nh.spinOnce();
  delay(50); //in ms
}
