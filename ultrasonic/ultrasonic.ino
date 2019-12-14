#include <ros.h>
#include <sensor_msgs/Range.h>
//#include <sensor_msgs/LaserScan.h>
#include <Servo.h>

Servo myservo;
ros::NodeHandle node;
//sensor_msgs::LaserScan scan_msg;
sensor_msgs::Range range_msg;
//ros::Publisher scan_pub("/LaserScan", &scan_msg);
ros::Publisher range_pub("/ultrasonic", &range_msg);

//define constants
const int trigPin = 2;
const int echoPin = 2;
const int maxD = 200;

// define variables
float duration;
float distance;
int count = 0;
int pos = 0;

void setup() {
  node.initNode();
  node.advertise(range_pub);
  myservo.attach(4);
  Serial.begin(57600);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 9) {
    myservo.write(pos);
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    range_msg.range = char(distance);
    range_pub.publish(&range_msg);
    Serial.print("Distance= ");
    Serial.print(pos);
    Serial.println(" cm");
    delay(100);
  }
  node.spinOnce();
}
