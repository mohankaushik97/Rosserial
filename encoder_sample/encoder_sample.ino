#include <ros.h>
#include <geometry_msgs/Pose.h>

ros::NodeHandle node;
geometry_msgs::Pose odom;
ros::Publisher odom_pub("/odom", &odom);

volatile int clicks = 0;
int encoderA = 2;
int encoderB = 3;
float distance_per_revolution = (2*3.14*2.5);
float distance_per_click = distance_per_revolution / 900;
int wheel_base = 15;
float left_distance;
float right_distance;

void setup(){
       Serial.begin(19200);
       counter = 0;
}

void loop(){
       attachInterrupt(digitalPinToInterrupt(2), count, RISING);
       if (abs(counter) < 905*2){
        delay(10);
        distance = distance_per_click*counter;        
        Serial.print("distance = ");
        Serial.print(distance);
        Serial.print("          Clicks =");
        Serial.print(counter);
        Serial.print("\n");
       }
}

void count(){
  //if (abs(counter) < 905*2){
       if (digitalRead(encoderB) == LOW){
        counter ++;
       }
       else{
        counter --;
       }
   //   }
  //else{
    //digitalWrite(5,LOW);
   //}
}

void endloop(){
}

#define 
