#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

ros::NodeHandle nh;


void toggle_led(const std_msgs::String& toggle_msg){
  if(toggle_msg.data == "1")
  {
   digitalWrite(13, HIGH);
  }
  else if(toggle_msg.data == "2")
  {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
  
}
ros::Subscriber<std_msgs::String> sub("toggle_led",toggle_led);


void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(sub);
  pinMode(13, OUTPUT);

}

void loop()
{
  nh.spinOnce();
  delay(500);
}
