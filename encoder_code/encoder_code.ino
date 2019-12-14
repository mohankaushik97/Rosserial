#include <ros.h>
#include <geometry_msgs/Pose2D.h>

ros::NodeHandle node;
geometry_msgs::Pose2D odom;
ros::Publisher odom_pub("odom", &odom);

int clicks = 0;
float distance_per_revolution;
float distance_per_click;
int wheel_base = 15;
float left_distance;
float right_distance;
int left_clicks = 0;
int right_clicks = 0;

int encoderA;
int encoderB;

void setup() {
  //variables
  Serial.begin(57600);
  node.initNode();
  node.advertise(odom_pub);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

}


void loop() {
  clicks = left_clicks;
  left_distance, left_clicks = distance_of_wheel(2, 4);
  Serial.print("left_distance =");
  Serial.println(left_clicks);
  clicks = right_clicks;
  right_distance, right_clicks = distance_of_wheel(3, 5);
  Serial.print("right_distance =");
  Serial.println(right_clicks);
  odom.x = (left_distance + right_distance) / 2;
  odom.theta = (left_distance - right_distance) / wheel_base;
  /*
    Serial.print("x = ");
    Serial.print(odom.x);
    Serial.print("     theta =");
    Serial.println(odom.theta);
  */
  odom_pub.publish(&odom);
  node.spinOnce();
  delay(500);
}

float distance_of_wheel(int eA, int eB) {

  encoderA = eA;
  encoderB = eB;
  float distance_per_revolution = (2 * PI * 5);
  //clicks = 0;
  float distance_per_click = distance_per_revolution / 900;
  attachInterrupt(digitalPinToInterrupt(encoderA), count, RISING);
  float distance = distance_per_click * clicks;
  //Serial.print("distance");
  //Serial.println(distance);
  return distance, clicks;
}

int count() {
  if (digitalRead(encoderB) == LOW) {
    clicks ++;
  }
  else {
    clicks --;
  }
  return clicks;
}
